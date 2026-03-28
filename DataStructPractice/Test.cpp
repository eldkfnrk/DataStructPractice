#include "MyOwnStack.h"
#include <iostream>
#include <string>

int main() {
	using namespace std;
	using namespace Stack;

	// int형 스택 테스트
	OwnStack<int> intStack(10);  // 크기 10인 int형 스택 생성
	// 생성했을 때 스택의 상태
	string isFull = intStack.IsFull() == 1 ? "Full" : "Not Full";
	string isEmpty = intStack.IsEmpty() == 1 ? "Empty" : "Not Empty";
	cout << isFull << endl;
	cout << isEmpty << endl;
	cout << endl << endl << endl;

	intStack.Push(10);
	intStack.Push(25);
	intStack.Push(60);
	intStack.Push(320);
	intStack.Push(70);
	intStack.Push(99);
	intStack.NowStack();

	cout<< intStack.Pop() << endl;
	cout<< intStack.Pop() << endl;
	intStack.NowStack();

	return 0;
}