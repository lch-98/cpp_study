/*
 * [Topic] Observer Pattern — 옵저버
 * 한 객체의 상태 변화를 여러 객체가 자동으로 통지받는 패턴.
 *
 * 사용 예: 이벤트 시스템, UI 업데이트, 데이터 바인딩
 * 구성:
 *   Subject  : 상태를 가진 발행자, 옵저버 등록/해제/알림
 *   Observer : 알림을 받아 처리하는 구독자
 *
 * Practice:
 *   - StockMarket Subject에 여러 투자자 Observer 연결하기
 *   - 특정 조건(가격 임계값)에서만 알림 받도록 필터링 추가
 */
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
using namespace std;

// 옵저버 인터페이스
class IObserver {
public:
    virtual void onEvent(const string& event, int value) = 0;
    virtual ~IObserver() = default;
};

// 발행자 (Subject)
class EventBus {
    vector<IObserver*> observers;
public:
    void subscribe(IObserver* obs) { observers.push_back(obs); }
    void unsubscribe(IObserver* obs) {
        observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
    }
    void publish(const string& event, int value) {
        cout << "[EventBus] 발행: " << event << " = " << value << "\n";
        for (auto* obs : observers) obs->onEvent(event, value);
    }
};

// 구체 옵저버들
class TemperatureMonitor : public IObserver {
    string name;
    int alert_threshold;
public:
    TemperatureMonitor(string n, int threshold) : name(n), alert_threshold(threshold) {}
    void onEvent(const string& event, int value) override {
        if (event != "temperature") return;
        cout << "  [" << name << "] 온도: " << value << "°C";
        if (value > alert_threshold) cout << " ⚠ 경보!";
        cout << "\n";
    }
};

class Logger : public IObserver {
public:
    void onEvent(const string& event, int value) override {
        cout << "  [Logger] " << event << "=" << value << " 기록\n";
    }
};

int main() {
    EventBus bus;

    TemperatureMonitor sensor1("거실 센서", 30);
    TemperatureMonitor sensor2("서버룸 센서", 25);
    Logger logger;

    bus.subscribe(&sensor1);
    bus.subscribe(&sensor2);
    bus.subscribe(&logger);

    bus.publish("temperature", 22);
    bus.publish("temperature", 28);
    bus.publish("temperature", 35);

    cout << "\n[거실 센서 구독 해제]\n";
    bus.unsubscribe(&sensor1);
    bus.publish("temperature", 40);

    return 0;
}
