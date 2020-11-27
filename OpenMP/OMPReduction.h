#pragma once
#include "omp.h"
#include <algorithm>
#include <iostream>
#include <ctime>
#include "OMPBase.h"
using namespace std;

// lab3
class Reduction :public OMP
{
	double Sum() final
	{
		auto a = this->a, b = this->b;
		double sum = 0;
		int i = 0;
		#pragma omp parallel  shared(a,b) private(i) reduction (+: sum) num_threads(thread_count) 
		{
			# pragma omp for //shedule(dynamic)
			for (i = 0; i < arr_count; i++)
			{
				sum += max(a[i], b[i]);
			}
		}
		return sum;
	}
public:
	Reduction(double* a, double* b, int thread_count, int arr_count) :OMP(a, b, thread_count, arr_count) {	}
	Reduction(int thread_count, int arr_count) :OMP(thread_count, arr_count) {	}
	std::string getName() final {
		return typeid(*this).name();
	}
};
