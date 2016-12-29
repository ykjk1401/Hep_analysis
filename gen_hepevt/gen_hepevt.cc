/*
  gen_hepevt.cc
*/

#include "belle.h"
#include <cmath>

#include "event/BelleEvent.h"
#include "tuple/BelleTupleManager.h"
#include "basf/module.h"
#include "basf/module_descr.h"
#include "benergy/BeamEnergy.h"
#include <panther/panther.h>
#include "mdst/mdst.h"

#include BELLETDF_H
#include HEPEVT_H
#include MDST_H

#if defined(BELLE_NAMESPACE)
namespace Belle {
#endif

class gen_hepevt : public Module {
public:
  gen_hepevt();
  ~gen_hepevt() {}
  void init(int *);
  void term();
  void disp_stat(const char*) {}
  void hist_def();
  void event(BelleEvent*, int*);
  void begin_run(BelleEvent*, int *);
  void end_run(BelleEvent*, int *);
  void other(int*, BelleEvent*, int*) {}
public: // BASF parameter
  int hep_number;
  // char my_filename[256];
private:
  BelleTuple *nt;
};

extern "C" Module_descr *mdcl_gen_hepevt() {
  gen_hepevt *module = new gen_hepevt;
  Module_descr *dscr = new Module_descr( "gen_hepevt", module );
  dscr->define_param( "hep_number", "hep_number",
                       &module->hep_number );
  // dscr->define_param ( "my_filename", "filename", 256,
  //                      module->my_filename );
  return dscr;
}

gen_hepevt::gen_hepevt() {
  puts( "***** [gen_hepevt] Module loaded successfully." );
  hep_number = 511;
  // strcpy( my_filename, "test" );
  return;
}

void gen_hepevt::init(int *) {
  printf( "\n[gen_hepevt] parameters\n" );
  printf( "hep_number = %d\n", hep_number );
  // printf( "my_filename = %s\n", my_filename );
  // Ptype dummy("VPHO");
  return;
}

void gen_hepevt::begin_run(BelleEvent* evptr, int *status) {
  (void)evptr; (void)status;
  return;
}

void gen_hepevt::end_run(BelleEvent* evptr, int *status) {
  (void)evptr; (void)status;
  return;
}

void gen_hepevt::hist_def() {
  extern BelleTupleManager *BASF_Histogram;
  BelleTupleManager *tm = BASF_Histogram;
  nt = tm->ntuple( "title", "mbc deltae b0mass", 1 );
  return;
}

void gen_hepevt::event(BelleEvent* evptr, int* status) {
  (void)evptr; (void)status;
	Belle_event_Manager &evt_mgr = Belle_event_Manager::get_manager();
	std::vector<Belle_event>::const_iterator evt = evt_mgr.begin();
	int expno, runno, evtno;
	if (evt == evt_mgr.end())
	{
		expno = 0; runno = 0; evtno = 0;
	}
	else
	{
		expno = evt->ExpNo();
		runno = evt->RunNo();
		evtno = evt->EvtNo();
	}
 	double eler(3.499218); // default beam energies used for new monte carlo (on sqrt(s) = 10.58 GeV )
	const double eher(7.998213); 
	const double theta(0.022); 
	const HepLorentzVector cm=HepLorentzVector(-eher*sin(theta), 0., -eher*cos(theta)+eler, eher+eler); 
	const double Ecm=cm.mag(); 
	const Hep3Vector CMBoost=cm.boostVector();
	Gen_hepevt_Manager &GenMgr = Gen_hepevt_Manager::get_manager();
	for ( std::vector<Gen_hepevt>::iterator i = GenMgr.begin();i!=GenMgr.end();i++)
	{
		Gen_hepevt &gen = *i;
		if( abs(gen.idhep()) == hep_number )
		{
			HepLorentzVector p = HepLorentzVector(gen.P(0),gen.P(1),gen.P(2),gen.P(3));
			p.boost(CMBoost);
			double px = p.px();
			double py = p.py();
			double pz = p.pz();
			double p_p =sqrt(pow( px,2) +pow(py,2) +pow(pz,2));
			double energy = p.e();
			double benergy =Benergy();
			double mbc;
			double deltae;
			double c = 1;
			mbc = sqrt ( pow((benergy/pow(c,2)),2) - pow((p_p/c),2) );
			deltae = energy-benergy;
			std::cout<<p<<std::endl;
			std::cout<<p_p<<std::endl;
			nt->column("mbc" , mbc);
			nt->column("deltae" , deltae);
			nt->column("b0mass" , gen.P(4));
			nt->dumpData();
		}
	}
  
	
	return;
}

void gen_hepevt::term() {
  return;
};

#if defined(BELLE_NAMESPACE)
} // namespace Belle
#endif
