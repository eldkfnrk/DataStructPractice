#include "MyOwnBFSDFS.h"

namespace Algorithm {
	// 문제 1. 단순 순회 - 시작 정점에서 방문한 정점을 순서대로 출력해보기
	// 문제 1을 구현하고 AI에게 얻은 개선 사항
	// 1. 시작 정점이 누락되고 있는데 시작 정점 또한 방문해야 할 정점으로 보아야 한다. 그래서 시작 정점은 어딘지도 처리를 해주어야 한다.
	// 2. visited라는 배열의 크기를 10으로 명시해놨는데 지금은 동작하지만 범용성이 떨어지기 때문에 그래프의 크기에 맞도록 수정하여야 한다.
	// 3. 인자로 배열을 그대로 받아오는 것은 복사로 받아오는 것이기 때문에 메모리 낭비가 발생한다. 데이터가 적은 지금은 괜찮으나 10만개 같이 엄청난 데이터를 가져올 때는 문제가 생기니 참조자나 포인터를 사용해서 복사가 아닌 접근을 해야 한다.(const로 변경되지 않도록 하는 것도 있어야 한다.)
	// 4. 큐에 시작 정점 인근 정점을 넣고 시작하는데 그래도 되지만 굳이 while 문에서 동일한 동작을 하고 있기 때문에 이는 불필요한 동작이다. while문 안에서 처리할 수 있도록 수정하여야 한다.
	// 5. while문이 끝나는 조건을 while문 안에 넣어놔서 다른 사람이 코드를 볼 때 직관적이지 않게 되어 있다. 그러니 직관적으로 볼 수 있도록 조건문을 수정해야 한다.(큐가 비어있다면 종료할 수 있도록 하면 될 것이다.)
	// 6. 큐의 size는 size_t 형태인데 int와 비교하고 있어서 문제가 발생할 수 있다. 그러니 이를 수정해야 한다.(현재는 문제가 없지만 컴파일러에 따라 문제가 있을 수 있다. 그러니 항상 자료형을 일치시키는 습관을 들여야 한다.)
	// 그리고 절대로 헤더 파일과 cpp 파일의 함수 형태는 동일해야 링크 오류가 발생하지 않는다. 자꾸 cpp는 바꾸고 헤더를 안 바꾸거나 헤더는 바꾸고 cpp는 안 바꿔서 이런 오류가 발생하는데 절대 망각하지 말아야 한다.(이 때문에 무의미하게 AI를 사용하는 시간을 소모하였다.)
	void BFS(int start, const vector<vector<int>>& searchGraph)
	{
		// BFS는 넓게 퍼져나가는 개념으로 각 층을 검사한다. 그렇기에 정점과 맞닿은 정점을 큐에 넣는 방식으로 진행된다.(이는 트리의 레벨 순서 순회와 유사하다.)

		// 문제 1
		// 인접 리스트를 활용한 그래프 사용
		queue<int> bfsQueue;
		int floor = 0;  // 방문하고 있는 계층이 어딘지 저장할 변수
		size_t queueLength = 0;
		vector<bool> visited = vector<bool>(searchGraph.size(), false);  // 방문하였는지를 저장하는 bool형 배열(각 인덱스에 해당하는 요소의 값을 바꾸는 것으로 true면 방문했음을 false면 아직 방문하지 않았음을 의미)

		bfsQueue.push(start);
		visited[start] = true;

		while (!bfsQueue.empty()) {
			queueLength = bfsQueue.size();
			
			if (floor == 0)
				cout << "시작 정점 : ";
			else
				cout << "거리 " << floor << " : ";

			for (size_t i = 0; i < queueLength; i++) {
				int vertexIndex = bfsQueue.front();
				bfsQueue.pop();
				cout << "Vertex " << vertexIndex << "  ";
				// 삭제한 인덱스 정점과 연결된 정점의 인덱스 번호 모두를 큐에 저장
				for (size_t j = 0; j < searchGraph[vertexIndex].size(); j++) {
					int insertVertexIndex = searchGraph[vertexIndex][j];
					if (visited[insertVertexIndex])  // 삽입하려는 정점이 이미 방문한 정점이면 건너뛴다.
						continue;
					bfsQueue.push(insertVertexIndex);
					visited[insertVertexIndex] = true;
				}
			}
			
			cout << endl;
			++floor;
		}
	}

	// 깃허브 제대로 연결되었는지 체크

	void DFS(int start, vector<vector<int>> searchGraph)
	{

	}
}