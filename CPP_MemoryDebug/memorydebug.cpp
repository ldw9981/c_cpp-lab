
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include <memory>

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int* arr = new int[100]; // new[]�� DEBUG_NEW �����

	// delete[] arr; �� �ּ� �� ���� �߻�

	return 0;
}
