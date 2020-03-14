#include "EventDump.h"
#include "Event.h"
#include "AnalysisFactory.h"
#include "util/include/ActiveObserver.h"

#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;


//concrete Factory
class EventDumpFactory: public AnalysisFactory::AbsFactory
{
  public:
  EventDumpFactory():AnalysisFactory::AbsFactory("dump"){}
  virtual AnalysisSteering* create (const AnalysisInfo* info)
  {
    return new EventDump (info);
  }
};

//factory globale
static EventDumpFactory ev_dump;



EventDump::EventDump (const AnalysisInfo* info): 
AnalysisSteering (info) {
}


EventDump::~EventDump() {
}


// function to be called at execution start
void EventDump::beginJob() {
  return;
}


// function to be called at execution end
void EventDump::endJob() {
  return;
}


// function to be called for each event
void EventDump::update( const Event& ev ) {

  cout<<ev.eventNumber()<<endl; //stampo identificativo e luogo dell'evento
    cout<<ev.x_event()<<"\t"<<ev.y_event()<<"\t"<<ev.z_event()<<endl;

    cout<<ev.nParticles()<<endl;

    for (int i=0; i<ev.nParticles(); i++) //per ogni particella stampo carica e momento
    {
        cout<<ev.particle(i)->charge<<"\t"<<ev.particle(i)->px<<"\t";
        cout<<ev.particle(i)->py<<"\t"<<ev.particle(i)->pz<<endl;
    }

  return;

}

