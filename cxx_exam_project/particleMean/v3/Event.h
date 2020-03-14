#ifndef Event_h
#define Event_h

#include <stdlib.h>
#include <vector>

using namespace std;

class Event {

 public:

  Event( int n, float x, float y, float z ); // create an event with number "n"
                                             // and coordinates x, y, z
  ~Event();

  // composite object Particle to hold all information for each particle
  // ( x,y,z momentum components and electric charge )
  struct Particle 
  {
    int charge;
    double px, py, pz; //momentum   
  };

  // add a particle to the event
  void add( float px, float py, float pz, int charge );

  // get event id.
  int eventNumber() const;

  // get decay point coordinates
  float x_event() const;
  float y_event() const;
  float z_event() const;

  // get number of particles
  int nParticles() const;

  // get particle
  const Particle* particle( unsigned int i ) const;

 private:

  // event-specific informations:
  int ev_number; // event id
  float x_decay, y_decay, z_decay; // decay point, li dichiaro float perchè non mi serve che abbiano una precisione elevata

  // vector of particles
  vector<Particle> particles;
};

#endif

