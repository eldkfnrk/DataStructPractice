#pragma once
#include "CommonInclude.h"
#include "MyOwnLinkedList.h"

namespace DataStruct {
	// 이번 그래프 구현에서는 책에 나온 방식인 도시 간 연결을 다뤄보려 한다.
	enum class City : int {  // enum은 그냥 열거형이고 enum class는 열거형 클래스로 enum에서 발생할 수 있는 문제들을 방지하기 위해 나온 개념으로 묵시적 형변환이 안 되고 열거형과 다른 자료형 비교를 불가능하도록 제한해 둔 개념이다.
		Seoul,
		Tokyo,
		Beijing,
		Shanghai,
		Dubai,
		Moscow,
		Istanbul,
		London,
		Paris,
		Madrid,
		Barcelona,
		Munich,
		Roma,
		NewYork,
		Washington,
		Boston,
		LA,
		Sanfrancisco,
		None,  // enum class의 마지막 번호를 가져오기 위해 추가한 값(None은 마지막을 의미)
	};

	// 그래프 
	// 실생활에서 순환 구조를 사용하여 표현하는 문제 해결을 위해 사용하는 자료구조
	// 그래프는 정점(Vertex)과 간선(Edge)의 집합으로 구성된 데이터 구조
	// 정점 - 자료 저장(노드라고도 한다.)  간선 - 정점 사이를 연결하는 선
	// 그래프는 방향성과 가중치라는 것이 존재한다. 
	// 방향성은 이동 가능한 경로라고 보면 되고 방향이 있는 간선은 양방향 도로, 없는 간선은 일방 통행 도로로 생각하면 이해하기 쉽다.
	// 가중치는 간선에 부여된 숫자로 해당 숫자는 비용, 거리, 시간 등을 의미한다.
	// 간선에 방향성의 유무에 따라 방향 or 무방향 그래프라고 하고 가중치의 여부에 따라 가중 or 비가중 그래프라고 한다.
	// 그래프를 표현하는 방법은 인접 행렬이나 인접 리스트를 사용하는 방법이 있다.
	class OwnGraph
	{
	public:
		// 그래프 생성, 간선 추가, 간선 삭제
		OwnGraph() {
			cityCount = static_cast<int>(City::None) - 1;  // enum class에 저장된 도시 개수를 가져오는 수식

			for (int i = 0; i <= cityCount; i++) {
				OwnLinkedList<int> newColumn;
				if (i == 0) {
					graphMatrix.InsertHeader(newColumn);
				}
				else {
					graphMatrix.InsertTail(newColumn);
				}

				for (int j = 0; j <= cityCount; j++) {
					// 0은 연결되지 않았음을 의미
					if (j == 0) {
						graphMatrix[i].InsertHeader(0);
					}
					else {
						graphMatrix[i].InsertTail(0);
					}
				}
			}
		}

		void AddEdge(const City c1, const City c2, int distance);  // 간선에 줄 가중치까지 인자로 받도록 설정
		void RemoveEdge(const City c1, const City c2);
		void CheckMatrixGraph();  // 그래프(인접 행렬 사용 그래프) 상황 체크 함수

	private:
		std::string CityToName(int i);

	private:
		// 연결 리스트의 사용은 그래프의 성능 장점을 무효화시키는 방법이기 때문에 동적 배열을 사용하는 것이 그래프에서는 나은 선택이다.
		OwnLinkedList<OwnLinkedList<int>> graphMatrix;  // 2차원 배열 형태의 연결 리스트(거리라는 가중치 부여 예정) - 인접 행렬
		int cityCount;
	};
}
