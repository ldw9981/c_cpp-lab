#include "custom_type.h"


int test_customType()
{
	MyKey k1{ 42, "foo" };
	MyKey k2{ 7, "bar" };

	// �ؽ� �� ���
	std::cout << "hash<MyKey>(k1) = "
		<< std::hash<MyKey>{}(k1) << "\n";
	std::cout << "hash<MyKey>(k2) = "
		<< std::hash<MyKey>{}(k2) << "\n\n";

	// unordered_map�� MyKey ��� ��
	std::unordered_map<MyKey, int> umap;
	umap.reserve(2);
	umap[k1] = 100;
	umap[k2] = 200;

	std::cout << "umap[k1] = " << umap[k1] << "\n";
	std::cout << "umap[k2] = " << umap[k2] << "\n";

	return 0;
}
