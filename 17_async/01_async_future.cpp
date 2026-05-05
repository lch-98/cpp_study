/*
 * [Topic] std::async & std::future
 * 스레드 생성 없이 비동기 작업을 실행하고 결과를 나중에 받는다.
 *
 * std::async(policy, func, args...) → future<T>
 *   launch::async    : 즉시 새 스레드에서 실행
 *   launch::deferred : future::get() 호출 시 현재 스레드에서 실행 (지연 평가)
 *
 * future<T>:
 *   get()   : 결과 반환 (완료까지 블로킹)
 *   wait()  : 완료까지 대기 (결과 안 받음)
 *   valid() : future 유효 여부
 *
 * thread vs async:
 *   thread  → 저수준, join/detach 수동 관리, 반환값 없음
 *   async   → 고수준, 반환값 자동 전달, 예외도 자동 전파
 *
 * Practice:
 *   - 5개의 작업을 비동기로 동시 실행하고 결과 합산하기
 *   - wait_for()로 타임아웃 있는 대기 구현해보기
 */
#include <iostream>
#include <future>
#include <vector>
#include <chrono>
#include <thread>
#include <numeric>
using namespace std;

// 무거운 계산 시뮬레이션
int heavy_compute(int n) {
    this_thread::sleep_for(chrono::milliseconds(100 * n));
    int result = 0;
    for (int i = 1; i <= n * 100; i++) result += i;
    return result;
}

// 병렬 합산: 벡터를 반으로 나눠 비동기 계산
long long parallel_sum(const vector<int>& v) {
    size_t mid = v.size() / 2;
    // 왼쪽 절반을 별도 스레드에서 계산
    auto left_fut = async(launch::async, [&](){
        return accumulate(v.begin(), v.begin() + mid, 0LL);
    });
    // 오른쪽 절반은 현재 스레드에서 계산 (동시 진행)
    long long right = accumulate(v.begin() + mid, v.end(), 0LL);
    return left_fut.get() + right;
}

int main() {
    cout << "=== 기본 async/future ===\n";
    auto t_start = chrono::steady_clock::now();

    // 3개 작업을 동시에 실행 (순차라면 100+200+300 = 600ms)
    auto f1 = async(launch::async, heavy_compute, 3);
    auto f2 = async(launch::async, heavy_compute, 2);
    auto f3 = async(launch::async, heavy_compute, 1);

    cout << "작업 시작, 결과 대기 중...\n";
    cout << "f3: " << f3.get() << "\n";
    cout << "f2: " << f2.get() << "\n";
    cout << "f1: " << f1.get() << "\n";

    auto elapsed = chrono::duration_cast<chrono::milliseconds>(
        chrono::steady_clock::now() - t_start).count();
    cout << "총 시간: " << elapsed << "ms (순차라면 ~600ms)\n\n";

    // launch::deferred — get() 호출 시점에 실행 (지연 평가)
    cout << "=== launch::deferred ===\n";
    auto lazy = async(launch::deferred, [](){
        cout << "  지금 실행됨 (get() 호출 시점)\n";
        return 42;
    });
    cout << "lazy 선언 후 — 아직 실행 안 됨\n";
    cout << "lazy.get() = " << lazy.get() << "\n\n";

    // 병렬 합산
    cout << "=== 병렬 합산 ===\n";
    vector<int> data(10000);
    iota(data.begin(), data.end(), 1);
    long long total = parallel_sum(data);
    cout << "1~10000 합: " << total << " (기대: 50005000)\n\n";

    // 예외도 future를 통해 전파됨
    cout << "=== 예외 전파 ===\n";
    auto bad = async(launch::async, []() -> int {
        throw runtime_error("비동기 작업 실패!");
        return 0;
    });
    try {
        bad.get();  // 예외가 여기서 다시 던져짐
    } catch (const exception& e) {
        cout << "예외 받음: " << e.what() << "\n";
    }

    return 0;
}
