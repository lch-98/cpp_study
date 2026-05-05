/*
 * [Topic] std::packaged_task — callable을 future에 연결
 * 함수(또는 람다)를 future와 묶어두고, 나중에 원하는 시점에 실행한다.
 *
 * async vs packaged_task:
 *   async         → 자동으로 스레드 생성 + 실행
 *   packaged_task → 실행 시점을 직접 제어 (수동 호출 or 스레드에 넘김)
 *
 * 주요 사용처:
 *   - Thread pool에서 작업을 큐잉할 때 (18_advanced_threading 참고)
 *   - 실행 시점을 분리해야 할 때
 *
 * Key points:
 *   - packaged_task<R(Args...)> task(func)
 *   - task.get_future() : 연결된 future 획득
 *   - task()            : 실행 (callable처럼 호출)
 *   - 스레드에 move해서 비동기 실행 가능
 *
 * Practice:
 *   - packaged_task를 queue에 넣고 순서대로 실행하는 간단한 큐 구현
 *   - async, promise, packaged_task 셋을 같은 작업에 적용해 비교
 */
#include <iostream>
#include <future>
#include <thread>
#include <queue>
#include <functional>
#include <chrono>
using namespace std;

int compute(int n) {
    this_thread::sleep_for(chrono::milliseconds(100));
    return n * n;
}

int main() {
    cout << "=== 기본 packaged_task ===\n";
    {
        // 함수를 future와 묶기
        packaged_task<int(int)> task(compute);
        future<int> fut = task.get_future();

        // 스레드에 task를 move해서 실행
        thread t(move(task), 7);
        cout << "7의 제곱: " << fut.get() << "\n";
        t.join();
    }

    cout << "\n=== 람다로 packaged_task ===\n";
    {
        packaged_task<string(string, int)> task([](string s, int n) {
            return s + " x" + to_string(n);
        });
        auto fut = task.get_future();

        thread t(move(task), "hello", 3);
        cout << "결과: " << fut.get() << "\n";
        t.join();
    }

    cout << "\n=== 작업 큐 (dispatch queue) ===\n";
    {
        queue<packaged_task<int()>> task_queue;
        vector<future<int>> futures;

        // 작업 큐잉 (아직 실행 안 함)
        for (int i = 1; i <= 4; i++) {
            packaged_task<int()> task([i]() {
                this_thread::sleep_for(chrono::milliseconds(50));
                return i * i;
            });
            futures.push_back(task.get_future());
            task_queue.push(move(task));
        }

        cout << "큐에 " << task_queue.size() << "개 작업 대기 중\n";

        // 순서대로 실행 (단일 스레드)
        while (!task_queue.empty()) {
            auto task = move(task_queue.front());
            task_queue.pop();
            task();  // 직접 실행
        }

        // 결과 수집
        cout << "결과: ";
        for (auto& f : futures) cout << f.get() << " ";
        cout << "\n";
    }

    cout << "\n=== async vs promise vs packaged_task 비교 ===\n";
    cout << "async          → 자동 실행, 가장 간편\n";
    cout << "promise        → 값 설정 시점 자유, 스레드 간 채널\n";
    cout << "packaged_task  → 실행 시점 분리, thread pool에 적합\n";

    return 0;
}
