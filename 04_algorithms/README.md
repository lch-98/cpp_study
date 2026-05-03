# 04. Algorithms (기본 알고리즘)

코딩 테스트와 실무에서 자주 쓰이는 탐색 알고리즘을 구현합니다.

---

## 학습 순서

| 파일 | 알고리즘 | 시간복잡도 | 설명 |
|------|---------|-----------|------|
| [binary_search.cpp](binary_search.cpp) | 이진 탐색 | O(log n) | 정렬된 범위에서 목표값 탐색 |
| [bfs_dfs.cpp](bfs_dfs.cpp) | BFS / DFS | O(V+E) | 4×4 미로 격자 경로 탐색 |
| [graph_with_bfs.cpp](graph_with_bfs.cpp) | BFS + 사이클 탐지 | O(N+M) | 무방향 그래프에서 사이클 존재 여부 판별 |

---

## 핵심 개념 요약

### Binary Search
```cpp
while (left <= right) {
    int mid = (left + right) / 2;
    if (mid < target) left = mid + 1;       // 오른쪽 탐색
    else if (mid > target) right = mid - 1;  // 왼쪽 탐색
    else break;                              // 탐색 성공
}
```

### BFS vs DFS
| | BFS | DFS |
|-|-----|-----|
| 자료구조 | Queue | Stack (재귀) |
| 최단 경로 | 보장 | 보장 안 됨 |
| 메모리 | 상대적으로 많이 사용 | 상대적으로 적게 사용 |
| 사용 사례 | 최단 거리, 레벨 탐색 | 경로 존재 여부, 사이클 탐지 |

### graph_with_bfs.cpp 입력 예시
```
입력:
4 4
1 2
2 3
3 4
4 2

출력: Cycle Detected
```

> **앞 단계:** [03_classes_oop](../03_classes_oop/)  
> **다음 단계:** [05_exception_handling](../05_exception_handling/)
