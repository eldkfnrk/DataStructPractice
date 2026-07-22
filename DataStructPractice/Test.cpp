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

	// Flood Fill용 인접 행렬 그래프
	vector<vector<int>> floodFillMatrix = vector<vector<int>>(6, vector<int>(6, 0));
	floodFillMatrix[0] = { 1, 1, 0, 0, 0, 1 };
	floodFillMatrix[1] = { 0, 1, 0, 0, 1, 0 };
	floodFillMatrix[2] = { 0, 1, 1, 0, 1, 0 };
	floodFillMatrix[3] = { 0, 0, 0, 0, 1, 0 };
	floodFillMatrix[4] = { 0, 1, 1, 1, 0, 0 };
	floodFillMatrix[5] = { 0, 0, 1, 1, 0, 0 };

	FloodFill::FloodFillBFS(floodFillMatrix, 1, 4);
	cout << endl;
	FloodFill::FloodFillDFS(floodFillMatrix, 0, 2);
	cout << endl;
	FloodFill::CountElement(floodFillMatrix, 5, 3);

	cout << "-----------------------------------------------" << endl;
	vector<vector<int>> shortestPathMatrix = vector<vector<int>>(15, vector<int>(15, 0));

	// 0 - 이동 가능, 1 - 벽(이동 불가), 2 - 몬스터(회피해야 하는 곳 - 이동 불가)
	shortestPathMatrix[0] =  { 0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1 };
	shortestPathMatrix[1] =  { 0,1,1,1,1,1,1,0,1,0,0,1,0,0,0,1 };
	shortestPathMatrix[2] =  { 0,0,0,0,0,0,1,0,1,0,0,0,0,2,0,1 };
	shortestPathMatrix[3] =  { 0,1,0,1,1,0,1,0,1,1,1,1,1,1,0,1 };
	shortestPathMatrix[4] =  { 0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,1 };
	shortestPathMatrix[5] =  { 0,1,0,1,0,0,1,1,1,0,1,1,1,1,0,1 };
	shortestPathMatrix[6] =  { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 };
	shortestPathMatrix[7] =  { 0,1,1,1,1,1,1,1,1,1,1,0,1,2,0,1 };
	shortestPathMatrix[8] =  { 0,1,2,0,1,2,2,1,0,0,0,0,1,0,0,1 };
	shortestPathMatrix[9] =  { 0,0,0,0,0,0,2,1,0,0,1,0,1,0,1,1 };
	shortestPathMatrix[10] = { 0,1,0,1,0,1,1,1,1,1,1,0,1,0,1,0 };
	shortestPathMatrix[11] = { 0,1,0,1,0,0,0,0,0,0,1,0,0,0,0,0 };
	shortestPathMatrix[12] = { 0,1,0,1,1,2,2,1,1,0,0,0,1,0,1,0 };
	shortestPathMatrix[13] = { 0,1,0,0,1,0,0,0,1,1,0,1,1,0,1,0 };
	shortestPathMatrix[14] = { 0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0 };

	ShortestPath::ShortestPathBFS(shortestPathMatrix, make_pair(2, 2), make_pair(3, 5));

	return 0;
}