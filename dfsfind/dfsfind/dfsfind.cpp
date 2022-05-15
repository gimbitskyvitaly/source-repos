#include <iostream>
#include <vector>
int n, m, from, to;
std::vector<int> visited;
std::vector<int> path;

std::vector<std::vector<int>> graph;
int dfs(int from, const int to) {
  if (visited[from] == true) return -1;
  visited[from] = true;
  if (from == to) {
    path[0] = to;
    return 0;
  }
  for (int i = 0; i < n; ++i) {
    if (graph[from][i] == 0) continue;
    int path_size = dfs(i, to);
    if (path_size < 0) continue;
    path[path_size + 1] = from;
    return path_size + 1;
  }
  return -1;
}
int main() {
  std::cin >> n >> m >> from >> to;
  for (int i = 0; i < n; i++) {
    graph.push_back(*(new std::vector<int>(n, 0)));
    visited.push_back(0);
    path.push_back(-1);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      graph[i][j] = 0;
    }
  }
  for (int i = 0; i < m; i++) {
    int a, b;
    std::cin >> a >> b;
    graph[a][b] = 1;
    graph[b][a] = 1;
  }
  for (int i = 0; i < n; i++) {
    visited[i] = 0;
  }
  int path_size = dfs(from, to);
  if (path_size < 0) {
    std::cout << "path does not exist";
  } else {
    for (int i = path_size; i >= 0; --i) {
      std::cout << path[i] + 1;
      if (i == 0) {
        std::cout << std::endl;

      } else {
        std::cout << "->";
      }
    }
  }
  return 0;
}