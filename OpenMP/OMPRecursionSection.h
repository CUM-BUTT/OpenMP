#pragma once
#include "OMPBase.h"
// lab5
class RecursionSection :
    public OMP
{
	int section_size;
	double Sum(int left, int right)
	{
		double sum;
		int delta = right - left;
		if (delta > section_size)
		{
			double sum1 = 0, sum2 = 0;
			#pragma omp sections private(sum1,sum2)
			{
				#pragma omp section
				{
					sum1 = Sum(left, left + delta / 2);
				}
				#pragma omp section
				{
					sum2 = Sum(left + delta / 2 + 1, right);
				}		
			}
			sum = sum1 + sum2;
		}
		else
		{
			sum = 0;
			for (int i = left; i <= right; i++)
			{
				sum += max(a[i], b[i]);
			}
		}
		return sum;
	}
	double Sum() final
	{
		this->section_size = arr_count * 0.2;
		return Sum(0, arr_count - 1);
	}
public:
	RecursionSection(double* a, double* b, int thread_count, int arr_count) :OMP(a, b, thread_count, arr_count){	}
	RecursionSection(int thread_count, int arr_count) :OMP(thread_count, arr_count) {}
	std::string getName() final {
		return typeid(*this).name();
	}
};

