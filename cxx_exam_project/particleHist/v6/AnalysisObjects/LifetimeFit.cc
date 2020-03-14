#include <iostream>
#include <math.h>
#include <vector>

#include "AnalysisObjects/LifetimeFit.h"
#include "AnalysisFramework/Event.h"
#include "AnalysisObjects/ParticleReco.h"
#include "AnalysisUtilities/QuadraticFitter.h"
#include "AnalysisObjects/ProperTime.h"

using namespace std;

LifetimeFit::LifetimeFit(double min_mass, double max_mass, double min_time, 
                         double max_time, double min_scan, double max_scan, 
                         double scan_step):
// initializations
min_mass(min_mass), max_mass(max_mass),
min_time(min_time), max_time(max_time), 
min_scan(min_scan), max_scan(max_scan), scan_step(scan_step)
{
}

LifetimeFit::~LifetimeFit() 
{
}

// add data from a new event
bool LifetimeFit::add( const Event& ev ) 
{
  //dalle istanze relative all'evento prendo massa e tempo del decadimento
  static ProperTime* time= ProperTime::instance();
  double t=time->decayTime(); 
  static ParticleReco* decayment= ParticleReco::instance();
  double m=decayment->invariantMass();
  // check for time being in range
  if (t<max_time && t>min_time && m>min_mass && m<max_mass) 
  {
    // update number of event
    decay_set.push_back(t);
    return true;
  }
  return false;
}


// compute mean and rms
void LifetimeFit::compute() 
{
    double Lt;
    QuadraticFitter time_fit;
    for (double t_s=min_scan; t_s<=max_scan; t_s+=scan_step)
    {
        Lt=0; //reimposto a zero primia di ogni ciclo sui tempi
        for (unsigned int i=0; i<decay_set.size(); i++)
        {
            Lt+=decay_set[i]/t_s+log(t_s)+log(exp(min_time/t_s)-exp(-max_time/t_s));
        }
        time_fit.add(t_s, Lt); //aggiungo al fitter
    }
    lifetime_mean=-time_fit.b()/(2*time_fit.c()); //ottengo i dati dal fit
    lifetime_error=1/(sqrt(2*time_fit.c()));
}


// return number of selected events
int LifetimeFit::nEvents()
{
  return decay_set.size();
}


double LifetimeFit::lifeTime()
{
  return lifetime_mean;
}

double LifetimeFit::lifeTimeError()
{
  return lifetime_error;
}