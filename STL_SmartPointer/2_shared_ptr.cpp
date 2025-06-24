#include <iostream>
#include <memory>

class Bullet {
public:
	Bullet() { std::cout << "Bullet 생성됨\n"; }
	~Bullet() { std::cout << "Bullet 소멸됨\n"; }
	void Fire() { std::cout << "발사!\n"; }
};

// shared_ptr로 Bullet을 공유해 사용하는 함수
void UseBullet(std::shared_ptr<Bullet> b) {
	b->Fire(); // 공유된 인스턴스를 사용
	// 함수 종료 시 참조 카운트 1 감소
}

int main() {
	// Bullet 인스턴스를 shared_ptr로 생성
	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>();

	UseBullet(bullet); // 참조 카운트 증가 (2)

	bullet->Fire(); // 여전히 사용 가능

	// main 종료 시 bullet이 마지막 소유자이므로 Bullet 소멸
}
