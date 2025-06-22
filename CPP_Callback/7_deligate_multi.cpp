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
			assert(!(s.instance == instance && s.method == method) && "이미 등록된 콜백입니다!");
		slots.push_back({ instance, method });
	}

	// 인스턴스 단위로 모두 삭제 (iterator 방식)
	void RemoveByInstance(T* instance) {
		for (auto it = slots.begin(); it != slots.end(); /* no ++ here */) {
			if (it->instance == instance)
				it = slots.erase(it); // erase는 다음 요소 iterator 반환
			else
				++it;
		}
	}
	// 모두 호출
	void BroadCast(Args... args) const {
		for (const auto& s : slots)
			(s.instance->*(s.method))(args...);
	}
};

// 사용 예시
class Handler {
public:
	void OnEvent(int v) { std::cout << "Handler(" << this << "): " << v << "\n"; }
};

int main() {
	MultiDelegate<Handler, int> onEvent;
	Handler h1, h2;

	onEvent.Add(&h1, &Handler::OnEvent);
	onEvent.Add(&h2, &Handler::OnEvent);
	onEvent.BroadCast(123); // h1.OnEvent, h2.OnEvent 모두 호출

	onEvent.RemoveByInstance(&h1); // h1 관련 모두 해제
	onEvent.BroadCast(77); // h2.OnEvent만 호출

	return 0;
}
