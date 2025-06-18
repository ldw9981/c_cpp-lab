#include <windows.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <set>
#include <iomanip>
#include "time.h"
#include "compare_vector.h"




int test_compareString()
{
	std::cout << __FUNCDNAME__ << "\n";
	int size = 1000;
	// 측정할 문자열 size개
	std::vector<std::string> data;
	for (int i = 0; i < size; ++i) {
		data.emplace_back("string_" + std::to_string(i));
	}

	double freq = getFrequency();

	// --- std::vector 측정 ---
	std::vector<std::string> vec;
	vec.reserve(size);
	LARGE_INTEGER t1 = now();
	for (auto& s : data) vec.push_back(s);
	LARGE_INTEGER t2 = now();
	double vec_insert_ms = (t2.QuadPart - t1.QuadPart) * 1000.0 / freq;

	t1 = now();
	for (auto& s : data) {
		if (std::find(vec.begin(), vec.end(), s) == vec.end())
			std::cerr << "Vector search failed for " << s << "\n";
	}
	t2 = now();
	double vec_search_ms = (t2.QuadPart - t1.QuadPart) * 1000.0 / freq;

	// --- std::unordered_set 측정 ---
	std::unordered_set<std::string> uset;
	uset.reserve(size);
	t1 = now();
	for (auto& s : data) uset.insert(s);
	t2 = now();
	double uset_insert_ms = (t2.QuadPart - t1.QuadPart) * 1000.0 / freq;

	t1 = now();
	for (auto& s : data) {
		if (uset.find(s) == uset.end())
			std::cerr << "Unordered_set search failed for " << s << "\n";
	}
	t2 = now();
	double uset_search_ms = (t2.QuadPart - t1.QuadPart) * 1000.0 / freq;

	// --- std::set 측정 ---
	std::set<std::string> oset;
	t1 = now();
	for (auto& s : data) oset.insert(s);
	t2 = now();
	double oset_insert_ms = (t2.QuadPart - t1.QuadPart) * 1000.0 / freq;

	t1 = now();
	for (auto& s : data) {
		if (oset.find(s) == oset.end())
			std::cerr << "Set search failed for " << s << "\n";
	}
	t2 = now();
	double oset_search_ms = (t2.QuadPart - t1.QuadPart) * 1000.0 / freq;

	// 결과 출력
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "std::vector       insert: " << vec_insert_ms << " ms, search: " << vec_search_ms << " ms\n";
	std::cout << "std::unordered_set insert: " << uset_insert_ms << " ms, search: " << uset_search_ms << " ms\n";
	std::cout << "Size:" << uset.size() << " BucketCount:" << uset.bucket_count() << " LoadFactor:" << uset.load_factor() << "\n";
	std::cout << "std::set           insert: " << oset_insert_ms << " ms, search: " << oset_search_ms << " ms\n";

	return 0;
}


int test_compareInt()
{
	std::cout << __FUNCDNAME__ << "\n";
	int size = 1000;
	// 측정할 문자열 
	std::vector<int> data;
	for (int i = 0; i < size; ++i) {
		data.emplace_back(i);
	}

	double freq = getFrequency();

	// --- std::vector 측정 ---
	std::vector<int> vec;
	vec.reserve(size);
	LARGE_INTEGER t1 = now();
	for (auto& s : data) vec.push_back(s);
	LARGE_INTEGER t2 = now();
	double vec_insert_ms = (t2.QuadPart - t1.QuadPart) * 1000.0 / freq;

	t1 = now();
	for (auto& s : data) {
		if (std::find(vec.begin(), vec.end(), s) == vec.end())
			std::cerr << "Vector search failed for " << s << "\n";
	}
	t2 = now();
	double vec_search_ms = (t2.QuadPart - t1.QuadPart) * 1000.0 / freq;

	// --- std::unordered_set 측정 ---
	std::unordered_set<int> uset;
	uset.reserve(size);
	t1 = now();
	for (auto& s : data) uset.insert(s);
	t2 = now();
	double uset_insert_ms = (t2.QuadPart - t1.QuadPart) * 1000.0 / freq;

	t1 = now();
	for (auto& s : data) {
		if (uset.find(s) == uset.end())
			std::cerr << "Unordered_set search failed for " << s << "\n";
	}
	t2 = now();
	double uset_search_ms = (t2.QuadPart - t1.QuadPart) * 1000.0 / freq;

	// --- std::set 측정 ---
	std::set<int> oset;
	t1 = now();
	for (auto& s : data) oset.insert(s);
	t2 = now();
	double oset_insert_ms = (t2.QuadPart - t1.QuadPart) * 1000.0 / freq;

	t1 = now();
	for (auto& s : data) {
		if (oset.find(s) == oset.end())
			std::cerr << "Set search failed for " << s << "\n";
	}
	t2 = now();
	double oset_search_ms = (t2.QuadPart - t1.QuadPart) * 1000.0 / freq;

	// 결과 출력
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "std::vector       insert: " << vec_insert_ms << " ms, search: " << vec_search_ms << " ms\n";
	std::cout << "std::unordered_set insert: " << uset_insert_ms << " ms, search: " << uset_search_ms << " ms\n";
	std::cout << "Size:" << uset.size() << " BucketCount:" << uset.bucket_count() << " LoadFactor:" << uset.load_factor() << "\n";
	std::cout << "std::set           insert: " << oset_insert_ms << " ms, search: " << oset_search_ms << " ms\n";

	return 0;
}