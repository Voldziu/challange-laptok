#pragma once

#include "Evaluator.h"
#include "MyConstants.h"
#include "CGA.h"
#include <random>
#include <vector>

using namespace std;

class COptimizer
{
public:
	COptimizer(CLFLnetEvaluator &cEvaluator);
	~COptimizer();

	void vInitialize();
	void vRunIteration();

	vector<int> *pvGetCurrentBest() { return &v_current_best; }

private:
	vector<CGA*>* pvec_CGA;
	vector<CLFLnetEvaluator*>* pvec_Evaluators;
	int iCurrentIteration;
	int iStuckCounter;
	int iMigrationCounter;
	void v_init_cgas();
	void v_migrate();
	void v_choose_island_best();

	CLFLnetEvaluator &c_evaluator;

	double d_current_best_fitness;
	vector<int> v_current_best;

	mt19937 c_rand_engine;
};//class COptimizer