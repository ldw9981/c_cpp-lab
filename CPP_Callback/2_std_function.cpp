#include <iostream>
#include <functional>

class Button {
	std::function<void()> onClick;
public:
	void SetOnClick(const std::function<void()>& cb) { onClick = cb; }
	void Click() {
		if (onClick) onClick();
	}
};

// 콜백 함수
void OnButtonClicked() {
	std::cout << "Button clicked! (std::function)\n";
}

int main() {
	Button btn;
	btn.SetOnClick(OnButtonClicked);
	btn.Click();

	// 람다도 가능!
	btn.SetOnClick([]() { std::cout << "Button clicked by lambda!\n"; });
	btn.Click();

	return 0;
}
