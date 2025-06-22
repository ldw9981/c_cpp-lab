#include <iostream>
/*

Template Argument Type Deduction

컴파일러가 함수 인자를 보고 템플릿의 타입을 결정하는 것을 말한다.
함수 인자의 타입과 완전히 동일한 타입으로 결정되지는 않는다.

*/

using namespace std;

// 함수 템플릿 인자가 값 타입(T a) 일때
template<typename T> void foo(T a)
{
	++a;
}

int main()
{
	int n = 0;
	int& r = n;
	const int c = n;
	const int& cr = c;

	foo(n);  // T : int
	foo(c);  // T : const int ?
	foo(r);  // T : int& ?
	foo(cr); // T : const int& ?
}
