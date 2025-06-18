#include <iostream>
#include <functional>  // std::hash
#include "hash_function.h"

int test_hash_function()
{
	// ������
	int i = 42;
	std::size_t hi = std::hash<int>{}(i);
	std::cout << "hash<int>(42) = " << hi << "\n";

	long l = 1234567890L;
	std::size_t hl = std::hash<long>{}(l);
	std::cout << "hash<long>(1234567890L) = " << hl << "\n";

	// �ε��Ҽ�����
	float f = 3.14f;
	std::size_t hf = std::hash<float>{}(f);
	std::cout << "hash<float>(3.14f) = " << hf << "\n";

	double d = 2.718281828;
	std::size_t hd = std::hash<double>{}(d);
	std::cout << "hash<double>(2.718281828) = " << hd << "\n";

	// ��������
	int* p = &i;
	std::size_t hp = std::hash<int*>{}(p);
	std::cout << "hash<int*>(p) = " << hp << "\n";

	// ���ڿ���
	std::string s = "hello";
	std::size_t hs = std::hash<std::string>{}(s);
	std::cout << "hash<string>(\"hello\") = " << hs << "\n";

	// bool��
	bool b = true;
	std::size_t hb = std::hash<bool>{}(b);
	std::cout << "hash<bool>(true) = " << hb << "\n";

	// ����� ���� Ÿ���� Ư��ȭ �ʿ�
	// struct MyKey { int x,y; };
	// namespace std { template<> struct hash<MyKey> { ... }; }

	return 0;
}
