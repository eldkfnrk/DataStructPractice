#include "MyOwnStack.h"
#include "MyOwnQueue.h"
#include "MyOwnLinkedList.h"
#include "MyOwnTree.h"
#include "MyOwnBST.h"
#include "MyOwnGraph.h"
#include "MyOwnBFSDFS.h"

int main() {
	using namespace std;
	using namespace DataStruct;
	using namespace Algorithm;

	// 자료구조의 종류
	// 배열, 연결 리스트, 스택, 큐, 트리, 그래프, 헤시 테이블, 힙(완전 이진 트리 형태의 자료구조)

	// 스택, 큐, 연결 리스트, 트리 테스트 완료

	// BST 테스트
	OwnBST test1;
	OwnBST test2(20);

	test1.InsertNode(30);
	test1.InsertNode(10);
	test1.InsertNode(20);
	test1.InsertNode(5);
	test1.InsertNode(49);
	test1.InsertNode(38);
	test1.InsertNode(67);
	test1.InsertNode(3);
	test1.InsertNode(6);

	test1.PreOrderTree(test1.GetRoot());
	cout << endl;
	test1.InOrderTree(test1.GetRoot());
	cout << endl;
	test1.PostOrderTree(test1.GetRoot());
	cout << endl;
	test1.LevelOrderTree();
	cout << endl;
	cout << test1.SearchMin() << endl;
	cout << test1.SearchMax() << endl;
	cout << test1.SearchData(60) << endl;

	test1.DeleteNode(5);
	test1.LevelOrderTree();
	cout << endl;

	test2.InsertNode(30);
	test2.InsertNode(10);
	test2.InsertNode(20);
	test2.InsertNode(5);
	test2.InsertNode(49);
	test2.InsertNode(38);
	test2.InsertNode(67);
	test2.InsertNode(3);
	test2.InsertNode(6);
	test2.PreOrderTree(test2.GetRoot());
	cout << endl;
	test2.InOrderTree(test2.GetRoot());
	cout << endl;
	test2.PostOrderTree(test2.GetRoot());
	cout << endl;
	test2.LevelOrderTree();
	cout << endl;
	test2.DeleteNode(49);
	test2.LevelOrderTree();
	cout << endl;

	cout << "---------------------------------------------------------------------------------" << endl;
	OwnMatrixGraph graphTest1;

	graphTest1.AddMatrixEdge(City::Seoul, City::Tokyo, 1150);
	graphTest1.AddMatrixEdge(City::Seoul, City::Beijing, 950);
	graphTest1.AddMatrixEdge(City::Seoul, City::NewYork, 11000);
	graphTest1.AddMatrixEdge(City::London, City::Istanbul, 2500);
	graphTest1.AddMatrixEdge(City::Paris, City::Moscow, 2500);
	graphTest1.AddMatrixEdge(City::Sanfrancisco, City::NewYork, 4200);
	graphTest1.AddMatrixEdge(City::Seoul, City::Shanghai, 880);
	graphTest1.AddMatrixEdge(City::Beijing, City::London, 8100);
	graphTest1.AddMatrixEdge(City::Seoul, City::Barcelona, 9600);
	graphTest1.AddMatrixEdge(City::Tokyo, City::Dubai, 7950);
	graphTest1.AddMatrixEdge(City::Munich, City::Roma, 800);
	graphTest1.AddMatrixEdge(City::Washington, City::LA, 3600);
	graphTest1.AddMatrixEdge(City::London, City::Boston, 5250);
	graphTest1.AddMatrixEdge(City::Seoul, City::Istanbul, 8000);

	cout << endl;
	graphTest1.CheckMatrixGraph();
	cout << endl;

	graphTest1.RemoveMatrixEdge(City::Seoul, City::Barcelona);
	graphTest1.RemoveMatrixEdge(City::Tokyo, City::Dubai);
	graphTest1.RemoveMatrixEdge(City::Munich, City::Roma);

	cout << endl;
	graphTest1.CheckMatrixGraph();

	cout << "---------------------------------------------------------------------------------" << endl;
	OwnListGraph graphTest2;

	graphTest2.AddListEdge(City::Seoul, City::Tokyo);
	graphTest2.AddListEdge(City::Seoul, City::Beijing);
	graphTest2.AddListEdge(City::Seoul, City::NewYork);
	graphTest2.AddListEdge(City::London, City::Istanbul);
	graphTest2.AddListEdge(City::Paris, City::Moscow);
	graphTest2.AddListEdge(City::Sanfrancisco, City::NewYork);
	graphTest2.AddListEdge(City::Seoul, City::Shanghai);
	graphTest2.AddListEdge(City::Beijing, City::London);
	graphTest2.AddListEdge(City::Seoul, City::Barcelona);
	graphTest2.AddListEdge(City::Tokyo, City::Dubai);
	graphTest2.AddListEdge(City::Munich, City::Roma);
	graphTest2.AddListEdge(City::Washington, City::LA);
	graphTest2.AddListEdge(City::London, City::Boston);
	graphTest2.AddListEdge(City::Seoul, City::Istanbul);

	graphTest2.CheckListGraph();
	cout << endl;

	graphTest2.RemoveListEdge(City::Munich, City::Roma);
	graphTest2.RemoveListEdge(City::Washington, City::LA);
	cout << endl;
	graphTest2.CheckListGraph();

	cout << "---------------------------------------------------------------------------------" << endl;
	OwnListWeightGraph graphTest3;

	graphTest3.AddWeightListEdge(City::Seoul, City::Tokyo, 1150);
	graphTest3.AddWeightListEdge(City::Seoul, City::Beijing, 950);
	graphTest3.AddWeightListEdge(City::Seoul, City::NewYork, 11000);
	graphTest3.AddWeightListEdge(City::London, City::Istanbul, 2500);
	graphTest3.AddWeightListEdge(City::Paris, City::Moscow, 2500);
	graphTest3.AddWeightListEdge(City::Sanfrancisco, City::NewYork, 4200);
	graphTest3.AddWeightListEdge(City::Seoul, City::Shanghai, 880);
	graphTest3.AddWeightListEdge(City::Beijing, City::London, 8100);
	graphTest3.AddWeightListEdge(City::Seoul, City::Barcelona, 9600);
	graphTest3.AddWeightListEdge(City::Tokyo, City::Dubai, 7950);
	graphTest3.AddWeightListEdge(City::Munich, City::Roma, 800);
	graphTest3.AddWeightListEdge(City::Washington, City::LA, 3600);
	graphTest3.AddWeightListEdge(City::London, City::Boston, 5250);
	graphTest3.AddWeightListEdge(City::Seoul, City::Istanbul, 8000);
	cout << endl;

	graphTest3.CheckWeightListGraph();
	cout << endl;

	graphTest3.RemoveWeightListEdge(City::Sanfrancisco, City::NewYork);
	graphTest3.RemoveWeightListEdge(City::Seoul, City::Shanghai);
	graphTest3.RemoveWeightListEdge(City::Beijing, City::London);
	graphTest3.RemoveWeightListEdge(City::Seoul, City::Barcelona);
	cout << endl;

	graphTest3.CheckWeightListGraph();
	cout << endl;

	cout << "---------------------------------------------------------------------------------" << endl;

	BFSDFSGraph graph;  // 문제 해결을 위해 생성한 하나의 그래프(인접 행렬과 인접 리스트가 모두 포함되어 있다.)

	Traversal::BFS(3, graph.graphMatrix);

	cout << endl << "---------------------------------------------------------------------------------" << endl;

	Traversal::DFS(3, graph.graphMatrix);

	cout << endl << "---------------------------------------------------------------------------------" << endl;

	ConnectVertexCount::BFS(graph.graphList);

	cout << endl << "---------------------------------------------------------------------------------" << endl;

	ConnectVertexCount::DFS(graph.graphList);

	return 0;
}