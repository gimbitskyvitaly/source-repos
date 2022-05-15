#include<iostream>
#include<vector>
#include<stack>
#include<fstream>
int n;
std::vector<std::vector<int>> h;
std::vector<bool> vis;
int next(int a) {
  int e = -1;
  for (int i = 0; i < n; i++) {
    if (h[a][i] == 1 && vis[i] == false && a != i) {
      return i;
    }
  }
  return e;
}
int main() {
  std::ifstream fin("input.txt");
  fin >> n;
  h = std::vector<std::vector<int>>(n, std::vector<int>(n));
  vis = std::vector<bool>(n, false);
  std::vector<int> a(n);
  int e;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      fin >> h[i][j];
    }
  }
  int l = 1;
  std::stack<int> s;
  for (int i = 0; i < n; i++) {
    if (vis[i] == false) {
      int v = i;
      while (v != -1) {
        s.push(v);
        vis[v] = true;
        a[v] = l;
        l++;
        v = next(v);
      }
      while (!s.empty()) {
        v = s.top();
        s.pop();
        v = next(v);
        while (v != -1) {
          s.push(v);
          vis[v] = true;
          a[v] = l;
          l++;
          v = next(v);
        }
      }
    }
  }
  std::ofstream fout;
  fout.open("output.txt");
  if (fout.is_open()) {
    for (int i = 0; i < n; i++) {
      fout << a[i] << " ";
    }
  }
  return 0;
}