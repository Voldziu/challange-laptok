#pragma once
#include "functionalities.h"

vector<int>* pvec_i_rewrite_vector(vector<int>* pvec_i_OriginalVector) {
	vector<int>* pvec_i_Copied = new vector<int>();
	pvec_i_Copied->reserve(pvec_i_OriginalVector->size());
	for (size_t i = 0; i < pvec_i_OriginalVector->size(); i++)
	{
		pvec_i_Copied->push_back( pvec_i_OriginalVector->at(i));
	}
	return pvec_i_Copied;
}