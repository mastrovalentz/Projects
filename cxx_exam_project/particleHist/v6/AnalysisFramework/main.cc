#include <vector>

#include "AnalysisFramework/EventSource.h"
#include "AnalysisFramework/SourceFactory.h"
#include "AnalysisFramework/AnalysisInfo.h"
#include "AnalysisFramework/AnalysisFactory.h"
#include "util/include/Dispatcher.h"

using namespace std;

int main( int argc, char* argv[] ) {

  // store command line parameters
  AnalysisInfo* info = new AnalysisInfo( argc, argv );

  // create data source
  EventSource* es = SourceFactory::create( info );

  // create a list of analyzers
  AnalysisFactory::create( info );

  // initialize all analyzers
  Dispatcher<AnalysisInfo::AnalysisStatus>::notify( AnalysisInfo::begin );

  // loop over events
  es->run();

  // finalize all analyzers
  Dispatcher<AnalysisInfo::AnalysisStatus>::notify( AnalysisInfo::end );

  return 0;

}

