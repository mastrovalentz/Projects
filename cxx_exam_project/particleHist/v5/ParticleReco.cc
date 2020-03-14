#include "ParticleReco.h"
#include "Event.h"
#include "Utilities.h"
#include "Constants.h"
#include <iostream>
#include <math.h>

using namespace std;

//la funzione update ha il codice della funzione mass quando era globale

// DA RICOMMENTARE

ParticleReco::ParticleReco() {
}


ParticleReco::~ParticleReco() {
}


// recompute tag informations for new event
void ParticleReco::update( const Event& ev ) {

  // set default quantities
  type   = unknown;
  energy = -1.0;
  mass   = -1.0;

  // code to compute total energy and invariant mass for the two
  // mass hypotheses for the decay products
  // variable to retrieve particles in the event

  typedef const Event::Particle* part_ptr;

  // variables to loop over particles

  // positive / negative track counters
  int pos_cont=0, neg_cont=0;

  // variables for momentum sums
  double sum_px=0, sum_py=0, sum_pz=0;

  // variables for energy sums, for K0 and Lambda0
  double energy_k0=0, energy_lambda=0, hyp_k0, hyp_lambda;

  // loop over particles - momenta
  for (int i=0; i<ev.nParticles(); i++) 
  {
    // get particle pointer
    part_ptr pp=ev.particle(i);
    
    // update momentum sums
    sum_px+=pp->px;
    sum_py+=pp->py;
    sum_pz+=pp->pz;

    // update energy sums, for K0 and Lambda0 hyptheses:
    // pion mass for K0,
    // proton or pion mass for Lambda0,
    // for positive or negative particles respectively
    hyp_k0=Utilities::energy(pp->px, pp->py, pp->pz, Constants::massPion);
    if (pp->charge==1)
    {
      hyp_lambda=Utilities::energy(pp->px, pp->py, pp->pz, Constants::massProton);
      pos_cont++;
    }
    else //potrei anceh mettere if (..==-1) ma la cariche hanno solo segno +/- dopo il decadimento
    {
      hyp_lambda=Utilities::energy(pp->px, pp->py, pp->pz, Constants::massPion);
      neg_cont++;
    }
    energy_k0+=hyp_k0;
    energy_lambda+=hyp_lambda;
    // update positive/negative track counters

      //li incremento direttamente dentro il calcolo dell'ipotesi di lambda

  }

  // compare invariant masses with known values and set final values
  // ( type, energy and mass )

  //elimino direttamente tutti i casi in cui le cariche non sono quelle che mi  
  //aspetto dal decadimento interrompendo la funzione in tal caso

  // check for exactly one positive and one negative track
  if (pos_cont!=1 || neg_cont!=1) return;

  //se le cariche sono giuste calcolo le masse invarianti 
  //e assegno i valori della più probabile

  // invariant masses for different decay product mass hypotheses
  double inv_mass_k0=Utilities::inv_mass(sum_px, sum_py, sum_pz, energy_k0);
  double inv_mass_lambda=Utilities::inv_mass(sum_px, sum_py, sum_pz, energy_lambda);

  // compare invariant masses with known values and return the nearest one
  if ((inv_mass_k0-Constants::massK0)<(inv_mass_lambda-Constants::massLambda0))
  {
    type=K0;
    mass=inv_mass_k0;
    energy=energy_k0;
  }
  else
  {
    type=Lambda0;
    mass=inv_mass_lambda;
    energy=energy_lambda;
  }
  return;
}


double ParticleReco::totalEnergy() 
{
  // check for new event and return result
  check();
  return energy;
}


double ParticleReco::invariantMass() 
{
  // check for new event and return result
  check();
  return mass;
}


ParticleReco::ParticleType ParticleReco::particleType() 
{
  // check for new event and return result
  check();
  return type;
}

