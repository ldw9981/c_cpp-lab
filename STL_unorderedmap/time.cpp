#include <windows.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <set>
#include "time.h"
#include <Functional>
double getFrequency()
{
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	return static_cast<double>(freq.QuadPart);
}

LARGE_INTEGER now()
{
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	return t;
}
