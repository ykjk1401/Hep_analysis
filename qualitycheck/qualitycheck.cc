/*
  qualitycheck.cc
*/

#include "belle.h"
#include <cmath>

#include "event/BelleEvent.h"
#include "tuple/BelleTupleManager.h"
#include "basf/module.h"
#include "basf/module_descr.h"
#include "mdst/mdst.h"
#include "mdst/Muid_mdst"
#include "eid/eid.h"

#include "/home/ykkim/Mymode/Kllll/analysis/headers/MdstRecontable.h"
#include "/home/ykkim/Mymode/Kllll/analysis/headers/MCUtils.h"

#include <panther/panther.h>
#include BELLETDF_H
#include HEPEVT_H
#include MDST_H

#if defined(BELLE_NAMESPACE)
namespace Belle {
#endif

class qualitycheck : public Module {
public:
  qualitycheck();
  ~qualitycheck() {}
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

extern "C" Module_descr *mdcl_qualitycheck() {
  qualitycheck *module = new qualitycheck;
	MdstRecontable *mdstrecon = new MdstRecontable;
	MCUtils *mcutils=new MCUtils;
  Module_descr *dscr = new Module_descr( "qualitycheck", module );
  // dscr->define_param( "my_parameter", "explanation",
  //                      &module->my_parameter );
  // dscr->define_param ( "my_filename", "filename", 256,
  //                      module->my_filename );
  return dscr;
}

qualitycheck::qualitycheck() {
  puts( "***** [qualitycheck] Module loaded successfully." );
  // my_parameter = 0.0;
  // strcpy( my_filename, "test" );
  return;
}

void qualitycheck::init(int *) {
  printf( "\n[qualitycheck] parameters\n" );
  // printf( "my_parameter = %f\n", my_parameter );
  // printf( "my_filename = %s\n", my_filename );
  // Ptype dummy("VPHO");
  return;
}

void qualitycheck::begin_run(BelleEvent* evptr, int *status) {
  (void)evptr; (void)status;
  return;
}

void qualitycheck::end_run(BelleEvent* evptr, int *status) {
  (void)evptr; (void)status;
  return;
}

void qualitycheck::hist_def() {
  extern BelleTupleManager *BASF_Histogram;
  BelleTupleManager *tm = BASF_Histogram;
  //  nt = tm->ntuple( "title", "mbc deltae", 1 );
  return;
}

void qualitycheck::event(BelleEvent* evptr, int* status) {
  (void)evptr; (void)status;
	Mdst_charged_Manager &chg_mgr = Mdst_charged_Manager::get_manager();
	std::vector<Mdst_charged> charged_mgr(100000);
	charged_mgr.clear();
	MdstRecontable mdstrecon;
	
	for(std::vector<Mdst_charged>::iterator i = chg_mgr.begin(); i!=chg_mgr.end();i++)
	{
		Mdst_charged &chg = *i;
		charged_mgr.push_back(chg);
	}
	std::vector<Particle> electron_list = mdstrecon.Recon_electron(charged_mgr,0.9);
	double a = mcutils.Reconquality( electron_list, "E+");
	double b = mcutils.Reconquality( electron_list, "E-");
  return;
}

void qualitycheck::term() {
  return;
};

#if defined(BELLE_NAMESPACE)
} // namespace Belle
#endif
