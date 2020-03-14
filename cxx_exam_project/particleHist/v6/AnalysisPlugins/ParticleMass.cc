#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

#include "AnalysisPlugins/ParticleMass.h"
#include "AnalysisFramework/Event.h"
#include "AnalysisObjects/MassMean.h"
#include "AnalysisFramework/AnalysisFactory.h"
#include "AnalysisFramework/AnalysisInfo.h"
#include "AnalysisObjects/ParticleReco.h"

#include "TH1F.h"
#include "TFile.h"

using namespace std;

//factory per ParticleMass come in Event dump
class ParticleMassFactory: public AnalysisFactory::AbsFactory
{
    public:
    ParticleMassFactory(): AnalysisFactory::AbsFactory ("plot") {}
    virtual AnalysisSteering* create (const AnalysisInfo* info)
    {
        return new ParticleMass (info);
    }
};

//factory global di Particle mass
static ParticleMassFactory pm;


ParticleMass::ParticleMass (const AnalysisInfo* info):
AnalysisSteering (info) {
}

ParticleMass::~ParticleMass()
{
}

// inizio esecuzione
void ParticleMass::beginJob()
{
    pList.reserve(10); 

    ifstream file( aInfo->value( "range" ).c_str() ); //prendo i range
    string name;
    double min_mass;
    double max_mass;
    while (file>>name>>min_mass>>max_mass) pCreate(name, min_mass, max_mass);

    return;
}

void ParticleMass::endJob()
{
    // save current working area
    TDirectory* currentDir = gDirectory;
    // open histogram file
    TFile* file = new TFile (aInfo->value ("plot").c_str(), "RECREATE");

    int n=pList.size(); //ciclo sugli elementi
    for (int i=0; i<n; i++)
    {
        MassMean* pMean= pList[i]->p_mean; //creato puntatori a mass mean e grafico
        TH1F* hMean= pList[i]-> p_hist;

        pMean->compute(); //calcolo risultati

        cout<<pMean->mMean()<<"\t"<<pMean->mRMS()<<"\t"<<pMean->nEvents()<<endl; //stampo i risultati
    
        hMean->Write();//salvo i dati sul file root
    }
    file->Close(); // close file
    delete file;// restore working area    
    currentDir->cd();
    return;
}

void ParticleMass::update(const Event& ev)
{
    //calcolo la massa invariante
    static ParticleReco* decayment= ParticleReco::instance();
    double m=decayment->invariantMass(); 
    //potrei evitare questa dichiarazione ma il codice \'e piu leggibile così 

    int n=pList.size(); //loop e aggiunta degli elemnti per le due masse
    for (int i=0; i<n; i++) 
    {
        if (pList[i]->p_mean->add(ev)==true) pList[i]->p_hist->Fill(m);
    }
    //per pgni elemento della lista chiamo add, se il risultato \'e true ovvero evento
    //accettato riempio l'istogramma con la massa invariante dell'evento
    return;
}


void ParticleMass::pCreate(const string& name, float min, float max)
{
    const char* h_name=("mass_"+name).c_str(); //nome per grafico

    Particle* mp= new Particle;
    mp-> p_name= name;
    mp-> p_mean= new MassMean (min, max);
    mp-> p_hist= new TH1F (h_name, h_name, 30, min, max); //uso 30 bin e prendo i valori dal masismo al minimo
    
    pList.push_back(mp);

    return;
}