#include "MyOwnBST.h"

namespace DataStruct {
	// 삽입 기능
	// root가 없는 경우에는 해당 값이 root가 되고 만약 있다면 규칙에 따라 삽입
	// BST의 삽입은 탐색한 노드보다 작으면 왼쪽으로 크면 오른쪽으로 이동시키는 것을 따르면 된다.
	// 내가 만드는 BST는 만약 동일한 값이 있다면 삽입 불가를 통보하고 멈추도록 한다.
	bool OwnBST::InsertNode(const int& data) {
		if (!root) {
			root = new Node{ data, nullptr, nullptr };
			++n;
			return true;
		}

		Node* checkNode = root;

		while (1) {
			// 삽입 값과 현재 확인 중인 노드의 데이터 값이 같다면 삽입 불가를 통보하고 실패를 반환
			if (checkNode->data == data) {
				std::cout << "Already exist \"" << data << "\" data. Can't insert data." << std::endl;
				return false;
			}
			// 삽입 값이 현재 확인 중인 노드의 데이터 값보다 작은 경우
			// 현재 확인 중인 노드의 왼쪽 노드가 비어있다면 그대로 삽입을 하고 종료, 비어있지 않다면 왼쪽에 있는 노드를 확인하도록 검색 노드 변환
			else if (checkNode->data < data) {
				if (!checkNode->leftNode) {
					checkNode->leftNode = new Node{ data,nullptr,nullptr };
					return true;
				}
				checkNode = checkNode->leftNode;
			}
			// 삽입 값이 현재 확인 중인 노드의 데이터 값보다 큰 경우
			// 현재 확인 중인 노드의 오른쪽 노드가 비어있다면 그대로 삽입을 하고 종료, 비어있지 않다면 오른쪽에 있는 노드를 확인하도록 검색 노드 변환
			else {
				if (!checkNode->rightNode) {
					checkNode->rightNode = new Node{ data,nullptr,nullptr };
					return true;
				}
				checkNode = checkNode->rightNode;
			}
		}
	}

	Node* OwnBST::FindNode(const int& data)
	{
		return nullptr;
	}

	bool OwnBST::DeleteNode(const int& data)
	{
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