#ifndef ParticleMass_h
#define ParticleMass_h

#include "AnalysisSteering.h"
#include <vector>

class Event;
class MassMean;

class ParticleMass: public AnalysisSteering
{
    public:
        ParticleMass();
        virtual ~ParticleMass();

        virtual void beginJob(); //inizio esecuzione
        virtual void endJob();   //fine esecuzione
        virtual void process( const Event& ev ); //loop sugli eventi

    private:
        std::vector<MassMean*> pList; //lista class MassMean per diverse energie
        //come nell'esempio uso due metodi per prevenire copie "senza avviso"
        ParticleMass           (const ParticleMass& x);
        ParticleMass& operator=(const ParticleMass& x);
};

#endif