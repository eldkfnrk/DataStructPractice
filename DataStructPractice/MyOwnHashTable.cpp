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
}
