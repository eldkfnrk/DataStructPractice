#include "MyOwnBST.h"
#include "MyOwnQueue.h"

namespace DataStruct {
	// 삽입 기능
	// root가 없는 경우에는 해당 값이 root가 되고 만약 있다면 규칙에 따라 삽입
	// BST의 삽입은 탐색한 노드보다 작으면 왼쪽으로 크면 오른쪽으로 이동시키는 것을 따르면 된다.
	// 내가 만드는 BST는 만약 동일한 값이 있다면 삽입 불가를 통보하고 멈추도록 한다.
	bool OwnBST::InsertNode(const int& data) {
		if (!root) {
			root = new BSTNode{ data, nullptr, nullptr };
			++n;
			return true;
		}

		// 삽입 값과 현재 확인 중인 노드의 데이터 값이 같다면 삽입 불가를 통보하고 실패를 반환
		if (FindNode(data)) {
			std::cout << "Already exist \"" << data << "\" data. Can't insert data." << std::endl;
			return false;
		}

		BSTNode* checkNode = root;
		bool isSuccess = false;

		// BST의 탐색 횟수는 BST의 높이 + 1과 동일하다. 그렇기 때문에 이런 반복문이 될 수 있다.
		for(int i = 0; i < h + 1; i++) {
			// 삽입 값이 현재 확인 중인 노드의 데이터 값보다 작은 경우
			// 현재 확인 중인 노드의 왼쪽 노드가 비어있다면 그대로 삽입을 하고 종료, 비어있지 않다면 왼쪽에 있는 노드를 확인하도록 검색 노드 변환
			if (checkNode->data > data) {
				if (!checkNode->leftNode) {
					checkNode->leftNode = new BSTNode{ data,nullptr,nullptr };
					isSuccess = true;
					++n;
					break;
				}
				checkNode = checkNode->leftNode;
			}
			// 삽입 값이 현재 확인 중인 노드의 데이터 값보다 큰 경우
			// 현재 확인 중인 노드의 오른쪽 노드가 비어있다면 그대로 삽입을 하고 종료, 비어있지 않다면 오른쪽에 있는 노드를 확인하도록 검색 노드 변환
			else {
				if (!checkNode->rightNode) {
					checkNode->rightNode = new BSTNode{ data,nullptr,nullptr };
					isSuccess = true;
					++n;
					break;
				}
				checkNode = checkNode->rightNode;
			}
		}

		SetHeight();  // 높이 재설정(높이가 안 달라질 수도 있지만 혹시 달라질 경우 이를 적용시켜야 하기 때문에 호출한다.)

		return isSuccess;
	}

	int OwnBST::SearchData(const int& data)
	{
		return 0;
	}

	int OwnBST::SearchMin()
	{
		if (!root) {
			std::cout << "This BST is empty. Can't search minimum data." << std::endl;
			return -10000;  // BST의 저장 값 범위를 -9999 ~ 10000으로 임의 지정한다. 그러면 -10000이라는 것은 BST에 들어갈 수 없는 값이라는 것이니 실패했다 혹은 오류가 있다를 의미한다.
		}

		BSTNode* checkNode = root;

		for (int i = 0; i < h + 1; i++) {
			if (!checkNode->leftNode)
				break;
			checkNode = checkNode->leftNode;
		}

		return checkNode->data;
	}

	int OwnBST::SearchMax()
	{
		if (!root) {
			std::cout << "This BST is empty. Can't search maximum data." << std::endl;
			return -10000;  // BST의 저장 값 범위를 -9999 ~ 10000으로 임의 지정한다. 그러면 -10000이라는 것은 BST에 들어갈 수 없는 값이라는 것이니 실패했다 혹은 오류가 있다를 의미한다.
		}

		BSTNode* checkNode = root;

		for (int i = 0; i < h + 1; i++) {
			if (!checkNode->rightNode)
				break;
			checkNode = checkNode->rightNode;
		}

		return checkNode->data;
	}

	BSTNode* OwnBST::FindNode(const int& data)
	{
		// 탐색 방법1) 함수를 재귀 함수로 만들어서 찾는다.
		// 탐색 방법2) 반복문을 사용하여 찾는다.

		if (!root)
			return nullptr;

		BSTNode* checkNode = root;

		for(int i = 0; i < h + 1; i++){
			if (checkNode->data == data || !checkNode)
				break;
			
			if (checkNode->data > data) {
				checkNode = checkNode->leftNode;
			}
			else {
				checkNode = checkNode->rightNode;
			}
		}

		if (checkNode) {
			// 이중 조건문을 사용한 이유는 혹시나 checkNode가 nullptr일 경우 문제가 발생할 수 있기 때문에 조금의 가독성은 포기하고 안정성을 높이기 위하여 이렇게 하였다.
			// &&연산자를 사용하면 괜찮을 거라 생각했지만 혹시 모를 문제를 근본적으로 방지하기 위해서 이렇게 하였다.
			if (checkNode->data != data) {
				checkNode = nullptr;
			}
		}

		return checkNode;
	}

	BSTNode* OwnBST::FindParentNode(const int& data)
	{
		// 찾는 노드가 root라면 부모 노드가 없으니 nullptr을 반환
		if (!root || root->data == data) 
			return nullptr;

		BSTNode* checkNode = root;

		for (int i = 0; i < h + 1; i++) {
			if (checkNode->leftNode->data == data || checkNode->rightNode->data == data || !checkNode)
				break;

			if (checkNode->data > data) {
				checkNode = checkNode->leftNode;
			}
			else {
				checkNode = checkNode->rightNode;
			}
		}

		if (checkNode) {
			if (checkNode->leftNode->data != data && checkNode->rightNode->data != data) {
				checkNode = nullptr;
			}
		}

		return checkNode;
	}

	bool OwnBST::DeleteNode(const int& data)
	{
		// BST의 삭제는 트리의 삭제처럼 자식이 있다고 실패하는 것이 아니라 노드를 삭제하고 노드 간 크기를 비교하여 삭제된 쪽을 재편하는 과정을 가진다.
		// 삭제 시 자식 노드들이 있는 경우 자식의 자식까지 다 찾아서 삭제한 노드보다 큰 값을 가진 노드 중 가장 작은 노드가 삭제된 노드의 자리를 대체한다.
		return false;
	}

	void OwnBST::PreOrderTree(BSTNode* checkNode)
	{
		if (!checkNode)
			return;

		std::cout << checkNode->data << " ";
		PreOrderTree(checkNode->leftNode);
		PreOrderTree(checkNode->rightNode);
	}

	void OwnBST::InOrderTree(BSTNode* checkNode)
	{
		if (!checkNode)
			return;

		InOrderTree(checkNode->leftNode);
		std::cout << checkNode->data << " ";
		InOrderTree(checkNode->rightNode);
	}

	void OwnBST::PostOrderTree(BSTNode* checkNode)
	{
		if (!checkNode)
			return;

		PostOrderTree(checkNode->leftNode);
		PostOrderTree(checkNode->rightNode);
		std::cout << checkNode->data << " ";
	}

	void OwnBST::LevelOrderTree()
	{
		if (!root) 
			return;

		OwnQueue<BSTNode*> bstQueue;
		bstQueue.Enqueue(root);

		BSTNode* deleteNode = nullptr;

		while (1) {
			int queueLength = bstQueue.GetLength();

			if (queueLength == 0)
				break;

			for (int i = 0; i < queueLength; i++) {
				deleteNode = bstQueue.Dequeue().value_or(nullptr);
				if (deleteNode->leftNode)
					bstQueue.Enqueue(deleteNode->leftNode);
				if (deleteNode->rightNode)
					bstQueue.Enqueue(deleteNode->rightNode);
				std::cout << deleteNode->data << " ";
			}

			std::cout << std::endl;
		}

		delete(deleteNode);
	}

	void OwnBST::SetHeight()
	{
		if (!root) {
			h = -1;
			return;
		}

		OwnQueue<BSTNode*> bstQueue;
		bstQueue.Enqueue(root);

		BSTNode* deleteNode = nullptr;
		int height = -1;

		while (1) {
			int queueLength = bstQueue.GetLength();

			if (queueLength == 0)
				break;

			for (int i = 0; i < queueLength; i++) {
				deleteNode = bstQueue.Dequeue().value_or(nullptr);
				if (deleteNode->leftNode)
					bstQueue.Enqueue(deleteNode->leftNode);
				if (deleteNode->rightNode)
					bstQueue.Enqueue(deleteNode->rightNode);
			}

			++height;
		}

		h = height;

		delete(deleteNode);
	}
}