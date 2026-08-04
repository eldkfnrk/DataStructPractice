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
			queue<pair<int, int>> bfsQueue;
			vector<vector<bool>> visited;
			for (int i = 0; i < (int)searchGraph.size(); i++) {
				visited.push_back(vector<bool>(searchGraph[i].size(), false));
			}
			// 상하좌우에 해당하는 값을 저장한 배열(여기에 대각선을 추가하는 것도 가능하다.)
			// dx는 x를 dy는 y를 상하좌우에 맞게 값을 맞추도록 하기 위해 추가한 배열
			int dx[] = { 0,0,-1,1 };
			int dy[] = { -1,1,0,0 };

			// 문제1

			//int count = 0;  // 영역 안에 몇 개의 값이 있는지 개수를 세는 변수

			//bfsQueue.push(make_pair(startX, startY));
			//int target = searchGraph[startX][startY];
			//visited[startX][startY] = true;
			//++count;

			//while (!bfsQueue.empty()) {
			//	pair<int, int> frontValue = bfsQueue.front();
			//	int x = frontValue.first;
			//	int y = frontValue.second;

			//	for (int i = 0; i < 4; i++) {
			//		int nx = x + dx[i];
			//		int ny = y + dy[i];
			//		if (nx < 0 || nx >= searchGraph.size())
			//			continue;
			//		if (ny < 0 || ny >= searchGraph[nx].size())
			//			continue;

			//		if (searchGraph[nx][ny] == target && !visited[nx][ny]) {
			//			bfsQueue.push(make_pair(nx, ny));
			//			visited[nx][ny] = true;
			//			++count;
			//		}
			//	}

			//	bfsQueue.pop();
			//}

			//// Flood Fill로 찾은 영역은 X 표시, 찾지 못하거나 아닌 영역은 자기 값 그대로 출력
			//for (size_t i = 0; i < searchGraph.size(); i++) {
			//	for (size_t j = 0; j < searchGraph[i].size(); j++) {
			//		if (visited[i][j])
			//			cout << "X" << " ";
			//		else
			//			cout << searchGraph[i][j] << " ";
			//	}
			//	cout << endl;
			//}

			//cout << "영역 안의 요소 개수 : " << count << endl;

			// 이 코드의 반드시 고쳐야 할 점
			// 1. 범위 계산이 잘못 되고 있다.(y는 열을 나타내는데 행의 개수와 비교하고 있고 x는 반대로 행인데 열의 개수와 비교하고 있다.(y+1 비교와 x+1 비교 부분을 의미) -> 버그 발생 - 수정 완료
			
			// 아쉬운 부분
			// 1. if문을 따로따로 4회 실시하고 있으며 이로 인해 확장성이 막히고 있다.(보통 이런 경우 배열로 상하좌우를 가질 수 있도록 하는데 이렇게 하면 여기에 대각선도 추가할 수 있는 좋은 확장성을 가진다.) - 수정 완료
			// 2. target 즉, 찾고 있는 값을 알지 저장하지 않고 있어서 딱 시작점부터의 영역만 검색이 가능한데 이를 저장한다면 동일한 값을 가진 각각의 모든 영역을 탐색할 수 있다. - 수정 완료


			// 문제2

			int elementCount = 0;
			int areaCount = 0;
			int target = searchGraph[startX][startY];
			vector<int> count;  // 각 영역의 요소 개수를 저장하는 배열

			for (int i = 0; i < (int)searchGraph.size(); i++) {
				for (int j = 0; j < (int)searchGraph[i].size(); j++) {
					if (searchGraph[i][j] == target && !visited[i][j]) {
						visited[i][j] = true;
						bfsQueue.push(make_pair(i, j));
						++areaCount;
						++elementCount;
						// 따로 함수로 만들어도 되지만 이번에는 그냥 하나의 함수 내에서 모두 진행
						while (!bfsQueue.empty()) {
							pair<int, int> frontValue = bfsQueue.front();
							for (int k = 0; k < 4; k++) {
								int nx = frontValue.first + dx[k];
								int ny = frontValue.second + dy[k];

								if (nx >= searchGraph.size() || nx < 0)
									continue;

								if (ny >= searchGraph[nx].size() || ny < 0)
									continue;

								if (searchGraph[nx][ny] == target && !visited[nx][ny]) {
									visited[nx][ny] = true;
									bfsQueue.push(make_pair(nx, ny));
									++elementCount;
								}
							}
							bfsQueue.pop();
						}
						count.push_back(elementCount);
						elementCount = 0;
					}
				}
			}

			for (int i = 0; i < (int)count.size(); i++) {
				cout << "영역" << i + 1 << "의 요소 개수 : " << count[i] << endl;
			}

			// 혹시나 영역이 어떻게 되어있나 궁금할 수 있으니 탐색한 영역 출력
			for (int i = 0; i < (int)searchGraph.size(); i++) {
				for (int j = 0; j < (int)searchGraph[i].size(); j++) {
					if (visited[i][j])
						cout << "X ";
					else
						cout << searchGraph[i][j] << " ";
				}
				cout << endl;
			}

			cout << "영역의 총 개수 : " << areaCount << endl;

			// 아쉬운 점
			// 1. areaCount 변수로 영역 개수를 세놓고 사용하지 않았다. - 수정 완료(그러나 이 부분은 요소 개수를 저장한 배열의 크기를 가지고 해도 되기 때문에 굳이 변수를 만들 필요가 없었다. - 참고용)
		}

		// DFS - 시작 위치와 동일한 이웃 발견 시 그 방향으로 끝까지 파고드는 방식
		// DFS는 구현 방법이 2개
		// 스택을 사용하는 방법과 재귀를 사용하는 방법
		// 모든 문제는 대각선은 체크하지 않고 상하좌우만 체크
		// 문제1 : 시작 지점과 동일한 값을 가진 영역을 확인하는 Flood Fill
		// 문제2 : 몇 개의 영역이 있는지 검사하는 Flood Fill
		void FloodFillDFS(const vector<vector<int>>& searchGraph, int startX, int startY)
		{
			// 문제 1
			int count = 0;  // 영역 안에 존재하는 요소의 개수를 세는 변수
			stack<pair<int, int>> dfsStack;

			vector<vector<bool>> visited;
			for (int i = 0; i < (int)searchGraph.size(); i++) {
				visited.push_back(vector<bool>(searchGraph[i].size(), false));
			}

			int dx[] = { 0,0,-1,1 };
			int dy[] = { -1,1,0,0 };

			int target = searchGraph[startX][startY];

			//dfsStack.push(make_pair(startX, startY));
			//visited[startX][startY] = true;
			//++count;

			//while (!dfsStack.empty()) {
			//	pair<int, int> topValue = dfsStack.top();
			//	int x = topValue.first;
			//	int y = topValue.second;

			//	for (int i = 0; i < 4; i++) {
			//		int nx = x + dx[i];
			//		int ny = y + dy[i];

			//		// 인덱스 범위 이탈 시 오류 방지를 위한 예외 처리
			//		if (nx >= searchGraph.size() || nx < 0)
			//			continue;
			//		if (ny >= searchGraph[nx].size() || ny < 0)
			//			continue;

			//		if (searchGraph[nx][ny] == target && !visited[nx][ny]) {
			//			visited[nx][ny] = true;
			//			pair<int, int> insertValue = make_pair(nx, ny);
			//			dfsStack.push(insertValue);
			//			++count;  // 새로 찾은 값이 증가했으므로 영역의 개수를 1증가시킨다.
			//		}
			//	}

			//	// 만약 위의 반복문에서 push가 이뤄지지 않았다면 while문 첫 번째 부분에서 저장한 스택의 top 값과 지금 현재 스택의 top값이 같을 것이다.
			//	// 그렇다면 더 이상 이 값의 주변을 순회할 필요가 없으니 스택에서 삭제한다.
			//	if (topValue == dfsStack.top())
			//		dfsStack.pop();
			//}

			//for (int i = 0; i < (int)searchGraph.size(); i++) {
			//	for (int j = 0; j < (int)searchGraph[i].size(); j++) {
			//		if (visited[i][j])
			//			cout << "X ";
			//		else
			//			cout << searchGraph[i][j] << " ";
			//	}
			//	cout << endl;
			//}

			//cout << endl << "영역 안의 요소 개수 : " << count << endl;

			// 이 코드의 반드시 고쳐야 할 점
			// 1. 새 값을 저장하려면 0번부터 시작해야 하는데 i를 넣으면서 그 앞에 것들은 검사를 안 하는 경우가 발생할 수 있다.
			// 2. 현재 스택의 top 값과 반복문 처음에 스택의 top 값이 같은 것을 분석하여 pop을 결정하는 것도 동작은 하지만 우회하는 방식이기에 bool로 찾았나 못 찾았나를 검사 후 못 찾았으면 pop을 하는 방식이 더 안정되고 명확해지는 방식이다.

			// 아쉬운 부분
			// 1. 방문 지점 구조가 너무 복잡하다. 키(pair) - 값(int) 구조가 간단하지 않고 복잡하다. 그리고 굳이 이렇게까지 할 필요가 없다.
			// 2. map을 사용하면서 값을 찾는 find를 통해 O(logN)이라는 불필요한 시간 비용을 사용하고 있다. 이것 또한 굳이 필요치 않다. 
			// 3. 굳이 map을 clear()할 필요가 없다.
			// 1, 2, 3번 문제 모두 굳이 map 사용을 하지 않고 방문마다 4방향 검사를 하는 것이 낫다라는 것을 가리키고 있다. 이건 괜찮은 시도이나 Flood Fill에서는 과한 설계로 비용 낭비로 이어졌다.

			// 위의 고쳐야 할 점, 아쉬운 부분 모두 억지로 어디까지 진행했는지를 저장하려고 해서 생긴 것인데 더 근본적으로 굳이 이렇게 설계하지 않고 BFS처럼 한 번에 4방향을 모두 삽입하고 스택에서 데이터를 pop하면 된다.
			// 그러면 스택의 동작 원리에 따라 DFS의 깊게 탐색하는 방법이 진행된다. 즉, Flood Fill에서는 BFS나 DFS나 동작은 다른 게 없다. 단지 자료구조에 따른 탐색 방법의 차이가 있을 뿐인 것이다. - 수정 완료

			// 문제 2
			vector<int> elementInArea;
			for (int i = 0; i < (int)searchGraph.size(); i++) {
				for (int j = 0; j < (int)searchGraph[i].size(); j++) {
					if (searchGraph[i][j] == target && !visited[i][j]) {
						visited[i][j] = true;
						dfsStack.push(make_pair(i, j));
						++count;
						while (!dfsStack.empty()) {
							pair<int, int> topValue = dfsStack.top();
							dfsStack.pop();
							for (int k = 0; k < 4; k++) {
								int nx = topValue.first + dx[k];
								int ny = topValue.second + dy[k];

								if (nx >= searchGraph.size() || nx < 0)
									continue;
								if (ny >= searchGraph[nx].size() || ny < 0)
									continue;

								if (searchGraph[nx][ny] == target && !visited[nx][ny]) {
									visited[nx][ny] = true;
									dfsStack.push(make_pair(nx, ny));
									++count;
								}
							}
						}
						elementInArea.push_back(count);
						count = 0;
					}
				}
			}

			for (int i = 0; i < (int)elementInArea.size(); i++) {
				cout << "영역 " << i + 1 << " 요소 개수 : " << elementInArea[i] << endl;
			}

			for (int i = 0; i < (int)searchGraph.size(); i++) {
				for (int j = 0; j < (int)searchGraph[i].size(); j++) {
					if (visited[i][j])
						cout << "X ";
					else
						cout << searchGraph[i][j] << " ";
				}
				cout << endl;
			}

			cout << "영역의 총 개수 : " << elementInArea.size() << endl;
		}

		vector<vector<bool>> recursionDfsVisted;
		const int dx[] = { 0,0,-1,1 };
		const int dy[] = { -1,1,0,0 };

		void CountElement(const vector<vector<int>>& searchGraph, int startX, int startY)
		{
			recursionDfsVisted = vector<vector<bool>>(searchGraph.size(), vector<bool>(searchGraph[0].size(), false));
			int target = searchGraph[startX][startY];
			int count = 0;
			// 문제 1
			//FloodFillRecursionDFS(searchGraph, recursionDfsVisted, startX, startY, target);

			//for (int i = 0; i < (int)searchGraph.size(); i++) {
			//	for (int j = 0; j < (int)searchGraph[i].size(); j++) {
			//		if (recursionDfsVisted[i][j]) {
			//			cout << "X ";
			//			++count;
			//		}
			//		else
			//			cout << searchGraph[i][j] << " ";
			//	}
			//	cout << endl;
			//}
			//cout << endl << "영역 안의 요소 개수 : " << count << endl;

			// 개선 사항
			// 1. 방문 여부 저장 배열의 초기화 시 열의 개수를 초기화 할 때 [startX]를 사용하는데 이보다는 [0]이 더 일반적이고 안전하다.(행마다 열의 개수가 다를 경우에는 이와 같이 진행하여야 오류가 없다.) - 수정 완료
			// 2. 출력을 위한 반복문에서 열의 개수를 확인하기 위한 for문의 탈출 조건에 행의 개수를 확인하는 오류가 있다.(searchGraph[i].size()여야 열의 개수를 확인하는데 searchGraph.size()를 하면서 행의 개수를 확인하는 오류를 범하고 있다.) - 수정 완료
			// 3. 상하좌우를 구분하기 위해 만든 배열이 재귀할 때마다 생기고 있기 때문에 메모리 낭비가 있게 되니 따로 빼서 사용하는 것이 좋다.(값이 변할 일이 없으니 const를 하여 수정을 방지하는 것이 좋다.) - 수정 완료
			// 4. DFS 내에서 방문 여부를 확인하고 방문했음을 저장하는데 이미 DFS가 호출된 순간 방문을 한 것이니 방문했음을 저장하면 되는데 필요 없이 조건문을 사용하고 있으므로 이는 수정하여야 한다. - 수정 완료
			// 5. 방문 여부를 저장하는 배열이나 시작 지점의 값(타겟)을 매번 생성하기 싫어서 전역으로 두거나 반복 초기화하는 것보다 지역으로 두고 이 값을 매개 변수로 넘기는 것이 메모리적으로나 안정성 측면에서 좋기 때문에 필요한 건 매개 변수로 전달하는 것이 좋다. - 수정 완료

			// 문제 2
			// 문제 2번을 해결하는 데에 있어서 DFS는 변형이 필요 없었고 그저 무엇을 얻으려 하는지 몇 번 반복할 것인지 등을 정의한 이 함수만 수정하면 되었다.
			for (int i = 0; i < (int)searchGraph.size(); i++) {
				for (int j = 0; j < (int)searchGraph[i].size(); j++) {
					if (searchGraph[i][j] == target && !recursionDfsVisted[i][j]) {
						FloodFillRecursionDFS(searchGraph, recursionDfsVisted, i, j, target);
						++count;
					}
				}
			}

			for (int i = 0; i < (int)searchGraph.size(); i++) {
				for (int j = 0; j < (int)searchGraph[i].size(); j++) {
					if (recursionDfsVisted[i][j])
						cout << "X ";
					else
						cout << searchGraph[i][j] << " ";
				}
				cout << endl;
			}

			cout << endl << "총 영역 개수 : " << count << endl;
		}

		// 재귀 방식 DFS
		void FloodFillRecursionDFS(const vector<vector<int>>& searchGraph, vector<vector<bool>>& visited, int startX, int startY, int target)
		{
			// 문제 1
			visited[startX][startY] = true;

			for (int i = 0; i < 4; i++) {
				int nx = startX + dx[i];
				int ny = startY + dy[i];

				if (nx >= searchGraph.size() || nx < 0)
					continue;

				if (ny >= searchGraph[nx].size() || ny < 0)
					continue;

				if (searchGraph[nx][ny] == target && !recursionDfsVisted[nx][ny]) {
					recursionDfsVisted[nx][ny] = true;
					FloodFillRecursionDFS(searchGraph, visited, nx, ny, target);
				}
			}
		}
	}

	// 최단 거리 BFS 문제를 해결하는 BFS
	namespace ShortestPath {
		// 부모 노드가 어느 방향에 있는지 저장하는 열거형
		enum Direction {
			Up,
			Down,
			Left,
			Right,
			None,  // 출발지이기 때문에 부모 노드가 없을 수 있으니 이를 알리기 위한 값
			NoVisit,
		};

		struct node
		{
			pair<int, int> nodeLocation;
			Direction dir;
		};

		// 노드를 저장하기 위한 해시 테이블
		class NodeHashTable {
		public:
			NodeHashTable(const vector<vector<int>>& searchgraph) {
				maxX = (int)searchgraph.size();
				maxY = (int)searchgraph[0].size();
				for (int i = 0; i < maxX + maxY - 1; i++) {
					directions.push_back(vector<pair<Direction, int>>());
				}
			}

			void Insert(const node& insertNode) {
				pair<int, int> loc = insertNode.nodeLocation;
				if (loc.first >= maxX || loc.second >= maxY) {
					cout << "삽입 불가" << endl;
					return;
				}
				int key = Hashing(loc);
				pair<Direction, int> direction = make_pair(insertNode.dir, loc.first);
				directions[key].push_back(direction);
			}

			Direction Find(const pair<int, int>& FindLoc) {
				int key = Hashing(FindLoc);
				if (directions[key].empty()) {
					cout << "해당 위치의 값이 저장되어 있지 않음" << endl;
					return Direction::NoVisit;
				}

				Direction dir = Direction::NoVisit;
				int vectorSize = (int)directions[key].size();

				if (vectorSize == 1) {
					if (directions[key][0].second == FindLoc.first)
						dir = directions[key][0].first;
				}
				else {
					for (int i = 0; i < vectorSize; i++) {
						if (directions[key][i].second == FindLoc.first) {
							dir = directions[key][i].first;
							break;
						}
					}
				}

				if (dir == Direction::NoVisit)
					cout << "해당 위치의 값이 저장되어 있지 않음" << endl;

				return dir;
			}

		private:
			int Hashing(const pair<int, int>& loc) {
				return loc.first + loc.second;
			}

			int maxX;
			int maxY;
			vector<vector<pair<Direction, int>>> directions;
		};

		void ShortestPathBFS(const vector<vector<int>>& searchgraph, pair<int, int> startNode, pair<int, int> endNode)
		{
			if (searchgraph.empty()) {
				cout << "행렬에 값이 존재하지 않음으로 실행 종료" << endl;
				return;
			}

			if (startNode == endNode) {
				cout << "출발지와 도착지가 같음으로 실행 종료" << endl;
				return;
			}

			// 최단 거리를 찾았을 때 자신의 앞 노드 값을 알면 어떤 길로 왔는지 쉽게 알 수 있다.
			// 혹은 자신을 기준으로 부모 노드가 어느 방향에 있었는지를 알아도 진행된 경로를 추정할 수 있다.

			queue<node> bfsQueue;
			vector<vector<bool>> visited;
			// 모든 행의 개수가 일치하고 모든 열의 개수가 일치하는 행렬이라는 것을 알고 이를 사용하기 위한 방문 여부 저장 배열
			visited = vector<vector<bool>>(searchgraph.size(), vector<bool>(searchgraph[0].size(), false));

			NodeHashTable visitedNodes(searchgraph);

			int startX = startNode.first;
			int startY = startNode.second;

			int canMoveValue = 0;
			int targetX = endNode.first;
			int targetY = endNode.second;

			int dx[] = { 0,0,-1,1 };
			int dy[] = { -1,1,0,0 };

			bool findDestination = false;  // 목적지를 찾은 경우 true가 되는 변수

			int countDistance = 0;

			visited[startX][startY] = true;

			node curNode = { make_pair(startX, startY), Direction::None };
			bfsQueue.push(curNode);
			visitedNodes.Insert(curNode);

			while (!findDestination) {
				++countDistance;
				int queueLength = (int)bfsQueue.size();

				for (int i = 0; i < queueLength; i++) {
					pair<int, int> frontValue = bfsQueue.front().nodeLocation;

					for (int j = 0; j < 4; j++) {
						int nx = frontValue.first + dx[j];
						int ny = frontValue.second + dy[j];

						if (nx < 0 || nx >= searchgraph.size())
							continue;
						if (ny < 0 || ny >= searchgraph[nx].size())
							continue;

						if (nx == targetX && ny == targetY) {
							findDestination = true;
							visited[nx][ny] = true;
							int dir = j % 2 == 0 ? j + 1 : j - 1;
							node curNode = { make_pair(nx, ny),(Direction)dir };
							visitedNodes.Insert(curNode);
							break;
						}

						if (searchgraph[nx][ny] == canMoveValue && !visited[nx][ny]) {
							visited[nx][ny] = true;
							// 짝수 값(상0,좌2)는 +1을 하면 홀수 값(하1,우3)이 되고 반대로 홀수 값은(하1,우3) -1을 하면 홀수 값(상0,좌2)가 되는 것을 활용한 식이다.
							int dir = j % 2 == 0 ? j + 1 : j - 1;  // 자식이 바라보는 부모의 방향은 부모가 바라보는 자식의 방향과 반대이기 때문에 좌-우, 상-하가 반대되게 하도록 해당 식을 사용
							node curNode = { make_pair(nx, ny),(Direction)dir };  // int형 변수 값을 열거형으로 전환
							visitedNodes.Insert(curNode);
							bfsQueue.push(curNode);
						}
					}
					if (findDestination)
						break;

					bfsQueue.pop();
				}

				if (!findDestination && bfsQueue.empty())
					break;
			}

			// 출발지에서 목적지까지 온 경로를 확인하는 과정
			
			// 이동 루트를 순서대로 확인할 수 있도록 저장하는 자료구조
			// 스택을 사용한 이유는 도착지부터 역순으로 찾아나갈 것이기 때문에 뒷 순서부터 저장이 될테니 출력할 때 위에서부터 출력할 수 있도록 하기 위해서이다.
			stack<pair<int, int>> pathStack;
			bool isComplete = false;

			pathStack.push(endNode);

			if (findDestination) {
				cout << "이동 거리 : " << countDistance << endl;
				while (!isComplete) {
					pair<int, int> curNode = pathStack.top();
					int restoreDir = (int)visitedNodes.Find(curNode);
					int nx = curNode.first + dx[restoreDir];
					int ny = curNode.second + dy[restoreDir];
					pathStack.push(make_pair(nx, ny));
					
					if (nx == startX && ny == startY)
						isComplete = true;
				}
			}
			else {
				cout << "목적지를 찾지 못하였다." << endl;
				pathStack.pop();  // 혹시 모를 상황을 대비해 스택을 비워두기 위한 pop
			}

			if (isComplete) {
				int order = 1;
				while (!pathStack.empty()) {
					pair<int, int> curNode = pathStack.top();
					if ((int)pathStack.size() == 1) {
						cout << "도착 노드 : (" << curNode.first << "," << curNode.second << ")" << endl;
					}
					else if (order != 1) {
						cout << order << "번째 방문 노드 : (" << curNode.first << "," << curNode.second << ")" << endl;
					}
					else {
						cout << "출발 노드 : (" << curNode.first << "," << curNode.second << ")" << endl;
					}
					++order;
					pathStack.pop();
				}
			}

			// 아쉬운 점
			// 1. visited에 역할을 두 개로 늘렸다.(실무에서 사용하거나 유용성이 높으려면 구조체를 따로 만들어 정리하는 방법이 읽기 쉽다.)
			// 2. 방향 값을 따로 주석을 달고 숫자만 작성하였다.(이런 방식보다는 열거형을 사용해 이름을 따로 주면 코드를 공유해야 하는 상황에 더 확실한 전달이 가능하다.)
			// 3. dx, dy와 cx, cy가 따로 존재한다.(따로 두는 것보다 하나만 두고 이걸 활용하는 방향으로 진행하는 것이 더욱 유지보수 등에서 쉽고 유리하다.)
			// 4. 탐색과 출력이 한 함수에 몰려있다.(지금은 만들어보는 시간이라 이렇게 해도 되지만 실무나 실제 사용할 예정이 있다면 따로 분리하는 연습이 필요하다.)

			// 고쳐야 할 점
			// 1. 나는 시작 노드는 이동이 불가능한 지역에서 시작해도 된다고 생각했는데 AI 분석을 받고 보니 이동 불가 지역에서 시작하면 다른 곳 이동이 불가능 할 수도 있고 아예 이동 불가 지역은 시작 지점으로 둬서는 안 된다는 생각을 하지 못하였다. 이를 검사하는 기능이 필요하다.
			// 2. 목적지도 1번과 마찬가지로 이동 가능한 지역인지 검사해서 가능한 지역인지 확인하는 것이 필요하다.
			// 3. 목적지 발견 시 바로 끝나지 않고 레벨 순회를 완료할 때까지 돈다. 이는 결과에 영향은 없지만 불필요한 동작이기에 수정이 필요하다.
			// 4. 빈 행렬인지와 시작지외 목적지의 위치가 행렬의 범위를 벗어났는지를 검사하여 혹시나 생길 문제를 미연에 방지하는 것이 좋다.
		}
	}

	// 다중 시작점 BFS 문제를 해결하는 BFS
	namespace MultiSource {
		// 이번엔 BFS와 출력을 분리해보는 작업을 함께 진행해 볼 것이다.
		// 문제는 총 4개를 해결해 볼 예정이다.
		// 문제 1. 편의점까지 최단 거리 지도 만들기 - 여러 편의점이 있다고 가정할 때 모든 칸에 대해 가장 가까운 편의점은 몇 분 걸리는 구하는 문제(1칸을 1분이라고 가정)
		// 문제 2. 좀비 감염 확산 시간 구하기 - 여러 지역에서 감염자가 발생했을 때 특정 좌표에 있는 사람이 감염되기까지 며칠이 걸릴지 구하는 문제(1칸을 하루라고 가정)
		// 문제 3. 여러 스피커의 소리 도달 범위 - 공연장에서 여러 대의 스피커가 동시에 소리를 퍼뜨린다고 할 때 가장 마지막에 소리가 도달하는 좌석까지 몇 초가 걸리는지 구하는 문제(1칸을 1초라고 가정)
		// 문제 4. 퍼지는 불 속에서 플레이어가 살아남을 수 있는가 - 불의 발원지에서 불이 퍼지고 불이 퍼지지 않은 장소로만 플레이어가 이동 가능할 때 탈출구까지 이동하여 생존이 가능한지 판단하는 문제(둘 다 동일하게 1칸씩만 이동한다고 가정)
		// 1 - 모든 칸의 거리를 구하고 이를 출력, 2 - 모든 칸의 거리를 구하고 특정 위치의 값만 출력, 3 - 모든 칸의 거리를 구하고 그 중 가장 큰 값을 출력, 4 - 모든 칸의 거리를 구하고 일반 BFS로 생존 가능 여부를 판단
		void Result(const vector<vector<int>>& searchGraph, const vector<pair<int, int>>& startLoc)
		{
			// 모든 행의 열 개수가 똑같은 행렬을 사용한다는 것을 알고 진행
			
			// 문제 1
			// 요소 값이 0이면 길 1이면 벽 2면 공사 중이라고 가정하고 0만 이동이 가능하며 편의점의 위치는 0 위에만 있을 수 있다.

			if (searchGraph.empty()) {
				cout << "탐색할 지도가 비어있다. 탐색 종료" << endl;
				return;
			}

			if (startLoc.empty()) {
				//cout << "탐색할 편의점 위치가 지정되어 있지 않다. 탐색 종료" << endl;
				cout << "스피커가 위한 자리가 지정되어 있지 않다. 탐색 종료" << endl;
				return;
			}

			for (int i = 0; i < (int)startLoc.size(); i++) {
				if (startLoc[i].first >= (int)searchGraph.size() || startLoc[i].first < 0 || startLoc[i].second >= (int)searchGraph[startLoc[i].first].size() || startLoc[i].second < 0) {
					cout << "범위를 벗어난 값이 존재. 탐색 종료" << endl;
					return;
				}
			}

			vector<vector<int>> saveDistances = vector<vector<int>>((int)searchGraph.size(), vector<int>((int)searchGraph[0].size(), -1));  // -1은 방문 불가, 실패 지역임을 의미

			//bool searchComplete = MultiSourceBFS(searchGraph, startLoc, saveDistances, 0);

			//if (!searchComplete)
			//	return;

			//for (int i = 0; i < (int)saveDistances.size(); i++) {
			//	for (int j = 0; j < (int)saveDistances[i].size(); j++) {
			//		if (saveDistances[i][j] == -1)
			//			cout << "#  ";
			//		else if (saveDistances[i][j] != 0)
			//			cout << saveDistances[i][j] << "  ";
			//		else
			//			cout << "B  ";
			//	}
			//	cout << endl;
			//}

			// 문제 3

			MultiSourceBFS(searchGraph, startLoc, saveDistances, 0);

			int maxValue = 0;
			vector<pair<int, int>> maxValuePos;

			// 최대 값을 찾을 때 해당 요소의 값이 2인 요소라면 이 요소는 제외하고 그 다음 값을 가진 요소를 찾아야 한다.
			for (int i = 0; i < (int)searchGraph.size(); i++) {
				for (int j = 0; j < (int)searchGraph[i].size(); j++) {
					cout << saveDistances[i][j] << "  ";
					if (saveDistances[i][j] > maxValue && searchGraph[i][j] == 0) {
						maxValue = saveDistances[i][j];
						maxValuePos.clear();
					}
					if (saveDistances[i][j] == maxValue && searchGraph[i][j] == 0)
						maxValuePos.push_back(make_pair(i, j));
				}
				cout << endl;
			}

			cout << "가장 마지막에 소리가 도달한 좌석 위치" << endl;
			for (int i = 0; i < (int)maxValuePos.size(); i++) {
				cout << "(" << maxValuePos[i].first << ", " << maxValuePos[i].second << ")" << endl;
			}
			cout << "가장 마지막에 소리가 도달하는 좌석까지 소리가 이동한 시간 : " << maxValue << "초" << endl;

			// 고쳐야 할 점
			// 1. 최대 값을 가진 좌석을 찾는 코드에서 좌석만 들어가도록 하는 조건이 없어 복도가 들어갈 수 있는 문제가 있다. - 수정 완료
			// 2. 시작점 거리 초기화 방식이 의도를 명확하게 전달하지 못하고 있음으로 +1을 하는 것이 아닌 0이라는 확실한 값을 전달하는 것이 나을 것이다. - 수정 완료

			// 고쳐야 할 버릇
			// 매직 넘버를 그대로 사용하는 버릇이 있는데 이를 변수를 사용해 의미를 전달하는 방법 등의 여러 방법을 이용하여 진행하는 것이 더 범용성 있고 협업이 가능한 코드가 될 것이다.
		}

		void Result(const vector<vector<int>>& searchGraph, const vector<pair<int, int>>& startLoc, const pair<int, int>& checkPoint)
		{
			// 문제 2
			// 모든 행의 열 개수가 똑같은 행렬을 사용한다는 것을 알고 진행하는 문제
			// 요소 값이 0이면 길 1이면 벽 2면 공사 중이라고 가정하고 0만 이동이 가능하며 편의점의 위치는 0 위에만 있을 수 있다.

			//if (searchGraph.empty()) {
			//	cout << "탐색할 지도가 비어있다. 탐색 종료" << endl;
			//	return;
			//}

			//if (startLoc.empty()) {
			//	cout << "탐색할 편의점 위치가 지정되어 있지 않다. 탐색 종료" << endl;
			//	return;
			//}

			//vector<vector<int>> saveDistances = vector<vector<int>>((int)searchGraph.size(), vector<int>((int)searchGraph[0].size(), -1));  // -1은 방문 불가, 실패 지역임을 의미

			//bool searchComplete = MultiSourceBFS(searchGraph, startLoc, saveDistances, 0);

			//if (!searchComplete)
			//	return;

			//for (int i = 0; i < (int)startLoc.size(); i++) {
			//	cout << "감염 시작 점" << i + 1 << " : (" << startLoc[i].first << ", " << startLoc[i].second << ")" << endl;
			//}
			//cout << "(" << checkPoint.first << ", " << checkPoint.second << ") 위치의 사람이 감염이 시작된 시점부터 감염되기까지 걸린 일 수 : " << saveDistances[checkPoint.first][checkPoint.second] << endl;
		}

		void Result(const vector<vector<int>>& searchGraph, const vector<pair<int, int>>& fireLocs, const pair<int, int>& playerLoc, const pair<int, int>& exitLoc)
		{
			// 문제 4
			// fireLocs - 불의 시작점, playerLoc - 플레이어의 위치, exitLoc - 탈출구의 위치
			// 문제 4는 여러 곳에서 퍼지는 불을 피해 플레이어가 탈출할 수 있는가를 찾는 문제로 플레이어는 불이 퍼지지 않은 위치로만 이동이 가능하다.

			// 불의 확산도를 다중 시작점 BFS를 통해 습득 후 플레이어를 BFS를 통해 길찾기를 실시하여 도착이 가능한지 여부를 판단
			// 플레이어의 동시 도착도 불가능으로 판단할 것이며 도착하지 못하였는데 더 이상 이동할 수 있는 곳이 없다면 실패로 도착했다면 성공으로 판단
			
			// 다중 시작점 BFS를 통해 각 불의 이동 시간과 위치를 확인할 수 있는 배열을 생성 - 이 배열에 저장된 위치의 값과 비교해가면서 플레이어의 이동 경로 생성

			if (searchGraph.empty()) {
				cout << "탐색할 행렬이 비어있는 상태. 탐색 불가" << endl;
				return;
			}

			if (fireLocs.empty()) {
				// 만약 불의 시작점을 저장한 배열이 비어있다면 그것은 불이 나지 않았다는 뜻이니 플레이어는 탈출 성공했음을 알린다.(에러지만 논리적으로 성공이기에 성공 표시)
				cout << "불의 시작점이 없으므로 플레이어 탈출 성공" << endl;
				return;
			}

			if (exitLoc.first >= searchGraph.size() || exitLoc.first < 0 || exitLoc.second >= searchGraph[exitLoc.first].size() || exitLoc.second < 0) {
				cout << "탈출 위치가 범위를 벗어나 있는 상태. 탐색 불가" << endl;
				return;
			}

			if (searchGraph[exitLoc.first][exitLoc.second] != 0) {
				cout << "탈출 위치가 이동 불가능한 위치에 존재. 탐색 불가" << endl;
				return;
			}

			for (int i = 0; i < (int)fireLocs.size(); i++) {
				if (fireLocs[i].first >= (int)searchGraph.size() || fireLocs[i].first < 0 || fireLocs[i].second >= (int)searchGraph[fireLocs[i].first].size() || fireLocs[i].second < 0) {
					cout << "범위를 벗어난 값이 존재. 탐색 종료" << endl;
					return;
				}
			}

			if (playerLoc.first >= searchGraph.size() || playerLoc.first < 0 || playerLoc.second >= searchGraph[playerLoc.first].size() || playerLoc.second < 0) {
				cout << "플레이어 위치가 범위를 벗어나 있는 상태. 탐색 불가" << endl;
				return;
			}

			if (searchGraph[playerLoc.first][playerLoc.second] != 0) {
				cout << "플레이어 위치가 위치할 수 없는 위치에 존재. 탐색 불가" << endl;
				return;
			}

			// 모든 행의 개수가 동일한 행렬을 사용
			// -1은 방문하지 않음 혹은 방문 불가를 의미
			// 행렬의 요소들 중 값이 0인 요소만 이동 가능한 공간으로 판정하여 이동
			vector<vector<int>> saveFireMoveTime = vector<vector<int>>(searchGraph.size(), vector<int>(searchGraph[0].size(), -1));
			vector<vector<bool>> playerVisited = vector<vector<bool>>(searchGraph.size(), vector<bool>(searchGraph[0].size(), false)); // 플레이어가 방문했는지 여부를 저장(불의 이동과는 다른 저장 공간이 필요하기에 추가)

			MultiSourceBFS(searchGraph, fireLocs, saveFireMoveTime, 0);

			// 따로 BFS를 만들어야 하지만 문제 해결이니 간단하게 결과 함수 내에서 BFS 정의
			queue<pair<int, int>> bfsQueue;
			int moveTime = 0;
			bool exitSuccess = false;
			int dx[] = { 0,0,-1,1 };
			int dy[] = { -1,1,0,0 };
			// 방문하지 않았거나 방문 불가 지역은 -2,-2 값을 갖고 시작점은 -1,-1의 값을 갖고 방문한 지역은 해당 방문 전 도달한 지역의 좌표를 저장한다.
			vector<vector<pair<int, int>>> parent = vector<vector<pair<int, int>>>(searchGraph.size(), vector<pair<int, int>>(searchGraph[0].size(), make_pair(-2, -2)));
			playerVisited[playerLoc.first][playerLoc.second] = true;
			parent[playerLoc.first][playerLoc.second] = make_pair(-1, -1);
			bfsQueue.push(playerLoc);

			while (!bfsQueue.empty()) {
				int queueLength = (int)bfsQueue.size();
				++moveTime;

				for (int i = 0; i < queueLength; i++) {
					pair<int, int> checkPoint = bfsQueue.front();
					for (int j = 0; j < 4; j++) {
						int nx = checkPoint.first + dx[j];
						int ny = checkPoint.second + dy[j];

						if (nx >= (int)searchGraph.size() || nx < 0)
							continue;
						if (ny >= (int)searchGraph[nx].size() || ny < 0)
							continue;

						// 탈출 위치에 도착한 즉시 모든 탐색이 종료될 것이고 그렇다는 것은 이 위치에 방문은 이번 한 번이 끝일 것이라는 의미이기 때문에 방문 검사는 하지 않는다.
						if (make_pair(nx, ny) == exitLoc && saveFireMoveTime[nx][ny] > moveTime) {
							exitSuccess = true;
							playerVisited[nx][ny] = true;
							parent[nx][ny] = make_pair(checkPoint.first, checkPoint.second);
							break;
						}

						// saveFireMoveTime[nx][ny] > moveDistance => 불의 이동 경로를 저장한 배열에 저장된 값은 불이 도착한 시간대를 의미 그러니까 현재 이동 중인 시간보다 값이 작거나 같다면 이미 도착했다는 의미이기 때문에 현재 이동 중인 시간보다 크지 않다면 방문이 불가
						if (searchGraph[nx][ny] == 0 && !playerVisited[nx][ny] && saveFireMoveTime[nx][ny] > moveTime) {
							playerVisited[nx][ny] = true;
							parent[nx][ny] = make_pair(checkPoint.first, checkPoint.second);
							bfsQueue.push(make_pair(nx, ny));
						}
					}
					
					if (exitSuccess)
						break;

					bfsQueue.pop();
				}

				// 탈출 성공 시 바로 반복문 종료
				if (exitSuccess) {
					// 혹시 몰라서 큐에 저장된 내용을 전부 삭제
					int currentQueueLength = (int)bfsQueue.size();
					for (int i = 0; i < currentQueueLength; i++) {
						bfsQueue.pop();
					}
					break;
				}
			}

			if (exitSuccess) {
				cout << "탈출 성공" << endl;
				cout << "이동 경로" << endl;
				stack<pair<int, int>> routeStack;
				routeStack.push(exitLoc);
				bool finish = false;
				while (!finish) {
					pair<int, int> previousNode = routeStack.top();
					pair<int, int> parentNode = parent[previousNode.first][previousNode.second];
					if (parentNode == make_pair(-1, -1)) {
						finish = true;
						break;
					}
					routeStack.push(parentNode);
				}

				int stackLength = (int)routeStack.size();
				for (int i = 0; i < stackLength; i++) {
					cout << i << " - (" << routeStack.top().first << ", " << routeStack.top().second << ")" << endl;
					routeStack.pop();
				}
			}
			else
				cout << "탈출 실패" << endl;

			cout << "불의 이동 경로" << endl;
			for (int i = 0; i < (int)saveFireMoveTime.size(); i++) {
				for (int j = 0; j < (int)saveFireMoveTime[i].size(); j++) {
					cout << saveFireMoveTime[i][j] << "   ";
				}
				cout << endl;
			}
		}

		// 아쉬운 점
		// 1. visited를 사용하지 않아도 되는데 사용하면서 메모리 손해를 보고 있다. - 수정 완료
		//    지금까지는 visited를 통해 방문 여부를 저장하였어야 했는데 지금은 이를 대체할 거리를 저장하는 배열이 있으니 이를 이용하여 방문하지 않은 숫자인 경우 방문했음과 몇 번째 순서로 방문했는지를 저장하면 된다.
		// 2. distance를 따로 저장할 필요가 없다. - 수정 완료
		//    레벨 순서 순회 방법을 사용한 거리 저장도 나쁘지 않으나 이전 방문지보다 +1 더 가는 것으로 설정하는 것이 추후 개념 확장(알고리즘 개념 확장)으로 더욱 쉽게 이어질 수 있다.
		// 고쳐야 할 점
		// 1. ny 범위를 볼 때 크기보다 더 크면 안 된다고 조건문을 달아둔 곳에 배열 인덱스를 방향 값인 j로 두는 버그가 있다. nx로 수정하여야 한다. - 수정 완료
		// 2. 시작점 검증이 되지 않고 있다. - 수정 완료
		// 3. checkPoint 검증이 이뤄지지 않고 그대로 사용되고 있다. 범위 검사가 필요하다. - 수정 완료

		void MultiSourceBFS(const vector<vector<int>>& searchGraph, const vector<pair<int, int>>& startLoc, vector<vector<int>>& saveDistances, int target)
		{
			queue<pair<int, int>> bfsQueue;
			int dx[] = { 0,0,-1,1 };
			int dy[] = { -1,1,0,0 };
			// 문제 1, 2
			//queue<pair<int, int>> bfsQueue;
			//int dx[] = { 0,0,-1,1 };
			//int dy[] = { -1,1,0,0 };
			//for (int i = 0; i < (int)startLoc.size(); i++) {
			//	if (startLoc[i].first >= searchGraph.size() || startLoc[i].first < 0) {
			//		cout << "범위를 벗어난 값 발견. 탐색 종료" << endl;
			//		return false;
			//	}
			//	if (startLoc[i].second >= searchGraph[startLoc[i].first].size() || startLoc[i].second < 0) {
			//		cout << "범위를 벗어난 값 발견. 탐색 종료" << endl;
			//		return false;
			//	}
			//	pair<int, int> startPoint = startLoc[i];
			//	bfsQueue.push(startPoint);
			//	saveDistances[startLoc[i].first][startLoc[i].second] += 1;
			//}

			//while (!bfsQueue.empty()) {
			//	int queueLength = (int)bfsQueue.size();

			//	for (int i = 0; i < queueLength; i++) {
			//		pair<int, int> checkPoint = bfsQueue.front();
			//		for (int j = 0; j < 4; j++) {
			//			int nx = checkPoint.first + dx[j];
			//			int ny = checkPoint.second + dy[j];

			//			if (nx >= (int)searchGraph.size() || nx < 0)
			//				continue;
			//			if (ny >= (int)searchGraph[nx].size() || ny < 0)
			//				continue;

			//			if (searchGraph[nx][ny] == target && saveDistances[nx][ny] == -1) {
			//				bfsQueue.push(make_pair(nx, ny));
			//				saveDistances[nx][ny] = saveDistances[checkPoint.first][checkPoint.second] + 1;
			//			}
			//		}
			//		bfsQueue.pop();
			//	}
			//}

			//return true;

			// 문제 3
			//for (int i = 0; i < (int)startLoc.size(); i++) {
			//	// 범위를 벗어나거나 단 하나의 스피커라도 스피커가 있을 수 없는 위치에 있다면 탐색 불가로 판정하고 탐색 종료
			//	if (startLoc[i].first >= (int)searchGraph.size() || startLoc[i].first < 0) {
			//		cout << "범위를 벗어난 값 발견. 탐색 종료." << endl;
			//		return false;
			//	}
			//	if (startLoc[i].second >= (int)searchGraph[startLoc[i].first].size() || startLoc[i].second < 0) {
			//		cout << "범위를 벗어난 값 발견. 탐색 종료." << endl;
			//		return false;
			//	}
			//	
			//	if (searchGraph[startLoc[i].first][startLoc[i].second] != 0) {
			//		cout << "스피커가 존재할 수 없는 위치에 존재. 탐색 불가." << endl;
			//		return false;
			//	}

			//	bfsQueue.push(startLoc[i]);
			//	saveDistances[startLoc[i].first][startLoc[i].second] = 0;
			//}

			// 0 - 스피커, 좌석, 빈 공간  1 - 무대(확인하지 않아도 되는 공간)  2 - 복도(소리는 이동하지만 좌석은 아니여서 결과 값에 포함되지 않아야 하는 공간)

			//while (!bfsQueue.empty()) {
			//	pair<int, int> curPoint = bfsQueue.front();
			//	for (int i = 0; i < 4; i++) {
			//		int nx = curPoint.first + dx[i];
			//		int ny = curPoint.second + dy[i];

			//		if (nx >= (int)searchGraph.size() || nx < 0)
			//			continue;
			//		if (ny >= (int)searchGraph[nx].size() || ny < 0)
			//			continue;

			//		if ((searchGraph[nx][ny] == target || searchGraph[nx][ny] == 2) && saveDistances[nx][ny] == -1) {
			//			saveDistances[nx][ny] = saveDistances[curPoint.first][curPoint.second] + 1;
			//			bfsQueue.push(make_pair(nx, ny));
			//		}
			//	}
			//	bfsQueue.pop();
			//}

			// 문제 4
			for (int i = 0; i < (int)startLoc.size(); i++) {
				bfsQueue.push(startLoc[i]);
				saveDistances[startLoc[i].first][startLoc[i].second] = 0;
			}

			while (!bfsQueue.empty()) {
				pair<int, int> curPoint = bfsQueue.front();
				for (int i = 0; i < 4; i++) {
					int nx = curPoint.first + dx[i];
					int ny = curPoint.second + dy[i];

					if (nx >= (int)searchGraph.size() || nx < 0)
						continue;
					if (ny >= (int)searchGraph[nx].size() || ny < 0)
						continue;

					if (searchGraph[nx][ny] == target && saveDistances[nx][ny] == -1) {
						saveDistances[nx][ny] = saveDistances[curPoint.first][curPoint.second] + 1;
						bfsQueue.push(make_pair(nx, ny));
					}
				}
				bfsQueue.pop();
			}
		}
	}
}