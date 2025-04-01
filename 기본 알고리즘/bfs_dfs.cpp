// https://blog.naver.com/dlcndgusgnss/223817754370 - 설명 참고
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> maze = { {1, 1, 0, 1}, {0, 1, 0, 1}, {1, 1, 1, 1}, {0, 0, 1, 1} };
vector<vector<int>> visited;
int dy[] = { -1, 1, 0, 0 };;
int dx[] = { 0, 0, -1, 1 };;
void init() {
	visited = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
}

void print() {
	for (int i = 0; i < maze.size(); i++)
	{
		for (int j = 0; j < maze[i].size(); j++)
		{
			cout << maze[i][j] << " ";
		}
		cout << "\n";
	}
}

void path_print() {
	cout << "\n";
	for (int i = 0; i < visited.size(); i++)
	{
		for (int j = 0; j < visited[i].size(); j++)
		{
			cout << visited[i][j] << " ";
		}
		cout << "\n";
	}
}

void bfs(pair<int,int> start) {
	queue<pair<int, int>> q;
	q.push(start);
	visited[start.first][start.second] = 1;

	while (!q.empty())
	{
		int curr_row = q.front().first;
		int curr_col = q.front().second;
		q.pop();

		for (int dr = 0; dr < 4; dr++)
		{
			int ny = curr_row + dy[dr];
			int nx = curr_col + dx[dr];
			if (ny < 0 || nx < 0 || ny >= maze.size() || nx >= maze[0].size()) continue;
			if (visited[ny][nx] != 0 || maze[ny][nx] != 1) continue;
			
			q.push({ny, nx});
			visited[ny][nx] = visited[curr_row][curr_col] + 1;
			if (ny == maze.size() - 1 && nx == maze[0].size() - 1) return;
		}
	}
}

void dfs(pair<int,int> curr, int depth) {
	visited[curr.first][curr.second] = depth;

	if (curr.first == maze.size() - 1 && curr.second == maze[0].size() - 1) return;

	for (int dr = 0; dr < 4; dr++) {
		int ny = curr.first + dy[dr];
		int nx = curr.second + dx[dr];

		if (ny < 0 || nx < 0 || ny >= maze.size() || nx >= maze[0].size()) continue;
		if (visited[ny][nx] != 0 || maze[ny][nx] != 1) continue;

		dfs({ny, nx}, depth + 1);
	}
}


int main() {
	print();
	
	init();
	bfs({ 0,0 });
	path_print();
	
	init();
	dfs({ 0,0 }, 1);
	path_print();
}