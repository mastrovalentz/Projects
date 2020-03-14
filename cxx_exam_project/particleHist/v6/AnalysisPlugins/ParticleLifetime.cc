#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

#include "AnalysisPlugins/ParticleLifetime.h"
#include "AnalysisFramework/Event.h"
#include "AnalysisObjects/LifetimeFit.h"
#include "AnalysisFramework/AnalysisFactory.h"
#include "AnalysisFramework/AnalysisInfo.h"
#include "AnalysisObjects/ProperTime.h"

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

    ifstream file( aInfo->value("trange").c_str() );
    string name;
    double min_mass, max_mass;
    double min_time, max_time; 
    double min_scan, max_scan, step;
    while (file>>name>>min_mass>>max_mass>>min_time>>max_time>>min_scan>>max_scan>>step) 
                pCreate(name, min_mass, max_mass, min_time, max_time,  
                            min_scan, max_scan, step);
    
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

        pFit->compute(); 
        cout<<pFit->lifeTime()<<"\t"<<pFit->lifeTimeError()<<endl;

        hMean->Write();
    }
    file->Close(); // close file
    delete file;// restore working area    
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


void ParticleLifetime::pCreate(const string& name, double min_mass, double max_mass,
                               double timeMin, double timeMax, double min_scan, 
                               double max_scan, double scan_step)
{
    const char* h_name=("time_"+name).c_str(); //nome per grafico

    Particle* mp= new Particle;
    mp-> p_name= name;
    mp-> p_mean= new LifetimeFit (min_mass, max_mass, timeMin, timeMax, min_scan, max_scan, scan_step);
    mp-> p_hist= new TH1F (h_name, h_name, 30, timeMin, timeMax); //uso 30 bin e prendo i valori dal masismo al minimo
 
    pList.push_back(mp);

    return;
}