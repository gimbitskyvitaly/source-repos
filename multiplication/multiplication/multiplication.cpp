#include <iostream>
#include<vector>
std::vector<long long> array;
std::vector<long long> s;
int p;
void tree(int indexSum, int left, int right) {
  if (right == left + 1) {
    s[indexSum - 1] = array[left];
  } else {
    int m = (left + right) / 2;
    tree(indexSum * 2, left, m);
    tree(indexSum * 2 + 1, m, right);
    s[indexSum - 1] = s[indexSum * 2 - 1] + s[indexSum * 2];
  }
} 

long long sum(int i, int left, int right, int l, int r) {
  if (l <= r || r <= array.size()) {
    if (left == l && right == r) {
      return s[i - 1];
    }
    int m = (left + right) / 2;
    if (r <= m) {
      return sum(i * 2, left, m, l, r);
    }
    if (l >= m) {
      return sum(i * 2 + 1, m, right, l, r);
    }
    return sum(i * 2, left, m, l, (left + right) / 2) +
           sum(i * 2 + 1, m, right, (left + right) / 2, r);
  }
}
  void h(int i, int a, int b, int j, int k) {
    if (a + 1 == b) {
    s[i -1] += k;
    }
    else {
      p = (a + b) / 2;


      if (j < p) {
        h(2 * i, a, p, j, k);
      }

      else {
        h(2 * i + 1, p, b, j, k);
      }
      s[i - 1] = s[2 * i - 1] + s[2 * i];
    }
}
int main() {
  int n;
  std::cin >> n;
  array = std::vector<long long>(n);
  s = std::vector<long long>(4 * n, INT64_MAX);
  std::string k;
  int i, j;
  int e;
  for (int i = 0; i < n; i++) {
    std::cin >> array[i];
  }
  tree(1, 0, n);
  int g;
  std::cin >> e;
  for (int i = 0; i < e; i++) {
    std::cin >> k;
    if (k == "FindSum") {
      std::cin >> g >> j;
        std::cout << sum(1, 0, n, g, j) << std::endl;
    } else {
      std::cin >> g >> j;

      h(1, 0, n, g, j);
    }}
  return 0;
}