/*
 * [Topic] Cycle Detection in Undirected Graph (BFS)
 * BFS를 사용해 무방향 그래프에서 사이클을 탐지하는 예제.
 *
 * 입력 형식:
 *   첫 줄: N(노드 수) M(간선 수)
 *   이후 M줄: u v (u-v 간선)
 *
 * 사이클 탐지 원리:
 *   - BFS 큐에 (현재 노드, 부모 노드) 쌍을 저장
 *   - 인접 노드가 이미 방문됐고 부모가 아니라면 → 사이클 존재
 *
 * 시간 복잡도: O(N + M)
 */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M;
vector<vector<int>> graph;
vector<int> visited;
bool hasCycle = false;

void bfs(int start_node) {
	queue<pair<int, int>> q; // (현재 노드, 부모 노드)
	q.push({start_node, -1});
	visited[start_node] = 1;

	while (!q.empty()) {
		int curr = q.front().first;
		int parent = q.front().second;
		q.pop();

		for (int neighbor : graph[curr]) {
			if (!visited[neighbor]) {
				visited[neighbor] = 1;
				q.push({neighbor, curr});
			}
			else if (neighbor != parent) {
				hasCycle = true;
				return;
			}
		}
	}
}

int main() {
	cin >> N >> M;
	graph = vector<vector<int>>(N + 1);
	visited = vector<int>(N + 1, 0);

	for (int i = 0; i < M; i++) {
		int u, v;
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u); // 양방향
	}

	for (int i = 1; i <= N; i++) {
		if (!visited[i]) bfs(i);
		if (hasCycle) break;
	}

	cout << (hasCycle ? "Cycle Detected" : "No Cycle") << "\n";
	return 0;
}
