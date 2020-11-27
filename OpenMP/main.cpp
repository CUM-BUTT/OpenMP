#include <iostream>
#include "OMPBase.h"
#include "OMPAtomic.h"
#include "OMPIterationSection.h"
#include "OMPLock.h"
#include "OMPBarrier.h"
#include "OMPRecursionSection.h"
#include "OMPReduction.h"
#include "math.h"
#include "OMPif.h"
#include "Critical.h"
using namespace std;

void Run3_6()
{
	cout << "class;"
		<< "thread_count" << ";" << "arr_count"
		<< ";" << "time" << "\n";
	for (size_t t = 1; t < 5; t++)
	{
		int c = 10000000;
		//for (size_t c = 1000; c < pow(10, 8); c *= 10)
		{
			//Critical(t, c).RunWithHrono(); //4 +
			//Atomic(t, c).RunWithHrono(); //4 +
			//IterationSection(t, c).RunWithHrono();//5 +
			Lock(t, c).RunWithHrono();//6 +
			Barrier(t, c).RunWithHrono();//6 +
			//Reduction(t, c).RunWithHrono();//3 +
		}
	}
}


double PartialSum(int left, int right, int*a,int*b)
{
	double chunk_sum = 0;
	for (size_t i = left; i < right; i++)
	{
		chunk_sum += max(a[i], b[i]);
	}
	return chunk_sum;
}
 
double Lena(int *a, int *b, int array_count)
{
	static int thread_count = 2;
	int t, left,right;
	int chunk_size = array_count / thread_count;
	double total_sum = 0, partial_sum = 0;

//#pragma omp parallel num_threads(thread_count) shared(total_sum) private(t, partial_sum, left, right) 
	for (t = 0; t < thread_count; t++)
	{
		left = t * chunk_size;
		right = (t + 1) * chunk_size;
		right = right > array_count ? array_count : right;
		partial_sum = PartialSum(left, right,a,b);
		#pragma omp barrier
		if (1 == omp_get_thread_num())
		{
			total_sum += partial_sum;
		}
		#pragma omp barrier
		if (0 == omp_get_thread_num())
		{
			total_sum += partial_sum;
		}
	}
 

	return total_sum;
}
void RunLena()
{
	auto b = new int[10]{ 1,2,3,4,5,6,7,8,9,10 },
		a = new int[10]{ 0,0,0,0,0,0,0,0,0,0 };

	auto sum = Lena(a, b, 10);
	cout << sum;

}
 

int main()
{
	RunLena();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
