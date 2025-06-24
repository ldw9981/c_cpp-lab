#include <iostream>
#include <memory>

class Bullet {
public:
	Bullet() { std::cout << "Bullet ������\n"; }
	~Bullet() { std::cout << "Bullet �Ҹ��\n"; }
	void Fire() { std::cout << "�߻�!\n"; }
};

// shared_ptr�� Bullet�� ������ ����ϴ� �Լ�
void UseBullet(std::shared_ptr<Bullet> b) {
	b->Fire(); // ������ �ν��Ͻ��� ���
	// �Լ� ���� �� ���� ī��Ʈ 1 ����
}

int main() {
	// Bullet �ν��Ͻ��� shared_ptr�� ����
	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>();

	UseBullet(bullet); // ���� ī��Ʈ ���� (2)

	bullet->Fire(); // ������ ��� ����

	// main ���� �� bullet�� ������ �������̹Ƿ� Bullet �Ҹ�
}
