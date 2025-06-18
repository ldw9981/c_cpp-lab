#include "iterate_chain.h"
#include <iostream>
#include <unordered_map>
#include <string>

int test_interateChain()
{
	// 0) unordered_multimap 키가 값은 데이터 추가
	std::unordered_multimap<std::string, int> m = {
		{"banana",      2},
		{"banana",      3},
		{"banana",      6},
		{"cherry",      3},
		{"date",        4},
		{"elderberry",  5}
	};

	// 1)“모든” 버킷을 전부 순회 
	std::cout << "\nAll buckets:\n";
	for (size_t b = 0; b < m.bucket_count(); ++b) {
		std::cout << " bucket #" << b << ":\n";
		for (auto it = m.begin(b); it != m.end(b); ++it) {
			std::cout
				<< "    " << it->first
				<< " => " << it->second << "\n";
		}
	}

	// 2) 단일 요소 검색	
	std::string key = "banana";
	std::cout << "\nFind " << key << "\n";
	auto it = m.find(key);
	if (it != m.end()) {
		std::cout << "Found \"" << it->first << "\" => " << it->second << "\n";
	}
	else {
		std::cout << "Key \"" << key << "\" not found\n";
	}
	// 3) 같은 버킷(chain) 안의 모든 요소 열람
	size_t idx = m.bucket(key);
	std::cout << "\nElements in bucket #" << idx
		<< " (same bucket as \"" << key << "\"):\n";

	for (auto local_it = m.begin(idx); local_it != m.end(idx); ++local_it) {
		std::cout << "  " << local_it->first
			<< " => " << local_it->second << "\n";
	}

	// 3) 해당 키의 값만 보기
	std::cout << "\nFind Element with Key " << key << "\n";
	auto range = m.equal_range("banana");
	for (auto it = range.first; it != range.second; ++it) {
		std::cout << it->first << " => " << it->second << "\n";
	}

	

	return 0;
}
