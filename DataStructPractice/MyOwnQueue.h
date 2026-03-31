#pragma once
#include "CommonInclude.h"

namespace Queue {
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

		}

		// 가득 찼는지 확인 - 가득 찼으면 1 아니면 0 반환
		int IsFull() {
			return 0;
		}

		// 비었는지 확인 - 비었으면 1 아니면 0 반환
		int IsEmpty() {
			return 0;
		}

		// 데이터 삽입 - 큐가 가득 차있는 상황이라면 삽입 불가를 알려야 한다.
		void Enqueue() {

		}

		// 데이터 삭제 - 큐가 비어있는 상황이라면 삭제 불가를 알려야 한다.
		T Dequeue() {

		}

		// 데이터 검색 - 큐가 비어있는 상황이라면 검색 불가를 알리고 헤더를 검색할지 마지막 요소를 검색할지 정해서 검색
		T Peek() {

		}

	private:
		std::vector<T> queueVector;
		int max;
		T header;
		T tail;
	};
}
