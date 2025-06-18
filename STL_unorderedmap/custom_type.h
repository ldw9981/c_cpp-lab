#pragma once
#include <iostream>
#include <functional>
#include <string>
#include <unordered_map>

// 1) ����� ���� Ű Ÿ��
struct MyKey {
	int         a;
	std::string b;

	//3) == �� ������(unordered_map, unordered_set�� �ʿ�)
	// ����� operator== ����
	bool operator==(MyKey const& rhs) const noexcept {
		return a == rhs.a && b == rhs.b;
	}
};

// 2) std::hash<MyKey> Ư��ȭ
namespace std {
	template<>
	struct hash<MyKey> {
		size_t operator()(MyKey const& k) const noexcept {
			// �⺻ Ÿ�� �ؽø� ����
			size_t h1 = std::hash<int>{}(k.a);
			size_t h2 = std::hash<std::string>{}(k.b);
			// ������ ��Ʈ ���� ���� ����
			return h1 ^ (h2 << 1);
		}
	};
}

int test_customType();