#include <iostream>
#include <vector>

#include "AnalysisFramework/Event.h"

using namespace std;

Event::Event( int n, float x, float y, float z ):
 // initializations
  ev_number(n),
  x_decay(x),
  y_decay(y),
  z_decay(z)
{
  // reserve memeory for 10 particles for the vector
  particles.reserve(10);
}


Event::~Event() 
{
  particles.clear();
}


void Event::add( float px, float py, float pz, int charge ) 
{
  // create the new particle and fill with data
  Particle p;
  p.px=px;
  p.py=py;
  p.pz=pz;
  p.charge=charge;

  // store the new particle pointer in the array and increase counter
  particles.push_back(p);
  return;

}


// get event id.
int Event::eventNumber() const 
{
  return ev_number;
}


// get decay point coordinates
float Event::x_event() const
{
  return x_decay;
}

float Event::y_event() const
{
  return y_decay;
}

float Event::z_event() const
{
  return z_decay;
}

// get number of particles
int Event::nParticles() const
{
  return particles.size();
}


// get particle
const Event::Particle* Event::particle( unsigned int i ) const 
{
  vector<Particle>::const_iterator it=particles.begin();
  if (i>=particles.size()) return NULL; //l'uguale serve perchè se chiedo l'ultima particella ad esempèio la numero nove essa è all'indice 8
  else while (i--) it++;
  return &*it; //ritornare un iteratore da un errore perchè non è cio che voglio
              // la soluzione è ritornare l'indirizzo dalla variabile a cui punta 
              //l'iteratore
}

