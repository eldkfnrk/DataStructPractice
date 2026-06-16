#pragma once
#include "CommonInclude.h"

namespace DataStruct {
	// 해시 테이블
	// 키-값 쌍으로 데이터를 저장하는 자료구조 -> 빠르게 데이터 검색이 가능
	// 빠른 검색 속도를 보장하는 이유 - 내부적으로 배열(버킷)을 사용하여 데이터를 저장
	// 해시 테이블은 각각의 키 값에 해시 함수를 적용 -> 배열의 고유한 index를 생성 -> index를 활용해 값을 저장하거나 검색
	// 이때 실제 값이 저장되는 장소를 버킷 혹은 슬롯이라 지칭
	// 그러니까 키는 해시 함수를 이용한 연산을 통해 해시 값으로 변환시키고 이 값을 index로 사용하여 데이터를 저장하는 키-값 매핑 자료구조인 것이다.
	// 간단하게 용어 정리를 해보면 아래와 같다.
	// 해싱 - 각각의 데이터를 가급적 고유한 숫자로 표현하고 나중에 이 숫자 값을 이용하여 데이터 유무 확인 혹은 원본 데이터 추출을 하는 작업을 의미
	// 해시 함수 - 데이터를 고유한 숫자 값으로 변환하도록 계산하는 함수
	// 해시 값 - 해시 함수에 의해 반환되는 숫자 값
	// 충돌 - 해시 함수가 서로 다른 키에 대해 같은 해시 값을 반환하면서 다수의 키가 같은 값을 갖게 되는 현상
	// 해시 테이블 연습은 여러 문제를 가지고 이 문제를 해결하기 위하여 만들어 볼 것이고 문제는 책에 나온 내용과 추가로 조사한 문제들을 사용할 예정이다.

	// 문제 1. 정수 값을 저장하는 간단한 사전(부호 없는 정수)
	namespace SaveInteger {
		// 이 문제는 정수 값을 저장하는 문제
		// 해시 테이블은 vector를 이용
		// 해시 값은 간단하게 저장할 정수 값에 해시 테이블로 이용할 vector의 크기를 나눈 나머지 값을 활용
		// 해당 해시 값의 위치에 값을 저장
		class OwnHashTable
		{
		public:
			OwnHashTable(int size);

			void Insert(int value);  // 값 삽입
			bool Find(int value);  // 값 탐색(있는지 없는지)
			void Delete(int value);  // 값 삭제

			~OwnHashTable();

		private:
			std::vector<int> hash_table;
			int size;
		};
	}

	// 문제 2. 체이닝을 사용하는 해시 테이블
	namespace UseChaining{
		// 이 문제는 충돌 문제를 해결하기 위한 여러 방법 중 하나인 체이닝을 이용하여 해시 테이블을 만들어 보는 문제이다.
		// 여기서 체이닝이란 충돌이 일어난 값을 모두 저장할 수 있는 여러 방법 중 하나이다.
		// 체이닝은 연결 리스트를 저장하여 충돌이 일어난 키 안에 충돌이 발생한 값들을 저장한 순서대로 저장하는 기법이다.
		// 해시 함수는 문제 1과 동일하게 모듈러 함수를 사용
		class OwnChainingHashTable {
		public:
			OwnChainingHashTable(int size);

			void ChainingInsert(int value);
			bool ChainingFind(int value);
			void ChainingDelete(int value);

			~OwnChainingHashTable();

		private:
			std::vector<std::list<int>> hashTable;
			int size;
		};
	}
}
