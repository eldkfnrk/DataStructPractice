#pragma once
#include "CommonInclude.h"

namespace DataStruct {
	// BST의 구현은 가장 쉽고 보편적인 정수 값을 저장하고 비교하는 방식을 사용해보려 한다.
	// 그렇기 때문에 노드의 데이터는 정수형 값만 들어가도록 한다.
	struct BSTNode {
		int data;
		BSTNode* leftNode;
		BSTNode* rightNode;
	};

	// BST(Binary Search Tree : 이진 탐색 트리)
	// BST는 부모 노드보다 값이 큰 노드를 오른쪽 노드에 작은 노드는 왼쪽 노드에 배치시키는 트리이다.
	// BST를 사용하면 좋은 점은 탐색 속도가 O(logN)으로 기존 트리의 탐색 속도보다 훨씬 빨라진다는 것에 있다.
	// 왜 그러냐면 BST는 탐색할 때 탐색할 값과 현재 계층의 노드 값을 비교해서 크면 오른쪽으로 작으면 왼쪽으로 이동해서 이를 반복하고 값을 찾으면 그만두면 되기 때문에 아무리 많은 데이터가 있어도 계층 개수만큼만 비교해보면 되기 때문이다.
	// BST는 이진 트리에서 삽입 과정과 탐색 과정이 살짝 다른 것 빼고는 큰 차이가 없다.
	// root가 있으면 root를 기준으로 root보다 크면 오른쪽으로 작으면 왼쪽으로 이걸 계층마다 반복해주면 된다.
	class OwnBST
	{
	public:
		OwnBST() : n(0), h(-1) {
			root = nullptr;
		}

		OwnBST(int data) : n(1), h(0) {
			root = new BSTNode{ data, nullptr, nullptr };
		}

		// 삽입, 검색(최대, 최소, 해당 값이 있는가), 삭제, 순회 기능
		
		bool InsertNode(const int& data);  // 삽입
		int SearchData(const int& data);  // 특정 값 검색
		int SearchMin();  // 최소 값 검색
		int SearchMax();  // 최대 값 검색
		BSTNode* FindNode(const int& data);  // 탐색
		BSTNode* FindParentNode(const int& data);  // 찾고자 하는 노드의 부모 노드 탐색
		bool DeleteNode(const int& data);  // 삭제
		void PreOrderTree(BSTNode* checkNode);  // 전위 순회
		void InOrderTree(BSTNode* checkNode);  // 중위 순회
		void PostOrderTree(BSTNode* checkNode);  // 후위 순회
		void LevelOrderTree();  // 레벨 순서 순회

		int GetLength() {
			return n;
		}

		int GetHeight() {
			return h;
		}

	private:
		void SetHeight();  // 트리의 높이를 수정하는 함수
		
	private:
		BSTNode* root;
		int n;  // BST 내에 있는 노드의 개수를 저장하는 변수
		int h;  // BST의 높이(root가 있는 계층은 제외하고 계산)
		// 트리의 높이는 가장 멀리 떨어진 리프 노드까지 경로에 있는 간선의 수를 의미한다.
	};
}
