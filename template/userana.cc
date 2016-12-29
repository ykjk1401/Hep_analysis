/*
  userana.cc
*/

#include "belle.h"
#include <cmath>

#include "event/BelleEvent.h"
#include "tuple/BelleTupleManager.h"
#include "basf/module.h"
#include "basf/module_descr.h"

#include <panther/panther.h>
#include BELLETDF_H
#include HEPEVT_H
#include MDST_H

#if defined(BELLE_NAMESPACE)
namespace Belle {
#endif

class userana : public Module {
public:
  userana();
  ~userana() {}
  void init(int *);
  void term();
  void disp_stat(const char*) {}
  void hist_def();
  void event(BelleEvent*, int*);
  void begin_run(BelleEvent*, int *);
  void end_run(BelleEvent*, int *);
  void other(int*, BelleEvent*, int*) {}
public: // BASF parameter
  // double my_parameter;
  // char my_filename[256];
private:
  // BelleTuple *nt;
};

extern "C" Module_descr *mdcl_userana() {
  userana *module = new userana;
  Module_descr *dscr = new Module_descr( "userana", module );
  // dscr->define_param( "my_parameter", "explanation",
  //                      &module->my_parameter );
  // dscr->define_param ( "my_filename", "filename", 256,
  //                      module->my_filename );
  return dscr;
}

userana::userana() {
  puts( "***** [userana] Module loaded successfully." );
  // my_parameter = 0.0;
  // strcpy( my_filename, "test" );
  return;
}

void userana::init(int *) {
  printf( "\n[userana] parameters\n" );
  // printf( "my_parameter = %f\n", my_parameter );
  // printf( "my_filename = %s\n", my_filename );
  // Ptype dummy("VPHO");
  return;
}

void userana::begin_run(BelleEvent* evptr, int *status) {
  (void)evptr; (void)status;
  return;
}

void userana::end_run(BelleEvent* evptr, int *status) {
  (void)evptr; (void)status;
  return;
}

void userana::hist_def() {
  extern BelleTupleManager *BASF_Histogram;
  BelleTupleManager *tm = BASF_Histogram;
  //  nt = tm->ntuple( "title", "mbc deltae", 1 );
  return;
}

void userana::event(BelleEvent* evptr, int* status) {
  (void)evptr; (void)status;
  return;
}

void userana::term() {
  return;
};

#if defined(BELLE_NAMESPACE)
} // namespace Belle
#endif
