#include "MyOwnGraph.h"

namespace DataStruct {
	std::ostream& operator<<(std::ostream& os, const City city) {
		os << CityToName(static_cast<int>(city));
		return os;
	}

	std::string CityToName(int i)
	{
		std::string cityName = "";

		switch (i)
		{
		case 0:
			cityName = "Seoul";
			break;
		case 1:
			cityName = "Tokyo";
			break;
		case 2:
			cityName = "Beijing";
			break;
		case 3:
			cityName = "Shanghai";
			break;
		case 4:
			cityName = "Dubai";
			break;
		case 5:
			cityName = "Moscow";
			break;
		case 6:
			cityName = "Istanbul";
			break;
		case 7:
			cityName = "London";
			break;
		case 8:
			cityName = "Paris";
			break;
		case 9:
			cityName = "Madrid";
			break;
		case 10:
			cityName = "Barcelona";
			break;
		case 11:
			cityName = "Munich";
			break;
		case 12:
			cityName = "Roma";
			break;
		case 13:
			cityName = "NewYork";
			break;
		case 14:
			cityName = "Washington";
			break;
		case 15:
			cityName = "Boston";
			break;
		case 16:
			cityName = "LA";
			break;
		case 17:
			cityName = "Sanfrancisco";
			break;
		}

		return cityName;
	}

	OwnMatrixGraph::~OwnMatrixGraph()
	{
	}

	void OwnMatrixGraph::AddMatrixEdge(const City c1, const City c2, int distance)
	{
		int city1 = static_cast<int>(c1);
		int city2 = static_cast<int>(c2);
		graphMatrix[city1][city2] = distance;
		graphMatrix[city2][city1] = distance;
		std::cout << "Add Edge : " << c1 << " - " << c2 << " : distance - " << distance << std::endl;
	}

	void OwnMatrixGraph::RemoveMatrixEdge(const City c1, const City c2)
	{
		int city1 = static_cast<int>(c1);
		int city2 = static_cast<int>(c2);
		graphMatrix[city1][city2] = 0;
		graphMatrix[city2][city1] = 0;

		std::cout << "Remove Edge : " << c1 << " - " << c2 << std::endl;
	}

	void OwnMatrixGraph::CheckMatrixGraph()
	{
		std::cout << "     Seoul   Tokyo   Beijing   Shanghai   Dubai   Moscow   Istanbul   London   Paris   Madrid   Barcelona   Munich   Roma   NewYork   Washington   Boston   LA   Sanfrancisco" << std::endl;
		for (int i = 0; i < cityCount; i++) {
			std::cout << CityToName(i) << " ";
			for (int j = 0; j < cityCount; j++) {
				std::cout << graphMatrix[i][j] << "   ";
			}
			std::cout << std::endl;
		}
	}

	void OwnListGraph::AddListEdge(const City c1, const City c2)
	{
		int city1 = static_cast<int>(c1);
		int city2 = static_cast<int>(c2);

		if (graphList[city1].GetListLength() == 0) {
			graphList[city1].InsertHeader(c2);
		}
		else {
			graphList[city1].InsertTail(c2);
		}

		if (graphList[city2].GetListLength() == 0) {
			graphList[city2].InsertHeader(c1);
		}
		else {
			graphList[city2].InsertTail(c1);
		}

		std::cout << "Add Edge : " << CityToName(city1) << " - " << CityToName(city2) << std::endl;
	}

	void OwnListGraph::RemoveListEdge(const City c1, const City c2)
	{
		int city1 = static_cast<int>(c1);
		int city2 = static_cast<int>(c2);

		bool haveEdge1 = false;
		bool haveEdge2 = false;

		// 삭제할 엣지가 있는지 확인(없으면 없음을 통보하고 함수 종료. 만약 어떠한 문제로 하나의 엣지만 남아있을 수 있기에 이것을 방지하기 위해 삭제시키는 것을 한 후에 통보)
		for (int i = 0; i < graphList[city1].GetListLength(); i++) {
			if (graphList[city1][i] == c2) {
				graphList[city1].DeleteNode(i);
				haveEdge1 = true;
				break;
			}
		}

		for (int i = 0; i < graphList[city2].GetListLength(); i++) {
			if (graphList[city2][i] == c1) {
				graphList[city2].DeleteNode(i);
				haveEdge2 = true;
				break;
			}
		}

		if (!haveEdge1 || !haveEdge2) {
			std::cout << "No exist edge. Can't remove edge." << std::endl;
			return;
		}

		std::cout << "Remove Edge : " << c1 << " - " << c2 << std::endl;
	}

	void OwnListGraph::CheckListGraph()
	{
		for (int i = 0; i < cityCount; i++) {
			std::cout << CityToName(i) << " - ";
			for (int j = 0; j < graphList[i].GetListLength(); j++) {
				std::cout << graphList[i][j] << "   ";
			}
			std::cout << std::endl;
		}
	}

	void OwnListWeightGraph::AddWeightListEdge(const City c1, const City c2, int distance)
	{
		int city1 = static_cast<int>(c1);
		int city2 = static_cast<int>(c2);

		auto pair1 = std::make_pair(c2, distance);
		auto pair2 = std::make_pair(c1, distance);

		graphWeightList[city1].push_back(pair1);
		graphWeightList[city2].push_back(pair2);

		std::cout << "Add Edge : " << c1 << " - " << c2 << " : distance - " << distance << std::endl;
	}

	void OwnListWeightGraph::RemoveWeightListEdge(const City c1, const City c2)
	{
		int city1 = static_cast<int>(c1);
		int city2 = static_cast<int>(c2);

		// vector의 erase 함수와 remove_if 함수를 결합하여 특정 원소를 제거할 수 있다. 여기서 찾는 값을 람다식을 활용하는 이유는 삭제할 원소가 pair인데 이것을 따로 함수를 만들어서 찾는 대신 간단하게 람다식으로 해결하기 위해서이다.
		graphWeightList[city1].erase(std::remove_if(graphWeightList[city1].begin(), graphWeightList[city1].end(), [c2](const auto& pair) {
			return pair.first == c2;
			}));
		graphWeightList[city2].erase(std::remove_if(graphWeightList[city2].begin(), graphWeightList[city2].end(), [c1](const auto& pair){
			return pair.first == c1;
			}));

		std::cout << "Remove Edge : " << c1 << " - " << c2 << std::endl;
	}

	void OwnListWeightGraph::CheckWeightListGraph()
	{
		for (int i = 0; i < cityCount; i++) {
			std::cout << CityToName(i) << " - ";
			for (int j = 0; j < graphWeightList[i].size(); j++) {
				std::cout << "\"" << graphWeightList[i][j].first << " - " << graphWeightList[i][j].second << "\"   ";
			}
			std::cout << std::endl;
		}
	}
}
