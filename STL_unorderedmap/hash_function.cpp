#include <iostream>
#include <functional>  // std::hash
#include "hash_function.h"

int test_hash_function()
{
	// 정수형
	int i = 42;
	std::size_t hi = std::hash<int>{}(i);
	std::cout << "hash<int>(42) = " << hi << "\n";

	long l = 1234567890L;
	std::size_t hl = std::hash<long>{}(l);
	std::cout << "hash<long>(1234567890L) = " << hl << "\n";

	// 부동소수점형
	float f = 3.14f;
	std::size_t hf = std::hash<float>{}(f);
	std::cout << "hash<float>(3.14f) = " << hf << "\n";

	double d = 2.718281828;
	std::size_t hd = std::hash<double>{}(d);
	std::cout << "hash<double>(2.718281828) = " << hd << "\n";

	// 포인터형
	int* p = &i;
	std::size_t hp = std::hash<int*>{}(p);
	std::cout << "hash<int*>(p) = " << hp << "\n";

	// 문자열형
	std::string s = "hello";
	std::size_t hs = std::hash<std::string>{}(s);
	std::cout << "hash<string>(\"hello\") = " << hs << "\n";

	// bool형
	bool b = true;
	std::size_t hb = std::hash<bool>{}(b);
	std::cout << "hash<bool>(true) = " << hb << "\n";

	// 사용자 정의 타입은 특수화 필요
	// struct MyKey { int x,y; };
	// namespace std { template<> struct hash<MyKey> { ... }; }

	return 0;
}
