/*
 * [Topic] Thread Pool — 스레드 풀 직접 구현
 * 미리 만들어 둔 고정된 수의 스레드들이 큐에서 작업을 꺼내 처리한다.
 * 매번 스레드 생성/소멸하는 비용(~수십μs)을 제거할 수 있다.
 *
 * 구성 요소:
 *   - workers    : 항상 실행 중인 스레드들
 *   - task queue : 함수 객체를 저장하는 안전한 큐
 *   - cv + mutex : 새 작업 도착 통지
 *   - stop flag  : 종료 신호
 *
 * Key points:
 *   - function<void()>로 임의 작업 저장
 *   - packaged_task로 future 연결 → 결과 회수 가능
 *   - 소멸자에서 stop=true, notify_all, 모든 join 처리
 *   - invoke_result_t<F> : 함수 반환 타입 추론 (C++17)
 *
 * Practice:
 *   - 스레드 수를 1~8로 바꾸며 처리 속도 비교
 *   - 최대 큐 크기를 제한하는 bounded pool 구현
 *   - 작업 우선순위(priority) 추가 (priority_queue 활용)
 */
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <functional>
#include <future>
#include <chrono>
using namespace std;

class ThreadPool {
    vector<thread> workers;
    queue<function<void()>> tasks;
    mutex mtx;
    condition_variable cv;
    bool stop = false;

public:
    explicit ThreadPool(size_t num_threads) {
        for (size_t i = 0; i < num_threads; i++) {
            workers.emplace_back([this] {
                while (true) {
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(mtx);
                        // 작업이 있거나 종료 신호가 올 때까지 대기
                        cv.wait(lock, [this]{ return stop || !tasks.empty(); });
                        if (stop && tasks.empty()) return;  // 종료
                        task = move(tasks.front());
                        tasks.pop();
                    }
                    task();  // lock 밖에서 실행 (다른 스레드가 큐 접근 가능)
                }
            });
        }
        cout << "ThreadPool: " << num_threads << "개 스레드 준비\n";
    }

    // 작업 제출 — future<T>로 결과 반환
    template<typename F>
    auto enqueue(F&& f) -> future<invoke_result_t<F>> {
        using RetType = invoke_result_t<F>;
        // packaged_task로 future 연결
        auto task = make_shared<packaged_task<RetType()>>(forward<F>(f));
        future<RetType> result = task->get_future();
        {
            lock_guard<mutex> lock(mtx);
            if (stop) throw runtime_error("ThreadPool 종료됨");
            // lambda로 감싸서 function<void()>에 저장
            tasks.emplace([task](){ (*task)(); });
        }
        cv.notify_one();  // 대기 중인 worker 하나 깨우기
        return result;
    }

    // 소멸자: 남은 작업 모두 처리 후 종료
    ~ThreadPool() {
        {
            lock_guard<mutex> lock(mtx);
            stop = true;
        }
        cv.notify_all();  // 모든 worker 깨우기
        for (auto& w : workers) w.join();
        cout << "ThreadPool 종료\n";
    }
};

int main() {
    ThreadPool pool(4);  // 4개 스레드

    cout << "\n=== 8개 작업 제출 ===\n";
    vector<future<int>> results;

    for (int i = 0; i < 8; i++) {
        results.push_back(pool.enqueue([i]() -> int {
            this_thread::sleep_for(chrono::milliseconds(100));
            cout << "  작업 " << i << " 완료 (thread "
                 << this_thread::get_id() << ")\n";
            return i * i;
        }));
    }

    cout << "결과: ";
    for (auto& f : results) cout << f.get() << " ";
    cout << "\n\n";

    cout << "=== 다양한 타입 반환 ===\n";
    auto s = pool.enqueue([]() -> string { return "string 작업"; });
    auto d = pool.enqueue([]() -> double { return 3.14; });
    cout << s.get() << "\n";
    cout << d.get() << "\n";

    return 0;
}
