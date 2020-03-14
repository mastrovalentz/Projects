#include <iostream>
#include <math.h>

#include "MassMean.h"
#include "Event.h"

using namespace std;

double mass(const Event& ev);

MassMean::MassMean( float min_mass, float max_mass ):
min_mass(min_mass),
max_mass(max_mass)
{
}


MassMean::~MassMean() 
{
}


// add data from a new event
void MassMean::add( const Event& ev ) 
{
  double m=mass(ev); //dichiaro questa variabile visto che mi servirà piu volte

  // check for mass being in range
  if (m<max_mass && m>min_mass) 
  {
    // update number of events and sums
    ev_accept++;
    mass_sum+=m;
    mass_squares+=pow(m,2);
  }

  return;
}


// compute mean and rms
void MassMean::compute() 
{
  mean=mass_sum/ev_accept; //non serve casting perchè mass_sum è double
  rms=sqrt(mass_squares/ev_accept-pow(mean,2)); //come sopra

  return;
}


// return number of selected events
int MassMean::nEvents()
{
  return ev_accept;
}

// return mean
double MassMean::mMean()
{
  return mean;
}

// return rms
double MassMean::mRMS()
{
  return rms;
}

