#include <iostream>
#include <string>

struct Logger {
    static int counter;   // 객체 생성 카운터
    int id;               // 인스턴스 고유 ID
    std::string name;

    Logger(const std::string& n)
        : id(++counter), name(n)
    {
        std::cout << this << " Construct [" << id << "]: " << name << "\n";
    }
    Logger(const Logger& other)
        : id(++counter), name(other.name)
    {
        std::cout << this << " Copy-construct [" << id << "] from [" << other.id << "]: " << name << "\n";
    }
    Logger(Logger&& other) noexcept
        : id(++counter), name(std::move(other.name))
    {
        std::cout << this << " Move-construct [" << id << "] from [" << other.id << "]: " << name << "\n";
    }
    ~Logger() {
        std::cout << this <<  " Destruct  [" << id << "]: " << name << "\n";
    }
};
// static 멤버 초기화
int Logger::counter = 0;


// 전역 변수
Logger global_logger("Global");

Logger byValueFunc(Logger param) {
    std::cout << "  inside byValueFunc()\n";

    // 매개변수 param(id는 복사/이동 생성 시 자동 증가)
    Logger local("Local var in other function");

    // static 로컬 변수
    static Logger static_local("StaticLocal");

    std::cout << "  returning local\n";
    return local;
}

int main() {
    std::cout << "--- main 시작 ---\n";

    // 1) 일반 지역변수
    Logger stack_var("Local var in main");

    // 2) 함수 파라미터, 리턴값 테스트
    std::cout << "\n--- byValueFunc 호출 ---\n";
    Logger ret = byValueFunc(stack_var);

    std::cout << "\n--- main 끝 ---\n";
    return 0;
}
