#include "MyOwnGraph.h"

namespace DataStruct {
	void OwnGraph::AddEdge(const City c1, const City c2, int distance)
	{
		int city1 = static_cast<int>(c1);
		int city2 = static_cast<int>(c2);
		graphMatrix[city1][city2] = distance;
		graphMatrix[city2][city1] = distance;
		std::cout << "Add Edge : " << CityToName(city1) << " - " << CityToName(city2) << " : distance - " << distance << std::endl;
	}

	void OwnGraph::RemoveEdge(const City c1, const City c2)
	{
		int city1 = static_cast<int>(c1);
		int city2 = static_cast<int>(c2);
		graphMatrix[city1][city2] = 0;
		graphMatrix[city2][city1] = 0;
	}

	void OwnGraph::CheckMatrixGraph()
	{
		std::cout << "     Seoul   Tokyo   Beijing   Shanghai   Dubai   Moscow   Istanbul   London   Paris   Madrid   Barcelona   Munich   Roma   NewYork   Washington   Boston   LA   Sanfrancisco" << std::endl;
		for (int i = 0; i <= cityCount; i++) {
			std::cout << CityToName(i) << " ";
			for (int j = 0; j <= cityCount; j++) {
				std::cout << graphMatrix[i][j] << "   ";
			}
			std::cout << std::endl;
		}
	}

	std::string OwnGraph::CityToName(int i)
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
}
