/*
 * [Topic] condition_variable — 조건 변수 (생산자-소비자 패턴)
 * 특정 조건이 만족될 때까지 스레드를 효율적으로 대기시킨다.
 * busy-wait(while 루프로 계속 확인)와 달리 CPU를 양보하며 대기한다.
 *
 * Key points:
 *   - wait(lock, pred) : pred가 false면 대기, 깨어나면 재확인 (spurious wakeup 방지)
 *   - notify_one()     : 대기 중인 스레드 하나를 깨움
 *   - notify_all()     : 대기 중인 모든 스레드를 깨움
 *   - unique_lock 필수 : lock_guard는 wait()에 사용 불가 (unlock이 필요하기 때문)
 *
 * Spurious wakeup:
 *   OS가 이유 없이 스레드를 깨울 수 있음 → wait의 predicate로 재확인 필수
 *
 * Practice:
 *   - 큐 최대 크기를 제한하는 bounded buffer 구현 (큐가 꽉 차면 생산자도 대기)
 *   - 생산자 2개, 소비자 2개로 늘려 동작 확인
 */
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>
using namespace std;

class TaskQueue {
    queue<int> q;
    mutex mtx;
    condition_variable cv;
    bool done = false;  // 생산 종료 신호

public:
    // 생산자: 값 추가 후 소비자 깨우기
    void produce(int val) {
        {
            lock_guard<mutex> lock(mtx);
            q.push(val);
            cout << "생산: " << val << "\n";
        }
        cv.notify_one();
    }

    // 생산 종료 신호
    void finish() {
        {
            lock_guard<mutex> lock(mtx);
            done = true;
        }
        cv.notify_all();  // 대기 중인 소비자 모두 깨움
    }

    // 소비자: 값이 올 때까지 대기
    bool consume(int& val) {
        unique_lock<mutex> lock(mtx);
        // 큐가 비어있고 아직 생산 중이면 대기
        cv.wait(lock, [this]{ return !q.empty() || done; });
        if (q.empty()) return false;  // done이고 큐도 비어있음 → 종료
        val = q.front();
        q.pop();
        cout << "  소비: " << val << "\n";
        return true;
    }
};

int main() {
    TaskQueue tq;

    thread producer([&](){
        for (int i = 1; i <= 5; i++) {
            tq.produce(i * 10);
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        tq.finish();
        cout << "생산자 종료\n";
    });

    thread consumer([&](){
        int val;
        while (tq.consume(val)) {
            // 소비가 생산보다 느린 상황 시뮬레이션
            this_thread::sleep_for(chrono::milliseconds(150));
        }
        cout << "소비자 종료\n";
    });

    producer.join();
    consumer.join();

    cout << "\n--- 핵심 정리 ---\n";
    cout << "busy-wait    : while(!ready) {}  → CPU 100% 낭비\n";
    cout << "cv.wait()    : 조건 만족까지 CPU 양보 → 효율적\n";
    cout << "predicate    : spurious wakeup 방지 필수\n";

    return 0;
}
