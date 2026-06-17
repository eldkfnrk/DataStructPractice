#include "MyOwnHashTable.h"

namespace DataStruct {
	namespace SaveInteger {
		OwnHashTable::OwnHashTable(int size) : size(size)
		{
			// 아무 값도 없는 경우를 -1로 표현(부호 없는 정수를 저장하는 해시 테이블이기 때문에 -1은 들어올 수 없어서)
			hash_table = std::vector<int>(size, -1);
		}

		void OwnHashTable::Insert(int value)
		{
			// 이 문제는 해시 함수를 사용하지 않고 해시 값을 간단한 모듈러 값을 이용
			hash_table[value % size] = value;
			std::cout << value % size << "위치에 " << value << "삽입" << std::endl;
		}

		bool OwnHashTable::Find(int value)
		{
			return (hash_table[value % size] == value);
		}

		void OwnHashTable::Delete(int value)
		{
			// 해당 해시 값에 저장된 값이 삭제할 값과 다를 경우에는 진행되지 못하도록 값을 확인 후 삭제
			if (hash_table[value % size] == value) {
				hash_table[value % size] = -1;
				std::cout << value << "삭제" << std::endl;
			}
		}

		OwnHashTable::~OwnHashTable()
		{
		}
	}

	namespace UseChaining {
		OwnChainingHashTable::OwnChainingHashTable(int size) : size(size)
		{
			hashTable = std::vector<std::list<int>>(size, std::list<int>());
		}

		void OwnChainingHashTable::ChainingInsert(int value)
		{
			int key = value % size;

			if (ChainingFind(value)) 
				std::cout << "값이 이미 존재 삽입 종료" << std::endl;
			else {
				hashTable[key].push_back(value);
				std::cout << key << "위치에 " << value << " 삽입" << std::endl;
			}
		}

		bool OwnChainingHashTable::ChainingFind(int value)
		{
			// list를 순회하는 반복문
			// list는 []를 통한 인덱스 접근이 불가능하여서 반복자를 통한 접근만이 가능하다.
			// 반복자를 사용하는 모든 자료구조는 아래와 같은 방식의 순회를 사용한다.
			// auto는 자동으로 자료형을 결정하는 C++문법인데 auto를 사용한 이유는 begin()이나 end()같이 반복자를 뱉는 함수의 반환형이 반복자라 굉장히 길고 실수가 생길 수 있기 때문이다.
			// 그러나 auto는 자동으로 다 자료형을 정해주기 때문에 어떤 자료형을 사용하고 있는지 모르는 상황이 발생할 수 있어서 사용에 주의가 필요하다.
			for (auto iter = hashTable[value % size].begin(); iter != hashTable[value % size].end(); iter++) {
				if (*iter == value)  // 반복자는 포인터형이기 때문에 다음과 같이 사용하여야 한다.
					return true;
			}
			return false;
		}

		void OwnChainingHashTable::ChainingDelete(int value)
		{
			int key = value % size;

			// 굳이 순회를 통해서 삭제를 하고 있는데 그럴 필요 없이 이 함수 내에서 한 번에 삭제가 가능하도록 하는 것이 좋다.
			// 힌트 - 반복문을 통해 값이 있는지 확인하고 있으면 찾음과 동시에 삭제

			if (ChainingFind(value)) {
				hashTable[key].remove(value);
				std::cout << key << "위치에 " << value << " 삭제" << std::endl;
			}
			else
				std::cout << "삭제하고자 하는 값이 존재하지 않음. 삭제 종료" << std::endl;
		}

		OwnChainingHashTable::~OwnChainingHashTable()
		{
		}
	}

	namespace LinearProbing {
		OwnLinearProbingHashTable::OwnLinearProbingHashTable(int size) : size(size)
		{
			// 아직까지는 부호 없는 정수를 저장하는 해시 테이블을 이용한 문제이기 때문에 -1을 사용하여 비었음을 표현
			hashTable = std::vector<int>(size, -1);
		}

		void OwnLinearProbingHashTable::LinearProbingInsert(int value)
		{
			int key = value % size;
			
			for (int i = key; i < size; i++) {
				if (hashTable[i] == value) {
					std::cout << "이미 있는 값이므로 삽입 불가." << std::endl;
					return;
				}

				if (hashTable[i] == -1) {
					hashTable[i] = value;
					std::cout << i << "위치에 " << value << " 삽입" << std::endl;
					return;
				}
			}

			for (int j = 0; j < key; j++) {
				if (hashTable[j] == value) {
					std::cout << "이미 있는 값이므로 삽입 불가." << std::endl;
					return;
				}

				if (hashTable[j] == -1) {
					hashTable[j] = value;
					std::cout << j << "위치에 " << value << " 삽입" << std::endl;
					return;
				}
			}

			// 재해싱 후 삽입 진행
			// 재해싱 후 값이 재해싱 한 값에 맞게 이동하여야 재해싱의 완성이므로 지금 현 상태는 반쪽짜리 재해싱이다.
			size *= 2;  // 크기를 2배로 확대
			hashTable.resize(size, -1);
			LinearProbingInsert(value);
		}

		bool OwnLinearProbingHashTable::LinearProbingFind(int value)
		{
			int key = value % size;
			for (int i = key; i < size; i++) {
				if (hashTable[i] == value)
					return true;
			}

			// 혹시나 맨 끝까지 탐사하고 키 값보다 작은 인덱스에 들어갔을 경우를 대비하여 키 값보다 작은 인덱스도 순회해본다.
			for (int j = 0; j < key; j++) {
				if (hashTable[j] == value)
					return true;
			}

			return false;
		}

		void OwnLinearProbingHashTable::LinearProbingDelete(int value)
		{
			// 삭제 후 값을 찾을 수 없는 경우가 발생하고 있다.
			// 예를 들어 동일한 키를 가지는 5가 먼저 삽입되었고 25가 나중에 삽입되었다고 가정하자.
			// 그러면 5를 삭제하고 나서 25를 탐색하려 하면 찾을 수 있어야 하는데 동일한 키를 가지고 먼저 삽입되었던 5가 삭제되면서 비었음이 되는데 그러면 탐사가 종료된다.
			// 그렇게 되면 25를 찾으려 하는 원하는 결과 값을 획득하지 못하고 탐사가 종료되는 것이다.
			// 현재 이 구현은 이런 문제를 가지고 있다.
			int key = value % size;

			for (int i = key; i < size; i++) {
				if (hashTable[i] == value) {
					hashTable[i] = -1;
					std::cout << i << "위치에 " << value << " 삭제" << std::endl;
					return;
				}
			}

			for (int j = 0; j < key; j++) {
				if (hashTable[j] == value) {
					hashTable[j] = -1;
					std::cout << j << "위치에 " << value << " 삭제" << std::endl;
					return;
				}
			}

			// 여기까지 온 거면 값이 없는 것으로 판단하고 없음과 삭제 실패를 통보
			std::cout << "삭제하고자 하는 값이 존재하지 않음. 삭제 실패" << std::endl;
		}

		OwnLinearProbingHashTable::~OwnLinearProbingHashTable()
		{
		}
	}
}
