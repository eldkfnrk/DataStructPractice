#include "MyOwnStack.h"
#include "MyOwnQueue.h"
#include "MyOwnLinkedList.h"

int main() {
	using namespace std;
	using namespace DataStruct;

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

	cout << "삭제된 요소 값 : " << intStack.Pop().value_or(0) << endl;
	cout << "삭제된 요소 값 : " << intStack.Pop().value_or(0) << endl;
	intStack.StackState();

	cout << "마지막 요소 값 : " << intStack.Peek().value_or(0) << endl;

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
	cout << "삭제된 요소 값 : " << stringStack.Pop().value_or(" ") << endl;
	cout << "삭제된 요소 값 : " << stringStack.Pop().value_or(" ") << endl;
	cout << "삭제된 요소 값 : " << stringStack.Pop().value_or(" ") << endl;

	cout << "마지막 요소 값 : " << stringStack.Peek().value_or(" ") << endl;
	stringStack.Push("닛케이225");
	stringStack.StackState();

	cout << "-----------------------------------------------------------------------------------" << endl;

	// int형 큐 테스트
	OwnQueue<int> intQueue(6);
	intQueue.QueueState();
	intQueue.Dequeue();
	intQueue.Enqueue(10);
	intQueue.Enqueue(80);
	intQueue.Enqueue(91);
	intQueue.Enqueue(365);
	intQueue.Enqueue(198);
	intQueue.Enqueue(658);
	intQueue.Enqueue(21);
	intQueue.QueueState();

	// std::optional<T> 반환형은 int형이 아니라 있을 수도 없을 수도 있다는 값이기 때문에 값을 그대로 쓸 수 없어서 value()나 value_or() 함수를 사용하여야 한다.
	// value() 함수를 사용할 때에는 has_value()라는 함수를 사용하여 값이 있는지 확인하고 사용하는 것이 권장되고 거의 반드시 이 동작을 수행해주어야 한다.
	// value_or(0)는 이 값이 int형이기 때문에 내가 기본 값을 0으로 둔 것이고 다른 자료형이면 알맞게 기본 값을 주면 된다. 이 함수는 value() 함수를 사용할 때 반드시 수행되는 has_value()로 값이 있는지 검사하는 것이 귀찮다면 그냥 없을 때는 기본 값을 있으면 그 값을 반환하게 한다.
	// std::optional<T>는 박스고 그 안에 값이라는 물건이 있을 수도 없을 수도 있고 이를 확인하거나 없다는 것을 표현하는 식으로 동작한다고 이해하면 된다.
	// 기본 값으로 반환했을 때 이게 값이 없다는 건지 이게 값이라는 건지 헷갈리는 문제가 발생할 수 있음을 인지하고 대책을 마련 후 사용하여야 한다.
	cout << "삭제된 요소 : " << intQueue.Dequeue().value_or(0) << endl;
	cout << "삭제된 요소 : " << intQueue.Dequeue().value_or(0) << endl;
	cout << "삭제될 요소 : " << intQueue.Peek().value_or(0) << endl;
	intQueue.QueueState();

	cout << "-----------------------------------------------------------------------------------" << endl;

	OwnLinkedList<int> firstIntList;  // 빈 리스트
	OwnLinkedList<int> secondIntList(12);  // 하나의 요소를 가진 리스트;

	firstIntList.CurrentListState();
	secondIntList.CurrentListState();

	firstIntList.InsertHeader(23);
	firstIntList.InsertHeader(46);
	firstIntList.InsertTail(520);
	firstIntList.InsertTail(461);
	firstIntList.InsertHeader(200);
	firstIntList.CurrentListState();

	cout << firstIntList.GetListLength() << endl << endl;
	//firstIntList.InsertNode(6, 50);
	firstIntList.CurrentListState();
	firstIntList.InsertNode(3, 50);
	firstIntList.CurrentListState();
	cout << endl;

	cout << "삭제한 값 : " << firstIntList.DeleteHeader().value_or(0) << endl;
	firstIntList.CurrentListState();
	cout << "삭제한 값 : " << firstIntList.DeleteHeader().value_or(0) << endl;
	firstIntList.CurrentListState();
	cout << "삭제한 값 : " << firstIntList.DeleteTail().value_or(0) << endl;
	firstIntList.CurrentListState();
	firstIntList.InsertHeader(120);
	firstIntList.InsertHeader(180);
	firstIntList.InsertTail(457);
	firstIntList.InsertTail(300);
	firstIntList.CurrentListState();

	cout << "삭제한 값 : " << firstIntList.DeleteNode(3).value_or(0) << endl;
	firstIntList.CurrentListState();


	return 0;
}