#include <iostream>
#include <math.h>

#include "Event.h"
#include "Constants.h"
#include "Utilities.h"

using namespace std;

double mass (const Event& ev) 
{
  // variable to retrieve particles in the event
  typedef const Event::Particle* part_ptr;

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
  }

  // check for exactly one positive and one negative track
  // otherwise return negative (unphysical) invariant mass
  if (pos_cont!=1 || neg_cont!=1) return -1;

  // invariant masses for different decay product mass hypotheses
  double inv_mass_k0=Utilities::inv_mass(sum_px, sum_py, sum_pz, energy_k0);
  double inv_mass_lambda=Utilities::inv_mass(sum_px, sum_py, sum_pz, energy_lambda);

  // compare invariant masses with known values and return the nearest one
  if ((inv_mass_k0-Constants::massK0)<(inv_mass_lambda-Constants::massLambda0))return inv_mass_k0;
  else return inv_mass_lambda;

}

