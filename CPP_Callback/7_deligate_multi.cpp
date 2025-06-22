#include <vector>
#include <iostream>
#include <cassert>

template<typename T, typename... Args>
class MultiDelegate {
	using MethodType = void(T::*)(Args...);
	struct Slot {
		T* instance;
		MethodType method;
	};
	std::vector<Slot> slots;

public:	
	void Add(T* instance, MethodType method) {
		for (const auto& s : slots)
			assert(!(s.instance == instance && s.method == method) && "�̹� ��ϵ� �ݹ��Դϴ�!");
		slots.push_back({ instance, method });
	}

	// �ν��Ͻ� ������ ��� ���� (iterator ���)
	void RemoveByInstance(T* instance) {
		for (auto it = slots.begin(); it != slots.end(); /* no ++ here */) {
			if (it->instance == instance)
				it = slots.erase(it); // erase�� ���� ��� iterator ��ȯ
			else
				++it;
		}
	}
	// ��� ȣ��
	void BroadCast(Args... args) const {
		for (const auto& s : slots)
			(s.instance->*(s.method))(args...);
	}
};

// ��� ����
class Handler {
public:
	void OnEvent(int v) { std::cout << "Handler(" << this << "): " << v << "\n"; }
};

int main() {
	MultiDelegate<Handler, int> onEvent;
	Handler h1, h2;

	onEvent.Add(&h1, &Handler::OnEvent);
	onEvent.Add(&h2, &Handler::OnEvent);
	onEvent.BroadCast(123); // h1.OnEvent, h2.OnEvent ��� ȣ��

	onEvent.RemoveByInstance(&h1); // h1 ���� ��� ����
	onEvent.BroadCast(77); // h2.OnEvent�� ȣ��

	return 0;
}
