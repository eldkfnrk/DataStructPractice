#include "MyOwnStack.h"
#include "MyOwnQueue.h"
#include "MyOwnLinkedList.h"
#include "MyOwnTree.h"
#include "MyOwnBST.h"

int main() {
	using namespace std;
	using namespace DataStruct;

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

	return 0;
}