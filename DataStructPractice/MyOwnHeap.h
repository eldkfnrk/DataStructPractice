#pragma once
#include "CommonInclude.h"

namespace DataStruct {
	struct heapNode
	{
		int data;
		heapNode* parentNode;
		heapNode* leftNode;
		heapNode* rightNode;
	};

	// 힙(heap)
	// 데이터에서 최댓값과 최솟값을 빠르게 찾기 위해 고안된 완전 이진 트리 기반 자료구조
	// 반정렬(느슨한 정렬) 상태를 유지 -> 큰 값이 상위 레벨 작은 값이 하위 레벨에 있다, 부모 노드의 값이 자식 노드의 값보다 항상 크거나 작은 이진 트리를 의미(최소 힙이냐 최대 힙이냐에 따라 달라지는 원리)
	// 종류 : 최대 힙(max heap) - 부모 노드의 값이 자식 노드의 값보다 크거나 같은 힙, 최소 힙(min heap) - 부모 노드의 값이 자식 노드의 값보다 작거나 같은 힙
	// 특징 : 힙은 중복 값을 허용
	// 연산 : 삽입, 삭제, 최대(최소) 값 반환
	// 힙은 완전 이진 트리이다.
	class OwnMaxHeap
	{
	public:
		// 1. 최대 힙
		// 우선 순위는 부모 - 왼쪽 - 오른쪽 순이다.
		OwnMaxHeap() : root(nullptr) {
			
		}

		// 삽입
		// 삽입은 root
		void HeapInsertNode(int data);

		// 삭제
		void HeapDeleteNode();

		// 힙의 저장 상태 확인
		void HeapState();

		// 최대 값 반환
		int MaxValue() {
			if (!root) {
				std::cout << "힙이 비어있다." << std::endl;
				return -999999;
			}

			return root->data;
		}

		~OwnMaxHeap();

	private:
		heapNode* root;  // 최대 힙이면 root 값이 가장 크고 최소 힙이면 가장 작다.
	};

	class OwnMinHeap
	{
	public:
		// 삽입
		void MinHeapInsert(int data);

		// 삭제
		void MinDataDelete();

		// 힙의 저장 상태 확인
		void MinHeapState();

		// 최대 값 반환
		int MinValue() {
			if (minHeapStorage.empty()) {
				std::cout << "힙이 비어있다." << std::endl;
				return -999999;
			}

			return minHeapStorage[0];
		}

		// 복사에 관한 것을 만들기 위한 연산자 오버로딩
		//void operator=(std::vector<int> a);

		~OwnMinHeap();

	private:
		std::vector<int> minHeapStorage;
	};
}