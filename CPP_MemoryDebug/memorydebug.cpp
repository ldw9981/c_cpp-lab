
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include <memory>

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int* arr = new int[100]; // new[]도 DEBUG_NEW 적용됨

	// delete[] arr; ← 주석 시 누수 발생

	return 0;
}
