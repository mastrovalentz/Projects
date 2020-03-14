#include <iostream>
#include <math.h>

#include "AnalysisObjects/MassMean.h"
#include "AnalysisFramework/Event.h"
#include "AnalysisObjects/ParticleReco.h"

using namespace std;


MassMean::MassMean( float min_mass, float max_mass ):
// initializations
min_mass(min_mass),
max_mass(max_mass)
{
}


MassMean::~MassMean() 
{
}


// add data from a new event
bool MassMean::add( const Event& ev ) 
{
  static ParticleReco* decayment= ParticleReco::instance();

  double m=decayment->invariantMass(); //dichiaro questa variabile visto che mi servirà piu volte il valore

  // check for mass being in range
  if (m<max_mass && m>min_mass) 
  {
    // update number of events and sums
    ev_accept++;
    mass_sum+=m;
    mass_squares+=pow(m,2);
    return true;
  }
  return false;
}


// compute mean and rms
void MassMean::compute() 
{
  mean=mass_sum/ev_accept; //non serve casting perchè mass_sum è double
  rms=sqrt(mass_squares/ev_accept-pow(mean,2)); //come sopra
}


// return number of selected events
int MassMean::nEvents()
{
  return ev_accept;
}

// return mean and rms
double MassMean::mMean()
{
  return mean;
}

double MassMean::mRMS()
{
  return rms;
}

