#include <iostream>
#include <unordered_map>
#include <string>
#include "bucket.h"


int test_buecket()
{
	// �⺻ ������ unordered_map (key: std::string, value: int)
	std::unordered_map<std::string, int> m;

	// �⺻ ��Ŷ �� ���
	std::cout << "Default bucket count: " << m.bucket_count() << std::endl;

	// �⺻ �ִ� ������ ���
	std::cout << "Default max load factor: " << m.max_load_factor() << std::endl;


	// ���ڿ� 1000���� ���������� �߰��ϸ� ��Ŷ �� ���
	for (int i = 1; i <= 2000; ++i) {
		std::string key = "key_" + std::to_string(i);
		m.emplace(key, i);

		// ���� ���� �� ��Ŷ �� ���
		std::cout << "After inserting " << i
			<< " elements, bucket count: "
			<< m.bucket_count() << '\n';
	}

	return 0;
}
