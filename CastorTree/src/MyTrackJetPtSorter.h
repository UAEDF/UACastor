#ifndef MyTrackJetPtSorter_h
#define MyTrackJetPtSorter_h

#include "./MyTrackJet.h"

class MyTrackJetPtSorter {

 public:

  bool operator() ( const MyTrackJet& a, const MyTrackJet& b ) {
    return ( a.pt_cal > b.pt_cal );
  }
  
};

#endif
