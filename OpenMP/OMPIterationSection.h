#pragma once
#include "OMPBase.h"
// lab5
class IterationSection :
	public OMP
{
	double Sum() final
	{
		double sum = 0;
		switch (thread_count)
		{
		case 1:
			sum = NoSections();
			break;
		case 2:
			sum = TwoSections();
			break;
		case 3:
			sum = ThreeSections();
			break;
		case 4:
			sum = FourSections();
			break;
		default:
			break;
		}
	return sum;
	}
	double NoSections()
	{
		return PartialSum(0, arr_count);
	}
	double TwoSections()
	{
		double sum1 = 0, sum2 = 0;
		int chunk_size = arr_count / 2;
#pragma omp parallel shared(sum1,sum2)
#pragma omp sections  
		{
#pragma omp section
			{
				sum1 = PartialSum(0, chunk_size);
			}
#pragma omp section
			{
				sum2 = PartialSum(chunk_size, chunk_size * 2);
			}
		}
		return sum2 + sum1;
	}
	double ThreeSections()
	{
		double sum[4];
		int chunk_size = arr_count / 3;
#pragma omp parallel shared(sum )
#pragma omp sections 
		{
#pragma omp section
			{
				sum[0] = PartialSum(0, chunk_size);
			}
#pragma omp section
			{
				sum[1] = PartialSum(chunk_size, chunk_size * 2);
			}
#pragma omp section
			{
				sum[2] = PartialSum(chunk_size * 2, chunk_size * 3);
			}
		}
		return sum[0] + sum[1] + sum[2];
	}
	double FourSections()
	{

		double sum[4];
		int chunk_size = arr_count / 4;
#pragma omp parallel shared(sum )
#pragma omp sections 
		{
#pragma omp section
			{
				sum[0] = PartialSum(0, chunk_size);
			}
#pragma omp section
			{
				sum[1] = PartialSum(chunk_size, chunk_size * 2);
			}
#pragma omp section
			{
				sum[2] = PartialSum(chunk_size * 2, chunk_size * 3);
			}
#pragma omp section
			{
				sum[3] = PartialSum(chunk_size * 3, chunk_size * 4);
			}
		}

		return sum[0] + sum[1] + sum[2] + sum[3];
	}
public:
	IterationSection(double* a, double* b, int thread_count, int arr_count) :OMP(a, b, thread_count, arr_count) {}
	IterationSection(int thread_count, int arr_count) :OMP(thread_count, arr_count) {}
	std::string getName() final {
		return typeid(*this).name();
	}
};

