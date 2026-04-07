#pragma once
#include "CommonInclude.h"

namespace DataStruct {
	template <typename T>
	struct Node {
		T data;  // 데이터
		Node* node;  // 다음 노드 시작 주소
	};

	template <typename T>
	class OwnLinkedList
	{
	public:
		// 생성, 삽입(처음, 중간, 마지막), 삭제, 값 찾기, 전체 조회 등의 기능을 가진다.
		// 생성자는 2개를 만든다. 1개는 빈 연결 리스트를 만드는 것이고 다른 1개는 1개의 노드를 가진 연결 리스트를 가지고 있는 것이다.
		OwnLinkedList() : listLength(0) {
			headerNode = nullptr;
			tailNode = nullptr;
		}

		OwnLinkedList(T data) : listLength(1) {
			// 1개의 노드 생성 및 이 노드를 헤더 노드와 테일 노드에 저장, 연결 리스트에 1개의 노드 밖에 없으니 해당 노드는 헤더이자 테일이 되는 것이다.
			Node* newNode = new Node();
			newNode->data = data;
			newNode->node = nullptr;
			headerNode = newNode;
			tailNode = headerNode;
		}

		// 맨 처음 요소로 삽입
		void InsertFront(T data) {
			Node* newNode = new Node();  // 새 노드 생성
			newNode->data = data;

			// 빈 연결 리스트일 경우
			if (!headerNode) {
				newNode->node = nullptr;
				headerNode = newNode;
				tailNode = headerNode;
				listLength = 1;
			}
			else {
				newNode->node = headerNode;
				headerNode = newNode;
				listLength++;
			}
		}

		// 중간 요소로 삽입(특정 인덱스 위치에 삽입)
		void InsertNode(int index, T data) {
			// 혹시나 연결 리스트가 비어있거나 1개 밖에 없는 경우에는 중간에 삽입하는 것은 불가능하기 때문에 불가하다는 메시지를 전달하고 함수 종료
			if (listLength <= 1) {
				std::cout << "Can't insert data in the middle of linked list." << std::endl;
				return;
			}

			Node* newNode = new Node();
			newNode->data = data;

			Node* prevNode = nullptr;  // 해당 인덱스 앞에 있는 인덱스 요소(해당 요소의 다음 데이터를 가리키는 요소의 주소 값을 저장하기 위해 가져와야 한다.)
			Node* nextNode = nullptr;  // 해당 인덱스의 요소(새로 삽입한 요소의 다음 데이터를 가리키는 요소의 주소 값을 저장하기 위해 가져와야 한다.)
			Node* curNode = headerNode;  // 반복문을 돌 때 현재 노드가 무엇인지를 찾기 위해 만든 노드 검색용 노드(헤더 노드부터 검사하기 때문에 헤더 노드를 가지고 온다.)
			for (int i = 0; i < listLength - 1; i++) {
				// 해당 인덱스의 앞 인덱스인 경우 prevNode에 현재 검사 중인 노드를 저장
				if (i = (index - 1)) {
					prevNode = curNode;
				}
				// 해당 인덱스인 경우 nextNode에 현재 검사 중인 노드를 저장하고 반복문 탈출
				else if (i = index) {
					nextNode = curNode;
					break;
				}
				curNode = curNode->node;  // 현재 검사 중인 노드를 다음 노드 주소로 변경
			}

			// prevNode의 다음 데이터를 가리키는 값을 새로 만든 노드의 주소 값으로 새로 만든 노드는 nextNode의 주소 값으로 변경
			prevNode->node = newNode;
			newNode->node = nextNode;
			listLength++;  // 리스트의 길이 1 상승
		}

	private:
		// 연결 리스트에는 이 2개는 가지고 있어야 동작을 할 때 어려움이 없다.
		Node<T>* headerNode;  // 맨 처음 노드(헤더 노드)
		Node<T>* tailNode;  // 맨 마지막 노드(테일 노드)
		int listLength;  // 연결 리스트의 길이
	};
}

