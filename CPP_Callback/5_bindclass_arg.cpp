#include <iostream>
#include <functional>

class Handler {
public:
	void MemberOnClick(int value) {
		std::cout << "Button clicked " << value << " (Member function via bind)\n";
	}
};

class Button {
	std::function<void(int)> onClick;
public:
	void SetOnClick(const std::function<void(int)>& cb) { onClick = cb; }
	void Click(int a) {
		if (onClick) onClick(a);
	}
};

int main() {
	Handler handler;
	Button btn;

	// ��� �Լ� ���ε� (std::bind)
	btn.SetOnClick(std::bind(&Handler::MemberOnClick, &handler, std::placeholders::_1));
	btn.Click(42); // 42�� ����

	return 0;
}
