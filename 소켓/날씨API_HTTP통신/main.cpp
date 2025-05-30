#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <unordered_map>
#include <curl/curl.h>
#include <json/json.h>  // jsoncpp

// libcurl 응답 버퍼에 저장
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// 현재 날짜 YYYYMMDD
std::string getCurrentDate() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[9];
    localtime_s(&tstruct, &now);
    strftime(buf, sizeof(buf), "%Y%m%d", &tstruct);
    return buf;
}

// 현재 시간 HHMM
std::string getCurrentHour() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[5];
    localtime_s(&tstruct, &now);
    strftime(buf, sizeof(buf), "%H%M", &tstruct);
    return buf;
}

int main() {
    // 날씨 코드와 상태를 매핑
    std::unordered_map<std::string, std::string> intToWeather = {
        {"0", "맑음"}, {"1", "비"}, {"2", "비/눈"}, {"3", "눈"},
        {"5", "빗방울"}, {"6", "빗방울눈날림"}, {"7", "눈날림"}
    };

    // 서비스 인증키
    std::string serviceKey = "Your API Key";  // ← URL 인코딩된 인증키

    // 날씨 데이터 API 요청 URL 생성
    std::ostringstream oss;
    oss << "http://apis.data.go.kr/1360000/VilageFcstInfoService_2.0/getUltraSrtNcst?"
        << "serviceKey=" << serviceKey
        << "&pageNo=1&numOfRows=10"
        << "&dataType=JSON"
        << "&base_date=" << getCurrentDate()
        << "&base_time=" << getCurrentHour()
        << "&nx=55&ny=127";

    std::string url = oss.str();  // 최종 URL
    std::string readBuffer;       // 서버 응답을 저장할 변수

    // curl 초기화 및 요청
    CURL* curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl failed: " << curl_easy_strerror(res) << std::endl;
            return 1;
        }
    }

    // JSON 파싱
    Json::Value root;
    Json::CharReaderBuilder reader;
    std::string errs;

    std::istringstream s(readBuffer);
    if (!Json::parseFromStream(reader, s, &root, &errs)) {
        std::cerr << "JSON parse error: " << errs << std::endl;
        return 1;
    }

    // 날씨 데이터 추출
    auto items = root["response"]["body"]["items"]["item"];
    std::string temp = "N/A";
    std::string skyCode = "N/A";

    // 날씨 정보 추출
    for (const auto& item : items) {
        if (item["category"].asString() == "T1H")  // 기온
            temp = item["obsrValue"].asString();
        if (item["category"].asString() == "PTY")  // 강수형태
            skyCode = item["obsrValue"].asString();
    }

    // 날씨 상태 매핑
    std::string sky = intToWeather.count(skyCode) ? intToWeather[skyCode] : "알 수 없음";

    // 결과 출력
    std::cout << "현재날짜: " << getCurrentDate().substr(0, 4) << "/" << getCurrentDate().substr(4, 2) << "/" << getCurrentDate().substr(6, 2) << std::endl;
    std::cout << "현재시간: " << getCurrentHour().substr(0, 2) << ":" << getCurrentHour().substr(2, 2) << std::endl;
    std::cout << "기온: " << temp << "°C" << std::endl;
    std::cout << "날씨: " << sky << std::endl;

    return 0;
}