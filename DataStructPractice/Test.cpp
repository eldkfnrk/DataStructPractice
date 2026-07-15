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

	// 자료구조의 종류
	// 배열, 연결 리스트, 스택, 큐, 트리, 그래프, 헤시 테이블, 힙(완전 이진 트리 형태의 자료구조)
	SaveInteger::OwnHashTable firstTest(10);

	auto printData = [&](int value) {
		if (firstTest.Find(value))
			cout << "해시 테이블에서 " << value << "값을 찾기 성공" << endl;
		else
			cout << "해시 테이블에서 " << value << "값을 찾기 실패" << endl;
		};

	firstTest.Insert(58);
	firstTest.Insert(103);

	printData(58);
	printData(59);
	printData(103);

	firstTest.Insert(16);
	firstTest.Insert(975);
	firstTest.Insert(163);

	printData(103);
	printData(163);

	firstTest.Insert(100);

	printData(100);

	firstTest.Delete(163);
	firstTest.Delete(58);
	firstTest.Delete(975);
	firstTest.Delete(100);

	printData(100);

	cout << "-----------------------------------------------------" << endl << endl;
	UseChaining::OwnChainingHashTable secondTest(10);

	auto printChainingData = [&](int value) {
		if (secondTest.ChainingFind(value))
			cout << "해시 테이블에서 " << value << "값을 찾기 성공" << endl;
		else
			cout << "해시 테이블에서 " << value << "값을 찾기 실패" << endl;
		};

	secondTest.ChainingInsert(55);
	secondTest.ChainingInsert(845);
	secondTest.ChainingInsert(91);
	secondTest.ChainingInsert(23);
	secondTest.ChainingInsert(61);
	secondTest.ChainingInsert(177);
	secondTest.ChainingInsert(882);
	secondTest.ChainingInsert(26);
	secondTest.ChainingInsert(845);
	secondTest.ChainingInsert(300);
	secondTest.ChainingInsert(234);
	secondTest.ChainingInsert(64);
	secondTest.ChainingInsert(108);
	secondTest.ChainingInsert(109);
	secondTest.ChainingInsert(88);

	printChainingData(845);
	printChainingData(55);
	printChainingData(300);
	printChainingData(301);

	secondTest.ChainingDelete(23);
	secondTest.ChainingDelete(61);
	secondTest.ChainingDelete(178);
	secondTest.ChainingDelete(845);
	secondTest.ChainingDelete(26);

	printChainingData(845);
	printChainingData(26);
	printChainingData(61);

	cout << "-----------------------------------------------------" << endl << endl;
	LinearProbing::OwnLinearProbingHashTable thirdTest(10);

	auto printLinearProbingData = [&](int value) {
		if (thirdTest.LinearProbingFind(value))
			cout << "해시 테이블에서 " << value << "값을 찾기 성공" << endl;
		else
			cout << "해시 테이블에서 " << value << "값을 찾기 실패" << endl;
		};

	thirdTest.LinearProbingInsert(5);
	thirdTest.LinearProbingInsert(25);
	thirdTest.LinearProbingInsert(15);
	thirdTest.LinearProbingInsert(95);
	thirdTest.LinearProbingInsert(76);
	thirdTest.LinearProbingInsert(5);
	thirdTest.LinearProbingInsert(159);
	thirdTest.LinearProbingInsert(63);
	thirdTest.LinearProbingInsert(20);
	thirdTest.LinearProbingInsert(14);

	printLinearProbingData(5);
	printLinearProbingData(86);
	printLinearProbingData(95);
	printLinearProbingData(14);

	thirdTest.LinearProbingInsert(158);
	thirdTest.LinearProbingInsert(98);
	thirdTest.LinearProbingInsert(55);
	thirdTest.LinearProbingInsert(12);

	printLinearProbingData(55);
	printLinearProbingData(86);
	printLinearProbingData(12);

	thirdTest.LinearProbingDelete(159);
	thirdTest.LinearProbingDelete(63);
	thirdTest.LinearProbingDelete(20);
	thirdTest.LinearProbingDelete(14);
	thirdTest.LinearProbingDelete(159);

	printLinearProbingData(159);
	printLinearProbingData(63);
	printLinearProbingData(20);

	cout << "-----------------------------------------------------" << endl << endl;

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
	FloodFill::FloodFillDFS(floodFillMatrix, 4, 2);

	FloodFill::CountElement(floodFillMatrix, 0, 2);

	return 0;
}