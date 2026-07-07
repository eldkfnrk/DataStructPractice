#include "MyOwnBFSDFS.h"

namespace Algorithm {
	// 단순 순회 문제를 해결하는 BFS/DFS
	namespace Traversal {
		// 문제 1. 단순 순회 - 시작 정점에서 방문한 정점을 순서대로 출력해보기
		void BFS(int start, const vector<vector<int>>& searchGraph)
		{
			// BFS는 넓게 퍼져나가는 개념으로 각 층을 검사한다. 그렇기에 정점과 맞닿은 정점을 큐에 넣는 방식으로 진행된다.(이는 트리의 레벨 순서 순회와 유사하다.)
			queue<int> bfsQueue;
			int floor = 0;  // 방문하고 있는 계층이 어딘지 저장할 변수
			size_t queueLength = 0;
			vector<bool> visited = vector<bool>(searchGraph.size(), false);  // 방문하였는지를 저장하는 bool형 배열(각 인덱스에 해당하는 요소의 값을 바꾸는 것으로 true면 방문했음을 false면 아직 방문하지 않았음을 의미)

			// 문제 1
			// 인접 리스트를 활용한 그래프 사용
			// 문제 1을 구현하고 AI에게 얻은 개선 사항
			// 1. 시작 정점이 누락되고 있는데 시작 정점 또한 방문해야 할 정점으로 보아야 한다. 그래서 시작 정점은 어딘지도 처리를 해주어야 한다.
			// 2. visited라는 배열의 크기를 10으로 명시해놨는데 지금은 동작하지만 범용성이 떨어지기 때문에 그래프의 크기에 맞도록 수정하여야 한다.
			// 3. 인자로 배열을 그대로 받아오는 것은 복사로 받아오는 것이기 때문에 메모리 낭비가 발생한다. 데이터가 적은 지금은 괜찮으나 10만개 같이 엄청난 데이터를 가져올 때는 문제가 생기니 참조자나 포인터를 사용해서 복사가 아닌 접근을 해야 한다.(const로 변경되지 않도록 하는 것도 있어야 한다.)
			// 4. 큐에 시작 정점 인근 정점을 넣고 시작하는데 그래도 되지만 굳이 while 문에서 동일한 동작을 하고 있기 때문에 이는 불필요한 동작이다. while문 안에서 처리할 수 있도록 수정하여야 한다.
			// 5. while문이 끝나는 조건을 while문 안에 넣어놔서 다른 사람이 코드를 볼 때 직관적이지 않게 되어 있다. 그러니 직관적으로 볼 수 있도록 조건문을 수정해야 한다.(큐가 비어있다면 종료할 수 있도록 하면 될 것이다.)
			// 6. 큐의 size는 size_t 형태인데 int와 비교하고 있어서 문제가 발생할 수 있다. 그러니 이를 수정해야 한다.(현재는 문제가 없지만 컴파일러에 따라 문제가 있을 수 있다. 그러니 항상 자료형을 일치시키는 습관을 들여야 한다.)
			// 그리고 절대로 헤더 파일과 cpp 파일의 함수 형태는 동일해야 링크 오류가 발생하지 않는다. 자꾸 cpp는 바꾸고 헤더를 안 바꾸거나 헤더는 바꾸고 cpp는 안 바꿔서 이런 오류가 발생하는데 절대 망각하지 말아야 한다.(이 때문에 무의미하게 AI를 사용하는 시간을 소모하였다.)

			//bfsQueue.push(start);
			//visited[start] = true;

			//while (!bfsQueue.empty()) {
			//	queueLength = bfsQueue.size();
			//	
			//	if (floor == 0)
			//		std::cout << "시작 정점 : ";
			//	else
			//		std::cout << "거리 " << floor << " : ";

			//	for (size_t i = 0; i < queueLength; i++) {
			//		int vertexIndex = bfsQueue.front();
			//		bfsQueue.pop();
			//		std::cout << "Vertex " << vertexIndex << "  ";
			//		// 삭제한 인덱스 정점과 연결된 정점의 인덱스 번호 모두를 큐에 저장
			//		for (size_t j = 0; j < searchGraph[vertexIndex].size(); j++) {
			//			int insertVertexIndex = searchGraph[vertexIndex][j];
			//			if (visited[insertVertexIndex])  // 삽입하려는 정점이 이미 방문한 정점이면 건너뛴다.
			//				continue;
			//			bfsQueue.push(insertVertexIndex);
			//			visited[insertVertexIndex] = true;
			//		}
			//	}
			//	
			//	std::cout << std::endl;
			//	++floor;
			//}

			// 인접 행렬을 활용한 그래프 사용
			// 문제 1을 구현하고 AI에게 얻은 개선 사항
			// 1. 무방향과 무가중치를 상정한 그래프로 범용성이 떨어진다.(정점에서 뻗어나가는지만 확인하면 되고 양방향임을 검증하려 할 이유가 없다.)
			// 2. 큐에 데이터를 삭제하는 타이밍이 맨 끝에 있어서 의도치 않은 위험성을 갖고 있으니 삭제할 데이터는 따로 저장 후 바로 삭제하여야 위험이 줄어든다.
			visited[start] = true;
			bfsQueue.push(start);

			while (!bfsQueue.empty()) {
				queueLength = bfsQueue.size();

				if (floor == 0) {
					std::cout << "시작 정점 : ";
				}
				else {
					std::cout << "거리" << floor << " : ";
				}

				for (size_t i = 0; i < queueLength; i++) {
					int vertexIndex = bfsQueue.front();
					bfsQueue.pop();
					for (size_t j = 0; j < searchGraph[vertexIndex].size(); j++) {
						if (searchGraph[vertexIndex][j] == 1 && searchGraph[j][vertexIndex] == 1) {
							if (visited[j])
								continue;
							visited[j] = true;
							bfsQueue.push(j);
						}
					}
					std::cout << "정점" << vertexIndex << " ";
				}

				std::cout << std::endl;
				++floor;
			}
		}

		vector<bool> dfsVisited;
		int startVertex;

		// 문제 1을 구현하고 AI에게 얻은 개선 사항
		// 재귀 DFS에 관한 문제점
		// 1. 방문 여부를 저장하는 visited 배열이 static 선언되어 있어서 재활용이 안 됨
		// 스택 DFS에 관한 문제점
		// 1. index 변수를 전역처럼 모든 정점이 공유해서 사용하고 있음 
		// 2. 스택 DFS에 어떤 정보가 저장되어서 넘어가야 하는지 파악하지 못하고 있음
		// 공통적인 문제점 - 출력 형태가 BFS와 다르다. 두 함수의 출력 형태가 일관성이 있어야 한다.
		void DFS(int start, const vector<vector<int>>& searchGraph)
		{
			// DFS는 깊게 파고드는 개념으로 연결된 끝까지 검사한다. 그렇기에 정점과 연결된 정점 그리고 그 정점에 연결된 정점으로 가는 것을 반복하여 끝을 보니 스택 혹은 재귀 방식으로 진행된다.(이는 트리의 전위 순회와 유사하다.)
			// DFS는 2가지 방법으로 만들 수 있는데 하나는 스택에 저장하면서 출력해 나가는 것이고 하나는 함수 자체를 재귀하여 나가는 것이다. 두 가지를 모두 한 번 만들어 볼 것이다.
			// 재귀를 사용하는 방법
			//static vector<bool> visited = vector<bool>(searchGraph.size(), false);  // 재귀를 사용하면 해당 배열이 계속 생성되기 때문에 원할한 방문 기록을 남길 수 없으니 정적 선언을 하여 메모리에 올려놓아서 초기화가 1번만 되도록 설정

			//if (visited[start]) {
			//	std::cout << std::endl;
			//	return;
			//}

			//visited[start] = true;
			//std::cout << "정점" << start << " - ";

			//for (size_t i = 0; i < searchGraph[start].size(); i++) {
			//	DFS(searchGraph[start][i], searchGraph);
			//}

			//// 스택을 사용하는 방법
			//stack<int> dfsStack;
			//dfsStack.push(start);

			//vector<bool> visited = vector<bool>(searchGraph.size(), false);
			//visited[start] = true;

			//int nextVertex = 0;
			//int index = 0;
			//int curVertex = 0;

			//std::cout << "시작 정점 : 정점" << start << std::endl;

			//while (!dfsStack.empty()) {
			//	curVertex = dfsStack.top();
			//	if ((size_t)index >= searchGraph[curVertex].size()) {
			//		index = 0;
			//		dfsStack.pop();
			//		std::cout << std::endl;
			//		continue;
			//	}

			//	nextVertex = searchGraph[curVertex][index];
			//	if (visited[nextVertex]) {
			//		++index;
			//		continue;
			//	}
			//	dfsStack.push(nextVertex);
			//	visited[nextVertex] = true;
			//	std::cout << "정점" << nextVertex << " - ";
			//}

			// 인접 행렬을 이용한 DFS
			// 스택을 이용하는 방법
			//stack<int> dfsStack;
			//dfsStack.push(start);
			//vector<bool> visited = vector<bool>(searchGraph.size(), false);
			//visited[start] = true;

			//size_t vectorLength = searchGraph.size();  // 모든 배열 길이가 같기 때문에 이렇게 하여도 된다.

			//std::cout << "정점" << start << " ";

			//// 방문 순서
			//while (!dfsStack.empty()) {
			//	int currentVertex = dfsStack.top();
			//	for (size_t i = 0; i < vectorLength; i++) {
			//		if (searchGraph[currentVertex][i] == 1 && !visited[i]) {
			//			visited[i] = true;
			//			dfsStack.push(i);
			//			std::cout << "정점" << i << " ";
			//			break;
			//		}

			//		// 위의 모든 과정을 거쳤음에도 이 if문의 조건에 걸린 것은 더 이상 이 정점과 연결되어 있으면서 방문한 적이 없는 정점이 없다는 것이다.
			//		if (i == vectorLength - 1) {
			//			dfsStack.pop();
			//		}
			//	}
			//}

			// 재귀를 이용하는 방법
			size_t vectorLength = searchGraph.size();

			// dfsVisited는 비어있는 전역 배열
			// startVertex는 재귀가 모두 끝나고 시작 정점의 함수까지 끝나기 전에 dfsVisited를 다시 비어 있는 배열로 만들기 위해 시작 정점이 무엇인지 기억하는 전역 변수
			if (dfsVisited.empty()) {
				dfsVisited = vector<bool>(searchGraph.size(), false);
				dfsVisited[start] = true;
				startVertex = start;
			}

			std::cout << "정점" << start << " ";

			for (size_t i = 0; i < vectorLength; i++) {
				if (searchGraph[start][i] == 1 && !dfsVisited[i]) {
					dfsVisited[i] = true;
					DFS(i, searchGraph);
				}
			}

			if (startVertex == start)
				dfsVisited.clear();
		}
	}
	
	// 그래프 연결성 문제를 해결하는 BFS/DFS
	// 문제 - 연결 요소 개수 세기 => 연결된 노드의 묶음이 몇 개인지를 세라는 의미
	namespace ConnectVertexCount {
		vector<bool> bfsVisited;
		vector<bool> dfsVisited;

		void BFS(const vector<vector<int>>& searchGraph) {
			// 인접 리스트 방식
			queue<int> bfsQueue;
			int count = 0;
			bfsVisited = vector<bool>(searchGraph.size(), false);
			size_t visitedListLength = bfsVisited.size();

			//while (startVertex < (int)visitedListLength) {
			//	if (!bfsVisited[startVertex]) {
			//		bfsQueue.push(startVertex);
			//		bfsVisited[startVertex] = true;
			//		++count;
			//		std::cout << "연결" << count << std::endl;
			//		std::cout << "정점" << startVertex << " ";
			//	}

			//	size_t queueLength = bfsQueue.size();

			//	for (size_t i = 0; i < queueLength; i++) {
			//		int frontQueue = bfsQueue.front();
			//		bfsQueue.pop();
			//		for (size_t j = 0; j < searchGraph[frontQueue].size(); j++) {
			//			int visitVertex = searchGraph[frontQueue][j];
			//			if (!bfsVisited[visitVertex]) {
			//				bfsVisited[visitVertex] = true;
			//				bfsQueue.push(visitVertex);
			//				std::cout << "정점" << visitVertex << " ";
			//			}
			//		}
			//	}

			//	if (bfsQueue.empty()) {
			//		for (size_t i = 0; i < visitedListLength; i++) {
			//			if (!bfsVisited[i]) {
			//				startVertex = (int)i;
			//				break;
			//			}

			//			if (i == (int)visitedListLength - 1) {
			//				startVertex = (int)visitedListLength;
			//			}
			//		}
			//	}
			//}

			// 인접 행렬 방식
			size_t matrixSize = searchGraph.size();

			for (size_t i = 0; i < visitedListLength; i++) {
				if (!bfsVisited[i]) {
					bfsVisited[i] = true;
					bfsQueue.push(i);
					std::cout << "연결" << ++count << std::endl;
				}

				while (!bfsQueue.empty()) {
					// 레벨 순서 순회를 포함한 동작
					/*size_t queueLength = bfsQueue.size();
					for (size_t j = 0; j < queueLength; j++) {
						int currentVertex = bfsQueue.front();
						bfsQueue.pop();
						std::cout << "정점" << currentVertex << " ";
						for (size_t k = 0; k < matrixSize; k++) {
							if (searchGraph[currentVertex][k] == 1) {
								if (!bfsVisited[k]) {
									bfsVisited[k] = true;
									bfsQueue.push(k);
								}
							}
						}
					}*/

					// 레벨 순서 순회를 포함하지 않는 동작
					int currentVertex = bfsQueue.front();
					bfsQueue.pop();
					std::cout << "정점" << currentVertex << " ";
					for (size_t k = 0; k < matrixSize; k++) {
						if (searchGraph[currentVertex][k] == 1) {
							if (!bfsVisited[k]) {
								bfsVisited[k] = true;
								bfsQueue.push(k);
							}
						}
					}
				}
			}

			cout << endl << "총 연결 요소 개수 : " << count << endl;
		}

		void DFS(const vector<vector<int>>& searchGraph)
		{
			// 스택 사용 DFS
			int count = 0;
			dfsVisited.assign(searchGraph.size(), false);

			// 인접 리스트 방식
			//stack<int> dfsStack;
			//for (size_t i = 0; i < dfsVisited.size(); i++) {
			//	if (!dfsVisited[i]) {
			//		std::cout << "연결" << ++count << std::endl;
			//		dfsStack.push(i);
			//		dfsVisited[i] = true;
			//		std::cout << "정점" << i << " ";
			//		while (dfsStack.size() != 0) {
			//			int currentVertex = dfsStack.top();
			//			int connectVertexCount = searchGraph[currentVertex].size();
			//			for (size_t j = 0; j < connectVertexCount; j++) {
			//				int connectVertex = searchGraph[currentVertex][j];
			//				if (!dfsVisited[connectVertex]) {
			//					dfsVisited[connectVertex] = true;
			//					dfsStack.push(connectVertex);
			//					std::cout << "정점" << connectVertex << " ";
			//					break;
			//				}
			//			}

			//			// 위의 반복문을 통해서 스택으로 값이 들어가지 않았다면 더 이상 찾을 요소가 없는 것으로 판단
			//			if (currentVertex == dfsStack.top()) {
			//				dfsStack.pop();
			//			}
			//		}
			//		std::cout << std::endl;
			//	}
			//}

			// 인접 행렬 방식
			stack<pair<int, int>> dfsStack;

			size_t matirxSize = searchGraph.size();
			for (size_t i = 0; i < dfsVisited.size(); i++) {
				if (!dfsVisited[i]) {
					dfsVisited[i] = true;
					dfsStack.push(make_pair(i, 0));
					cout << "연결" << ++count << endl;
					cout << "정점" << i << " ";
				}

				if (dfsStack.empty())
					continue;

				while (!dfsStack.empty()) {
					pair<int, int>* currentVertex = &dfsStack.top();
					for (size_t j = currentVertex->second; j < matirxSize; j++) {
						++currentVertex->second;
						if (searchGraph[currentVertex->first][j] == 1) {
							if (!dfsVisited[j]) {
								dfsVisited[j] = true;
								dfsStack.push(make_pair(j, 0));
								cout << "정점" << j << " ";
								break;
							}
						}
					}

					if (currentVertex->second == matirxSize)
						dfsStack.pop();
				}

				cout << endl;
			}

			std::cout << "총 연결 요소 개수 : " << count << std::endl;
		}

		void DFS(const vector<vector<int>>& searchGraph, int start) {
			// 재귀 사용 DFS
			
			// 인접 리스트 방식
			//dfsVisited[start] = true;
			//std::cout << "정점" << start << " ";
			//int connectVertexCount = searchGraph[start].size();

			//for (size_t i = 0; i < connectVertexCount; i++) {
			//	int currentVertex = searchGraph[start][i];
			//	if (!dfsVisited[currentVertex]) {
			//		DFS(searchGraph, currentVertex);
			//	}
			//}

			// 인접 행렬 방식
			size_t matrixSize = searchGraph.size();
			dfsVisited[start] = true;
			cout << "정점" << start << " ";
			
			for (size_t i = 0; i < matrixSize; i++) {
				if (searchGraph[start][i] == 1) {
					if (!dfsVisited[i])
						DFS(searchGraph, i);
				}
			}
		}

		void CountConnectComponent(const vector<vector<int>>& searchGraph)
		{
			dfsVisited.assign(searchGraph.size(), false);
			int count = 0;

			for (size_t i = 0; i < dfsVisited.size(); i++) {
				if (!dfsVisited[i]) {
					std::cout << "연결" << ++count << std::endl;
					DFS(searchGraph, i);
					std::cout << std::endl;
				}
			}

			std::cout << "총 연결 요소 개수 : " << count << std::endl;
		}
	}

	// Flood Fill 문제를 해결하는 BFS/DFS
	namespace FloodFill {
		// 모든 문제는 대각선은 체크하지 않고 상하좌우만 체크
		// 문제1 : 시작 지점과 동일한 값을 가진 영역을 확인하는 Flood Fill
		// 문제2 : 몇 개의 영역이 있는지 검사하는 Flood Fill

		// BFS - 시작 위치에 인접한 모든 이웃 검사, 그 다음 단계로 넓혀가는 방식
		void FloodFillBFS(const vector<vector<int>>& searchGraph, int startX, int startY)
		{
			// 문제1
			queue<pair<int,int>> bfsQueue;

			int count = 0;  // 영역 안에 몇 개의 값이 있는지 개수를 세는 변수

			vector<vector<bool>> visited = vector<vector<bool>>(searchGraph.size(), vector<bool>(searchGraph[0].size(), false));

			bfsQueue.push(make_pair(startX, startY));
			visited[startX][startY] = true;
			++count;

			while (!bfsQueue.empty()) {
				pair<int, int> frontValue = bfsQueue.front();
				int x = frontValue.first;
				int y = frontValue.second;

				if (y - 1 >= 0) {
					if (searchGraph[x][y - 1] == searchGraph[x][y] && !visited[x][y - 1]) {
						visited[x][y - 1] = true;
						bfsQueue.push(make_pair(x, y - 1));
						++count;
					}
				}

				if (y + 1 < searchGraph.size()) {
					if (searchGraph[x][y + 1] == searchGraph[x][y] && !visited[x][y + 1]) {
						visited[x][y + 1] = true;
						bfsQueue.push(make_pair(x, y + 1));
						++count;
					}
				}

				if (x - 1 >= 0) {
					if (searchGraph[x - 1][y] == searchGraph[x][y] && !visited[x - 1][y]) {
						visited[x - 1][y] = true;
						bfsQueue.push(make_pair(x - 1, y));
						++count;
					}
				}

				if (x + 1 < searchGraph[x].size()) {
					if (searchGraph[x + 1][y] == searchGraph[x][y] && !visited[x + 1][y]) {
						visited[x + 1][y] = true;
						bfsQueue.push(make_pair(x + 1, y));
						++count;
					}
				}

				bfsQueue.pop();
			}

			// Flood Fill로 찾은 영역은 X 표시, 찾지 못하거나 아닌 영역은 자기 값 그대로 출력
			for (size_t i = 0; i < searchGraph.size(); i++) {
				for (size_t j = 0; j < searchGraph[i].size(); j++) {
					if (visited[i][j])
						cout << "X" << " ";
					else
						cout << searchGraph[i][j] << " ";
				}
				cout << endl;
			}

			cout << "영역 안의 요소 개수 : " << count << endl;
		}

		// DFS - 시작 위치와 동일한 이웃 발견 시 그 방향으로 끝까지 파고드는 방식
		void FloodFillDFS(const vector<vector<int>>& searchGraph, int startX, int startY)
		{

		}
	}
}