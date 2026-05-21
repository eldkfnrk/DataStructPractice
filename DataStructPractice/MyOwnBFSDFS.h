#pragma once
#include "CommonInclude.h"

namespace Algorithm {
	using namespace std;

	// 그래프 탐색 문제(그래프 순회 문제)
	// 그래프 탐색 문제란 그래프에서 특정 정점을 찾기 위한 용도로 사용하는 문제이다.
	// 이 그래프 탐색 문제를 해결하기 위해 이번에 배워볼 그래프 탐색 알고리즘은 BFS(Breadth First Search : 너비 우선 탐색)과 DFS(Depth First Search : 깊이 우선 탐색)이다.

	// BFS(너비 우선 탐색)
	// 루트 노드(시작 정점)에서 시작해서 인접한 노드(정점)를 먼저 탐색하는 그래프 탐색 알고리즘이다. 깊게 탐색하는 것보다 넓게 탐색하는 것을 우선으로 한다.
	// 장점 - 출발 정점에서 목표 정점까지 최단 길이 경로를 보장
	// 단점 - 경로가 매우 길 경우 탐색 가지가 급격히 증가함에 따라 보다 많은 기억 공간 필요, 해가 존재하지 않는 경우 유한 그래프는 모든 그래프 탐색 후 실패로 끝나지만 무한 그래프는 해도 못 찾고 탐색도 끝내지 못 한다.

	// BFS/DFS 전용 그래프(인접 리스트를 이용한 그래프)
	class OwnBFSDFSGraph
	{
	public:
		OwnBFSDFSGraph() {
			graphList = vector<vector<int>>();
		}

	private:
		vector<vector<int>> graphList;
	};
}
