#include "ProperTime.h"
#include "Event.h"
#include "Utilities.h"
#include "Constants.h"
#include "ParticleReco.h"

#include <iostream>
#include <math.h>

using namespace std;

//la funzione update ha il codice della funzione mass quando era globale

// DA RICOMMENTARE

ProperTime::ProperTime() {
}


ProperTime::~ProperTime() {
}


// recompute tag informations for new event
void ProperTime::update( const Event& ev ) 
{
  //calcolo la massa invariante e l'energia con ParticleReco
  static ParticleReco* decayment= ParticleReco::instance();
  double m=decayment->invariantMass();
  double e=decayment->totalEnergy();

  //prendo le coordinate dell'evento e calcolo la distanza
  //nell'evento i punti sono float ma time è una variabile double
  //quindi conviene calcolare già d come double
  float x=ev.x_event();
  float y=ev.y_event();
  float z=ev.z_event();
  double d=sqrt(x*x+y*y+z*z); // potevo anche usa pow ma \'e piu snello cosi

  //calcolo il momento p e il tempo di decadimento
  double p=sqrt(e*e-m*m);
  time=d*m/(p*Constants::lightVelocity);
  return;
}


double ProperTime::decayTime () 
{
  // check for new event and return result
  check();
  return time;
}
