#ifndef CASCADE_WRAPPER_H
#define CASCADE_WRAPPER_H

//-- Note the pyhepc routine is used by Pythia to fill
//-- the HEPEVT common block uses double precision and 4000 entries.


#include <ctype.h>
#include <cstring>

//-- Initialization routine


//-- PYTHIA Common Block Declarations


//-- PYTHIA routines declarations

#define pytcha pytcha_
#define pyedit pyedit_

//-- CASCADE routines declarations

#define casini casini_
#define steer steer_
#define cascha cascha_
#define cascade cascade_
#define caend caend_
//-- #define event event_  //-- conflict with event() in Cascade2Hadronizer.cc
#define rluxgo rluxgo_

extern "C" {
  
  //-- PYTHIA routines
  
  void pytcha();
  void pyedit(int*);
  
  //-- CASCADE routines
  
  void casini();
  void steer();
  void cascha();
  void cascade();
  void caend(int*);
  void event();
  void rluxgo(int*,int*,int*,int*);
}


//-- PYTHIA routines

inline void call_pytcha() {pytcha();}
inline void call_pyedit( int mode){pyedit( &mode);}

//inline void call_pyhepc( int mode ){ pyhepc( &mode ); }
//inline void call_pylist( int mode ){ pylist( &mode ); }
//inline void call_pystat( int mode ){ pystat( &mode ); }
//inline void call_pyevnt(){ pyevnt(); }

//-- CASCADE routines

inline void call_casini() {casini();}
inline void call_steer() {steer();}
inline void call_cascha() {cascha();}
inline void call_cascade() {cascade();}
inline void call_caend( int mode){caend( &mode);}
inline void call_event() {event();}
inline void call_rluxgo(int mode1, int mode2, int mode3, int mode4) {rluxgo(&mode1, &mode2, &mode3, &mode4 );}


// PYTHIA block data
//  with gcc it works to initialize the block data by calling pydata(); at beginning, 
//  but this fails for f77, so the fortran routine initpydata.f is supplied
//  call it instead for platform independent behaviour

/*
#define pydata pydata_
extern "C" {
    void pydata(void);
}
*/

#endif  // CASCADE_WRAPPER_H

