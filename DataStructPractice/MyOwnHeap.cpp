#include "MyOwnHeap.h"

namespace DataStruct {
	void OwnHeap::HeapInsertNode(int data)
	{
		// 힙의 삽입 연산(검색을 통해 알게 된 점)
		// 우선 삽입할 노드를 완전 이진 트리를 만족하는 위치에 삽입
		// 삽입 이후 부모와 값을 비교하여 부모의 값보다 크면 값을 교환
		// 좌 우 자식의 위치는 대소 관계를 반영하지 않기 때문에 좌 우 비교는 필요하지 않다.

		heapNode* insertNode = new heapNode();
		insertNode->data = data; 

		if (!root) {
			root = insertNode;
			return;
		}

		std::queue<heapNode*> levelNodes;
		levelNodes.push(root);
		bool insertComplete = false;

		while (!insertComplete) {
			int queueLength = (int)levelNodes.size();
			for (int i = 0; i < queueLength; i++) {
				heapNode* curNode = levelNodes.front();
				if (!curNode->leftNode) {
					insertNode->parentNode = curNode;
					curNode->leftNode = insertNode;
					insertComplete = true;
					break;
				}
				
				if (!curNode->rightNode) {
					insertNode->parentNode = curNode;
					curNode->rightNode = insertNode;
					insertComplete = true;
					break;
				}

				levelNodes.push(curNode->leftNode);
				levelNodes.push(curNode->rightNode);

				levelNodes.pop();
			}
		}

		heapNode* lastNode = insertNode;
		bool sortComplete = false;

		while (!sortComplete) {
			// root에 도달했으니 종료하라는 의미(root까지 바뀔 정도의 값이 삽입되면 root까지도 이어질 수 있으니 이를 위한 조건문)
			if (lastNode == root)
				break;

			// 삽입한 노드의 값이 해당 노드의 부모 노드 값보다 크면 최대 힙을 만족하지 못하기 때문에 부모 노드의 값과 교환
			if (lastNode->data > lastNode->parentNode->data) {
				int temp = lastNode->data;
				lastNode->data = lastNode->parentNode->data;
				lastNode->parentNode->data = temp;
				lastNode = lastNode->parentNode;  // 전환이 되면 부모 노드도 검사를 해봐야 한다. 왜냐면 부모 노드의 부모 노드 값보다 큰 값일 수 있기 때문이다.
			}
			else {
				sortComplete = true;
			}
		}
	}

	void OwnHeap::HeapDeleteNode()
	{
		// 이 모든 정보는 검색을 통해 습득하였다.
		// 힙의 삭제 연산은 항상 root 노드를 삭제
		// 이러면 최대 힙일 때는 최댓값이 최소 힙일 때는 최솟값이 삭제되는 것이다.
		// root 노드 삭제 이후 가장 마지막 노드를 root 노드로 설정하고 각 힙을 만족하도록 정렬한다.

		// 힙이 비어있는 경우
		if (!root) {
			std::cout << "힙이 비어있어 삭제 연산 불가." << std::endl;
			return;
		}

		// root 밖에 없는 경우
		if (!root->leftNode && !root->rightNode) {
			heapNode* deleteNode = root;
			root = nullptr;
			delete(deleteNode);
			return;
		}

		// 가장 마지막 노드 찾기 - 큐를 이용
		std::queue<heapNode*> levelNodes;
		std::stack<heapNode*> findLastNodeStack;
		levelNodes.push(root);

		while (!levelNodes.empty()) {
			int queueLength = (int)levelNodes.size();
			for (int i = 0; i < queueLength; i++) {
				heapNode* curNode = levelNodes.front();
				
				if (curNode->leftNode) {
					levelNodes.push(curNode->leftNode);
					findLastNodeStack.push(curNode->leftNode);
				}

				if (curNode->rightNode) {
					levelNodes.push(curNode->rightNode);
					findLastNodeStack.push(curNode->rightNode);
				}

				levelNodes.pop();
			}
		}

		heapNode* lastNode = findLastNodeStack.top();
		findLastNodeStack.pop();  // 마지막 노드를 삭제(메모리 해제)할 예정인데 이걸 담고 있으면 문제가 생길 수 있기 때문에 삭제
		root->data = lastNode->data;  // root 삭제가 반드시 root 노드 자체를 삭제하고 마지막 노드를 root로 변경해야 하는 것은 아니니 root와 마지막 노드의 값만 교환하고 마지막 노드를 삭제

		// 마지막 노드와 그 부모 노드의 부모-자식 관계 끊기(없는 노드를 있다고 하였다가 없어서 생기는 오류를 방지하기 위하여)
		heapNode* parentNode = lastNode->parentNode;
		if (parentNode->leftNode == lastNode)
			parentNode->leftNode = nullptr;
		else
			parentNode->rightNode = nullptr;

		delete(lastNode);

		// 힙 정렬(최대 힙이기 때문에 root 값이 최대가 될 때까지 진행)
		heapNode* curNode = root;
		heapNode* curNodeChild = nullptr;
		bool isSortComplete = false;

		while (!isSortComplete) {
			if (!curNode->leftNode && !curNode->rightNode)
				break;
			
			if (!curNode->leftNode)
				curNodeChild = curNode->rightNode;
			else if (!curNode->rightNode)
				curNodeChild = curNode->leftNode;
			else  // 두 자식의 값 중 더 큰 값과 비교하면 교환을 하더라도 부모 노드 값이 모든 자식 노드 값보다 크다는 것을 만족하기 때문에 두 자식 중 값이 더 큰 자식을 찾아서 부모와 비교
				curNodeChild = curNode->leftNode->data < curNode->rightNode->data ? curNode->rightNode : curNode->leftNode;

			if (curNode->data < curNodeChild->data) {
				int temp = curNode->data;
				curNode->data = curNodeChild->data;
				curNodeChild->data = temp;

				curNode = curNodeChild;
			}
			else {
				isSortComplete = true;
			}
		}
	}

	void OwnHeap::HeapState()
	{
		std::queue<heapNode*> levelNodes;
		levelNodes.push(root);

		while (!levelNodes.empty()) {
			int queueLength = (int)levelNodes.size();
			for (int i = 0; i < queueLength; i++) {
				heapNode* curNode = levelNodes.front();
				std::cout << curNode->data << " ";

				if (curNode->leftNode)
					levelNodes.push(curNode->leftNode);
				if (curNode->rightNode)
					levelNodes.push(curNode->rightNode);

				levelNodes.pop();
			}
			std::cout << std::endl;
		}
	}
}