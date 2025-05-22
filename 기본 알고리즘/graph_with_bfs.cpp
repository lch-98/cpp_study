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
