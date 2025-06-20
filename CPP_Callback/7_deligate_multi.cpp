#include <iostream>
#include <vector>
#include <memory>
#include <functional>

template <typename... Args>
class MulticastDelegate {
	struct ICallback {
		virtual ~ICallback() = default;
		virtual void Invoke(Args... args) = 0;
	};

	// ����/�Լ�
	template <typename Func>
	struct FunctorCallback : ICallback {
		Func func;
		FunctorCallback(Func&& f) : func(std::forward<Func>(f)) {}
		void Invoke(Args... args) override {
			func(std::forward<Args>(args)...);
		}
	};

	// ��� �Լ�
	template <typename T>
	struct MethodCallback : ICallback {
		T* instance;
		void (T::* method)(Args...);
		MethodCallback(T* inst, void (T::* m)(Args...)) : instance(inst), method(m) {}
		void Invoke(Args... args) override {
			(instance->*method)(std::forward<Args>(args)...);
		}
	};

	std::vector<std::unique_ptr<ICallback>> callbacks;

public:
	// ��� �Լ� �߰�
	template <typename T>
	void Add(T* instance, void (T::* method)(Args...)) {
		callbacks.emplace_back(std::make_unique<MethodCallback<T>>(instance, method));
	}

	// ����/���� �Լ� �߰�
	template <typename Func>
	void Add(Func&& f) {
		callbacks.emplace_back(std::make_unique<FunctorCallback<std::decay_t<Func>>>(std::forward<Func>(f)));
	}

	// ���� ȣ�� (Broadcast)
	void Broadcast(Args... args) {
		for (auto& cb : callbacks) {
			cb->Invoke(std::forward<Args>(args)...);
		}
	}

	// ��ü ����
	void Clear() {
		callbacks.clear();
	}
};
class Listener {
public:
	void OnNotify(int value) {
		std::cout << "Listener::OnNotify called with " << value << "\n";
	}
};

void GlobalCallback(int value) {
	std::cout << "GlobalCallback called with " << value << "\n";
}

int main() {
	MulticastDelegate<int> OnEvent;

	Listener a, b;

	// ��� �Լ� ���
	OnEvent.Add(&a, &Listener::OnNotify);
	OnEvent.Add(&b, &Listener::OnNotify);

	// ���� �Լ� ���
	OnEvent.Add(&GlobalCallback);

	// ���� ���
	OnEvent.Add([](int v) {
		std::cout << "Lambda received: " << v << "\n";
		});

	// ��ü ȣ��
	OnEvent.Broadcast(100);
}
