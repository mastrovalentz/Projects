#include <iostream>
#include <math.h>

#include "Event.h"
#include "Particle.h"

using namespace std;

// compute energy from momentum x,y,z components and invariant mass
double energy (double px, double py, double pz, double m) 
{
    return sqrt(pow(px,2)+pow(py,2)+pow(pz,2)+pow(m,2));
} 

// compute invariant mass from momentum x,y,z components and energy
double inv_mass (double px, double py, double pz, double e) 
{
    return sqrt(pow(e,2)-pow(px,2)-pow(py,2)-pow(pz,2));
} 

const double massPion    = 0.1395706;   // GeV/c^2
const double massProton  = 0.938272;    // GeV/c^2
const double massK0      = 0.497611;    // GeV/c^2
const double massLambda0 = 1.115683;    // GeV/c^2

double mass (const Event& ev) 
{
  // retrieve particles in the event
  typedef const Particle* part_ptr;
  const part_ptr* particles = ev.p_decay;

  // variables to loop over particles

  // positive / negative track counters
  int pos_cont=0, neg_cont=0;

  // variables for momentum sums
  double sum_px=0, sum_py=0, sum_pz=0;

  // variables for energy sums, for K0 and Lambda0
  double energy_k0=0, energy_lambda=0, hyp_k0, hyp_lambda;

  // loop over particles - momenta
  for (int i=0; i<ev.particle_number; i++) 
  {
    // get particle pointer
    const Particle* pp=particles[i];
    Particle p=*pp;
    // update momentum sums
    sum_px+=p.px;
    sum_py+=p.py;
    sum_pz+=p.pz;

    // update energy sums, for K0 and Lambda0 hyptheses:
    // pion mass for K0,
    // proton or pion mass for Lambda0,
    // for positive or negative particles respectively
    hyp_k0=energy(p.px, p.py, p.pz, massPion);
    if (p.charge==1)
    {
      hyp_lambda=energy(p.px, p.py, p.pz, massProton);
      pos_cont++;
    }
    else //potrei anceh mettere if (..==-1) ma la cariche hanno solo segno +/- dopo il decadimento
    {
      hyp_lambda=energy(p.px, p.py, p.pz, massPion);
      neg_cont++;
    }
    energy_k0+=hyp_k0;
    energy_lambda+=hyp_lambda;
    // update positive/negative track counters

      //li incremento direttamente dentro il calcolo dell'ipotesi di lambda
  }
  // check for exactly one positive and one negative track
  // otherwise return negative (unphysical) invariant mass
  if (pos_cont!=1 || neg_cont!=1) return -1;

  // invariant masses for different decay product mass hypotheses
  double inv_mass_k0=inv_mass(sum_px, sum_py, sum_pz, energy_k0);
  double inv_mass_lambda=inv_mass(sum_px, sum_py, sum_pz, energy_lambda);


  // compare invariant masses with known values and return the nearest one
  if ((inv_mass_k0-massK0)<(inv_mass_lambda-massLambda0))return inv_mass_k0;
  else return inv_mass_lambda;

}

