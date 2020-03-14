#include <iostream>
#include "Event.h"

using namespace std;

Event::Event( int n, float x, float y, float z ):
  ev_number(n),
  x_decay(x),
  y_decay(y),
  z_decay(z)
{
  // allocate a buffer for particle pointers
  particles=new part_ptr [max_particle]; 
}


Event::~Event() 
{
  // delete all the particle pointers
  for (unsigned int i=0; i<max_particle; i++)
  {
    delete particles[i];
  }
  // delete the pointers array
  delete [] particles;
}


void Event::add( float px, float py, float pz, int charge ) 
{

  // check for the number of particles, if maximum reached do nothing
  // and return
  if (particle_number==max_particle) return;

  // create the new particle and fill with data
  Particle* p= new Particle;
  p->px=px;
  p->py=py;
  p->pz=pz;
  p->charge=charge;

  // store the new particle pointer in the array and increase counter
  particles[particle_number]=p;
  particle_number++;
  
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
  return particle_number;
}


// get particle
const Event::Particle* Event::particle( unsigned int i ) const 
{
  part_ptr p;
  //se chiedo il numero di una particella maggiore di quelle in memoria
  //metto il puntatore a vuoto
  if (i>=particle_number) p=NULL; 
  else p=particles[i];
  
  return p;
}

