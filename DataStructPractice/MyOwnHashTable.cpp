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
}
