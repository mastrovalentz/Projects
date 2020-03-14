#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

#include "ParticleMass.h"
#include "Event.h"
#include "MassMean.h"
#include "AnalysisFactory.h"
#include "AnalysisInfo.h"
#include "ParticleReco.h"

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
    pCreate( "particle_k0", 0.495, 0.500);
    pCreate( "particle_L0", 1.115, 1.116); 
    //la chiamo L0 perchè sennò attaccando la string
    //mass risulta troppo lunga 

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
        hMean->Write();//scrivo sul file
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
        if (pList[i]->p_mean->add(ev)) pList[i]->p_hist->Fill(m);
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