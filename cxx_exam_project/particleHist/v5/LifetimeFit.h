#ifndef LifetimeFit_h
#define LifetimeFit_h

#include <vector>
#include <iostream>

using namespace std;

class Event;

class LifetimeFit 
{
 public:
  LifetimeFit(double min_mass, double max_mass, double min_time, 
              double max_time, double min_scan, double max_scan, double scan_step);
  ~LifetimeFit();

  bool add( const Event& ev );      // add data from a new event
  void compute();                   // compute mean and rms
  
  int nEvents();                   // return number of accepted events
  double lifeTime();
  double lifeTimeError();
 
 private:

  double min_mass, max_mass;// min mass and max mass
  double min_time, max_time;
  double min_scan, max_scan;
  double scan_step;

  std::vector<double> decay_set; //metto qui i tempi di decadimento
  double lifetime_mean;
  double lifetime_error;
};

#endif

