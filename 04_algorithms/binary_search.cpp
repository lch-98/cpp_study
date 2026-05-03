/*
 * [Topic] Binary Search
 * 정렬된 범위에서 목표값을 O(log n)으로 찾는 이진 탐색 구현.
 *
 * 동작 원리:
 *   1. 탐색 범위의 중간값(mid)을 target과 비교
 *   2. mid < target → 왼쪽 절반 제거 (left = mid + 1)
 *   3. mid > target → 오른쪽 절반 제거 (right = mid - 1)
 *   4. mid == target → 탐색 성공
 *
 * 주의: 입력 배열이 반드시 정렬되어 있어야 한다.
 * 시간 복잡도: O(log n)  /  공간 복잡도: O(1)
 */
#include <iostream>
using namespace std;

int main() {
	int left = 1;
	int right = 10;

	int target = 7;
	while (left <= right) {
		int mid = (left + right) / 2;

		if (mid < target) left = mid + 1;
		else if (mid > target) right = mid - 1;
		else if (mid == target) {
			cout << "answer: " << left << " " << right << " " << mid << "\n";
			break;
		}
		cout << left << " " << right << " " << mid << "\n";
	}
}
