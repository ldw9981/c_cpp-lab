#include <iostream>

// 버튼 콜백 타입 정의.  이름으로 함수타입을 지정한다.
typedef void(*ButtonCallback)();

class Button {
	ButtonCallback onClick = nullptr;
public:
	void SetOnClick(ButtonCallback cb) { onClick = cb; }
	void Click() {
		if (onClick) onClick();
	}
};

// 콜백 함수
void OnButtonClicked() {
	std::cout << "Button clicked! (Function Pointer)\n";
}

int main() {
	Button btn;
	btn.SetOnClick(OnButtonClicked);
	btn.Click(); // 버튼을 "누른다"
	return 0;
}
