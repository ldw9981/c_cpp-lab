/*
값 범주(Value Categories) 기본 설명:
- lvalue (locator or left value): 이름 있는 식별 가능한 값 (변수, 배열 요소 등)
- prvalue (pure rvalue): 순수 임시값
  - 리터럴(literal): 소스코드에 직접 작성된 상수 값 (예: 42, 3.14)
  - 연산 결과, 함수 반환 임시 값 등
- xvalue (eXpiring value): 만료 직전의 값
  - rvalue 참조로 캐스트된 식별자 (예: static_cast<T&&>(x))
  - rvalue 참조 반환 함수 호출 표현식
*/

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

// 두 정수를 더해 결과를 반환하는 함수 (반환값: prvalue)
int add(int x, int y) {
    return x + y;
}

// 임의의 클래스 예시: 동적 배열을 멤버로 가지는 Buffer
class Buffer {
public:
    int* m_pData;
    std::size_t m_size;

    // 생성자: 동적 배열 할당
    Buffer(std::size_t size)
        : m_size(size), m_pData(new int[size]()) {
    }

    // 복사 생성자: 딥 카피
    Buffer(const Buffer& other)
        : m_size(other.m_size), m_pData(new int[other.m_size]) {
        std::copy(other.m_pData, other.m_pData + m_size, m_pData);
    }

    // 이동 생성자: 소유권 이전 (xvalue 바인딩)
    Buffer(Buffer&& other) noexcept
        : m_size(other.m_size), m_pData(other.m_pData) {
        other.m_size = 0;
        other.m_pData = nullptr;
    }

    // 소멸자: 배열 해제
    ~Buffer() {
        delete[] m_pData;
    }
};

int main() {
    // 1) 리터럴과 lvalue
    int a = 5;                     // 5: prvalue, a: lvalue

    // 2) 함수 호출 결과(prvalue)로 초기화
    int b = add(a, 10);            // add(a,10): prvalue, b: lvalue

    // 3) 이동할 수 있는 컨테이너 예시
    std::vector<int> v1 = { 1, 2, 3 };       // initializer_list: prvalue, v1: lvalue
    std::vector<int> v2 = std::move(v1);   // std::move(v1): xvalue, v2: lvalue
    // v1은 빈 상태가 되고, v2가 자원을 이전 받음

    // 4) 사용자 정의 클래스 Buffer에서 std::move 사용
    Buffer buf1(100);                      // buf1: lvalue, 내부에서 new int[100] 할당
    Buffer buf2 = std::move(buf1);         // std::move(buf1): xvalue → 이동 생성자 호출
    // buf1.m_pData는 nullptr로 설정되어 더 이상 배열을 가리키지 않음

    // 출력
    std::cout << "a=" << a
        << ", b=" << b << "\n"
        << "v1.size()=" << v1.size()
        << ", v2.size()=" << v2.size() << "\n"
        << "buf1.pData=" << buf1.m_pData
        << ", buf2.pData=" << buf2.m_pData
        << std::endl;

    return 0;
}
