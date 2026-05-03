/*
 * [Topic] Binary File I/O — 바이너리 파일 입출력
 * 텍스트가 아닌 바이너리 형식으로 데이터를 저장하고 읽는다.
 *
 * 장점:
 *   - 텍스트보다 공간 효율적 (int 4바이트, 텍스트는 최대 11바이트)
 *   - 읽기/쓰기 속도 빠름
 *   - 숫자를 변환 없이 그대로 저장
 *
 * Key points:
 *   - write(reinterpret_cast<char*>(&val), sizeof(val))
 *   - read(reinterpret_cast<char*>(&val), sizeof(val))
 *   - seekg/seekp : 파일 포인터 이동
 *   - tellg/tellp : 현재 파일 포인터 위치
 *
 * Practice:
 *   - Student 구조체 배열을 바이너리로 저장하고 읽어보기
 *   - 특정 인덱스의 레코드만 수정하는 함수 만들기 (seekp 활용)
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Record {
    int id;
    double value;
    char label[32];  // 고정 크기 문자열 (직렬화 편의)
};

int main() {
    const string filename = "data.bin";

    // 바이너리 쓰기
    {
        ofstream out(filename, ios::binary);
        vector<Record> records = {
            {1, 3.14, "pi"},
            {2, 2.718, "e"},
            {3, 1.414, "sqrt2"},
        };
        for (const auto& r : records)
            out.write(reinterpret_cast<const char*>(&r), sizeof(Record));
        cout << records.size() << "개 레코드 저장\n";
    }

    // 파일 크기 확인
    {
        ifstream in(filename, ios::binary | ios::ate);  // ate: 끝에서 시작
        cout << "파일 크기: " << in.tellg() << " bytes\n";
        cout << "예상 크기: " << 3 * sizeof(Record) << " bytes\n";
    }

    // 바이너리 읽기
    {
        ifstream in(filename, ios::binary);
        Record r;
        cout << "\n--- 저장된 레코드 ---\n";
        while (in.read(reinterpret_cast<char*>(&r), sizeof(Record)))
            cout << "id=" << r.id << " val=" << r.value << " label=" << r.label << "\n";
    }

    // 랜덤 접근: 두 번째 레코드만 읽기
    {
        ifstream in(filename, ios::binary);
        in.seekg(sizeof(Record));  // 첫 번째 레코드 건너뜀
        Record r;
        in.read(reinterpret_cast<char*>(&r), sizeof(Record));
        cout << "\n두 번째 레코드: " << r.label << " = " << r.value << "\n";
    }

    return 0;
}
