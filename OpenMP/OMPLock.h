#pragma once
#include "OMPBase.h"

class Lock :
    public OMP
{
	double Sum() final
	{
		double chunk_sum = 0, total_sum = 0,left, right;
		int chunk_size = arr_count / thread_count,
			t = 1, i = 0;
		auto a = this->a, b = this->b;

		omp_lock_t lock;
		omp_init_lock(&lock);

		#pragma omp parallel private(t,left, right) shared(a,b,total_sum) num_threads(thread_count)
		{
			#pragma omp for 
			for (t = 1; t <= thread_count; t++)
			{
				int left = t * chunk_size;
				int right = (t + 1) * chunk_size;
				right = right > arr_count ? arr_count : right;
				auto chunk_sum = PartialSum(left, right);

				omp_set_lock(&lock);
				total_sum += chunk_sum;
				omp_unset_lock(&lock);
			}
		}
		omp_destroy_lock(&lock);
		return total_sum;
	}
public:
	Lock(double* a, double* b, int thread_count, int arr_count) :OMP(a, b, thread_count, arr_count) {	}
	Lock(int thread_count, int arr_count) :OMP(thread_count, arr_count) {	}
	std::string getName() final {
		return typeid(*this).name();
	}
};

