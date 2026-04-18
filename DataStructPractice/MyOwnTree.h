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
			root = new Node<T>();
			root->data = data;
			root->firstNode = nullptr;
			root->secondNode = nullptr;
		}

		// 삽입 기능(삽입은 root부터 시작해서 아래 계층으로 내려가서 아래 계층의 왼쪽부터 삽입한다. bool 반환 타입을 가지도록 한 것은 삽입 연산이 재귀적으로 돌아야 하는데 재귀를 멈춰야 할 시점을 검사하기 위해서이다.)
		// 디폴트 매개 변수를 통해 사용자는 데이터만 넣으면 되고 내부에서는 계속해서 다음 검사 노드를 불러와서 검사한다.
		bool InsertNode(T data, Node<T>* checkNode = root) {
			if (!checkNode) {  // 검사하는 노드가 비어있다면 해당 노드에 값을 추가
				checkNode = new Node<T>();
				checkNode->data = data;
				checkNode->firstNode = nullptr;
				checkNode->secondNode = nullptr;
				return true;
			}

			// 재귀 함수를 어떻게 설계할지 더 알아보기(04-18)
		}


	private:
		Node<T>* root;  // 최상위 노드를 저장하는 변수.
	};
}
