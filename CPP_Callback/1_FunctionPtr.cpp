#include <iostream>



// ���� Ÿ�Կ� �ٸ� �̸��� ���̴� ���
// ���⼭�� �Լ� ������ Ÿ�Կ� ��Ī�� ����
//typedef void(*ButtonCallback)();  // C ��Ÿ��.  
using ButtonCallback = void(*)();  // C++11 ��Ÿ��

class Button {
	ButtonCallback onClick = nullptr;
public:
	void SetOnClick(ButtonCallback cb) { onClick = cb; }
	void Click() {
		if (onClick) onClick();
	}
};

// �ݹ� �Լ�
void OnButtonClicked() {
	std::cout << "Button clicked! (Function Pointer)\n";
}

int main() {
	Button btn;
	btn.SetOnClick(OnButtonClicked);
	btn.Click(); // ��ư�� "������"
	return 0;
}
