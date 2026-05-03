/*
 * [Topic] JSON Read/Write with jsoncpp
 * 설정 파일, API 응답 등 실무에서 가장 많이 쓰는 데이터 형식.
 *
 * 빌드 요구사항:
 *   - jsoncpp 설치: vcpkg install jsoncpp
 *   - CMake: find_package(jsoncpp CONFIG REQUIRED)
 *             target_link_libraries(target PRIVATE jsoncpp_lib)
 *
 * Key points:
 *   - Json::Value : 모든 JSON 타입을 표현하는 범용 클래스
 *   - Json::Reader / CharReaderBuilder : JSON 파싱
 *   - Json::StreamWriterBuilder : JSON 직렬화
 *
 * Practice:
 *   - config.json에서 설정을 읽어 프로그램에 적용하는 패턴 구현
 *   - 중첩 JSON (객체 안의 배열 안의 객체) 읽기/쓰기
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
// jsoncpp가 없는 환경을 위해 수동 JSON 생성/파싱 예제도 함께 제공
// #include <json/json.h>
using namespace std;

// jsoncpp 없이 간단한 JSON 문자열 생성 (학습용)
string make_simple_json(const string& name, int age, bool active) {
    return "{\n"
           "  \"name\": \"" + name + "\",\n"
           "  \"age\": " + to_string(age) + ",\n"
           "  \"active\": " + (active ? "true" : "false") + "\n"
           "}";
}

// 설정 파일 읽기 패턴 (jsoncpp 사용 시)
/*
Json::Value load_config(const string& path) {
    ifstream in(path);
    Json::Value root;
    Json::CharReaderBuilder reader;
    string errs;
    Json::parseFromStream(reader, in, &root, &errs);
    return root;
}

void save_config(const string& path, const Json::Value& config) {
    ofstream out(path);
    Json::StreamWriterBuilder writer;
    writer["indentation"] = "  ";
    out << Json::writeString(writer, config);
}
*/

int main() {
    // JSON 파일 생성 (수동)
    const string filename = "config.json";
    {
        ofstream out(filename);
        out << "{\n"
            << "  \"app_name\": \"MyApp\",\n"
            << "  \"version\": 1,\n"
            << "  \"debug\": false,\n"
            << "  \"server\": {\n"
            << "    \"host\": \"localhost\",\n"
            << "    \"port\": 8080\n"
            << "  },\n"
            << "  \"features\": [\"auth\", \"logging\", \"cache\"]\n"
            << "}\n";
        cout << filename << " 생성\n";
    }

    // JSON 파일 읽기 (단순 출력)
    {
        ifstream in(filename);
        cout << "\n--- " << filename << " 내용 ---\n";
        cout << in.rdbuf();
    }

    // jsoncpp 사용 패턴 예시 (주석 형태로 제공)
    cout << "\n--- jsoncpp 사용 패턴 (주석 참고) ---\n";
    cout << "// Json::Value config = load_config(\"config.json\");\n";
    cout << "// string host = config[\"server\"][\"host\"].asString();\n";
    cout << "// int port = config[\"server\"][\"port\"].asInt();\n";
    cout << "// for (auto& f : config[\"features\"]) cout << f.asString();\n";

    // 수동 JSON 생성
    cout << "\n" << make_simple_json("홍길동", 30, true) << "\n";

    return 0;
}
