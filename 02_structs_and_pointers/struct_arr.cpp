/*
 * [Topic] Struct Array with Embedded Pointer & typedef
 * 내부에 포인터 멤버를 가진 구조체 배열과 typedef 사용법.
 *
 * struct pos    : 기존 방식 (C++ 에서는 struct 키워드 없이도 사용 가능)
 * typedef struct: C 스타일 별칭 정의 → 타입 이름만으로 선언 가능
 *
 * 포인터 멤버(uint8_t* map) 접근:
 *   example[i].map[j]          → 배열 인덱스로 접근
 *   *(example[i].map + j)      → 포인터 산술로 접근 (동일한 결과)
 */
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"

int main() {
	struct pos {
		int x, y;
		uint8_t *map;
	};

	typedef struct {
		int x, y;
		uint8_t *map;
	}position;

	uint8_t map1[] = { 1, 2, 3 };
	uint8_t map2[] = { 5, 6, 7 };

	struct pos example[] = { // cpp 파일이면 typedef 선언없이 pos example[]도 가능
		{1, 2, map1},
		{3, 4, map2},
	};

	position example1[] = {
		{5, 6, map1},
		{7, 8, map2},
	};

	for (int i = 0; i < 2; i++) {
		printf("example의 위치 값: %d, %d", example[i].x, example[i].y);
		printf("\n");
		for (int j = 0; j < 3; j++) {
			printf("example map%d의 값: %d, %d  ",i+1, example[i].map[j], *(example[i].map + j)); // 포인터로도 값 출력이 가능하다는 것을 보이기 위함 둘다 같은 표현
		}
		printf("\n\n");
		printf("example1의 위치 값: %d, %d", example1[i].x, example1[i].y);
		printf("\n");
		for (int j = 0; j < 3; j++) {
			printf("example1 map%d의 값: %d, %d ", i + 1, example1[i].map[j], *(example1[i].map + j));
		}
		printf("\n\n");
	}
}
