#include "MyOwnStack.h"
#include <iostream>
#include <string>

int main() {
	using namespace std;
	using namespace Stack;

	// 자료구조의 종류
	// 배열, 연결 리스트, 스택, 큐, 트리, 그래프, 헤시 테이블, 힙(완전 이진 트리 형태의 자료구조)

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
	intStack.StackState();

	cout << "삭제된 요소 값 : " << intStack.Pop() << endl;
	cout << "삭제된 요소 값 : " << intStack.Pop() << endl;
	intStack.StackState();

	cout << "마지막 요소 값 : " << intStack.Peek() << endl;

	// string형 스택 테스트
	OwnStack<string> stringStack(6);

	stringStack.Push("코스피");
	stringStack.Push("코스닥");
	stringStack.Push("S&P500");
	stringStack.Push("나스닥");
	stringStack.Push("다우존스");
	stringStack.Push("러셀2000");
	stringStack.Push("닛케이225");

	isFull = stringStack.IsFull() == 1 ? "Full" : "Not Full";
	isEmpty = stringStack.IsEmpty() == 1 ? "Empty" : "Not Empty";

	cout << isFull << endl;
	cout << isEmpty << endl;
	cout << endl << endl << endl;

	stringStack.StackState();
	cout << "삭제된 요소 값 : " << stringStack.Pop() << endl;
	cout << "삭제된 요소 값 : " << stringStack.Pop() << endl;
	cout << "삭제된 요소 값 : " << stringStack.Pop() << endl;

	cout << "마지막 요소 값 : " << stringStack.Peek() << endl;
	stringStack.Push("닛케이225");
	stringStack.StackState();

	return 0;
}