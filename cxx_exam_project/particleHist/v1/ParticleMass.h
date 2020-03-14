#ifndef ParticleMass_h
#define ParticleMass_h

#include <string>
#include <vector>

#include "AnalysisSteering.h"

class Event;
class MassMean;
class TH1F;

class ParticleMass: public AnalysisSteering
{
    public:
        ParticleMass();
        virtual ~ParticleMass();

        virtual void beginJob(); //inizio esecuzione
        virtual void endJob();   //fine esecuzione
        virtual void process( const Event& ev ); //loop sugli eventi

    private:
        //come nell'esempio uso due metodi per prevenire copie "senza avviso"
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