#include "Optimizer.h"
#include "CIndividual.h"
#include <cfloat>
#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>

using namespace std;


COptimizer::COptimizer(CLFLnetEvaluator &cEvaluator)
	: c_evaluator(cEvaluator)
{
	random_device c_seed_generator;
	c_rand_engine.seed(c_seed_generator());

	d_current_best_fitness = 0;
	iCurrentIteration = 0;
	iStuckCounter = 0;
	iMigrationCounter = 0;
	
	
}//COptimizer::COptimizer(CEvaluator &cEvaluator)
COptimizer::~COptimizer() {
	for (int i = 0; i < CONST_NUMBER_OF_GENETIC_ALGORYTHMS; i++)
	{
		delete pvec_CGA->at(i);
		delete pvec_Evaluators->at(i);

	}
	delete pvec_CGA;
	delete pvec_Evaluators;
}

void COptimizer::vInitialize()
{
	v_init_cgas();
	
	d_current_best_fitness = -DBL_MAX;
	v_current_best.clear();
}//void COptimizer::vInitialize()

void COptimizer::vRunIteration()
{
	double dPreviousBest;
	std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
	
	if (iMigrationCounter == CONST_NUMBER_OF_ITERATIONS_TO_MIGRATE) {
		v_migrate();
	}
	
	#pragma omp parallel for
		for (int ii = 0; ii < CONST_NUMBER_OF_GENETIC_ALGORYTHMS; ii++)
		{
			pvec_CGA->at(ii)->v_run_one_iteration();
		}

	#pragma omp barrier
	cout << "Iteration: " << iCurrentIteration<<endl;

	v_choose_island_best();
	
	cout <<endl<< "Best: " << d_current_best_fitness << endl;


	
	iMigrationCounter++;

	std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double,std::milli> duration = (endTime - startTime);

	// Output the elapsed time
	std::cout << "Iteration "<<iCurrentIteration++<< " lasted: " << duration.count() << " ms" << std::endl;
	
}//void COptimizer::vRunIteration()

void COptimizer::v_init_cgas() {
	CString sName = c_evaluator.sGetNetName();
	pvec_Evaluators = new vector<CLFLnetEvaluator*>(CONST_NUMBER_OF_GENETIC_ALGORYTHMS);
	pvec_CGA = new vector<CGA*>(CONST_NUMBER_OF_GENETIC_ALGORYTHMS);


	for (int i = 0; i < CONST_NUMBER_OF_GENETIC_ALGORYTHMS; i++)
	{
		CLFLnetEvaluator* pC_cevaluator = new CLFLnetEvaluator();
		pC_cevaluator->bConfigure(sName);
		pvec_Evaluators->at(i) = pC_cevaluator;


		CGA* pC_CGA = new CGA(100, 0.0001, 0.8, *pC_cevaluator, 20, 20, 4);
		pvec_CGA->at(i) = pC_CGA;
	}

}
void COptimizer::v_migrate() {
	cout << "MIGRATION" << endl;


	for (int i = 0; i < CONST_NUMBER_OF_GENETIC_ALGORYTHMS; i++)
	{

		int iRandomAlg = lRand(CONST_NUMBER_OF_GENETIC_ALGORYTHMS);
		int iRandomIndividual = lRand(pvec_CGA->at(iRandomAlg)->get_pC_Population()->size());
		CIndividual* pc_Best = (pvec_CGA->at(i)->pc_get_BestIndividualInCurrentIteration());
		pvec_CGA->at(i)->v_set_best_to_null();
		pvec_CGA->at(iRandomAlg)->get_pC_Population()->push_back(pc_Best);
		pvec_CGA->at(iRandomAlg)->v_inc_PopSize();
		std::vector<CIndividual*>::iterator it = std::find(pvec_CGA->at(i)->get_pC_Population()->begin(), pvec_CGA->at(i)->get_pC_Population()->end(), pc_Best);
		pvec_CGA->at(i)->get_pC_Population()->erase(it);
		pvec_CGA->at(i)->v_dec_PopSize();


	}


	iMigrationCounter = 0;
}
void COptimizer::v_choose_island_best() {
	for (int i = 0; i < CONST_NUMBER_OF_GENETIC_ALGORYTHMS; i++)
	{
		double dChosenGaFitness = pvec_CGA->at(i)->d_get_BestFitness();
		cout << "\t" << "CGA_" << i + 1 << ": " << dChosenGaFitness;

		if (dChosenGaFitness > d_current_best_fitness) {
			d_current_best_fitness = dChosenGaFitness;
			v_current_best = *(pvec_CGA->at(i)->pc_get_Best_Individual()->getGenotype());

		}

	}
}




