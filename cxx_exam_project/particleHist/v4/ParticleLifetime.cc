#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

#include "ParticleLifetime.h"
#include "Event.h"
#include "LifetimeFit.h"
#include "AnalysisFactory.h"
#include "AnalysisInfo.h"
#include "ProperTime.h"

#include "TH1F.h"
#include "TFile.h"

using namespace std;

//factory per ParticleLifetime come in Event dump
class ParticleLifetimeFactory: public AnalysisFactory::AbsFactory
{
    public:
    ParticleLifetimeFactory(): AnalysisFactory::AbsFactory ("time") {}
    virtual AnalysisSteering* create (const AnalysisInfo* info)
    {
        return new ParticleLifetime (info);
    }
};

//factory global di Particle mass
static ParticleLifetimeFactory pm;


ParticleLifetime::ParticleLifetime (const AnalysisInfo* info):
AnalysisSteering (info) {
}

ParticleLifetime::~ParticleLifetime()
{
}

// inizio esecuzione
void ParticleLifetime::beginJob()
{
    pList.reserve(10); 
    pCreate( "particle_k0", 0.495, 0.500, 10.0, 500.0);
    pCreate( "particle_L0", 1.115, 1.116, 10.0, 1000.0); //la chiamo L0 perchè sennò attaccando la stringa
                                                          //mass risulta troppo lunga (non so perchè)


    return;
}

void ParticleLifetime::endJob()
{
    // save current working area
    TDirectory* currentDir = gDirectory;
    // open histogram file
    TFile* file = new TFile (aInfo->value ("time").c_str(), "RECREATE");

    int n=pList.size(); //ciclo sugli elementi
    for (int i=0; i<n; i++)
    {
        LifetimeFit* pFit= pList[i]->p_mean; //creato puntatori a mass mean e grafico
        TH1F* hMean= pList[i]-> p_hist;

        pFit->compute(); //per ora non esegue operazioni

        hMean->Write();
    }
    file->Close(); // close file
    //delete file;// restore working area    
    currentDir->cd();
    return;
}

void ParticleLifetime::update(const Event& ev)
{
    //calcolo la massa invariante
    static ProperTime* decayment= ProperTime::instance();
    double m=decayment->decayTime(); 
    //potrei evitare questa dichiarazione ma il codice \'e piu leggibile così 

    int n=pList.size(); //loop e aggiunta degli elemnti per i decadimenti
    for (int i=0; i<n; i++) 
    {
        if (pList[i]->p_mean->add(ev)) pList[i]->p_hist->Fill(m);
    }
    //per pgni elemento della lista chiamo add, se il risultato \'e true ovvero evento
    //accettato riempio l'istogramma con il tmepo di decadimento dell'evento
    return;
}


void ParticleLifetime::pCreate(const string& name, float min, float max, double timeMin, double timeMax)
{
    const char* h_name=("time_"+name).c_str(); //nome per grafico

    Particle* mp= new Particle;
    mp-> p_name= name;
    mp-> p_mean= new LifetimeFit (timeMin, timeMax);
    mp-> p_hist= new TH1F (h_name, h_name, 30, timeMin, timeMax); //uso 30 bin e prendo i valori dal masismo al minimo
    
    pList.push_back(mp);

    return;
}