/*
 * [Topic] std::promise — 값을 직접 설정하는 비동기 채널
 * promise는 생산자(값을 설정), future는 소비자(값을 기다림).
 * async는 자동으로 promise/future를 연결하지만,
 * promise를 직접 쓰면 값 설정 시점을 더 세밀하게 제어할 수 있다.
 *
 * Key points:
 *   - promise<T>::set_value(v)      : future에 값 전달
 *   - promise<T>::set_exception(e)  : 예외 전달
 *   - future는 한 번만 get() 가능
 *   - shared_future : 여러 스레드가 같은 결과를 공유
 *   - wait_for(duration) : 타임아웃 있는 대기
 *
 * Practice:
 *   - wait_for()로 1초 타임아웃 구현해보기
 *   - 여러 스레드가 하나의 결과를 기다리는 shared_future 실습
 */
#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <stdexcept>
using namespace std;

// promise로 스레드 간 값 전달
void producer(promise<int> prom, int delay_ms) {
    this_thread::sleep_for(chrono::milliseconds(delay_ms));
    cout << "  생산자: 값 생성 완료\n";
    prom.set_value(42);
}

// promise로 예외 전달
void risky_producer(promise<string> prom, bool fail) {
    try {
        if (fail) throw runtime_error("생산자 실패!");
        prom.set_value("성공적인 결과");
    } catch (...) {
        prom.set_exception(current_exception());
    }
}

// shared_future — 여러 소비자가 같은 결과를 공유
void consumer(shared_future<int> sf, int id) {
    // 각 스레드가 독립적으로 get() 가능
    cout << "  소비자 " << id << ": 결과 = " << sf.get() << "\n";
}

int main() {
    cout << "=== 기본 promise/future ===\n";
    {
        promise<int> prom;
        future<int> fut = prom.get_future();

        thread t(producer, move(prom), 200);
        cout << "소비자: 결과 기다리는 중...\n";
        cout << "소비자: 받은 값 = " << fut.get() << "\n";
        t.join();
    }

    cout << "\n=== 예외 전달 ===\n";
    {
        promise<string> prom;
        auto fut = prom.get_future();
        thread t(risky_producer, move(prom), true);
        t.join();
        try {
            cout << fut.get() << "\n";
        } catch (const exception& e) {
            cout << "예외 받음: " << e.what() << "\n";
        }
    }

    cout << "\n=== wait_for (타임아웃) ===\n";
    {
        promise<int> prom;
        auto fut = prom.get_future();

        thread t([](promise<int> p) {
            this_thread::sleep_for(chrono::milliseconds(300));
            p.set_value(99);
        }, move(prom));

        // 100ms마다 확인
        while (true) {
            auto status = fut.wait_for(chrono::milliseconds(100));
            if (status == future_status::ready) {
                cout << "완료! 값 = " << fut.get() << "\n";
                break;
            } else {
                cout << "  아직 대기 중...\n";
            }
        }
        t.join();
    }

    cout << "\n=== shared_future (다중 소비자) ===\n";
    {
        promise<int> prom;
        // future → shared_future 변환
        shared_future<int> sf = prom.get_future().share();

        thread c1(consumer, sf, 1);
        thread c2(consumer, sf, 2);
        thread c3(consumer, sf, 3);

        this_thread::sleep_for(chrono::milliseconds(50));
        prom.set_value(99);  // 세 소비자 모두 99를 받음

        c1.join(); c2.join(); c3.join();
    }

    return 0;
}
