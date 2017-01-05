/*
  MCUtils.h
*/

#include "belle.h"
#include <cmath>

#include "event/BelleEvent.h"
#include "tuple/BelleTupleManager.h"
#include "basf/module.h"
#include "basf/module_descr.h"
#include "particle/Particle.h"

#include <panther/panther.h>
#include BELLETDF_H
#include HEPEVT_H
#include MDST_H

#if defined(BELLE_NAMESPACE)
namespace Belle {
#endif

class MCUtils : public Module {
public:
  MCUtils();
  ~MCUtils() {}
  void init(int *);
  void term();
  void disp_stat(const char*) {}
  void hist_def();
  void event(BelleEvent*, int*);
  void begin_run(BelleEvent*, int *);
  void end_run(BelleEvent*, int *);
  void other(int*, BelleEvent*, int*) {}
	void module_err(std::string modulename);
	double Reconquality(std::vector<Particle> particle_list, std::string pname);
public: // BASF parameter
  // double my_parameter;
  // char my_filename[256];
private:
  // BelleTuple *nt;
};
	
double MCUtils::Reconquality (std::vector<Particle> particle_list, std::string pname)
{
	double reconquality;
	int not_genhep=0;
	int gen_hep=0;
	int well_reconed_num=0;
	std::vector<Particle> __particle_list = particle_list;
	char *__pname = *pname;
	int pid = Ptype(__pname).lund();
	if(!particle_list.empty())
	{
		for(std::vector<Particle>::iterator i = __particle_list.begin(); i!=__particle_list.end(); i++)
		{
			Particle &p=*i;
			if(p.genHepevt())
			{
				if(p.genHepevt().idhep()==pid)
				{
					well_reconed_num++;
				}
				else
				{
					gen_hep++;
				}
			}
			else
			{
				not_genhep++;
			}
		}
	}
	reconquality = well_reconed_num/(well_reconed_num+gen_hep+not_genhep);
	std::cout<<"***********************************"<<std::endl;
	std::cout<<"Recon quality check for : "<<__pname<<std::endl;
	std::cout<<"well reconed : "<<well_reconed_num<<std::endl;
	std::cout<<"reconed but wrong id : "<<gen_hep<<std::endl;
	std::cout<<"Not even gen_hep : " <<not_genhep<<std::endl;
	std::cout<<"***********************************"<<std::endl;
	return reconquality;
}



void MCUtils::module_err(std::string modulename)
{
	std::cout<<"MCUtils Error : "<< modulename<<std::endl;
	return;
}


extern "C" Module_descr *mdcl_MCUtils() {
  MCUtils *module = new MCUtils;
  Module_descr *dscr = new Module_descr( "MCUtils", module );
  // dscr->define_param( "my_parameter", "explanation",
  //                      &module->my_parameter );
  // dscr->define_param ( "my_filename", "filename", 256,
  //                      module->my_filename );
  return dscr;
}

MCUtils::MCUtils() {
  puts( "***** [MCUtils] Module loaded successfully." );
  // my_parameter = 0.0;
  // strcpy( my_filename, "test" );
  return;
}

void MCUtils::init(int *) {
  printf( "\n[MCUtils] parameters\n" );
  // printf( "my_parameter = %f\n", my_parameter );
  // printf( "my_filename = %s\n", my_filename );
  // Ptype dummy("VPHO");
  return;
}

void MCUtils::begin_run(BelleEvent* evptr, int *status) {
  (void)evptr; (void)status;
  return;
}

void MCUtils::end_run(BelleEvent* evptr, int *status) {
  (void)evptr; (void)status;
  return;
}

void MCUtils::hist_def() {
  extern BelleTupleManager *BASF_Histogram;
  BelleTupleManager *tm = BASF_Histogram;
  //  nt = tm->ntuple( "title", "mbc deltae", 1 );
  return;
}

void MCUtils::event(BelleEvent* evptr, int* status) {
  (void)evptr; (void)status;
  return;
}

void MCUtils::term() {
  return;
};

#if defined(BELLE_NAMESPACE)
} // namespace Belle
#endif
