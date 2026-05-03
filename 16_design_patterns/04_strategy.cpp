/*
 * [Topic] Strategy Pattern — 전략
 * 알고리즘을 캡슐화하여 런타임에 교체 가능하게 한다.
 *
 * 사용 예: 정렬 알고리즘 선택, 압축 방식 선택, 결제 방식
 * OCP (개방/폐쇄 원칙): 새 전략 추가 시 기존 코드 수정 없음
 *
 * Practice:
 *   - PaymentStrategy 인터페이스와 CreditCard, PayPal 전략 구현
 *   - 전략을 설정 파일에서 읽어 동적으로 선택하도록 수정
 */
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

// 정렬 전략 인터페이스
class ISortStrategy {
public:
    virtual void sort(vector<int>& data) = 0;
    virtual string name() const = 0;
    virtual ~ISortStrategy() = default;
};

class BubbleSort : public ISortStrategy {
public:
    void sort(vector<int>& data) override {
        for (size_t i = 0; i < data.size(); i++)
            for (size_t j = 0; j + 1 < data.size() - i; j++)
                if (data[j] > data[j+1]) swap(data[j], data[j+1]);
    }
    string name() const override { return "BubbleSort"; }
};

class QuickSort : public ISortStrategy {
    void qsort(vector<int>& d, int l, int r) {
        if (l >= r) return;
        int pivot = d[r], i = l;
        for (int j = l; j < r; j++) if (d[j] <= pivot) swap(d[i++], d[j]);
        swap(d[i], d[r]);
        qsort(d, l, i-1); qsort(d, i+1, r);
    }
public:
    void sort(vector<int>& data) override { if (!data.empty()) qsort(data, 0, data.size()-1); }
    string name() const override { return "QuickSort"; }
};

class StdSort : public ISortStrategy {
public:
    void sort(vector<int>& data) override { std::sort(data.begin(), data.end()); }
    string name() const override { return "StdSort"; }
};

// Context — 전략을 사용하는 클래스
class Sorter {
    unique_ptr<ISortStrategy> strategy;
public:
    void setStrategy(unique_ptr<ISortStrategy> s) { strategy = move(s); }
    void sort(vector<int>& data) {
        cout << strategy->name() << " 실행: ";
        strategy->sort(data);
        for (int x : data) cout << x << " ";
        cout << "\n";
    }
};

int main() {
    Sorter sorter;
    vector<int> data = {5, 2, 8, 1, 9, 3};

    sorter.setStrategy(make_unique<BubbleSort>());
    auto d1 = data;
    sorter.sort(d1);

    sorter.setStrategy(make_unique<QuickSort>());
    auto d2 = data;
    sorter.sort(d2);

    sorter.setStrategy(make_unique<StdSort>());
    auto d3 = data;
    sorter.sort(d3);

    return 0;
}
