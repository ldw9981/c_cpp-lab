#include <iostream>
#include <memory>

class NPC {
public:
	NPC() { std::cout << "NPC 생성됨\n"; }
	~NPC() { std::cout << "NPC 소멸됨\n"; }
	void Talk() { std::cout << "대화 시작\n"; }
};

int main() {
	std::weak_ptr<NPC> weakNpc; // 소유권 없는 포인터 선언

	{
		// NPC 인스턴스 생성과 컨트롤 블록생성
		std::shared_ptr<NPC> npc = std::make_shared<NPC>(); 
		weakNpc = npc; // weak_ptr은 참조 카운트 증가 X

		if (auto shared = weakNpc.lock()) {
			// lock()을 통해 유효하면 shared_ptr로 승격 가능
			shared->Talk(); // 유효한 객체 사용
		}
		// npc가 유효한 동안은 weakNpc도 유효함
	} // shared_ptr 소멸 → NPC 객체 삭제됨

	// 여기서 weakNpc는 expired 상태
	if (weakNpc.expired()) {  
		std::cout << "NPC는 이미 소멸되었습니다.\n";
	}

	// 다시 lock해도 nullptr 반환됨
	if (auto shared = weakNpc.lock()) {
		shared->Talk(); // 호출 안됨
	}
	else {
		std::cout << "더 이상 사용할 수 없습니다.\n";
	}
}
