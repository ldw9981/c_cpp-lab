#include <iostream>
#include <functional>

class IHandler
{
public:
	virtual void MemberOnClick() = 0; // 순수 가상 함수로 인터페이스 정의
};

class MyComponent :public IHandler  // 인터페이스 구현
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

	// 인터페이스를 통해 멤버 함수 호출	
	btn.SetOnClick(&handler);
	btn.Click();	
	return 0;
}
