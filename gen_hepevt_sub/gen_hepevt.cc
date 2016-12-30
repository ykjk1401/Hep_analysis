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
			BelleTuple *m_nt;
			BelleTuple *newhist;
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
		BelleTupleManager *m_tm = BASF_Histogram;
		BelleTupleManager *hist = BASF_Histogram;
		nt = tm->ntuple( "title", "e_px e_py e_pz e_e", 1 );
		m_nt = m_tm->ntuple( "title2", "k_px k_py k_pz k_e",2);
		newhist = hist->ntuple( "title3", "k_e e1_e e2_e e3_e e4_e",3);
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
		double myenergy[4];
		int electroncounter=1;
		for ( std::vector<Gen_hepevt>::iterator i = GenMgr.begin();i!=GenMgr.end();i++)
		{
			Gen_hepevt &gen = *i;
			if(gen.mother()!=NULL)
			{
				if( abs(gen.mother().idhep()) == hep_number )
				{
					HepLorentzVector p = HepLorentzVector(gen.P(0),gen.P(1),gen.P(2),gen.P(3));
					double px = p.px();
					double py = p.py();
					double pz = p.pz();
					double p_p =sqrt(pow( px,2) +pow(py,2) +pow(pz,2));
					double energy = p.e();
					double c = 1;
					if(abs(gen.idhep())==11)
					{
						myenergy[electroncounter]=energy;
						electroncounter++;
						nt->column("e_px" , px);
						nt->column("e_py" , py);
						nt->column("e_pz" , pz);
						nt->column("e_e", energy);
						nt->dumpData();
					}

					else if(abs(gen.idhep())==311)
					{
						myenergy[0]=energy;
						m_nt->column("k_px" , px);
						m_nt->column("k_py" , py);
						m_nt->column("k_pz" , pz);
						m_nt->column("k_e" , energy);
						m_nt->dumpData();
					}

				}
			}
		}
		newhist->column("k_e",myenergy[0]);
		newhist->column("e1_e",myenergy[1]);
		newhist->column("e2_e",myenergy[2]);
		newhist->column("e3_e",myenergy[3]);
		newhist->column("e4_e",myenergy[4]);
		newhist->dumpData();

		return;
	}

	void gen_hepevt::term() {
		return;
	};

#if defined(BELLE_NAMESPACE)
} // namespace Belle
#endif
