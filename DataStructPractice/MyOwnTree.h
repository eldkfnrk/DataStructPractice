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

	template <typename T>
	class OwnTree
	{
	public:
		// 생성, 삽입, 삭제, 순회 등의 기능 추가
		// 순회에는 전위, 중위, 후위, 레벨 순서 순회가 있다.
		// 전위(현재 - 왼 - 오), 중위(왼 - 현재 - 오), 후위(왼 - 오 - 현재), 레벨 순서(단계 별로 한 단계에 노드가 두 개면 왼 - 오 순서로 순회)

	private:
		Node<T>* root;  // 최상위 노드를 저장하는 변수.
	};
}
