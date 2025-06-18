#pragma once
#include <iostream>
#include <functional>
#include <string>
#include <unordered_map>

// 1) 사용자 정의 키 타입
struct MyKey {
	int         a;
	std::string b;

	//3) == 비교 연산자(unordered_map, unordered_set이 필요)
	// 멤버로 operator== 정의
	bool operator==(MyKey const& rhs) const noexcept {
		return a == rhs.a && b == rhs.b;
	}
};

// 2) std::hash<MyKey> 특수화
namespace std {
	template<>
	struct hash<MyKey> {
		size_t operator()(MyKey const& k) const noexcept {
			// 기본 타입 해시를 조합
			size_t h1 = std::hash<int>{}(k.a);
			size_t h2 = std::hash<std::string>{}(k.b);
			// 간단한 비트 연산 조합 예시
			return h1 ^ (h2 << 1);
		}
	};
}

int test_customType();