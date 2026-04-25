#pragma once
#include "CommonInclude.h"

namespace DataStruct {
	// 큐
	// 큐는 사전적으로 줄을 서다라는 의미로 사전적 의미에서 유추할 수 있듯이 큐는 줄을 선 순서대로 입장이 가능하다. 즉, 먼저 들어오면 먼저 나가는 구조를 가진 자료구조이다.
	// 이런 형태를 선입선출(FIFO : First In First Out)이라고 부른다.
	// 큐 또한 스택과 동일한 5가지의 기본 동작이 있고 그 세부 내용만이 살짝의 차이가 있다.
	// 스택은 마지막에 들어온 것을 그대로 삭제하면 되었지만 큐는 삭제할 때 맨 처음 것을 삭제하고 다른 요소들의 인덱스를 앞으로 이동시켜야 한다는 차이가 있다.
	template <typename T>
	class OwnQueue
	{
	public:
		OwnQueue(int max) : max(max) {
			queueVector.reserve(max);
			top = -1;
		}

		// 가득 찼는지 확인 - 가득 찼으면 1 아니면 0 반환
		int IsFull() {
			if (top == (max - 1))
				return 1;

			return 0;
		}

		// 비었는지 확인 - 비었으면 1 아니면 0 반환
		int IsEmpty() {
			if (top == -1)
				return 1;

			return 0;
		}

		// 데이터 삽입 - 큐가 가득 차있는 상황이라면 삽입 불가를 알려야 한다.
		void Enqueue(T data) {
			// 데이터 삽입은 당연하게 마지막 요소로 추가
			// 만약 큐가 가득 찬 상황이라면 삽입 불가를 통보 후 삽입 종료
			if (IsFull() == 1) {
				std::cout << "Queue is full. Can't enqueue." << std::endl;
				return;
			}

			queueVector.push_back(data);
			top++;
		}

		// 데이터 삭제 - 큐가 비어있는 상황이라면 삭제 불가를 알려야 한다.
		// std::optional<T>는 값이 있는지 없는지를 구분하는 문법으로 c++17부터 도입된 문법이다.(그래서 컴파일러를 17이상으로 설정하여야 한다.)
		std::optional<T> Dequeue() {
			// 삭제할 데이터는 큐의 맨 앞에 있는 요소
			// 만약 큐가 비어있다면 삭제 불가를 통보 후 종료
			
			if (IsEmpty() == 1) {
				std::cout << "Queue is empty. Can't dequeue." << std::endl;
				return std::nullopt;  // 값이 없다는 것을 반환하는 것으로 이 값은 해당 자료형의 기본 값으로 대체된다.
			}

			T data = queueVector[0];
			// 벡터의 특정 요소 삭제 함수는 erase()
			// 큐는 첫 번째 요소를 반환하는 함수는 begin()
			// queueVector.erase(queueVector.begin());는 첫 번째 요소를 삭제하는 동작을 한다.
			// 지금 당장은 vector의 우수한 기능을 통해서 인덱스 변경이 쉽게 이루어지고 있지만 추후에는 스스로 할 수 있는 기능을 만들어야 한다.
			queueVector.erase(queueVector.begin());
			top--;
			
			return data;
		}

		// 데이터 검색 - 큐가 비어있는 상황이라면 검색 불가를 알리고 삭제될 데이터를 반환(삭제되는 것은 아니고 어떤 데이터가 삭제될 예정인지 확인)
		std::optional<T> Peek() {
			// 삭제할 데이터는 큐의 맨 앞에 있는 요소
			// 만약 큐가 비어있다면 데이터를 못 찾음을 통보
			if (IsEmpty() == 1) {
				std::cout << "Queue is empty. Can't peek." << std::endl;
				return std::nullopt;
			}
			T data = queueVector[0];

			return data;
		}

		// 큐에 저장된 데이터를 한 눈에 볼 수 있도록 해주는 함수
		void QueueState() {
			if (IsEmpty() == 1)
				return;

			for(int i = 0; i <= top; i++)
			{
				std::cout << queueVector[i] << " ";
			}
			std::cout << std::endl;
		}

		int GetLength() {
			// top은 가장 마지막 인덱스 값을 가지기 때문에 길이는 top 값보다 1 높다.
			return top + 1;
		}

	private:
		std::vector<T> queueVector;
		int max;
		int top;
	};
}
