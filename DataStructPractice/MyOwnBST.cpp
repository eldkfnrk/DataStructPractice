#include "MyOwnBST.h"

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

		BSTNode* checkNode = root;
		bool isSuccess = false;

		// BST의 탐색 횟수는 BST의 높이와 동일하다. 그렇기 때문에 이런 반복문이 될 수 있다.
		for(int i = 0; i < h; i++) {
			// 삽입 값과 현재 확인 중인 노드의 데이터 값이 같다면 삽입 불가를 통보하고 실패를 반환
			if (checkNode->data == data) {
				std::cout << "Already exist \"" << data << "\" data. Can't insert data." << std::endl;
				isSuccess = false;
				break;
			}
			// 삽입 값이 현재 확인 중인 노드의 데이터 값보다 작은 경우
			// 현재 확인 중인 노드의 왼쪽 노드가 비어있다면 그대로 삽입을 하고 종료, 비어있지 않다면 왼쪽에 있는 노드를 확인하도록 검색 노드 변환
			else if (checkNode->data < data) {
				if (!checkNode->leftNode) {
					checkNode->leftNode = new BSTNode{ data,nullptr,nullptr };
					isSuccess = true;
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
					break;
				}
				checkNode = checkNode->rightNode;
			}
		}
	}

	int OwnBST::SearchData(const int& data)
	{
		return 0;
	}

	int OwnBST::SearchMin()
	{
		return 0;
	}

	int OwnBST::SearchMax()
	{
		return 0;
	}

	BSTNode* OwnBST::FindNode(const int& data)
	{
		// 탐색 방법1) 함수를 재귀 함수로 만들어서 찾는다.
		// 탐색 방법2) 반복문을 사용하여 찾는다.

		if (!root)
			return nullptr;

		BSTNode* checkNode = root;

		for(int i = 0; i < h; i++){
			if (checkNode->data == data) 
				break;
			
			if (checkNode->data < data) {
				checkNode = checkNode->leftNode;
			}
			else {
				checkNode = checkNode->rightNode;
			}
		}

		return checkNode;
	}

	BSTNode* OwnBST::FindParentNode(const int& data)
	{
		if (!root) 
			return nullptr;
	}

	bool OwnBST::DeleteNode(const int& data)
	{
		// BST의 삭제는 트리의 삭제처럼 자식이 있다고 실패하는 것이 아니라 노드를 삭제하고 노드 간 크기를 비교하여 삭제된 쪽을 재편하는 과정을 가진다.
		// 삭제를 하고 자식만 있는 경우는 해당 자식을 끌어올리면 되는 것이고 만약 자식의 자식까지 있는 상황에서는 규칙을 가지고 있어야 한다. 이 규칙은 다음 시간에 알아보도록 한다.(05-02)
		return false;
	}

	void OwnBST::PreOrderTree()
	{
	}

	void OwnBST::InOrderTree()
	{
	}

	void OwnBST::PostOrderTree()
	{
	}

	void OwnBST::LevelOrderTree()
	{
	}
}