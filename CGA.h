#pragma once
#include "CIndividual.h"
#include "functionalities.h"
#include "MyConstants.h"




	class CGA
	{
	public:
		CGA(int iPopSize, double dMutationProb, double dCrossoverProb, CLFLnetEvaluator& Cevaluator, int iMutationDeviation, int iCrossoverPercent,int iTournamentSize);
		~CGA();
		void run(int iIterations);
		void v_run_one_iteration();
		void v_grande_mutation();
		double d_get_BestFitness() { return dBestFitness; }
		CIndividual* pc_get_Best_Individual() { return pC_BestIndividual; }
		CIndividual* pc_get_BestIndividualInCurrentIteration() { return pC_BestIndividualInCurrentIteration; }

		std::vector<CIndividual*>* get_pC_Population() {return pvec_pC_Population;}
		void v_dec_PopSize() { iPopSize--; }
		void v_inc_PopSize() { iPopSize++; }
		void v_set_best_to_null() { pC_BestIndividual = NULL; }

	private:
		int iPopSize;
		int iTournamentSize;
		std::vector<CIndividual*>* pvec_pC_Population;
		CIndividual* pC_BestIndividual;
		CIndividual* pC_BestIndividualInCurrentIteration;
		double dMutationProb;
		double dMatingProb;
		double dBestFitness;
		CLFLnetEvaluator& CEvaluator;
		int iMutationDeviation;
		int iCrossoverPercent;
		CIndividual* pC_make_tournament(int iShots);
		void v_make_children_by_crossover(CIndividual* CParent1, CIndividual* CParent2, CIndividual** Child1, CIndividual** Child2);

		void v_initialize_Population();
		void v_eval_Population();
		
		
		



	};


