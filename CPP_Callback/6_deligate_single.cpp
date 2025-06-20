#include <memory>
#include <stdexcept>

template <typename Ret, typename... Args>
class Delegate {
	using FuncType = Ret(*)(Args...);

	struct IInvoker {
		virtual ~IInvoker() = default;
		virtual Ret Invoke(Args... args) = 0;
	};

	// ���� �Լ��� ����
	template <typename Callable>
	struct FunctorInvoker : IInvoker {
		Callable callable;
		FunctorInvoker(Callable c) : callable(c) {}
		Ret Invoke(Args... args) override {
			return callable(std::forward<Args>(args)...);
		}
	};

	// ��� �Լ�
	template <typename T>
	struct MethodInvoker : IInvoker {
		T* instance;
		Ret(T::* method)(Args...);

		MethodInvoker(T* inst, Ret(T::* m)(Args...)) : instance(inst), method(m) {}
		Ret Invoke(Args... args) override {
			return (instance->*method)(std::forward<Args>(args)...);
		}
	};

	std::unique_ptr<IInvoker> invoker;

public:
	Delegate() = default;

	// ���� �Լ��� ���� ���ε�
	template <typename Callable>
	void Bind(Callable&& func) {
		invoker = std::make_unique<FunctorInvoker<std::decay_t<Callable>>>(std::forward<Callable>(func));
	}

	// ��� �Լ� ���ε�
	template <typename T>
	void Bind(T* instance, Ret(T::* method)(Args...)) {
		invoker = std::make_unique<MethodInvoker<T>>(instance, method);
	}

	bool IsBound() const {
		return (bool)invoker;
	}

	Ret Execute(Args... args) {
		if (invoker)
			return invoker->Invoke(std::forward<Args>(args)...);
		else
			throw std::runtime_error("Delegate not bound!");
	}
};


#include <iostream>

class Handler {
public:
	int OnEvent(int a, float b) {
		std::cout << "Handler::OnEvent: " << a << ", " << b << "\n";
		return a + static_cast<int>(b);
	}
};

int GlobalFunction(int a, float b) {
	std::cout << "GlobalFunction: " << a << ", " << b << "\n";
	return a * static_cast<int>(b);
}

int main() {
	Delegate<int, int, float> del;

	Handler handler;

	// ��� �Լ� ���ε�
	del.Bind(&handler, &Handler::OnEvent);
	std::cout << "Result: " << del.Execute(2, 3.5f) << "\n";

	// ���� �Լ� ���ε�
	del.Bind(&GlobalFunction);
	std::cout << "Result: " << del.Execute(2, 3.5f) << "\n";

	// ���� ���ε�
	del.Bind([](int a, float b) {
		std::cout << "Lambda: " << a << ", " << b << "\n";
		return static_cast<int>(a - b);
		});
	std::cout << "Result: " << del.Execute(5, 1.0f) << "\n";

	return 0;
}
