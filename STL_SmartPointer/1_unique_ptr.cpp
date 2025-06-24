#include <iostream>
#include <memory>

class Enemy {
public:
	Enemy() { std::cout << "Enemy 생성됨\n"; }
	~Enemy() { std::cout << "Enemy 소멸됨\n"; }	
	void Attack() { std::cout << "공격!\n"; }
};

// 소유권을 이동받아 사용하는 함수
void Play(std::unique_ptr<Enemy> e) {
	e->Attack(); // 정상 사용 가능
	// 함수 종료 시 e의 수명이 끝나며 Enemy 자동 소멸
}

int main() {
	// std::make_unique를 통해 Enemy 인스턴스를 생성하고 unique_ptr로 소유
	std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>();

	enemy->Attack(); // 직접 호출 가능
		
	Play(std::move(enemy)); // enemy의 소유권(리소스를)을 함수로 이동	
	if (!enemy) {
		std::cout << "enemy는 이제 nullptr입니다. 더 이상 사용할 수 없습니다.\n";
	}

	// enemy는 더 이상 Enemy 객체를 소유하지 않음
}
