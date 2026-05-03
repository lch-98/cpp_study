/*
 * [Topic] Move Semantics — 이동 시멘틱
 * 불필요한 복사를 없애 성능을 높이는 C++11의 핵심 기능.
 *
 * lvalue : 이름이 있는 값, 주소를 취할 수 있음
 * rvalue : 이름이 없는 임시 값, 표현식 결과
 *
 * 이동 생성자: 자원을 복사하지 않고 소유권을 이전
 * std::move:  lvalue를 rvalue로 캐스팅 (이동 허용)
 *
 * Key points:
 *   - 이동 후 원본은 유효하지만 비어있는 상태
 *   - 이동 생성자/대입연산자는 noexcept 선언 권장
 *   - Rule of Five: 소멸자, 복사 생성자, 복사 대입, 이동 생성자, 이동 대입
 *
 * Practice:
 *   - BigData에서 move 없이 vector push_back과 move 있는 버전 성능 비교
 *   - 이동 생성자를 delete 하면 어떻게 되는지 확인
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Buffer {
    int* data;
    size_t size;
public:
    Buffer(size_t n) : size(n), data(new int[n]) {
        cout << "생성 (size=" << n << ")\n";
    }
    // 복사 생성자
    Buffer(const Buffer& other) : size(other.size), data(new int[other.size]) {
        copy(other.data, other.data + size, data);
        cout << "복사 생성\n";
    }
    // 이동 생성자
    Buffer(Buffer&& other) noexcept : size(other.size), data(other.data) {
        other.data = nullptr;
        other.size = 0;
        cout << "이동 생성\n";
    }
    // 복사 대입
    Buffer& operator=(const Buffer& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            copy(other.data, other.data + size, data);
            cout << "복사 대입\n";
        }
        return *this;
    }
    // 이동 대입
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
            cout << "이동 대입\n";
        }
        return *this;
    }
    ~Buffer() {
        delete[] data;
        cout << "소멸 (size=" << size << ")\n";
    }
    size_t getSize() const { return size; }
};

Buffer make_buffer(size_t n) {
    return Buffer(n);  // RVO/NRVO로 이동도 생략될 수 있음
}

int main() {
    cout << "=== 복사 ===\n";
    Buffer b1(100);
    Buffer b2 = b1;  // 복사 생성자

    cout << "\n=== 이동 ===\n";
    Buffer b3 = move(b1);  // 이동 생성자 (b1은 이후 비어있음)
    cout << "b1.size after move: " << b1.getSize() << "\n";

    cout << "\n=== 함수 반환 ===\n";
    Buffer b4 = make_buffer(50);  // RVO 적용 가능

    cout << "\n=== vector에 이동 ===\n";
    vector<Buffer> vec;
    vec.push_back(Buffer(10));  // rvalue → 이동
    Buffer b5(20);
    vec.push_back(move(b5));   // move로 이동

    cout << "\n=== 소멸 ===\n";
    return 0;
}
