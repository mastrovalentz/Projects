#ifndef MassMean_h
#define MassMean_h

class Event;

class MassMean {

 public:

  MassMean( float min, float max ); // mass range
  ~MassMean();

  bool add( const Event& ev );      // add data from a new event
  void compute();                   // compute mean and rms

  int nEvents ();                   // return number of accepted events
  double mMean ();                  // return mean mass
  double mRMS();                    // return rms  mass

 private:

  double min_mass, max_mass;// min mass and max mass

  int ev_accept;// number of accepted events
  double mass_sum, mass_squares, mean, rms;// sum of masses
  // sum of masses square
  // mean mass
  // rms  mass
};

#endif

