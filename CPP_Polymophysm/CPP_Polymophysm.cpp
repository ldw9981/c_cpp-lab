// CPP_Polymophysm.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

class Parent
{
public:
    virtual void Function()
    {
        std::cout << "Parent::Function\n";
    }

    void Function2()
    {
        std::cout << __FUNCDNAME__ << "\n";
    }
};

class Child :public Parent
{
public:
	void Function() override
	{
		std::cout << "Child::Function\n";
	}
	void Function2()
	{
		std::cout << __FUNCDNAME__ << "\n";
	}
};

int main()
{
    Parent a;
    a.Function();
    a.Function2();

    Child b;
    b.Function();
    b.Function2();
}
