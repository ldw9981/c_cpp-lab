#include <iostream>
#include <functional>

class Handler {
public:
	void MemberOnClick() {
		std::cout << "Button clicked! (Member function via bind)\n";
	}
};

class Button {
	std::function<void()> onClick;
public:
	void SetOnClick(const std::function<void()>& cb) { onClick = cb; }
	void Click() {
		if (onClick) onClick();
	}
};

int main() {
	Handler handler;
	Button btn;

	// ��� �Լ� ���ε� (std::bind)
	btn.SetOnClick(std::bind(&Handler::MemberOnClick, &handler));
	btn.Click();

	// (����) ���� ĸó�ε� ��� �Լ� ȣ�� ����
	// btn.SetOnClick([&](){ handler.MemberOnClick(); });
	// btn.Click();

	return 0;
}
