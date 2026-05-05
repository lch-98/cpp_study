/*
 * [Topic] std::atomic — 원자적 연산 (lock-free)
 * mutex 없이 단순 연산을 스레드 안전하게 수행한다.
 * 내부적으로 CPU의 CAS(Compare-And-Swap) 명령어를 사용한다.
 *
 * Key points:
 *   - atomic<T>의 모든 연산은 분리되지 않음 (all-or-nothing)
 *   - mutex보다 빠름 (OS 개입 없는 하드웨어 수준 동기화)
 *   - 복잡한 연산(여러 변수 동시 수정)은 여전히 mutex 필요
 *   - fetch_add(n) : 더하기 전 값 반환 (원자적)
 *   - compare_exchange_weak/strong : CAS 연산
 *     expected값과 현재값이 같으면 desired로 교체, 아니면 expected 업데이트
 *
 * lock-free vs mutex:
 *   mutex   → OS 커널 개입, context switch 가능, 느림
 *   atomic  → 하드웨어 명령 하나, 빠름, 단순 연산에만 적합
 *
 * Practice:
 *   - atomic<bool> running 플래그로 스레드 중단 구현
 *   - lock-free 단일 연결 리스트 push_front 구현 (고급)
 */
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <chrono>
using namespace std;

// ===== 비교: 일반 int vs atomic<int> =====
int regular_counter = 0;
atomic<int> atomic_counter{0};

void increment_regular() {
    for (int i = 0; i < 100000; i++) regular_counter++;  // 경쟁 상태!
}
void increment_atomic() {
    for (int i = 0; i < 100000; i++) atomic_counter++;   // 안전
}

// ===== atomic 플래그로 스레드 중단 =====
atomic<bool> running{true};

void background_task(int id) {
    int count = 0;
    while (running.load(memory_order_relaxed)) {
        count++;
        this_thread::sleep_for(chrono::microseconds(10));
    }
    cout << "worker " << id << " 종료 (count=" << count << ")\n";
}

// ===== CAS(Compare-And-Swap) 사용 예 =====
atomic<int> shared_val{0};

bool try_increment_if_less_than(int limit) {
    int expected = shared_val.load();
    while (expected < limit) {
        // expected와 현재값이 같으면 expected+1로 교체, 아니면 expected 업데이트
        if (shared_val.compare_exchange_weak(expected, expected + 1))
            return true;
        // 실패 시 expected가 현재 값으로 자동 업데이트됨 → 재시도
    }
    return false;
}

int main() {
    cout << "=== 경쟁 상태 비교 (10스레드 x 100000) ===\n";
    {
        vector<thread> threads;
        for (int i = 0; i < 10; i++) {
            threads.emplace_back(increment_regular);
            threads.emplace_back(increment_atomic);
        }
        for (auto& t : threads) t.join();
        cout << "regular_counter: " << regular_counter
             << " (기대: 1000000, 불일치 가능)\n";
        cout << "atomic_counter:  " << atomic_counter.load()
             << " (항상 1000000)\n\n";
    }

    cout << "=== atomic 플래그로 스레드 중단 ===\n";
    {
        thread w1(background_task, 1);
        thread w2(background_task, 2);
        this_thread::sleep_for(chrono::milliseconds(30));
        running.store(false, memory_order_relaxed);
        w1.join(); w2.join();
    }

    cout << "\n=== fetch_add / fetch_sub ===\n";
    {
        atomic<int> val{0};
        int old = val.fetch_add(10);  // 더하기 전 값 반환
        cout << "fetch_add(10): old=" << old << " new=" << val << "\n";
        old = val.fetch_sub(3);
        cout << "fetch_sub(3): old=" << old << " new=" << val << "\n";
    }

    cout << "\n=== compare_exchange (CAS) ===\n";
    {
        atomic<int> val{10};
        int expected = 10;
        bool ok = val.compare_exchange_strong(expected, 99);
        cout << "CAS(10→99): " << (ok ? "성공" : "실패") << " val=" << val << "\n";

        expected = 10;  // 이미 99이므로 실패
        ok = val.compare_exchange_strong(expected, 0);
        cout << "CAS(10→0): " << (ok ? "성공" : "실패")
             << " val=" << val << " expected(업데이트됨)=" << expected << "\n";
    }

    cout << "\n=== CAS 기반 제한 증가 ===\n";
    {
        shared_val = 0;
        vector<thread> threads;
        atomic<int> success_count{0};
        for (int i = 0; i < 5; i++) {
            threads.emplace_back([&](){
                if (try_increment_if_less_than(3)) success_count++;
            });
        }
        for (auto& t : threads) t.join();
        cout << "shared_val: " << shared_val
             << " (최대 3), 성공: " << success_count << "번\n";
    }

    cout << "\n--- 선택 기준 ---\n";
    cout << "단순 카운터/플래그  → atomic<int>, atomic<bool>\n";
    cout << "여러 변수 동시 보호 → mutex\n";
    cout << "조건 만족까지 대기  → condition_variable\n";

    return 0;
}
