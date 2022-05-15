#include<iostream>
#include<vector>
#include<queue>
#include<fstream>
std::vector<std::vector<int>> g;
std::vector<bool> vis;
std::vector<std::pair<int, int>> e;
int main() {
  int n;
  std::ifstream fin("in.txt");
  fin >> n;
  g = std::vector<std::vector<int>>(n);
  int a;
  int x;
  for (int i = 0; i < n; i++) {
    fin >> a;
    for (int j = 0; j < a; j++) {
      fin >> x;
      x--;
      g[i].push_back(x);
    }
  }
  int h = 0;
  for (int j = 0; j < n; j++) {
    int len = 0;
    bool x;
    bool s = false;
    std::queue<int> q;
    q.push(j);
    vis = std::vector<bool>(n, false);
    vis[j] = true;
    int v;
    int ve;
    while (!q.empty()) {
      v = q.front();
      q.pop();
      x = false;
      for (int i = 0; i < g[v].size(); i++) {
        ve = i;
        if (vis[g[v][i]] == false) {
          x = true;
          vis[g[v][i]] = true;
          q.push(g[v][i]);
        }
      }
      if (x == true) {
        len++;
      }
    }
    for (int k = 0; k < n; k++) {
        if (vis[k] == false) {
          h++;
          s = true;
          break;
      }
    }
    if (s == false) {
      e.push_back(std::pair<int, int>(len, j));
    }
  }
  if (h == n) {
    std::ofstream fout;
    fout.open("out.txt");
    if (fout.is_open()) {
      fout << "impossible" << std::endl;
      return 0;
    }
  }sort(e.begin(), e.end());
  std::ofstream fout;
  fout.open("out.txt");
  if (fout.is_open()) {
    fout << e[e.size() - 1].first << std::endl;
    fout << e[e.size() - 1].second + 1 << std::endl;
  }
  return 0;
}