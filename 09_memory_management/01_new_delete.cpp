/*
 * [Topic] new / delete — Heap Memory
 * 스택(자동) vs 힙(수동) 메모리의 차이와 new/delete 사용법.
 *
 * 스택: 함수 종료 시 자동 해제, 크기 제한 있음
 * 힙:  프로그래머가 직접 해제해야 함, 크기 제한 거의 없음
 *
 * Key points:
 *   - new T       : 힙에 T 하나 할당, 포인터 반환
 *   - new T[n]    : 힙에 T 배열 할당
 *   - delete p    : 단일 객체 해제
 *   - delete[] p  : 배열 해제 (new[]와 반드시 쌍으로)
 *
 * Practice:
 *   - delete 없이 실행 후 메모리 사용량 변화 관찰
 *   - new[]를 delete(대괄호 없이)로 해제하면 어떤 UB가 생기는지 조사
 */
#include <iostream>
using namespace std;

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {
        cout << "Point(" << x << "," << y << ") 생성\n";
    }
    ~Point() {
        cout << "Point(" << x << "," << y << ") 소멸\n";
    }
};

int main() {
    // 스택 할당 — 스코프 끝나면 자동 소멸
    {
        Point stack_pt(1, 2);
        cout << "스택 Point: " << stack_pt.x << ", " << stack_pt.y << "\n";
    }
    cout << "스코프 종료 후\n\n";

    // 힙 할당 — delete 하기 전까지 살아있음
    Point* heap_pt = new Point(3, 4);
    cout << "힙 Point: " << heap_pt->x << ", " << heap_pt->y << "\n";
    delete heap_pt;

    // 배열 힙 할당
    int n = 5;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) arr[i] = i * 10;
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\n";
    delete[] arr;  // 반드시 [] 사용

    return 0;
}
