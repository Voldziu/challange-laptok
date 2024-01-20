#pragma once
#include <vector>
#include "Evaluator.h"

class CIndividual
{
public:
	CIndividual();
	CIndividual(std::vector<int>* pvec_i_genotype);
	CIndividual(const CIndividual& COther);
	~CIndividual();


	double evaluate(CLFLnetEvaluator& Cevaluator);

	void v_print_genotype();
	void v_mutate_genotype(CLFLnetEvaluator& Cevaluator,double dMutationProb,int iMutationDeviation);

	double getFitness();
	std::vector<int>* getGenotype();
private:
	std::vector<int>* pvec_i_Genotype;
	double dFitness;
	bool bIsEvaluated;
};

