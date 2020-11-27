#pragma once
#include "OMPBase.h"
class Critical :
    public OMP
{
	double Sum()final
	{
		int t = 0;
		int chunk_size = arr_count / thread_count;
		double total_sum = 0;

		#pragma omp parallel num_threads(thread_count) shared(total_sum) private(t) 
		#pragma omp for
		for (t = 0; t < thread_count; t++)
		{
			int left = t * chunk_size;
			int right = (t + 1) * chunk_size;
			right = right > arr_count ? arr_count : right;
			auto chunk_sum = PartialSum(left, right);

			#pragma omp critical
			total_sum += chunk_sum;
		}
		return total_sum;
	}
public:
	Critical(double* a, double* b, int thread_count, int arr_count) :OMP(a, b, thread_count, arr_count) {	}
	Critical(int thread_count, int arr_count) :OMP(thread_count, arr_count) {	}

	std::string getName() final {
		return typeid(*this).name();
	}
};

