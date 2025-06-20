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
		std::cout << "Button clicked! (Member function via bind)\n";
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
		
	btn.SetOnClick(&handler);
	btn.Click();	
	return 0;
}
