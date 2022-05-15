#include <iostream>
#include <vector>
int f = 1000000000;
int n, m;
std::vector<std::vector<int>> x;
std::vector<std::vector<int>> h;
std::vector<int> visited;
std::vector<int> pred;

void findpath(int v) {
  visited[v] = 1;
  for (int i = 0; i < n; i++) {
    if (h[v][i] > 0 && visited[i] == 0) {
      pred[i] = v;
      findpath(i);
    }
  }
}

std::vector<int> restorepath(int x) {
  std::vector<int> path;
  path.push_back(x);
  while (pred[x] != -1) {
    path.push_back(pred[x]);
    f = std::min(f, h[pred[x]][x]);
    x = pred[x];
  }
  return path;
}
int main() {
  std::cin >> n >> m;
  x = std::vector<std::vector<int>>(n, std::vector<int>(n));
  h = std::vector<std::vector<int>>(n, std::vector<int>(n));
  visited = std::vector<int>(n);
  pred = std::vector<int>(n);
  int flow = 0;
  int u, v, k;
  for (int i = 0; i < m; i++) {
    std::cin >> u >> v >> k;
    h[u - 1][v - 1] += k;
  }
  std::vector<int> path;
  while (true) {
    visited = std::vector<int>(n);
    pred = std::vector<int>(n, -1);
    findpath(0);
    if (visited[n - 1] == 0) {
      break;
    }
    path = restorepath(n - 1);
    flow += f;
    for (int i = path.size() - 1; i > 0; i--) {
      h[path[i]][path[i - 1]] -= f;
      h[path[i - 1]][path[i]] += f;
    }
    f = 1000000000;
  }
  std::cout << flow;
  return 0;
}