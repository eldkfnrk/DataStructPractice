#include "MyOwnHeap.h"

namespace DataStruct {
	void OwnMaxHeap::HeapInsertNode(int data)
	{
		// 힙의 삽입 연산(검색을 통해 알게 된 점)
		// 우선 삽입할 노드를 완전 이진 트리를 만족하는 위치에 삽입
		// 삽입 이후 부모와 값을 비교하여 부모의 값보다 크면 값을 교환
		// 좌 우 자식의 위치는 대소 관계를 반영하지 않기 때문에 좌 우 비교는 필요하지 않다.

		// 잘 된 부분
		// 1. 힙에 대한 개념 파악은 잘 완수되었다.
		// 2. 삽입 연산에서 부모와 값을 비교하여 교환하는 것을 잘 구현하였다.
		// 3. 삭제에서도 동일하게 값 비교와 교환을 잘 구현하였다.
		// 4. 중복 값 허용을 잘 적용하였다.

		// 아쉬운 점
		// 1. 삽입, 삭제를 제외한 다른 연산에서는 빈 힙에 대한 예외 처리가 없다. - 수정 완료
		// 2. 시간 복잡도가 높아졌다.(힙은 배열로 구현할 수 있는 자료구조로 O(LogN)을 보장할 수 있는데 트리로 구현하면서 O(N)까지 높아졌다. 배열로 힙을 구현하는 것은 최소 힙을 만들어보면서 진행할 예정. 최대 힙에서는 수정 x)
		// 3. 삭제에서 스택을 사용하면서 메모리 손해가 발생하였다.(그러나 이 문제는 배열로 구현했을 때 해결되는 문제고 트리 구조에서는 이 방법을 사용해야 하기 때문에 배열로 구현하면 알아서 해결되니 수정 x)

		// 반드시 고쳐야 할 점
		// 1. 소멸자가 없어 메모리 누수가 발생하고 있으니 소멸자를 추가하여야 한다. - 수정 완료

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

	void OwnMaxHeap::HeapDeleteNode()
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

	void OwnMaxHeap::HeapState()
	{
		if (!root) {
			std::cout << "힙이 비어있다." << std::endl;
			return;
		}

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

	OwnMaxHeap::~OwnMaxHeap()
	{
		std::queue<heapNode*> bfsQueue;
		bfsQueue.push(root);
		while (!bfsQueue.empty()) {
			heapNode* curNode = bfsQueue.front();

			if (!curNode->leftNode)
				bfsQueue.push(curNode->leftNode);
			if (!curNode->rightNode)
				bfsQueue.push(curNode->rightNode);

			bfsQueue.pop();
			delete(curNode);
		}
	}

	void OwnMinHeap::MinHeapInsert(int data)
	{
		minHeapStorage.push_back(data);

		int lastIndex = (int)minHeapStorage.size() - 1;
		
		while (lastIndex != 0) {
			int parentIndex = (lastIndex - 1) / 2;
			if (minHeapStorage[parentIndex] > minHeapStorage[lastIndex]) {
				int temp = minHeapStorage[parentIndex];
				minHeapStorage[parentIndex] = minHeapStorage[lastIndex];
				minHeapStorage[lastIndex] = temp;

				lastIndex = parentIndex;
			}
			else {
				break;
			}
		}
	}

	void OwnMinHeap::MinDataDelete()
	{
		if (minHeapStorage.empty()) {
			std::cout << "힙이 비어있으므로 연산 불가" << std::endl;
			return;
		}

		int lastIndex = (int)minHeapStorage.size() - 1;

		if (lastIndex == 0) {
			minHeapStorage.pop_back();
			return;
		}

		minHeapStorage[0] = minHeapStorage[lastIndex];
		minHeapStorage.pop_back();

		lastIndex = (int)minHeapStorage.size() - 1;
		int currentIndex = 0;  // root부터 아래로 비교해 가면서 교환을 해야 하기 때문에 

		// 정렬
		while (currentIndex < lastIndex) {
			// 자식 노드의 인덱스는 2i+1, 2i+2이다.
			int leftIndex = currentIndex * 2 + 1;
			int rightIndex = currentIndex * 2 + 2;
			int childIndex;  // 현재 노드 값과 비교할 자식 노드의 인덱스

			if (leftIndex > lastIndex) {  // 왼쪽 자식의 순서보다 배열의 마지막 인덱스가 작다는 것은 자식이 없는 노드라는 의미이고 이는 정렬이 완료되었다는 의미이므로 정렬을 종료
				break;
			}
			else if (leftIndex == lastIndex) {  // 왼쪽 자식만 있는 경우는 왼쪽 자식이 마지막인 경우 밖에 없기 때문에 따로 비교 없이 바로 왼쪽 자식의 순서 인덱스 값을 저장
				childIndex = lastIndex;
			}
			else {  // 자식이 둘 다 있기 때문에 둘 중 더 작은 값을 가진 노드의 인덱스를 저장하여 부모와 비교
				childIndex = minHeapStorage[leftIndex] > minHeapStorage[rightIndex] ? rightIndex : leftIndex;
			}

			if (minHeapStorage[currentIndex] > minHeapStorage[childIndex]) {  // 부모의 값이 자식의 값보다 작아야 최소 힙을 만족하니 부모 값이 더 크면 값 교환
				int temp = minHeapStorage[currentIndex];
				minHeapStorage[currentIndex] = minHeapStorage[childIndex];
				minHeapStorage[childIndex] = temp;

				currentIndex = childIndex;
			}
			else {  // 부모 값이 자식 값보다 작거나 같으면 더 이상 교환은 안 해도 되고 그러면 최소 힙을 만족하는 것이기 때문에 정렬 종료
				break;
			}
		}
	}

	void OwnMinHeap::MinHeapState()
	{
		int floor = 0;
		int floorMaxIndex = 1;
		int lastIndex = (int)minHeapStorage.size() - 1;
		bool traversalComplete = false;  // traversal - 순회, 힙 순회를 마쳤는지에 대한 정보를 저장하는 변수

		// 비효율적이지만 층대로 나눠서 보여줄 수 있도록 설정
		while (!traversalComplete) {
			int floorElementCount = 1;
			for (int i = 0; i < floor; i++) {
				floorElementCount *= 2;
			}
			if (floorElementCount == 1)
				floorElementCount = 0;

			floorMaxIndex += floorElementCount;

			int startIndex = floor == 0 ? 0 : 2 * floor - 1;

			for (int i = startIndex; i < floorMaxIndex; i++) {
				std::cout << minHeapStorage[i] << " ";
				if (i == lastIndex) {
					traversalComplete = true;
					break;
				}
			}
			std::cout << std::endl;

			++floor;
		}
	}

	OwnMinHeap::~OwnMinHeap()
	{

	}
}