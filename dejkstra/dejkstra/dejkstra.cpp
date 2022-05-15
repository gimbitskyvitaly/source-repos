#include<iostream>
#include<vector>
#include<set>
#include<queue>
#include<fstream>
long long inf = INT64_MAX;
std::vector<std::vector<std::pair<int, int>>> g;
int main() {
  int n, m;
  std::ifstream fin("input.txt");
  fin >> n >> m;
  g = std::vector<std::vector<std::pair<int, int>>>(n);
  if (n == 1) {
    std::ofstream fout;
    fout.open("output.txt");
    if (fout.is_open()) {
      fout << 0;
    }
    return 0;
  }
  int e, h, a;
  for (int i = 0; i < m; i++) {
    fin >> e >> h >> a;
    g[e - 1].push_back(std::pair<int, int>(a, h - 1));
    g[h - 1].push_back(std::pair<int, int>(a, e - 1));
  }
  int s = 0;
  std::vector<long long> d(n, inf);
  d[s] = 0;
  std::priority_queue<std::pair<long long, int>> q;
  q.push(std::make_pair(0, s));
  while (!q.empty()) {
    int v = q.top().second, cur_d = -q.top().first;
    q.pop();
    if (cur_d > d[v]) continue;

    for (int j = 0; j < g[v].size(); j++) {
      int to = g[v][j].second, len = g[v][j].first;
      if (d[v] + len < d[to]) {
        d[to] = d[v] + len;
        q.push(std::make_pair(-d[to], to));
      }
    }
  }
  std::ofstream fout;
  fout.open("output.txt");
  if (fout.is_open()) {
    fout << d[n - 1];
  }
  return 0;
}