/*
 * [Topic] Deadlock — 교착 상태 발생과 해결
 * 두 스레드가 서로의 자원을 기다리며 영원히 블로킹되는 상황.
 *
 * Deadlock 발생 4대 조건 (모두 만족 시 발생):
 *   1. 상호 배제 (Mutual Exclusion) : 자원을 한 번에 하나만 사용
 *   2. 점유 대기 (Hold and Wait)   : 자원을 쥔 채 다른 자원 대기
 *   3. 비선점   (No Preemption)    : 강제로 자원 빼앗기 불가
 *   4. 순환 대기 (Circular Wait)   : A→B 대기하고, B→A 대기
 *
 * 해결 방법:
 *   1. 순환 대기 제거 — 항상 같은 순서로 lock
 *   2. std::scoped_lock (C++17) — 여러 mutex를 deadlock 없이 동시 획득
 *   3. std::lock() + adopt_lock — C++11 방식
 *   4. lock 시도 실패 시 포기 — try_lock 사용
 *
 * Practice:
 *   - 아래 deadlock_version 함수의 주석을 풀고 실제 deadlock을 경험해보기
 *     (Ctrl+C로 종료)
 *   - scoped_lock 버전으로 수정하면 항상 정상 종료됨을 확인
 */
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

mutex mtx_A, mtx_B;

// ===== Deadlock 발생 버전 (주석 풀면 실제로 멈춤!) =====
/*
void deadlock_thread1() {
    lock_guard<mutex> la(mtx_A);           // A 획득
    this_thread::sleep_for(chrono::milliseconds(10));
    lock_guard<mutex> lb(mtx_B);           // B 대기 (thread2가 B 점유 중)
    cout << "Thread1: A, B 획득\n";
}
void deadlock_thread2() {
    lock_guard<mutex> lb(mtx_B);           // B 획득
    this_thread::sleep_for(chrono::milliseconds(10));
    lock_guard<mutex> la(mtx_A);           // A 대기 (thread1이 A 점유 중)
    cout << "Thread2: B, A 획득\n";        // 영원히 도달 못 함
}
*/

// ===== 해결 1: 항상 같은 순서로 lock =====
void safe_order_1() {
    lock_guard<mutex> la(mtx_A);  // 항상 A → B
    this_thread::sleep_for(chrono::milliseconds(10));
    lock_guard<mutex> lb(mtx_B);
    cout << "safe_order Thread1: A, B 획득\n";
}
void safe_order_2() {
    lock_guard<mutex> la(mtx_A);  // 항상 A → B (순서 통일)
    this_thread::sleep_for(chrono::milliseconds(10));
    lock_guard<mutex> lb(mtx_B);
    cout << "safe_order Thread2: A, B 획득\n";
}

// ===== 해결 2: std::scoped_lock (C++17 권장) =====
void scoped_1() {
    scoped_lock lock(mtx_A, mtx_B);  // 내부적으로 deadlock-free 알고리즘 사용
    cout << "scoped_lock Thread1: A, B 획득\n";
}
void scoped_2() {
    scoped_lock lock(mtx_B, mtx_A);  // 순서 달라도 안전!
    cout << "scoped_lock Thread2: B, A 획득\n";
}

// ===== 해결 3: std::lock + adopt_lock (C++11) =====
void adopt_1() {
    lock(mtx_A, mtx_B);  // 두 mutex를 deadlock 없이 동시 획득
    lock_guard<mutex> la(mtx_A, adopt_lock);  // 이미 잠근 mutex 관리 위임
    lock_guard<mutex> lb(mtx_B, adopt_lock);
    cout << "adopt_lock Thread1: A, B 획득\n";
}
void adopt_2() {
    lock(mtx_B, mtx_A);
    lock_guard<mutex> lb(mtx_B, adopt_lock);
    lock_guard<mutex> la(mtx_A, adopt_lock);
    cout << "adopt_lock Thread2: B, A 획득\n";
}

int main() {
    cout << "=== 해결 1: 동일 순서 lock ===\n";
    { thread t1(safe_order_1), t2(safe_order_2); t1.join(); t2.join(); }

    cout << "\n=== 해결 2: scoped_lock (C++17) ===\n";
    { thread t1(scoped_1), t2(scoped_2); t1.join(); t2.join(); }

    cout << "\n=== 해결 3: std::lock + adopt_lock ===\n";
    { thread t1(adopt_1), t2(adopt_2); t1.join(); t2.join(); }

    cout << "\n--- Deadlock 예방 원칙 ---\n";
    cout << "1. 항상 같은 순서로 mutex 획득\n";
    cout << "2. scoped_lock으로 여러 mutex 동시 획득\n";
    cout << "3. lock 보유 시간 최소화 (임계 구역을 최대한 짧게)\n";
    cout << "4. 중첩 lock 최대한 피하기\n";

    return 0;
}
