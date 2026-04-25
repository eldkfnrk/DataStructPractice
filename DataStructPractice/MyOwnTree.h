#pragma once
#include "CommonInclude.h"
#include "MyOwnQueue.h"

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

		// 전위 탐색 기능
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
			// 이것은 전위 순회 방법과 유사하다.
		}

		// 찾고자 하는 노드의 부모 노드를 탐색하는 기능
		Node<T>* FindParentNode(const T& data, Node<T>* checkNode = root) {
			if (!checkNode)
				return nullptr;
			
			if (checkNode->firstNode) {
				if (checkNode->firstNode->data == data)
					return checkNode;
			}

			if (checkNode->secondNode) {
				if (checkNode->secondNode->data == data)
					return checkNode;
			}

			Node<T>* searchFirstNode = FindParentNode(data, checkNode->firstNode);

			if (searchFirstNode)
				return searchFirstNode;

			return FindParentNode(data, checkNode->secondNode);
		}

		// 삽입 기능
		// 매개변수에 const 참조형을 사용한 이유는 혹시 모를 값 변형을 막고 배열 등의 데이터가 매개변수로 들어올 수 있도록 하기 위해서이다.
		// 앞의 매개변수는 삽입할 위치의 상위 노드 데이터, 뒤의 매개변수는 삽입할 데이터를 나타낸다.
		bool InsertNode(const T& topData, const T& data) {
			// 삽입 과정
			// 삽입은 특정 노드의 자식 노드로 들어가는 것을 의미. 그렇기에 부모가 될 노드를 찾는 것부터 시작. 그 전에 동일한 데이터가 있는지부터 확인하여 만약 있다면 삽입 불가 통보 후 실패 전달.
			// 부모가 될 노드가 없다면 불가능을 알리고 실패를 전달. 있다면 그 노드에 빈 자식 노드 자리가 있는지 확인. 왼쪽부터 채우는 것을 규칙으로 설정.
			// 빈 자식 노드 자리가 없다면 삽입 불가를 알리고 실패를 전달. 있다면 해당 자리에 삽입 후 삽입 성공을 전달.
			// 부모 노드 탐색 -> 부모 노드의 빈 자식 노드 자리 탐색 -> 빈 자식 노드 자리에 삽입

			if (FindNode(data)) {
				std::cout << "This data already exists. Can't insert data." << std::endl;
				return false;
			}
			
			Node<T>* parentNode = FindNode(topData);

			if (!parentNode) {
				std::cout << "Can't insert data. Can't find \"" << topData << "\" node." << std::endl;
				return false;
			}

			Node<T>* newNode = new Node<T>{ data, nullptr,nullptr };

			if (!parentNode->firstNode) {
				parentNode->firstNode = newNode;
			}
			else if (!parentNode->secondNode) {
				parentNode->secondNode = newNode;
			}
			else {
				std::cout << "Can't insert data. \"" << topData << "\" node is full." << std::endl;
				delete(newNode);  // 생성된 노드는 메모리 상에 남게 되기에 메모리 낭비가 발생. 이를 막기 위해 메모리 해제가 필요
				return false;
			}

			return true;
		}

		// 삭제 기능
		// 삭제할 데이터를 찾아서 해당 데이터를 삭제
		bool DeleteNode(const T& data) {
			// 삭제 과정
			// 해당 데이터를 가진 노드를 탐색. 탐색 결과 그런 노드가 없으면 노드가 없어서 삭제 불가하다는 것을 알리고 실패 전달.
			// 있다면 해당 데이터가 자식 노드를 가지고 있는가 확인. 1개라도 가지고 있다면 자식 노드가 있어 삭제 불가하다는 것을 알리고 실패 전달.
			// 자식 노드가 하나도 없다면 해당 노드와 부모 노드의 연결을 끊고 해당 노드의 메모리 해제 후 성공 전달.

			if (!root) {
				std::cout << "Can't delete node. This tree is empty." << std::endl;
				return false;
			}

			Node<T>* deleteNode = FindNode(data);
			if (!deleteNode) {  // 삭제할 노드가 없는 경우
				std::cout << "Can't delete node. Because can't find \"" << data << "\" node." << std::endl;
				return false;
			}
			else if (deleteNode->firstNode || deleteNode->secondNode) {  // 삭제할 노드에 자식 노드가 있는 경우
				std::cout << "Can't delete Node. Because this node has at least one child node." << std::endl;
				return false;
			}

			// 삭제할 노드를 찾았고 자식 노드가 1개도 없는 상황에서 만약 삭제할 노드가 root 노드라면 root 노드가 가리키는 노드를 없애고 해당 노드를 삭제
			if (deleteNode == root) {  
				root = nullptr;
				delete(deleteNode);
				return true;
			}

			// 삭제 노드를 찾았으니 해당 노드의 부모 노드를 찾아서 부모 노드와 해당 노드 간 연결을 끊어주고 해당 노드를 삭제
			Node<T>* parentNode = FindParentNode(data);

			switch (data)
			{
			case parentNode->firstNode->data:
				parentNode->firstNode = nullptr;
				break;
			case parentNode->secondNode->data:
				parentNode->secondNode = nullptr;
				break;
			}

			delete(deleteNode);
			return true;
		}

		// 순회 기능
		// 모든 트리의 요소를 보여주는 순회 기능을 레벨 순서 순회로 생성(순회는 영어로 order, 순서도 영어로 order라 그냥 레벨 순서 순회를 levelorder 명명)
		void LevelOrder() {
			// 큐에 노드 저장 - 현재 큐에 저장된 노드들을 반복문을 사용하여 순서대로 삭제 - 각 노드들이 큐에서 삭제될 때 값을 출력 및 자식 노드들을 큐에 저장
			// 위의 과정을 반복하면 큐에는 각 계층의 노드 값들만이 저장되고 그러면 계층 별로 값이 출력되도록 할 수 있다.
			if (!root)
				return;

			OwnQueue<Node<T>*> treeNodes(root);
			Node<T>* currentNode = nullptr;

			while (1) {
				int queueLength = treeNodes.GetLength();

				if (queueLength == 0)
					break;

				for (int i = 0; i < queueLength; i++) {
					currentNode = treeNodes.Dequeue().value_or(nullptr);

					if (!currentNode)
						break;

					std::cout << currentNode->data << " ";

					if (!currentNode->firstNode)
						continue;
					else
						treeNodes.Enqueue(currentNode->firstNode);

					if (!currentNode->secondNode)
						continue;
					else
						treeNodes.Enqueue(currentNode->secondNode);
				}
				std::cout << std::endl;
			}
		}

	private:
		Node<T>* root;  // 최상위 노드를 저장하는 변수.
	};
}
