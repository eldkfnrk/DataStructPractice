#pragma once
#include <iostream>
#include <vector>

namespace Stack {
	// 스택
	// 스택은 자료구조 중 하나로 사전적 의미인 쌓아놓은 더미라는 것으로 의미로 유추할 수 있듯이 데이터를 차곡차곡 쌓아두는 형태의 자료구조를 말한다.
	// 아래에서 위로 차곡차곡 쌓아두는 형태이니 이를 하나씩 꺼내 쓸 때는 위에서부터 꺼내서 쓰게 될 것이다.
	// 이를 이해하기 쉽게 예를 들면 접시가 있을 수 있다. 
	// 즉 후입선출(LIFO : Last In First Out) 방식으로 늦게 들어온 데이터를 먼저 사용하는 방식의 자료구조이다.
	// 기본 기능은 총 5가지 존재한다.
	// 비어있는지 확인 - IsEmpty, 가득 찼는지 확인 - IsFull, 데이터 삽입 - Push, 데이터 삭제 - Pop, 스택의 맨 위 데이터를 조회(없다면 비어있음을 반환) - Peek
	// Pop이랑 Peek는 비슷하게 마지막 요소를 조회하는데 Pop은 데이터 삭제이기 때문에 스택에서 값을 삭제시키지만 Peek는 데이터를 조회할 뿐 데이터를 삭제는 하지 않는다.

	// 하나 알게 된 사실 - 템플릿은 구조상 선언과 정의가 분리가 이루어질 수 없다.

	template <typename T>
	class OwnStack
	{
	public:
		OwnStack(int max) {  // 생성자의 매개 변수의 자료형을 정해주지 않으면 에러가 눈으로 명시되지 않지만 큰 에러가 발생하기 때문에 주의해야 한다.(생성자도 함수라는 것을 기억하자.)
			this->max = max;
			stackVector.reserve(max);  // vector의 공간을 미리 확보해주는 함수(vector는 스스로 크기를 변화시키는 가변 배열로 굳이 크기를 정해줄 필요가 없지만 필요하다면 reverse 함수로 가능하다.)
			top = -1;
		}

		// 스택이 비어있는지 확인 - 비어있다면 true(1), 아니라면 false(0)를 반환
		int IsEmpty() {
			// 비어있는지 확인하려면 마지막 요소의 인덱스를 저장하고 있는 top을 비교해보면 된다.
			// top이 -1이면 빈 스택이라는 의미이고 아니라면 스택에 데이터가 있다는 것을 의미한다.
			if (OwnStack::GetTop() == -1)
				return 1;

			return 0;
		}

		// 스택이 가득 찼는지 확인 - 맞다면 true(1), 아니라면 false(0)를 반환
		int IsFull() {
			// 가득 찼는지 확인하려면 마지막 인덱스 번호가 스택의 최대 길이 - 1을 비교하면 된다.
			// top이 스택의 최대 길이 - 1과 동일하다면 가득찬 것이고 아니라면 아직 빈 공간이 있다는 것을 의미한다.
			if (top == (max - 1))
				return 1;

			return 0;
		}

		// 데이터 삽입 - 스택이 가득 차서 안 되는 상황이라면 가득 찼음을 알려야 한다.
		void Push(T data) {
			// 스택이 가득찼다면 가득 찼음을 알리고 함수 종료
			if (IsFull() == 1) {
				std::cout << "Stack is full. Can't data push.";
				return;
			}
			
			// 스택이 가득차지 않았다면 해당 데이터를 배열에 저장
			stackVector.push_back(data);
		}

		// 데이터 삭제 - 스택이 비어서 삭제할 데이터가 없다면 비었음을 알려야 한다. 성공적으로 삭제하였다면 삭제한 데이터의 값을 반환한다.
		T Pop() {
			return;
		}

		// 스택의 맨 위 데이터를 조회하는 Peek 함수 - 스택의 맨 위 데이터를 조회하여 반환한다. 없다면 없음을 알려야 한다.
		T Peek() {
			return;
		}

	private:
		std::vector<T> stackVector;  // 스택에 삽입된 데이터를 저장할 배열
		int max;  // 스택의 최대 길이
		int top;  // 마지막 요소의 인덱스 번호(빈 스택인 경우 -1)
	};
}
