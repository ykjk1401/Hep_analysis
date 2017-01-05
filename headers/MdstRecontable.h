/**********************************************
	MdstRecontable.h
 ********************************************/

#include "belle.h"
#include <cmath>
#include <iostream>
#include <vector>
#include "basf/module.h"
#include "basf/module_descr.h"
#include <panther/panther.h>
#include "mdst/mdst.h"
#include "particle/Particle.h"
#include "kid/atc_pid.h"
#include "eid/eid.h"
#include "ip/IpProfile.h"
#include "mdst/findKs.h"



#if defined(BELLE_NAMESPACE)
namespace Belle {
#endif
	class MdstRecontable : public Module 
	{
		public:
			MdstRecontable();
			~MdstRecontable(){}
			void init(int *);
			void term();
			void disp_stat(const char*) {}
			void hist_def();
			void event(BelleEvent*, int*);
			void begin_run(BelleEvent*, int *);
			void end_run(BelleEvent*, int *);
			void other(int*, BelleEvent*, int*) {}
			void empty_list_err(std::string module_name);
			//std::vector<std::vector<Particle>> Mdst_charged_selection(Mdst_charged_Manager &chg_mgr,double eid_cut,double muid_cut,double KPI_cut,double PPI_cut);
			std::vector<Particle> Recon_Ks ( std::vector<Mdst_vee2> &vee2_mgr,const HepPoint3D &ip );
			//from Mdst_charged
			std::vector<Particle> Recon_electron ( std::vector<Mdst_charged> &chg_mgr , double e_cut);
			std::vector<Particle> Recon_muon ( std::vector<Mdst_charged> &chg_mgr , double mu_cut);
			std::vector<Particle> Recon_Kaon ( std::vector<Mdst_charged> &chg_mgr , double KPI_cut , double KP_cut );
	};
	
	std::vector<Particle> MdstRecontable::Recon_Kaon ( std::vector<Mdst_charged> &chg_mgr , double KPI_cut = 0.6 , double KP_cut = 0.6 )
	{
		std::string module_name = "Recon Kaon from Mdst_charged";
		std::vector<Mdst_charged> chged_mgr = chg_mgr;
		std::vector<Particle> kaon_list(100000);
		atc_pid selKPI (3,1,5,3,2);
		atc_pid selPK (3,1,5,4,3);
		double KPI = KPI_cut;
		double KP = KP_cut;
		kaon_list.clear();
		if(!chg_mgr.empty())
		{
			for( std::vector<Mdst_charged>::iterator i = chged_mgr.begin() ; i!=chged_mgr.end() ; i++)
			{
				Mdst_charged &chg = *i;
				double atcKPI = selKPI.prob(chg);
				double atcKP = 1.0-selPK.prob(chg);
				if( (atcKPI>KPI_cut)&&(atcKP>KP_cut))
				{
					Particle Kaon (chg, Ptype (chg.charge()>0?"K+":"K-"));
					getHepevt(chg)?Kaon.relation().genHepevt(getHepevt(chg)):;
					kaon_list.push_back(Kaon);
				}
			}
		}
		else
		{
			this->empty_list_err(module_name);
		}
		return kaon_list;
	}

	std::vector<Particle> MdstRecontable::Recon_electron ( std::vector<Mdst_charged> &chg_mgr ,double e_cut = 0.9)
	{
		std::string module_name = "Recon electron from Mdst_charged";
		std::vector <Mdst_charged> chged_mgr = chg_mgr;
		std::vector <Particle> electron_list(100000);
		double ecut=e_cut;
		electron_list.clear();
		if(!chg_mgr.empty())
		{
			for(std::vector<Mdst_charged>::iterator i = chged_mgr.begin() ; i != chged_mgr.end() ; i++ )
			{
				Mdst_charged &chg = *i;
				eid sel_e(chg);
				Muid_mdst muID(chg);
				double e_id = sel_e.prob(3,1,5);
				double mu_id;
				if(muID.Chi_2()>0)
				{
					mu_id = muID.Muon_likelihood();
				}
				else
				{
					mu_id = 0;
				}
				if(good_charged(chg, 1.e-25, 40 , 30 ))
				{
					if( (e_id>ecut)&&(e_id>mu_id) )
					{
						Particle electron (chg, Ptype (chg.charge()>0?"E+":"E-"));
						electron_list.push_back(electron);
					}
				}
			}
		}
		else
		{
			this->empty_list_err(module_name);
		}
		return electron_list;
	}
	
	std::vector<Particle> MdstRecontable::Recon_muon ( std::vector<Mdst_charged> &chg_mgr ,double mu_cut = 0.9)
	{
		std::string module_name = "Recon muon from Mdst_charged";
		std::vector <Mdst_charged> chged_mgr = chg_mgr;
		std::vector <Particle> muon_list(100000);
		double mucut=mu_cut;
		muon_list.clear();
		if(!chg_mgr.empty())
		{
			for(std::vector<Mdst_charged>::iterator i = chged_mgr.begin() ; i != chged_mgr.end() ; i++ )
			{
				Mdst_charged &chg = *i;
				eid sel_e(chg);
				Muid_mdst muID(chg);
				double e_id = sel_e.prob(3,1,5);
				double mu_id;
				if(muID.Chi_2()>0)
				{
					mu_id = muID.Muon_likelihood();
				}
				else
				{
					mu_id = 0;
				}
				if(good_charged(chg, 1.e-25, 40 , 30 ))
				{
					if( (mu_id>mucut)&&(mu_id>e_id) )
					{
						Particle muon (chg, Ptype (chg.charge()>0?"MU+":"MU-"));
						muon_list.push_back(muon);
					}
				}
			}
		}
		else
		{
			this->empty_list_err(module_name);
		}
		return muon_list;
	}
	
	std::vector<Particle> MdstRecontable::Recon_Ks ( std::vector<Mdst_vee2> &vee2_mgr, const HepPoint3D &ip)
	{
		std::vector<Mdst_vee2> vee2_manager = vee2_mgr;
		std::string module_name = "Recon K0S from Mdst_vee2";
		std::vector<Particle> ks_list(100000);
		ks_list.clear();
		const HepPoint3D &_ip = ip;
		if(!vee2_mgr.empty())
		{
			for(std::vector<Mdst_vee2>::iterator i = vee2_manager.begin(); i != vee2_manager.end();i++)
			{
				Mdst_vee2 &vee2 = *i;
				int goodVee(0);
				int kind = vee2.kind();
				//kind 1 ks 2 lambda 3 lambda_bar 4 gamma-ee
				if( kind == 1)
				{
					FindKs findks;
					findks.candidates( vee2, _ip);
					goodVee = findks.goodKs();
					if(goodVee == 1)
					{
						Particle KS(vee2,false);
						ks_list.push_back(KS);
					}
				}
			}
		}
		else
		{
			this->empty_list_err(module_name);
		}
		return ks_list;
	}
	/*
	std::vector<std::vector<Particle>> MdstRecontable::Mdst_charged_selection(Mdst_charged_Manager &chg_mgr,double eid_cut,double muid_cut,double KPI_cut,double PPI_cut)
	{
		atc_pid selKPI(3,1,5,3,2);
		atc_pid selPPI(3,1,5,4,2);
		atc_pid selPK(3,1,5,4,3);
		std::string module_name = "Mdst_charged_selection";
		std::vector<std::vector<Particle>> selected(4); //0 e 1 mu 2 K 3 P 4 PI
		selected.clear();
		std::vector<Particle> electron_list(100000);
		std::vector<Particle> muon_list(100000);
		std::vector<Particle> kaon_list(100000);
		std::vector<Particle> proton_list(100000);
		std::vector<Particle> electron_list(100000);
		charged_mgr=chg_mgr;
		if(!chg_mgr.empty())
		{
			for( std::vector<Mdst_charged>::iterator i = charged_mgr.begin(); i!=charged_mgr.end(); i++)
			{
				Mdst_charged &chg  = *i;
				double e_cut = eid_cut;
				double mu_cut = muid_cut;
				double kpi_cut = KPI_cut;
				double ppi_cut = ppi_cut;
				int id = (int) chg.get_ID();
				eid sel_e(chg);
				Muid_mdst muID(chg);
				double e_id = sel_e.prob(3,1,5);
				double mu_id;
				double atcKPI = selKPI.prob(chg);
				double atcPPI = selPPI.prog(chg);
				if(muID.Chi_2()>0)
				{
					mu_id = muID.Muon_likelihood();
				}
				else
				{
					mu_id = 0;
				}
				if(good_charged(chg,1.e-25,40,30))
				{
					if( (e_id>e_cut)&&(e_id>mu_id) )
					{
						Particle electron (chg, Ptype ( chg.charge()>0?"E+":"E-" ) );
						electron_list.push_back(electron);
					}
					else if ( (mu_id>mu_cut)&&(mu_id>e_id) )
					{
					}
				}

				
			}
		}
		else
		{
			this->empty_list_err(module_name);
		}
		return selected;
	}
	*/
	void MdstRecontable::empty_list_err(std::string module_name)
	{
		std::cout<<"["<<module_name<<"]"<<"given Mdst is empty"<<std::endl;
		return;
	}
	extern "C" Module_descr *mdcl_MdstRecontable()
	{
		MdstRecontable *mdstrecontable = new MdstRecontable;
		Module_descr *dscr = new Module_descr ( "MdstRecontable", mdstrecontable);
		return dscr;
	}
	MdstRecontable::MdstRecontable()
	{
		return;
	}
	void MdstRecontable::init(int *)
	{
		return;
	}
	void MdstRecontable::begin_run(BelleEvent* evptr, int *status)
	{
		eid::init_data();
		IpProfile::begin_run();
		return;
	}
	void MdstRecontable::end_run(BelleEvent* evptr, int *status)
	{
		return;
	}
	void MdstRecontable::hist_def()
	{
		extern BelleTupleManager *BASF_Histogram;
		return;
	}
	void MdstRecontable::event(BelleEvent* evptr, int *status)
	{
		(void)evptr; (void)status;
		return;
	}
	void MdstRecontable::term()
	{
		return;
	}




#if defined(BELLE_NAMESPACE)
}
#endif

