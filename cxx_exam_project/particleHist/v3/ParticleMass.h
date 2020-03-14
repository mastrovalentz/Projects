#ifndef ParticleMass_h
#define ParticleMass_h

#include "AnalysisSteering.h"
#include <string>
#include <vector>

class Event;
class MassMean;
class TH1F;

class ParticleMass: public AnalysisSteering
{
    public:
        ParticleMass (const AnalysisInfo* info);
        virtual ~ParticleMass();

        virtual void beginJob(); //inizio esecuzione
        virtual void endJob();   //fine esecuzione
        virtual void process( const Event& ev ); //loop sugli eventi

    private:
        ParticleMass           (const ParticleMass& x);
        ParticleMass& operator=(const ParticleMass& x);

        struct Particle
        {
            std::string p_name; //nome
            MassMean* p_mean;   //oggetto
            TH1F* p_hist;       //grafico
        };

        std::vector <Particle*> pList; //lista strutture Particle per diverse energie
        void pCreate (const std::string& name, float min, float max);

};

#endif