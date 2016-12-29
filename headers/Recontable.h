/***********************************************
	Recontable.h

Modes : K0S	->	PI+PI-		(K0S_PIPI)
				K0S	->	PI0PI0		(K0S_PI0PI0)
				K0	->	K0S				(K0_K0S)
				K0	->	K0L				(K0_K0L)



 ***********************************************/
#include "belle.h"
#include <cmath>
#include <iostream>
#include <vector>
#include "basf/module.h"
#include "basf/module_descr.h"
#include <panther/panther.h>
#include "mdst/mdst.h"
#include "particle/Particle.h"

#if defined(BELLE_NAMESPACE)
namespace Belle {
#endif
	class Recontable : public Module
	{
		public:
			Recontable();
			~Recontable(){}
			void init(int *);
			void term();
			void disp_stat(const char*) {}
			void hist_def();
			void event(BelleEvent*, int*);
			void begin_run(BelleEvent*, int *);
			void end_run(BelleEvent*, int *);
			void other(int*, BelleEvent*, int*) {}
			/* B meson mode */
			std::vector<Particle> B0_K0eeee (std::vector<Particle> k0_list, std::vector<Particle> electron_list);
			/* K meson mode */
			std::vector<Particle> K0_K0S (std::vector<Particle> k0s_list);
			std::vector<Particle> K0_K0L (std::vector<Particle> k0l_list);
			std::vector<Particle> K0S_PIPI (std::vector<Particle> chg_pion);
			std::vector<Particle> K0S_PI0PI0 (std::vector<Particle> pizero_list);

			void empty_list_err(std::string module_name);
	};
	extern "C" Module_descr *mdcl_Recontable() {

		Recontable *recontable = new Recontable;
		Module_descr *dscr = new Module_descr( "Recontable", recontable );
		return dscr;
	}
	Recontable::Recontable(){
		return;
	}
	void Recontable::init(int *){
		return;
	}
	void Recontable::begin_run(BelleEvent* evptr, int *status)
	{
		return;
	}
	void Recontable::end_run(BelleEvent* evptr, int *status)
	{
		(void)evptr; (void)status;
		return;
	}
	void Recontable::hist_def()
	{
		extern BelleTupleManager *BASF_Histogram;
		//BelleTupleManager *tm = BASF_Histogram;
		return;
	}
	void Recontable::event(BelleEvent* evptr, int* status)
	{
		(void)evptr; (void)status;
		return;
	}
	void Recontable::term()
	{
		return;
	}
	/* Reconstruct B0->K0eeee */
	std::vector<Particle> Recontable::B0_K0eeee(std::vector<Particle> k0_list, std::vector<Particle> electron_list)
	{
		std::string module_name = "Recon B0_K0eeee";
		std::vector<Particle> b0_list(100000);
		b0_list.clear();
		if((!k0_list.empty())&&(!electron_list.empty()))
		{
			std::vector<Particle> __k0_list = k0_list;
			std::vector<Particle> __electron_list = electron_list;
			for (std::vector<Particle>::iterator k0 = __k0_list.begin(); k0!=__k0_list.end(); k0++)
			{
				for (std::vector<Particle>::iterator e1=__electron_list.begin(); e1!=__electron_list.end() ; e1++)
				{
					for (std::vector<Particle>::iterator e2=e1;e2!=__electron_list.end(); e2++ )
					{
						for(std::vector<Particle>::iterator e3=e2; e3!=__electron_list.end(); e3++)
						{
							for(std::vector<Particle>::iterator e4=e3; e4!=__electron_list.end(); e4++)
							{
								if((e1!=e2)&&(e2!=e3)&&(e3!=e4))
								{
									Particle &K0 = *k0;
									Particle &electron_1 = *e1;
									Particle &electron_2 = *e2;
									Particle &electron_3 = *e3;
									Particle &electron_4 = *e4;
									HepLorentzVector p_B;
									HepLorentzVector p_e12;
									HepLorentzVector p_e34;
									HepLorentzVector p_electron;
									double m_K0 = K0.p().mag();
									double m_e1 = electron_1.p().mag();
									double m_e2 = electron_2.p().mag();
									double m_e3 = electron_3.p().mag();
									double m_e4 = electron_4.p().mag();
									if((!isnan(m_K0))&&(!isnan(m_e1))&&(!isnan(m_e2))&&(!isnan(m_e3))&&(!isnan(m_e4)))
									{
										double charge12 = electron_1.charge() + electron_2.charge();
										double charge34 = electron_3.charge() + electron_4.charge();
										double netcharge = charge12+charge34;
										p_e12 = electron_1.p() + electron_2.p();
										p_e34 = electron_3.p() + electron_4.p();
										p_electron = p_e12 + p_e34;
										p_B = p_electron + K0.p();
										if( (netcharge == 0)&&(!isnan(p_B.mag())) )
										{
											Particle B0 ( p_B , Ptype("B0"));
											B0.relation().append(K0);
											B0.relation().append(electron_1);
											B0.relation().append(electron_2);
											B0.relation().append(electron_3);
											B0.relation().append(electron_4);
											b0_list.push_back(B0);
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			this->empty_list_err(module_name);
		}
		return b0_list;
	}
	/* Reconstruct K0->Ks (K0 anti-K0)*/ 
	std::vector<Particle> Recontable::K0_K0S(std::vector<Particle> k0s_list)
	{
		std::string module_name = "Recon K0_K0S";
		std::vector<Particle> k0_list(100000);
		k0_list.clear();
		if(!k0s_list.empty())
		{
			std::vector<Particle> ks_list = k0s_list;
			for( std::vector<Particle>::iterator ks = ks_list.begin(); ks!=ks_list.end();ks++)
			{
				Particle &KS = *ks;
				HepLorentzVector p_KS = KS.p();
				double m = p_KS.mag();
				if(!isnan(m))
				{
					Particle K0 (p_KS, Ptype("K0"));
					K0.relation().append(KS);
					k0_list.push_back(K0);
				}
			}
		}
		else
		{
			this->empty_list_err(module_name);
		}
		return k0_list;
	}
	/* Reconstruct K0->KL (K0 anti-K0)*/ 
	std::vector<Particle> Recontable::K0_K0L(std::vector<Particle> k0l_list)
	{
		std::string module_name = "Recon K0_K0L";
		std::vector<Particle> k0_list(100000);
		k0_list.clear();
		if(!k0l_list.empty())
		{
			std::vector<Particle> kl_list = k0l_list;
			for( std::vector<Particle>::iterator kl = kl_list.begin(); kl!=kl_list.end();kl++)
			{
				Particle &KL = *kl;
				HepLorentzVector p_KL = KL.p();
				double m = p_KL.mag();
				if(!isnan(m))
				{
					Particle K0 (p_KL, Ptype("K0"));
					K0.relation().append(KL);
					k0_list.push_back(K0);
				}
			}
		}
		else
		{
			this->empty_list_err(module_name);
		}
		return k0_list;
	}

	/* Reconstruct Ks->pi+ pi- */
	std::vector<Particle> Recontable::K0S_PIPI(std::vector<Particle> chg_pion)
	{
		std::string module_name = "Recon K0S_PI+PI-";
		std::vector<Particle> ks_list(100000);
		ks_list.clear();
		if(!chg_pion.empty())
		{
			std::vector<Particle> pion_list=chg_pion;
			for ( std::vector<Particle>::iterator pi1 = pion_list.begin() ; pi1!=pion_list.end(); pi1++)
			{
				for ( std::vector<Particle>::iterator pi2 = pi1 ; pi2!=pion_list.end(); pi2++)
				{
					if(pi1!=pi2)
					{
						Particle &pion_1 = *pi1;
						Particle &pion_2 = *pi2;
						double pi1_m = pion_1.p().mag();
						double pi2_m = pion_2.p().mag();
						if((pion_1.charge()+pion_2.charge()==0)&&(!isnan(pi1_m))&&(!isnan(pi2_m)))
						{
							HepLorentzVector p_Ks = pion_1.p()+pion_2.p();
							double Ks_m = p_Ks.mag();
							if(!isnan(Ks_m))
							{
								Particle Ks(p_Ks, Ptype("K0S"));
								Ks.relation().append(pion_1);
								Ks.relation().append(pion_2);
								ks_list.push_back(Ks);
							}
						}
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
	std::vector<Particle> Recontable::K0S_PI0PI0(std::vector<Particle> pizero_list)
	{
		std::string module_name = "Recon K0S_PI0PI0";
		std::vector<Particle> ks_list(100000);
		ks_list.clear();
		if(!pizero_list.empty())
		{
			std::vector<Particle> pi0_list=pizero_list;
			for( std::vector <Particle>::iterator pi1 = pi0_list.begin(); pi1!=pi0_list.end(); pi1++ )
			{
				Particle &pi0_1 = *pi1;
				for (std::vector <Particle>::iterator pi2 = pi1; pi2!=pi0_list.end();     pi2++)
				{
					Particle &pi0_2 = *pi2;
					if(pi1!=pi2)
					{
						HepLorentzVector p_Ks = pi0_1.p()+pi0_2.p();
						double m = p_Ks.mag();
						if(!isnan(m))
						{
							Particle Ks (p_Ks, Ptype("K0S"));
							Ks.relation().append(pi0_1);
							Ks.relation().append(pi0_2);
							ks_list.push_back(Ks);
						}
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


	void Recontable::empty_list_err(std::string module_name)
	{
		std::cout<<"["<<module_name<<"]"<<"Particle list is empty"<<std::endl;
	}

#if defined(BELLE_NAMESPACE)
} // namespace Belle
#endif

