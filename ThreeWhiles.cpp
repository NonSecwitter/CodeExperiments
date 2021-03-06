//The assembly for each of these, on Visual Studio 2013 Pro, is remarkably similair
//The second while loop has the smallest instruction set, the first version is next, and the final version
//has the largest instruction set.

//The test will fill an array with random numbers, search the array for a non-existent item, 
//calculate the time taken to search
//and calculate/display an avearge time for LONG_MAX iterations of the entire process.
#include <stdint.h>
#include <limits.h>
#include <iostream>

uint64_t rdtsc();
void fillArray(int*, const long, int);


int main()
{
	const int ARR_SIZE = 30000;
	int intArr[ARR_SIZE];

	//using -5 for my search item guarantees that linear search will
	//not find a result, and therefore examine every element, because
	//the array is populated using rand(), which returns 0 to RAND_MAX
	int searchItem = -5; 

	int count = 0;
	bool found = false;

	uint64_t t0, t1;
	unsigned long long avg1 = 0, avg2 = 0, avg3 =0;
	
	const long ITERATIONS = std::numeric_limits<int>::max();
	
	for (int i = 0; i < ITERATIONS; i++)
	{
		fillArray(intArr, ARR_SIZE, i);
		//searchItem = intArr[(ARR_SIZE-1)];

		//
		t0 = rdtsc();
		while (count < ARR_SIZE && intArr[count] != searchItem && ++count);
		t1 = rdtsc();
		avg1 += (t1 - t0);

		count = 0;

		//
		t0 = rdtsc();
		while (count < ARR_SIZE && intArr[count] != searchItem)
			count++;
		t1 = rdtsc();
		avg2 += (t1 - t0);

		count = 0;

		//
		t0 = rdtsc();
		while (count < ARR_SIZE && !found)
		{
			if (intArr[count] != searchItem)
				count++;
			else
				found = true;
		}
		t1 = rdtsc();
		avg3 += (t1 - t0);

		//std::cout << "Iteration: " << i << std::endl;
	}

	avg1 /= ITERATIONS;
	avg2 /= ITERATIONS;
	avg3 /= ITERATIONS;

	std::cout << avg1 << std::endl << avg2 << std::endl << avg3 << std::endl;

	std::cin.get();
	return 0;
}


// Cycle counting function borrowed from 
// http://stackoverflow.com/questions/13772567/get-cpu-cycle-count
//  Windows
#ifdef _WIN32

#include <intrin.h>
uint64_t rdtsc(){
	return __rdtsc();
}

//  Linux/GCC
#else

uint64_t rdtsc(){
	unsigned int lo, hi;
	__asm__ __volatile__("rdtsc" : "=a" (lo), "=d" (hi));
	return ((uint64_t)hi << 32) | lo;
}

#endif

void fillArray(int *_arr, const long _size, int _i)
{
	for (int i = 0; i < _size; i++)
	{
		*(_arr + i) = rand();
	}

}
