#pragma once
#include "CommonInclude.h"

namespace Algorithm {
	using namespace std;

	// 그래프를 따로 만드는 것이 아닌 그래프 역할을 할 인접 리스트를 만드는 것으로 그래프 구조 생성 대체
	// 10개의 정점이 있는 인접 리스트와 인접 행렬을 각각 하나씩 생성
	struct BFSDFSGraph {
		vector<vector<int>>	graphList;
		vector<vector<int>>	graphMatrix;

		void AddEdgeMatrix(int i, int j) {
			graphMatrix[i][j] = 1;
			graphMatrix[j][i] = 1;
		}

		BFSDFSGraph() {
			graphList = vector<vector<int>>(10, vector<int>());
			graphMatrix = vector<vector<int>>(10, vector<int>(10, 0));

			graphList[0] = { 3, 4, 7 };
			graphList[1] = { 2, 4, 5, 8, 9 };
			graphList[2] = { 1, 3, 6, 7 };
			graphList[3] = { 0, 2, 5, 8, 9 };
			graphList[4] = { 0, 1, 5, 6, 7, 8 };
			graphList[5] = { 1, 3, 4, 9 };
			graphList[6] = { 2, 4 };
			graphList[7] = { 0, 2, 4, 8, 9 };
			graphList[8] = { 1, 3, 4, 7 };
			graphList[9] = { 1, 3, 5, 7 };

			AddEdgeMatrix(0, 3);
			AddEdgeMatrix(0, 4);
			AddEdgeMatrix(0, 7);
			AddEdgeMatrix(1, 2);
			AddEdgeMatrix(1, 4);
			AddEdgeMatrix(1, 5);
			AddEdgeMatrix(1, 8);
			AddEdgeMatrix(1, 9);
			AddEdgeMatrix(2, 3);
			AddEdgeMatrix(2, 6);
			AddEdgeMatrix(2, 7);
			AddEdgeMatrix(3, 5);
			AddEdgeMatrix(3, 8);
			AddEdgeMatrix(3, 9);
			AddEdgeMatrix(4, 5);
			AddEdgeMatrix(4, 6);
			AddEdgeMatrix(4, 7);
			AddEdgeMatrix(4, 8);
			AddEdgeMatrix(5, 9);
			AddEdgeMatrix(7, 8);
			AddEdgeMatrix(7, 9);
		}
	};

	// 임의로 각 그래프에 값을 삽입(값은 똑같으나 형태가 다르다.)
	// 각 그래프의 값은 아래처럼 설정
	// 인접 리스트(인덱스 번호로 지칭)
	// 0 - 3, 4, 7
	// 1 - 2, 4, 5, 8, 9
	// 2 - 1, 3, 6, 7
	// 3 - 0, 2, 5, 8, 9
	// 4 - 0, 1, 5, 6, 7, 8
	// 5 - 1, 3, 4, 9
	// 6 - 2, 4
	// 7 - 0, 2, 4, 8, 9
	// 8 - 1, 3, 4, 7
	// 9 - 1, 3, 5, 7
	// 인접 행렬
	// 0 0 0 1 1 0 0 1 0 0
	// 0 0 1 0 1 1 0 0 1 1
	// 0 1 0 1 0 0 1 1 0 0
	// 1 0 1 0 0 1 0 0 1 1
	// 1 1 0 0 0 1 1 1 1 0
	// 0 1 0 1 1 0 0 0 0 1
	// 0 0 1 0 1 0 0 0 0 0
	// 1 0 1 0 1 0 0 0 1 1
	// 0 1 0 1 1 0 0 1 0 0
	// 0 1 0 1 0 1 0 1 0 0

	// 그래프 탐색 문제(그래프 순회 문제)
	// 그래프 탐색 문제란 그래프에서 특정 정점을 찾기 위한 용도로 사용하는 문제이다.(미로에서 길 찾기, 최단 거리 계산, 친구 관계 확인 및 추천 시스템 등)
	// 이 그래프 탐색 문제를 해결하기 위해 이번에 배워볼 그래프 탐색 알고리즘은 BFS(Breadth First Search : 너비 우선 탐색)과 DFS(Depth First Search : 깊이 우선 탐색)이다.
	// 간단하게 말하면 정점과 간선을 따라 이동하며 답을 찾는 문제를 해결하기 위한 알고리즘이다.

	// BFS(너비 우선 탐색)
	// 정의 : 그래프나 트리 구조에서 시작 노드와 가장 가까운 인접 노드부터 먼저 방문하며 넓게 탐색해 나가는 알고리즘

	// DFS(깊이 우선 탐색)
	// 정의 : 트리나 그래프에서 한 방향으로 끝까지 탐색한 후 더 이상 갈 곳이 없으면 가장 최근의 갈림길로 되돌아와 다른 경로를 탐색하는 알고리즘

	// 정의를 보면 BFS는 트리의 레벨 순서 순회와 DFS는 트리의 전위 순회와 비슷한 모습을 하고 있다는 것을 알 수 있다.
	// 그렇기에 BFS는 큐를 사용하여 인접 정점을 탐색해 나가고 DFS는 재귀적으로 정점에 접근해서 탐색해 나가는 모습을 추론할 수 있다.
	
	// 그러나 탐색 문제에서는 이 정점을 방문했는지 여부를 저장해야 한다는 차이가 존재한다. 
	// 왜냐하면, 이를 저장하지 않으면 방문한 정점을 계속 방문하거나 탐색을 끝마치지 못하는 무한 루프 문제가 발생할 수 있기 때문이다.
	// 예를 들어 설명하면 그래프를 탐색하는 문제가 있다고 칠 때 그래프가 순환 구조일 경우 이미 한 번 탐색한 정점을 또 하고 또 하고를 반복하다가 무한 루프에 빠지는 것이다.

	// BFS
	// 장점 : 간단하고 이해하기 쉬운 구조이며 출발 정점에서 도착 정점까지의 최단 거리를 보장하고 연결된 모든 정점을 찾는데 이용할 수 있다.
	// 단점 : 경로가 매우 길 경우 탐색할 정점이 많아지기 때문에 많은 메모리를 차지하고 무한 그래프의 경우에는 목표를 찾지 못하고 끝내지도 못하며 그래프 순회 시 가중치를 고려하지 않기 때문에 가중 그래프에 적절치 못하다.(정점의 수가 많으면 비효율적이다.)
	 
	// DFS
	// 장점 : 재귀적 동작을 취하기 때문에 BFS에 비해 메모리 공간을 덜 차지하고 특정 정점 혹은 모든 정점에 최대한 빨리 도달하는 문제일 때 유용하다.(그래프에서 순환을 감지할 수 있다.)
	// 단점 : 순환 그래프의 경우 무한 루프에 빠질 수 있고 두 정점 사이 최단 경로를 찾으려는 경우 사용하기에 좋은 알고리즘이 아닐 수 있다.

	// 각각의 장단점을 종합한 결론은 DFS는 특정 상황에서 매우 유용하지만 항상 최선의 선택이 되지 않기에 BFS를 쓰면 좋은 경우도 있고 BFS는 메모리 사용이 많고 정점이 많은 그래프나 가중치 그래프의 경우 제대로 작동하지 않지만 특정 문제에서 큰 장점을 발휘한다.

	// 각 알고리즘 유리한 경우는 다음과 같다
	// BFS - 최단 경로 찾기, 최단 경로가 유일한 경우, 상태 공간 탐색(상태 공간에서 최소 이동/변경 횟수 찾는 문제 - 예시:퍼즐, 스도쿠 등)
	// DFS - 경로 찾기(단순한 두 정점 사이 경로 존재 여부), 깊이 우선 탐색이 필요한 경우, 해결 책의 수가 많은 경우

	// 단순 순회 문제를 해결하는 BFS/DFS
	namespace Traversal {
		void BFS(int start, const vector<vector<int>>& searchGraph);
		void DFS(int start, const vector<vector<int>>& searchGraph);
	}

	// 그래프 연결성 문제를 해결하는 BFS/DFS
	// 문제 - 연결 요소 개수 세기
	namespace ConnectVertexCount {
		void BFS(const vector<vector<int>>& searchGraph);
		void DFS(const vector<vector<int>>& searchGraph);
		void DFS(const vector<vector<int>>& searchGraph, int start);
		void CountConnectComponent(const vector<vector<int>>& searchGraph);  // DFS로 순회 후 연결 요소 개수를 세는 함수(Component가 요소라는 의미)
	}

	// Flood Fill 문제를 해결하는 BFS/DFS
	// Flood Fill이란 시작 위치와 같은 조건을 만족하는 칸들을 상하좌우로 계속해서 탐색하여 하나의 영역을 모두 방문하는 알고리즘이다.
	// 시작 위치 값이 2였다면 똑같이 값이 2인 연결된 영역을 탐색하는 것으로 이해하면 된다.
	namespace FloodFill {
		void FloodFillBFS(const vector<vector<int>>& searchGraph, int startX, int startY);
		void FloodFillDFS(const vector<vector<int>>& searchGraph, int startX, int startY);  // 스택을 사용하는 DFS
		void FloodFillRecursionDFS(const vector<vector<int>>& searchGraph, vector<vector<bool>>& visited, int startX, int startY, int target);  // 재귀를 사용하는 DFS(Recursion - 재귀)
		void CountElement(const vector<vector<int>>& searchGraph, int startX, int startY);
	}

	// 최단 거리 BFS(무방향, 무가중치)
	// 이 문제는 우선 행렬을 사용하여 구현(추후 인접 리스트 그래프로도 할 예정)
	// 최단 거리 BFS는 말 그대로 두 노드 사이 경로 중 가장 짧은 거리의 경로를 구하는 것이다.
	// 최단 거리를 구하는 방식은 BFS가 적합하기에 BFS만 진행(DFS는 깊이 탐색하는 것을 목표로 하기 때문이다.)
	namespace ShortestPath {
		// 대각선 이동은 없고 두 노드의 값이 같지는 않아도 된다. 그러나 이동 가능한 요소 값은 존재한다.
		// 그러니 미로라고 생각하고 요소 값들은 이동 가능한 요소와 지나가지 못하는 요소를 두고 시작 노드에서 목표 노드까지 가장 빠르게 가는 거리를 찾는 것이다.
		void ShortestPathBFS(const vector<vector<int>>& searchgraph, pair<int,int> startNode, pair<int, int> endNode);
	}
}
