#include <iostream>
#include <fstream>
#include <string>

#include "Event.h"
#include "MassMean.h"

using namespace std;

//range masse per i due tipi di decadimento
const double min_k0=0.490, max_k0=0.505;
const double min_lambda0=1.114, max_lambda0 = 1.118; 

void dump (const Event&);
const Event* read (ifstream &);

int main( int argc, char* argv[] ) 
{
  // open input file
  string file= argv[1];
  ifstream input (file); 

  // create MassMean objects
  MassMean k0 (min_k0, max_k0);
  MassMean lambda0 (min_lambda0, max_lambda0); 

  // loop over events
  const Event* ev;

  //se non ci sono valori read ritorna 0 che il while 
  //interpreta come false uscendo dal ciclo 
  while ((ev=read(input))!=0)  
  {
      k0.add(*ev);
      lambda0.add(*ev);
      dump(*ev);
  }
  delete ev;

  // compute results
  k0.compute();
  lambda0.compute();

  // print number of selected events and results for both particles
  cout<<k0.mMean()<<"\t"<<k0.mRMS()<<endl;
  cout<<lambda0.mMean()<<"\t"<<lambda0.mRMS()<<endl;

  return 0;
}

