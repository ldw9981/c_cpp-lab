#include <iostream>
#include <memory>

class NPC {
public:
	NPC() { std::cout << "NPC ������\n"; }
	~NPC() { std::cout << "NPC �Ҹ��\n"; }
	void Talk() { std::cout << "��ȭ ����\n"; }
};

int main() {
	std::weak_ptr<NPC> weakNpc; // ������ ���� ������ ����

	{
		// NPC �ν��Ͻ� ������ ��Ʈ�� ��ϻ���
		std::shared_ptr<NPC> npc = std::make_shared<NPC>(); 
		weakNpc = npc; // weak_ptr�� ���� ī��Ʈ ���� X

		if (auto shared = weakNpc.lock()) {
			// lock()�� ���� ��ȿ�ϸ� shared_ptr�� �°� ����
			shared->Talk(); // ��ȿ�� ��ü ���
		}
		// npc�� ��ȿ�� ������ weakNpc�� ��ȿ��
	} // shared_ptr �Ҹ� �� NPC ��ü ������

	// ���⼭ weakNpc�� expired ����
	if (weakNpc.expired()) {  
		std::cout << "NPC�� �̹� �Ҹ�Ǿ����ϴ�.\n";
	}

	// �ٽ� lock�ص� nullptr ��ȯ��
	if (auto shared = weakNpc.lock()) {
		shared->Talk(); // ȣ�� �ȵ�
	}
	else {
		std::cout << "�� �̻� ����� �� �����ϴ�.\n";
	}
}
