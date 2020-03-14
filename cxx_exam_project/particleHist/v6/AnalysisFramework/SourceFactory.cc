#include <iostream>
#include <sstream>

#include "AnalysisFramework/SourceFactory.h"
#include "AnalysisFramework/AnalysisInfo.h"
#include "AnalysisFramework/EventReadFromFile.h"
#include "AnalysisFramework/EventSim.h"

using namespace std;

SourceFactory::SourceFactory() {
}


SourceFactory::~SourceFactory() {
}


// create event source
EventSource* SourceFactory::create( const AnalysisInfo* info ) {
  if ( info->contains( "input" ) ) {
    return new EventReadFromFile( info->value( "input" ) );
  }
  if ( info->contains( "sim"   ) ) {
    stringstream sstr;
    // get number of events to generate
    sstr.str( info->value( "sim" ) );
    unsigned int nevt;
    sstr >> nevt;
    // set seed if available
    unsigned int seed = 1;
    if ( info->contains( "seed" ) ) {
      sstr.clear();
      sstr.str( info->value( "seed" ) );
      sstr >> seed;
    }
    return new EventSim( nevt, seed );
  }
  return 0;
}

