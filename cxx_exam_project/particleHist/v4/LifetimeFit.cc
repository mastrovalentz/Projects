#include <iostream>
#include <math.h>

#include "LifetimeFit.h"
#include "Event.h"
#include "ParticleReco.h"

using namespace std;

double mass(const Event& ev);

LifetimeFit::LifetimeFit( float min_mass, float max_mass ):
// initializations
min_mass(min_mass),
max_mass(max_mass)
{
}


LifetimeFit::~LifetimeFit() 
{
}


// add data from a new event
bool LifetimeFit::add( const Event& ev ) 
{
  static ParticleReco* decayment= ParticleReco::instance();
  double m=decayment->invariantMass(); 

  // check for mass being in range
  if (m<max_mass && m>min_mass) 
  {
    // update number of event
    ev_accept++;
    return true;
  }
  return false;
}

void LifetimeFit::compute() 
{
  return;
}


// return number of selected events
int LifetimeFit::nEvents()
{
  return ev_accept;
}


