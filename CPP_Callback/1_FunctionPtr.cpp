#include <iostream>



// 기존 타입에 다른 이름을 붙이는 방법
// 여기서는 함수 포인터 타입에 별칭을 붙임
//typedef void(*ButtonCallback)();  // C 스타일.  
using ButtonCallback = void(*)();  // C++11 스타일

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
