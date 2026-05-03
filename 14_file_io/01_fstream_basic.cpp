/*
 * [Topic] fstream — 파일 입출력 기초
 * C++ 표준 파일 스트림으로 텍스트 파일을 읽고 쓴다.
 *
 * ifstream : 파일 읽기
 * ofstream : 파일 쓰기
 * fstream  : 읽기 + 쓰기
 *
 * Key points:
 *   - is_open() 으로 열기 성공 여부 확인
 *   - getline() 으로 한 줄씩 읽기
 *   - ios::app : 기존 내용 유지하고 뒤에 추가
 *   - ios::binary : 바이너리 모드
 *   - RAII: ifstream 소멸 시 자동으로 close()
 *
 * Practice:
 *   - 파일에서 숫자들을 읽어 합계와 평균 출력하기
 *   - 로그 파일에 타임스탬프와 함께 메시지 추가하기 (ios::app)
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    const string filename = "sample.txt";

    // 파일 쓰기
    {
        ofstream out(filename);
        if (!out.is_open()) {
            cerr << "파일 열기 실패\n";
            return 1;
        }
        out << "첫 번째 줄\n";
        out << "두 번째 줄\n";
        out << "세 번째 줄\n";
        out << 42 << " " << 3.14 << "\n";
        cout << filename << " 쓰기 완료\n";
    }  // ofstream 소멸 → 자동 close

    // 파일 읽기 — 한 줄씩
    {
        ifstream in(filename);
        if (!in.is_open()) { cerr << "파일 없음\n"; return 1; }

        string line;
        int lineNum = 1;
        while (getline(in, line)) {
            cout << lineNum++ << ": " << line << "\n";
        }
    }

    // 파일 읽기 — 단어/숫자 단위
    {
        ifstream in(filename);
        string word;
        vector<string> words;
        while (in >> word) words.push_back(word);
        cout << "단어 수: " << words.size() << "\n";
    }

    // 추가 쓰기 (append)
    {
        ofstream out(filename, ios::app);
        out << "추가된 줄\n";
    }

    // 전체 다시 읽기
    {
        ifstream in(filename);
        cout << "\n--- 최종 파일 내용 ---\n";
        cout << in.rdbuf();  // 전체 내용을 한 번에 출력
    }

    return 0;
}
