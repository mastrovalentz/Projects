#ifndef ParticleLifetime_h
#define ParticleLifetime_h

#include <string>
#include <vector>

#include "AnalysisFramework/AnalysisSteering.h"
#include "util/include/ActiveObserver.h"

class Event;
class LifetimeFit;
class TH1F;

class ParticleLifetime: public AnalysisSteering, public ActiveObserver <Event>
{
    public:
        ParticleLifetime (const AnalysisInfo* info);
        virtual ~ParticleLifetime();

        virtual void beginJob(); //inizio esecuzione
        virtual void endJob();   //fine esecuzione
        virtual void update ( const Event& ev ); //loop sugli eventi

    private:
        //come nell'esempio uso due metodi per prevenire copie "senza avviso"
        ParticleLifetime           (const ParticleLifetime& x);
        ParticleLifetime& operator=(const ParticleLifetime& x);

        struct Particle
        {
            std::string p_name; //nome
            LifetimeFit* p_mean;   //oggetto
            TH1F* p_hist;       //grafico
        };

        std::vector <Particle*> pList; //lista strutture Particle per diverse energie
        void pCreate (const std::string& name, double min, double max,
                         double timeMin, double timeMax, double min_scan, 
                         double max_scan, double scan_step);
};

#endif