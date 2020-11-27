#pragma once
#include "OMPBase.h"
#include "omp.h"
#include <algorithm>
#include <iostream>
#include <ctime>
#include <ostream>
#include <chrono>
using namespace std;
class OMP
{
protected:

	virtual std::string getName() {
		return typeid(*this).name();
	}
	double* a, * b;
	int thread_count, arr_count;

	double* ArrGen()
	{
		double* arr = new double[arr_count];
		for (size_t i = 0; i < arr_count; i++)
		{
			arr[i] = rand() % 20 - 10;
		}
		return arr;
	}

	virtual double Sum() { return .0; }


	double PartialSum(int left, int right)
	{
		double chunk_sum = 0;
		for (size_t i = left; i < right; i++)
		{
			chunk_sum += max(a[i], b[i]);
		}
		return chunk_sum;
	}


public:
	~OMP()
	{
		delete(a);
		delete(b);
	}

	OMP(double* a, double* b, int thread_count, int arr_count): 
		arr_count(arr_count),
		thread_count(thread_count > arr_count ? arr_count : thread_count),
		a(a),
		b(b)
	{
	}

	OMP(int thread_count, int arr_count):
		arr_count(arr_count),
		thread_count(thread_count > arr_count ? arr_count : thread_count)
	{
		a = ArrGen();
		b = ArrGen();
	}
	void Run()
	{
		auto begin = clock();
		Sum();
		auto end = clock();
		cout << getName() + ";"
			<<thread_count<< ";" <<arr_count
			<< ";" << end - begin << "\n";
	}

	void RunWithHrono()
	{
		std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
		start = std::chrono::high_resolution_clock::now();
		Sum();
		stop = std::chrono::high_resolution_clock::now();
 
		cout << getName() + ";"
			<< thread_count << ";" << arr_count
			<< ";" << std::chrono::duration_cast<chrono::milliseconds> (stop - start).count() << "\n";
	}

	void RunTest()
	{
		int size = 5;
		a = new double[size] {1, -2, 3, -4, 5};
		b = new double[size] {-1, 2, -3, 4, -5};
		cout <<"test " + getName() + ":\t" << Sum() <<"\texprcted:\t15\n";
	}

};

