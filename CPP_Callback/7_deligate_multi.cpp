#include <vector>
#include <functional>
#include <iostream>
#include <math.h>

template<typename... Args>
class MultiDelegate {
	struct Slot {
		void* instance; // �ݹ� ���п� ������(�ַ� this)
		std::function<void(Args...)> func;
	};
	std::vector<Slot> slots;

public:
	void Add(void* instance, const std::function<void(Args...)>& f) {
		slots.push_back({ instance, f });
	}
	// tag(������)�� ����
	void Remove(void* instance) {
		slots.erase(
			std::remove_if(slots.begin(), slots.end(),
				[instance](const Slot& s) { return s.instance == instance; }),
			slots.end());
	}
	void Clear() { slots.clear(); }
	void BroadCast(Args... args) const {
		for (const auto& s : slots)
			if (s.func) s.func(args...);
	}
};

class OtherComponent {
public:
	void OnChangeHealth(int prev, int curr)
	{
		std::cout << __FUNCDNAME__ << prev << " " << curr << "\n";
	}
};

class HealthComponent {
public:
	int HP = 100;
	MultiDelegate<int, int> onChangeHealth;	// Prev,Curr
	void TakeDamage(int value)
	{
		int result = std::max<int>(0, HP - value);
		SetHP(result);
	}
	void SetHP(int value)
	{
		if (HP != value) {
			int prev = HP;
			HP = value;
			onChangeHealth.BroadCast(prev, HP);
			// ü���� ��ȭ�� �޴� �Լ��� ��� ȣ��
		}
	}
};

class Player {
public:
	OtherComponent other;
	HealthComponent health;
	void Start()
	{
		health.onChangeHealth.Add(&other,
			std::bind(&OtherComponent::OnChangeHealth, &other,
				std::placeholders::_1, std::placeholders::_2));
	}
};

int main() {
	Player player;
	player.Start();
	//�ܺο��� TakeDamage�� ȣ���Ѵ�.
	player.health.TakeDamage(20);  // HP�� 80�� �� �� onChangeHealth ��ε�ĳ��Ʈ
	player.health.TakeDamage(20);  // HP�� 60�� �� �� onChangeHealth ��ε�ĳ��Ʈ

	return 0;
}
