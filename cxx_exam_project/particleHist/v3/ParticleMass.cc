#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

#include "ParticleMass.h"
#include "Event.h"
#include "MassMean.h"
#include "AnalysisFactory.h"
#include "AnalysisInfo.h"

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

double mass(const Event& ev); //serve per riempire gli istogrammi

ParticleMass::ParticleMass (const AnalysisInfo* info):
AnalysisSteering (info) {
}

ParticleMass::~ParticleMass()
{
}

// inizio esecuzione
void ParticleMass::beginJob()
{
    pList.reserve(10);  //riservo memoria
    pCreate( "particle_k0", 0.495, 0.500); //creo le liste delle due particelle
    pCreate( "particle_Lambda0", 1.115, 1.116);

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

        //stampo i risultati
        cout<<pMean->mMean()<<"\t"<<pMean->mRMS()<<"\t"<<pMean->nEvents()<<endl;      
        hMean->Write(); //scrivo sul file root
    }
    file->Close(); // close file
    delete file;// restore working area    
    currentDir->cd();
    return;
}

void ParticleMass::process(const Event& ev)
{
    int n=pList.size(); //loop e aggiunta degli elemnti per le due masse
    for (int i=0; i<n; i++) 
    {
        if (pList[i]->p_mean->add(ev)) pList[i]->p_hist->Fill(mass(ev));
    }
    //per pgni elemento della lista chiamo add, se il risultato \'e true ovvero evento
    //accettato riempio l'istogramma con la massa invariante dell'evento
}


void ParticleMass::pCreate(const string& name, float min, float max)
{
    const char* h_name=name.c_str(); //nome per grafico

    Particle* mp= new Particle;
    mp-> p_name= name;
    mp-> p_mean= new MassMean (min, max);
    //creo istogramma con valori tra massimo e minimo di accettazione
    mp-> p_hist= new TH1F (h_name, h_name, 30, min, max); 
    
    pList.push_back(mp);

    return;
}