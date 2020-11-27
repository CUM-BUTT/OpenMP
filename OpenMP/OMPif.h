#include <omp.h>
#include <stdio.h>
#include <ctime>
#pragma once
class OMPif
{
	
	int current_size = 100;
	int limit = 10;
	float** a;

	void Sum()
	{
			int i, j;
			auto a = this->a;
			float sum;
			#pragma omp parallel shared(a) if (current_size>limit)
			{
				#pragma omp for private(i,j,sum)
				for (i = 0; i < current_size; i++)
				{
					sum = 0;
					for (j = 0; j < current_size; j++)
						sum += a[i][j];
					//printf("Сумма элементов строки %d равна %f\n", i, sum);
				}
			} /* Завершение параллельного фрагмента */
	}
public:
	int max_size = 100;

	OMPif(int max_size = 1000):
		max_size(max_size)
	{
		a = new float* [max_size];
		for (int i = 0; i < max_size; i++)
		{
			a[i] = new float[max_size];
			for (int j = 0; j < max_size; j++)
				a[i][j] = i + j;
		}

	}

	void Run(int size = 100,
		int limit = 10)
	{
		this->limit = limit;
		this->current_size = size;
		auto start = clock();
		Sum();
		auto fin = clock();
		auto time = fin - start;
		printf("%d; %d; %d\n", limit, size, time);
	}
	~OMPif()
	{
		delete(a);
	}
};

