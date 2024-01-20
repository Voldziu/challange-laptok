
#include "CIndividual.h" 
#include "functionalities.h"


CIndividual::CIndividual() {

	dFitness = -DBL_MAX;
	bIsEvaluated = false;
	pvec_i_Genotype = nullptr;

}
CIndividual::CIndividual(std::vector<int>* pvec_i_genotype) {
	
	dFitness = -DBL_MAX;
	bIsEvaluated = false;
	pvec_i_Genotype = pvec_i_genotype;
	

}
CIndividual::CIndividual(const CIndividual& COther)
{
	dFitness = COther.dFitness;
	bIsEvaluated = COther.bIsEvaluated;
	pvec_i_Genotype = pvec_i_rewrite_vector(COther.pvec_i_Genotype);
}


CIndividual::~CIndividual()
{
	delete pvec_i_Genotype;
}


double CIndividual::evaluate(CLFLnetEvaluator& CEvaluator) {
	if (!bIsEvaluated) {
		
		dFitness = CEvaluator.dEvaluate(pvec_i_Genotype);
		bIsEvaluated = true;
	}
	return dFitness;

}

void CIndividual::v_print_genotype() {
	for (int i = 0; i < pvec_i_Genotype->size(); i++)
	{
		std::cout << pvec_i_Genotype->at(i) << " ";
	}
	std::cout << std::endl;
}

double CIndividual::getFitness() {
	return dFitness;
}
std::vector<int>* CIndividual::getGenotype() {
	return pvec_i_Genotype;
}

void CIndividual::v_mutate_genotype(CLFLnetEvaluator& Cevaluator,double dMutationProb,int iMutationDeviation) {
	int iGenSize = pvec_i_Genotype->size();
	
		for (int i = 0; i < iGenSize; i++)
		{
			if (dRand() < dMutationProb) {
				pvec_i_Genotype->at(i) = lRand(Cevaluator.iGetNumberOfValues(i));

			}

		}

	}
