/*
 * [Topic] std::vector — 동적 배열
 * 가장 많이 쓰는 STL 컨테이너. 연속 메모리, 랜덤 접근 O(1).
 *
 * Key points:
 *   - push_back vs emplace_back : emplace_back이 불필요한 복사 없음
 *   - reserve() : 메모리 미리 확보 (reallocation 방지)
 *   - size() vs capacity() : 원소 수 vs 할당된 메모리
 *   - 범위 기반 접근 : at() (범위 체크), [] (범위 체크 없음)
 *
 * Practice:
 *   - push_back 전 reserve(1000) 하는 버전과 안 하는 버전의 속도 비교
 *   - erase + remove_if 조합으로 홀수만 삭제해보기
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

int main() {
    // 기본 생성
    vector<int> v = {5, 3, 1, 4, 2};

    // 정렬
    sort(v.begin(), v.end());
    for (int x : v) cout << x << " ";
    cout << "\n";

    // push_back vs emplace_back
    vector<Point> pts;
    pts.reserve(10);  // 미리 공간 확보
    pts.push_back(Point(1, 2));      // 임시 객체 생성 후 이동
    pts.emplace_back(3, 4);          // 직접 생성 (더 효율적)

    cout << "size: " << pts.size() << ", capacity: " << pts.capacity() << "\n";

    // 삭제: erase-remove 이디엄
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8};
    nums.erase(remove_if(nums.begin(), nums.end(),
               [](int x) { return x % 2 == 0; }),  // 짝수 제거
               nums.end());
    for (int x : nums) cout << x << " ";
    cout << "\n";

    // 2D vector
    int rows = 3, cols = 4;
    vector<vector<int>> grid(rows, vector<int>(cols, 0));
    grid[1][2] = 42;
    cout << "grid[1][2] = " << grid[1][2] << "\n";

    return 0;
}
