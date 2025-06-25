#include <cstddef>   // std::size_t
#include <cstring>   // std::memcpy

class MyClass {
public:
	static constexpr std::size_t Capacity = 100;

	// 1) 기본 생성자: Capacity 크기의 int 배열을 0으로 초기화
	MyClass()
		: Data(new int[Capacity]())
	{
	}

	// 2) 복사 생성자: 딥 카피
	MyClass(const MyClass& other)
		: Data(new int[Capacity])
	{
		std::memcpy(Data, other.Data, Capacity * sizeof(int));
	}

	// 3) 이동 생성자: 포인터 소유권 이전
	MyClass(MyClass&& other) noexcept
		: Data(other.Data)
	{
		other.Data = nullptr;
	}

	// 4) 소멸자: 배열 해제
	~MyClass() {
		delete[] Data;
	}

	// 5) 복사 대입 연산자: 기존 메모리 해제 후 딥 카피
	MyClass& operator=(const MyClass& other) {
		if (this != &other) {
			int* newData = new int[Capacity];
			std::memcpy(newData, other.Data, Capacity * sizeof(int));
			delete[] Data;
			Data = newData;
		}
		return *this;
	}

	// 6) 이동 대입 연산자: 기존 메모리 해제 후 소유권 이전
	MyClass& operator=(MyClass&& other) noexcept {
		if (this != &other) {
			delete[] Data;
			Data = other.Data;
			other.Data = nullptr;
		}
		return *this;
	}

	// (선택) 특정 인덱스에 값 설정
	void Set(std::size_t idx, int value) {
		if (idx < Capacity)
			Data[idx] = value;
	}

	// (선택) 특정 인덱스 값 조회
	int Get(std::size_t idx) const {
		return (idx < Capacity) ? Data[idx] : 0;
	}

private:
	int* Data;
};


#include <iostream>
#include <vector>
#include <utility> // std::move


int main() {
	// 1) 기본 생성 및 값 세팅
	MyClass a;
	for (std::size_t i = 0; i < MyClass::Capacity; ++i) {
		a.Set(i, static_cast<int>(i * 2)); // a[i] = i*2
	}
	std::cout << "a[10] = " << a.Get(10) << "\n"; // 20

	// 2) 복사 생성자
	MyClass b = a;
	std::cout << "b[10] = " << b.Get(10) << "\n"; // 역시 20

	// 3) 이동 생성자
	MyClass c = std::move(a);
	std::cout << "c[10] = " << c.Get(10) << "\n";          // 20
	std::cout << "a[10] (moved-from) = " << a.Get(10) << "\n"; // 0 또는 정의된 기본값

	// 4) 복사 대입 연산자
	MyClass d;
	d = b;
	std::cout << "d[20] = " << d.Get(20) << "\n"; // 40

	// 5) 이동 대입 연산자
	MyClass e;
	e = std::move(b);
	std::cout << "e[20] = " << e.Get(20) << "\n";          // 40
	std::cout << "b[20] (moved-from) = " << b.Get(20) << "\n"; // 0 또는 기본값

	// 6) STL 컨테이너와 함께 쓰기
	std::vector<MyClass> vec;
	vec.reserve(3);

	// emplace_back: default 생성자 호출
	vec.emplace_back();

	// push_back(MyClass()): 임시 객체가 이동 생성자로 vec에 삽입
	vec.push_back(MyClass());

	// push_back(std::move(c)): 이미 값을 가진 c를 이동
	vec.push_back(std::move(c));

	std::cout << "vec[2][10] = " << vec[2].Get(10) << "\n"; // c의 원본 값 20

	return 0;
}
