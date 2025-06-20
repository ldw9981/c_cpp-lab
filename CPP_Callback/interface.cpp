#include <iostream>
#include <functional>

class IHandler
{
public:
	virtual void MemberOnClick() = 0; // ���� ���� �Լ��� �������̽� ����
};

class MyComponent :public IHandler  // �������̽� ����
{
public:
	void MemberOnClick() override {
		std::cout << "Button clicked! (Member function via Interface Class)\n";
	}
};

class Button {
	IHandler* pHandler=nullptr;
public:
	void SetOnClick(IHandler* handler) { pHandler = handler; }
	void Click() {
		if (pHandler) pHandler->MemberOnClick();
	}
};

int main() {
	MyComponent handler;
	Button btn;

	// �������̽��� ���� ��� �Լ� ȣ��	
	btn.SetOnClick(&handler);
	btn.Click();	
	return 0;
}
