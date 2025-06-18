#include <iostream>
#include <unordered_map>
#include <string>
#include "bucket.h"


int test_buecket()
{
	// 기본 생성된 unordered_map (key: std::string, value: int)
	std::unordered_map<std::string, int> m;

	// 기본 버킷 수 출력
	std::cout << "Default bucket count: " << m.bucket_count() << std::endl;

	// 기본 최대 부하율 출력
	std::cout << "Default max load factor: " << m.max_load_factor() << std::endl;


	// 문자열 1000개를 순차적으로 추가하며 버킷 수 출력
	for (int i = 1; i <= 2000; ++i) {
		std::string key = "key_" + std::to_string(i);
		m.emplace(key, i);

		// 현재 삽입 후 버킷 수 출력
		std::cout << "After inserting " << i
			<< " elements, bucket count: "
			<< m.bucket_count() << '\n';
	}

	return 0;
}
