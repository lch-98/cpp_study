# 14. File I/O & Serialization (파일 입출력)

파일을 읽고 쓰는 것은 모든 실용 프로그램의 기본이다.

---

## 학습 순서

| 파일 | 주제 | 핵심 API |
|------|------|---------|
| [01_fstream_basic.cpp](01_fstream_basic.cpp) | 텍스트 파일 읽기/쓰기 | `ifstream`, `ofstream`, `getline` |
| [02_binary_io.cpp](02_binary_io.cpp) | 바이너리 파일, 랜덤 접근 | `ios::binary`, `write/read`, `seekg` |
| [03_csv_parser.cpp](03_csv_parser.cpp) | CSV 파싱 및 저장 | `stringstream`, `split`, 정렬 |
| [04_json_readwrite.cpp](04_json_readwrite.cpp) | JSON 읽기/쓰기 | `jsoncpp`, 설정 파일 패턴 |

---

## 핵심 패턴

```cpp
// 텍스트 읽기
ifstream in("file.txt");
string line;
while (getline(in, line)) { /* 처리 */ }

// 텍스트 쓰기
ofstream out("file.txt");
out << "내용\n";

// 바이너리 쓰기
ofstream out("file.bin", ios::binary);
out.write(reinterpret_cast<const char*>(&data), sizeof(data));

// 바이너리 읽기
ifstream in("file.bin", ios::binary);
in.read(reinterpret_cast<char*>(&data), sizeof(data));
```

### 실무 팁
- 파일 경로는 절대 경로보다 상대 경로 + 환경 설정으로 관리
- 대용량 파일은 한 줄씩 읽거나 메모리 매핑(mmap) 고려
- 직렬화 라이브러리: jsoncpp, nlohmann/json, protobuf, cereal

> **앞 단계:** [13_modern_cpp](../13_modern_cpp/)
> **다음 단계:** [15_testing](../15_testing/)
