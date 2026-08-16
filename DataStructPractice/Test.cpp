#include "MyOwnStack.h"
#include "MyOwnQueue.h"
#include "MyOwnLinkedList.h"
#include "MyOwnTree.h"
#include "MyOwnBST.h"
#include "MyOwnGraph.h"
#include "MyOwnBFSDFS.h"
#include "MyOwnHashTable.h"

int main() {
	using namespace std;
	using namespace DataStruct;
	using namespace Algorithm;

	//// Flood Fill용 인접 행렬 그래프
	//vector<vector<int>> floodFillMatrix = vector<vector<int>>(6, vector<int>(6, 0));
	//floodFillMatrix[0] = { 1, 1, 0, 0, 0, 1 };
	//floodFillMatrix[1] = { 0, 1, 0, 0, 1, 0 };
	//floodFillMatrix[2] = { 0, 1, 1, 0, 1, 0 };
	//floodFillMatrix[3] = { 0, 0, 0, 0, 1, 0 };
	//floodFillMatrix[4] = { 0, 1, 1, 1, 0, 0 };
	//floodFillMatrix[5] = { 0, 0, 1, 1, 0, 0 };

	//FloodFill::FloodFillBFS(floodFillMatrix, 1, 4);
	//cout << endl;
	//FloodFill::FloodFillDFS(floodFillMatrix, 0, 2);
	//cout << endl;
	//FloodFill::CountElement(floodFillMatrix, 5, 3);

	//cout << "-----------------------------------------------" << endl;
	//vector<vector<int>> shortestPathMatrix = vector<vector<int>>(15, vector<int>(15, 0));

	//// 0 - 이동 가능, 1 - 벽(이동 불가), 2 - 몬스터(회피해야 하는 곳 - 이동 불가)
	//shortestPathMatrix[0] =  { 0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1 };
	//shortestPathMatrix[1] =  { 0,1,1,1,1,1,1,0,1,0,0,1,0,0,0,1 };
	//shortestPathMatrix[2] =  { 0,0,0,0,0,0,1,0,1,0,0,0,0,2,0,1 };
	//shortestPathMatrix[3] =  { 0,1,0,1,1,0,1,0,1,1,1,1,1,1,0,1 };
	//shortestPathMatrix[4] =  { 0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,1 };
	//shortestPathMatrix[5] =  { 0,1,0,1,0,0,1,1,1,0,1,1,1,1,0,1 };
	//shortestPathMatrix[6] =  { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 };
	//shortestPathMatrix[7] =  { 0,1,1,1,1,1,1,1,1,1,1,0,1,2,0,1 };
	//shortestPathMatrix[8] =  { 0,1,2,0,1,2,2,1,0,0,0,0,1,0,0,1 };
	//shortestPathMatrix[9] =  { 0,0,0,0,0,0,2,1,0,0,1,0,1,0,1,1 };
	//shortestPathMatrix[10] = { 0,1,0,1,0,1,1,1,1,1,1,0,1,0,1,0 };
	//shortestPathMatrix[11] = { 0,1,0,1,0,0,0,0,0,0,1,0,0,0,0,0 };
	//shortestPathMatrix[12] = { 0,1,0,1,1,2,2,1,1,0,0,0,1,0,1,0 };
	//shortestPathMatrix[13] = { 0,1,0,0,1,0,0,0,1,1,0,1,1,0,1,0 };
	//shortestPathMatrix[14] = { 0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0 };

	//ShortestPath::ShortestPathBFS(shortestPathMatrix, make_pair(2, 2), make_pair(14, 13));

	//vector<pair<int, int>> convenience;
	//convenience.push_back(make_pair(2, 3));
	//convenience.push_back(make_pair(9, 9));
	////MultiSource::Result(shortestPathMatrix, convenience);
	////MultiSource::Result(shortestPathMatrix, convenience, make_pair(6, 5));

	//cout << "-----------------------------------------------" << endl;
	//vector<vector<int>> hallMatrix;
	//hallMatrix.resize(10);
	//for (int i = 0; i < (int)hallMatrix.size(); i++) {
	//	hallMatrix[i].resize(10);
	//}

	//// 0 - 스피커, 좌석, 빈 공간  1 - 무대(확인하지 않아도 되는 공간)  2 - 복도(소리는 이동하지만 좌석은 아니여서 결과 값에 포함되지 않아야 하는 공간)
	//hallMatrix[0] = { 0,0,1,1,1,1,1,1,0,0 };
	//hallMatrix[1] = { 0,0,1,1,1,1,1,1,0,0 };
	//hallMatrix[2] = { 2,2,2,2,2,2,2,2,2,2 };
	//hallMatrix[3] = { 0,0,2,0,0,0,0,2,0,0 };
	//hallMatrix[4] = { 0,0,2,0,0,0,0,2,0,0 };
	//hallMatrix[5] = { 0,0,2,0,0,0,0,2,0,0 };
	//hallMatrix[6] = { 2,2,2,2,2,2,2,2,2,2 };
	//hallMatrix[7] = { 0,0,2,0,0,0,0,2,0,0 };
	//hallMatrix[8] = { 0,0,2,0,0,0,0,2,0,0 };
	//hallMatrix[9] = { 0,0,2,0,0,0,0,2,0,0 };

	//vector<pair<int, int>> speakerPos;
	//speakerPos.push_back(make_pair(0, 0));
	//speakerPos.push_back(make_pair(0, 9));
	//speakerPos.push_back(make_pair(9, 9));
	//speakerPos.push_back(make_pair(9, 0));
	////MultiSource::Result(hallMatrix, speakerPos);

	//vector<pair<int, int>> fireOrigins;
	//pair<int, int> playerStartPoint = make_pair(14, 15);
	//pair<int, int> exitPoint = make_pair(11, 11);

	//fireOrigins.push_back(make_pair(4, 0));
	//fireOrigins.push_back(make_pair(1, 14));
	//fireOrigins.push_back(make_pair(14, 0));
	//MultiSource::Result(shortestPathMatrix, fireOrigins, playerStartPoint, exitPoint);

	//AdjacencyList::ResultQ1();
	//AdjacencyList::ResultQ2();
	AdjacencyList::ResultQ3();

	return 0;
}