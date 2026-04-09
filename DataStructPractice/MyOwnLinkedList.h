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
		void InsertHeader(T data) {
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
			if (listLength <= 1 || index >= listLength - 1) {
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

		// 맨 마지막 요소로 삽입
		void InsertTail (T data) {
			Node* newNode = new Node();  
			newNode->data = data;
			newNode->node = nullptr;

			// 빈 연결 리스트일 경우
			if (!headerNode) {
				headerNode = newNode;
				tailNode = headerNode;
				listLength = 1;
			}
			else {
				tailNode->node = newNode;
				tailNode = newNode;
				listLength++;
			}
		}

		// STL에서는 안 그럴 수도 있지만 내가 정의하는 리스트는 삭제 시 값을 반환하도록 생성할 것이다.
		// 맨 처음 요소 삭제
		std::optional<T> DeleteHeader() {
			// 만약 리스트가 비어있다면 삭제 불가능을 통보하고 값이 없음을 반환
			if (listLength == 0) {
				std::cout << "Can't delete data. List is empty." << std::endl;
				return std::nullopt;
			}
			// 만약 리스트의 길이가 1이라면(헤더와 테일이 동일하다) 삭제는 동일하게 진행하되 헤더와 테일 모두 빈 값으로 만들어 주어야 한다.
			else if (listLength == 1) {
				// 테일 노드를 굳이 삭제하지 않는 이유는 헤더 노드와 테일 노드가 가리키는 메모리 주소가 같기 때문에 헤더 노드가 가리키는 데이터의 메모리를 해제했을 때 이미 테일 노드가 가리키는 메모리는 해제된 상태가 되기 때문이다.
				delete(headerNode);
				listLength = 0;
			}

			// 메모리 손실이 발생하지 않도록 헤더 노드였던 노드 값을 따로 저장한 후 삭제시키는 작업을 진행
			Node* deleteNode = headerNode;
			headerNode = headerNode->node;
			delete(deleteNode);
		}

		// 특정 요소 삭제
		std::optional<T> DeleteNode(int index) {
			// 특정 요소 삭제는 특수하게 인덱스를 1 ~ (마지막 인덱스-1) 범위 내에서만 가능하도록 할 것이다.
			// 왜냐하면 0과 마지막 인덱스 삭제는 각각 따로 삭제 연산을 만들었는데 굳이 또 여기서까지 실행하게 할 의미가 없기 때문이다.
			// 만약 리스트가 비어있거나 길이가 2 이하이면 삭제 불가능을 통보하고 값이 없음을 반환(길이가 3이상이어야 중간 노드가 생기기 때문이다.)
			// 그리고 인덱스 값이 1 미만이거나 마지막 인덱스 값보다 크면 안 되도록 한다.
			if (listLength <= 2 || (index < 1 && index >= listLength)) {
				std::cout << "Can't delete data. List is empty." << std::endl;
				return std::nullopt;
			}

			Node* curNode = headerNode->node;  // 헤더 노드는 삭제하지 않을 것이기 때문에 그 다음 노드부터 검사해보도록 한다.

			for (int i = 1; i < index; i++) {  // 인덱스까지만 이동하도록 값을 주었고 i가 1부터 시작하는 것은 헤더부터 가져온 것이 아니라 그 다음 값인 인덱스 1번의 값부터 가져왔기 때문이다.

			}

			// 삭제할 노드를 찾으면 어떻게 메모리 해제시킬 수 있도록 할 수 있을지를 고민해보아야 한다.(04-09)
		}

		// 맨 마지막 요소 삭제
		std::optional<T> DeleteTail() {
			// 만약 리스트가 비어있다면 삭제 불가능을 통보하고 값이 없음을 반환
			if (listLength == 0) {
				std::cout << "Can't delete data. List is empty." << std::endl;
				return std::nullopt;
			}
			// 만약 리스트의 길이가 1이라면(헤더와 테일이 동일하다) 삭제는 동일하게 진행하되 헤더와 테일 모두 빈 값으로 만들어 주어야 한다.
			else if (listLength == 1) {
				// 테일 노드를 굳이 삭제하지 않는 이유는 헤더 노드와 테일 노드가 가리키는 메모리 주소가 같기 때문에 헤더 노드가 가리키는 데이터의 메모리를 해제했을 때 이미 테일 노드가 가리키는 메모리는 해제된 상태가 되기 때문이다.
				delete(headerNode);
				listLength = 0;
			}
		}

		// 현재 리스트에 저장된 데이터 출력
		void CurrentListState() {
			Node* curNode = headerNode;

			for (int i = 0; i < listLength; i++) {
				std::cout << curNode->data << " ";
				curNode = curNode->node;
			}

			std::cout << std::endl;
		}

		// 특정 요소 데이터 검색
		std::optional<T> SearchData(int index) {
			// 만약 검색하고자 하는 요소의 인덱스가 없다면 잘못된 것이니 못 찾음을 통보하고 함수 종료(인덱스가 음수인 경우에도 불가능하도록 막아두고자 한다.)
			if (index >= listLength || index < 0) {
				std::cout << "Can't search data " << index << " index in list. List's last index is " << listLength - 1 << "." << std::endl;
				return std::nullopt;
			}

			Node* curNode = headerNode;

			for (int i = 0; i < index; i++) {
				curNode = curNode->node;
			}

			return curNode->data;
		}

	private:
		// 연결 리스트에는 이 2개는 가지고 있어야 동작을 할 때 어려움이 없다.
		Node<T>* headerNode;  // 맨 처음 노드(헤더 노드)
		Node<T>* tailNode;  // 맨 마지막 노드(테일 노드)
		int listLength;  // 연결 리스트의 길이
	};
}

