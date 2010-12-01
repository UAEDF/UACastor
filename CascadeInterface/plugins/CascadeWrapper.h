#ifndef CASCADE_WRAPPER_H
#define CASCADE_WRAPPER_H

//-- the pyhepc routine used by Pythia to fill the HEPEVT common block
//-- is using double precision and 4000 entries

#include <ctype.h>
#include <cstring>

//-- CASCADE Common Block Declarations

extern "C" {
  extern struct {
    int KE,KP,KEB,KPH,KGL,KPA,NFLAV;
    } caluco_;
  }
#define caluco caluco_

extern "C" {
  extern struct {
    int LST[30],IRES[2];
  } capar6_;
}
#define capar6 capar6_

extern "C" {
  extern struct {
    double PLEPIN,PPIN;
    int NFRAG,ILEPTO,IFPS,IHF,INTER,ISEMIH,IFINAL;
  } cainpu_;
}
#define cainpu cainpu_

extern "C" {
  extern struct {
    int IPST;
  } cashower_;
}
#define cashower cashower_

extern "C" {
  extern struct {
    int ipsipol,ipsiel1,ipsiel2;
    //-- int i23s;  //-- from version 2.2.03 on 
  } jpsi_;
}
#define jpsi jpsi_

extern "C" {
  extern struct {
    int IORDER,ITIMSHR,ICCFM;
  } casshwr_;
}
#define casshwr casshwr_

extern "C" {
  extern struct {
    int IPRO,IRUNA,IQ2,IRUNAEM;
  } capar1_;
}
#define capar1 capar1_

extern "C" {
  extern struct {
    int IHFLA,KPSI,KCHI;
  } cahflav_;
}
#define cahflav cahflav_

extern "C" {
  extern struct {
    int ICOLORA,IRESPRO,IRPA,IRPB,IRPC,IRPD,IRPE,IRPF,IRPG;
  } cascol_;
}
#define cascol cascol_

extern "C" {
  extern struct {
    int IGLU;
  } cagluon_;
}
#define cagluon cagluon_

extern "C" {
  extern struct {
    int IRspl;
  } casprre_;
}
#define casprre casprre_

extern "C" {
  extern struct {
    double PT2CUT[1000];
  } captcut_;
}
#define captcut captcut_

extern "C" {
  extern struct {
    double ACC1,ACC2;
    int IINT,NCB;
  } integr_;
}
#define integr integr_

extern "C" {
  extern struct {
    double SCALFA,SCALFAF;
  } scalf_;
}
#define scalf scalf_

extern "C" {
  extern struct {
    const char* PDFPATH;
  } caspdf_;
}
#define caspdf caspdf_

//-- CASCADE routines declarations

#define casini casini_
#define steer steer_
#define cascha cascha_
#define cascade cascade_
#define caend caend_
//-- #define event event_  //-- conflict with event() in Cascade2Hadronizer.cc
#define rluxgo rluxgo_

extern "C" {
  void casini();
  void steer();
  void cascha();
  void cascade();
  void caend(int*);
  void event();
  void rluxgo(int*,int*,int*,int*);
}

inline void call_casini() {casini();}
inline void call_steer() {steer();}
inline void call_cascha() {cascha();}
inline void call_cascade() {cascade();}
inline void call_caend( int mode){caend( &mode);}
inline void call_event() {event();}
inline void call_rluxgo(int mode1, int mode2, int mode3, int mode4) {rluxgo(&mode1, &mode2, &mode3, &mode4 );}

//-- PYTHIA Common Block Declarations

//-- PYTHIA routines declarations

#define pytcha pytcha_
#define pyedit pyedit_

extern "C" {
  void pytcha();
  void pyedit(int*);
}

inline void call_pytcha() {pytcha();}
inline void call_pyedit( int mode){pyedit( &mode);}

//inline void call_pyhepc( int mode ){ pyhepc( &mode ); }
//inline void call_pylist( int mode ){ pylist( &mode ); }
//inline void call_pystat( int mode ){ pystat( &mode ); }
//inline void call_pyevnt(){ pyevnt(); }

#endif  // CASCADE_WRAPPER_H

