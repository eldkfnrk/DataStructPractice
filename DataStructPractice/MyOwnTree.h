#pragma once
#include "CommonInclude.h"

namespace DataStruct {
	// 트리의 노드
	template <typename T>
	struct Node {
		// 노드의 구성은 데이터와 자식 노드들을 가리키는 주소 값들로 자식 노드는 최대 2개로 지정
		T data;
		Node<T>* firstNode;
		Node<T>* secondNode;
	};

	// 트리
	// 비선형 문제 중 계층적 문제를 해결하기 위한 자료구조
	// 각각의 노드 안에 데이터가 있고 그 노드의 자식 노드의 주소를 가지고 있는 구조를 가지고 있다.
	// 부모-자식 관계를 갖고 있는 특성 덕에 계층적 문제를 해결할 수 있는 자료구조이다.

	template <typename T>
	class OwnTree
	{
	public:
		// 생성, 삽입, 삭제, 순회 등의 기능 추가
		// 순회에는 전위, 중위, 후위, 레벨 순서 순회가 있다.
		// 전위(현재 - 왼 - 오), 중위(왼 - 현재 - 오), 후위(왼 - 오 - 현재), 레벨 순서(단계 별로 한 단계에 노드가 두 개면 왼 - 오 순서로 순회)

		// 생성자를 통한 트리 생성(연결 리스트처럼 아예 빈 트리로 만들거나 root 노드만 가지고 있는 트리로 만든다.)
		OwnTree() {
			root = nullptr;
		}

		OwnTree(T data) {
			// 이런 식으로 new를 사용함과 동시에 구조체 멤버 값 초기화가 가능하다.
			root = new Node<T>{ data, nullptr, nullptr };
		}

		// 그 동안 순차적 자료구조를 알아보면서 나도 모르게 이것 또한 정해진 순서대로 값을 삽입해야 한다는 착각을 해버렸다.
		// 그러나 트리는 계층 구조이기 때문에 특정 노드가 특정 노드 밑으로 삽입되어야 한다는 것을 알게 되었다.
		// 그렇기 때문에 특정 노드를 찾고 그 아래에 들어갈 공간이 있는지 확인하고 없다면 삽입 불가를 있다면 삽입을 진행하는 구조로 가야 한다.

		// 탐색 기능
		Node<T>* FindNode(const T& data, Node<T>* checkNode = root) {
			if (!checkNode) 
				return nullptr;

			// 현재 탐색 중인 노드의 데이터와 탐색하고자 하는 데이터를 비교하여 맞다면 해당 노드를 반환하고 아니라면 하위 노드를 탐색
			// 만약 하위 노드가 없다면 오른쪽 노드를 탐색하는 식으로 진행
			if (checkNode->data == data)
				return checkNode;

			Node<T>* firstFindNode = FindNode(data, checkNode->firstNode);  // 왼쪽 노드를 쭉 순회해서 해당 데이터를 가진 노드가 있는지 확인

			if (firstFindNode)
				return firstFindNode;

			return FindNode(data, checkNode->secondNode);  // 왼쪽 노드들을 쭉 탐색하다가 발견하지 못하였다면 오른쪽 노드들도 탐색

			// 위의 구현된 동작들을 보면 쭉 해당 노드의 데이터를 비교 후 아니면 쭉 왼쪽으로 탐색하다가 왼쪽 노드가 비었다면 오른쪽 노드를 탐색해보는 식이다. 조금 더 이해가 쉽게 트리의 구조와 탐색 순서를 시각적으로 보여주면 아래와 같다.
			//      1
			//   2     3
			// 4  5  6   7
			// 탐색 순서 : 1 - 2 - 4 - 5 - 3 - 6 - 7
		}

		// 삽입 기능
		// 매개변수에 const 참조형을 사용한 이유는 혹시 모를 값 변형을 막고 배열 등의 데이터가 매개변수로 들어올 수 있도록 하기 위해서이다.
		// 앞의 매개변수는 삽입할 위치의 상위 노드 데이터, 뒤의 매개변수는 삽입할 데이터를 나타낸다.
		bool InsertNode(const T& topData, const T& data) {
			Node<T>* parentNode = FindNode(topData);

			// 삽입할 위치는 상위 노드의 아래이기 때문에 상위 노드를 먼저 찾고 그 아래에 삽입 가능한지를 찾는 연산이 진행되어야 한다.(04-21)
		}


	private:
		Node<T>* root;  // 최상위 노드를 저장하는 변수.
	};
}
