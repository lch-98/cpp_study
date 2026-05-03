/*
 * [Topic] CSV Parsing — CSV 파일 파싱
 * 콤마로 구분된 데이터 파일을 읽고 쓰는 실용 예제.
 *
 * Key points:
 *   - getline(stream, token, ',') : 구분자 지정 getline
 *   - stringstream : 문자열을 스트림으로 파싱
 *   - 따옴표 안의 쉼표 처리는 실무에서 중요 (여기서는 단순화)
 *
 * Practice:
 *   - 성적 CSV를 읽어 평균 점수 기준으로 정렬 후 저장하기
 *   - 특정 열만 추출해서 새 CSV 파일 생성하기
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Student {
    string name;
    int math, english, science;
    double average() const { return (math + english + science) / 3.0; }
};

vector<string> split(const string& line, char delim) {
    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (getline(ss, token, delim))
        tokens.push_back(token);
    return tokens;
}

int main() {
    const string filename = "students.csv";

    // CSV 쓰기
    {
        ofstream out(filename);
        out << "name,math,english,science\n";
        out << "Alice,95,88,92\n";
        out << "Bob,72,85,78\n";
        out << "Charlie,88,91,85\n";
        out << "Diana,65,79,70\n";
    }

    // CSV 읽기
    vector<Student> students;
    {
        ifstream in(filename);
        string line;
        getline(in, line);  // 헤더 스킵

        while (getline(in, line)) {
            auto cols = split(line, ',');
            if (cols.size() < 4) continue;
            students.push_back({
                cols[0],
                stoi(cols[1]),
                stoi(cols[2]),
                stoi(cols[3])
            });
        }
    }

    // 평균 기준 정렬 (내림차순)
    sort(students.begin(), students.end(),
         [](const Student& a, const Student& b) {
             return a.average() > b.average();
         });

    // 출력
    cout << "이름          수학  영어  과학  평균\n";
    cout << string(40, '-') << "\n";
    for (const auto& s : students)
        cout << s.name << "\t" << s.math << "\t"
             << s.english << "\t" << s.science << "\t"
             << s.average() << "\n";

    // 결과 CSV 저장
    {
        ofstream out("students_sorted.csv");
        out << "name,math,english,science,average\n";
        for (const auto& s : students)
            out << s.name << "," << s.math << ","
                << s.english << "," << s.science << ","
                << s.average() << "\n";
        cout << "\nstudents_sorted.csv 저장 완료\n";
    }

    return 0;
}
