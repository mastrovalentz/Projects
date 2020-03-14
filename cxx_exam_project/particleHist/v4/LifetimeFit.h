#ifndef LifetimeFit_h
#define LifetimeFit_h

class Event;

class LifetimeFit {

 public:

  LifetimeFit( float min, float max ); // mass range
  ~LifetimeFit();

  bool add( const Event& ev );      // add data from a new event
  void compute();                   // compute mean and rms
  
  int nEvents ();                   // return number of accepted events
 
 private:

  double min_mass, max_mass;// min mass and max mass
  int ev_accept;// number of accepted events
};

#endif

