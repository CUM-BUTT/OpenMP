#pragma once
#include "OMPBase.h"
class Barrier :
	virtual public OMP
{
	double Sum()final
	{
		int t = 0;
		int chunk_size = arr_count / thread_count;
		auto chunk_sums = new double[thread_count];
		double total_sum = 0;
		double chunk_sum = 0;
		
		#pragma omp parallel num_threads(thread_count) shared(total_sum) private(t) 
		#pragma omp for 
		for (t = 0; t < thread_count; t++)
		{
			int left = t * chunk_size;
			int right = (t + 1) * chunk_size;
			right = right > arr_count ? arr_count : right;
			chunk_sums[t] = PartialSum(left, right);
		}

		#pragma omp barrier  
		#pragma omp master
		{
			for (size_t t = 0; t < thread_count; t++)
			{
				total_sum += chunk_sums[t];
			}
		}

		return total_sum;
	}
public:
	Barrier(double* a, double* b, int thread_count, int arr_count) :OMP(a, b, thread_count, arr_count) {	}
	Barrier(int thread_count, int arr_count) :OMP(thread_count, arr_count) {	}
	std::string getName() final {
		return typeid(*this).name();
	}
};

