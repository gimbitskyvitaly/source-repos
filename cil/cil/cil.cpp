#include <iostream>
#include <vector>
class node {
 public:
  long long mult, max, min;
  node(long long x, long long a, long long j) {
    mult = x;
    max = a;
    min = j;
  }
};
std::vector<long long> array;
std::vector<node*> s;
int p;

long long maximum(std::vector<long long> &a) {
  long long e = INT64_MIN;
  for (int i = 0; i < a.size(); i++) {
    if (a[i] > e) {
      e = a[i];
    }
  }
  return e;
}
void tree(int indexSum, int left, int right) {
  if (right == left) {
    s[indexSum] = new node(INT64_MIN, array[left], array[left]);
  } else {
    int m = (left + right) / 2;
    tree(indexSum * 2 + 1, left, m);
    tree(indexSum * 2 + 2, m + 1, right);
    s[indexSum] = new node(0, 0, 0);
    s[indexSum]->max =
        std::max(s[indexSum * 2 + 1]->max, s[indexSum * 2 + 2]->max);
    s[indexSum]->min =
        std::min(s[indexSum * 2 + 1]->min, s[indexSum * 2 + 2]->min);
    std::vector<long long> e;
    e.push_back(s[indexSum * 2 + 1]->mult);
    e.push_back(s[indexSum * 2 + 2]->mult);
    e.push_back(s[indexSum * 2 + 1]->min * s[indexSum * 2 + 2]->min);
    e.push_back(s[indexSum * 2 + 1]->max * s[indexSum * 2 + 2]->max);
    s[indexSum]->mult = maximum(e);
  }
}
node* maxmult(int i, int left, int right, int l, int r) {
  if (l <= r || r <= array.size()) {
    if (left == l && right == r) {
      return s[i];
    }
    int m = (left + right) / 2;
    if (r <= m) {
      return maxmult(i * 2 + 1, left, m, l, r);
    }
    if (l > m) {
      return maxmult(i * 2 + 2, m + 1, right, l, r);
    }
    std::vector<long long> e;
    node* x = maxmult(i * 2 + 1, left, m, l, m);
    node* y = maxmult(i * 2 + 2, m + 1, right, m + 1, r);
    e.push_back(x->mult);
    e.push_back(y->mult);
    e.push_back(x->min * y->min);
    e.push_back(x->max * y->max);
    return new node(maximum(e), std::max(x->max, y->max),
                    std::min(x->min, y->min));
  }
}
void mod(int i, int vl, int vr, int a, int b) {
    if (vl == vr) {
        s[i] = new node(INT64_MIN, b, b);
        return;
    }
    int m = (vl + vr) / 2;
    if (a <= m) {
      mod(2 * i + 1, vl, m, a, b);
    } else {
      mod(2 * i + 2, m + 1, vr, a, b);
    }
    node* x = s[2 * i + 1];
    node* y = s[2 * i + 2];
    std::vector<long long> e;

    e.push_back(x->mult);
    e.push_back(y->mult);
    e.push_back(x->min * y->min);
    e.push_back(x->max * y->max);

    delete s[i];
    s[i] = new node(maximum(e), std::max(x->max, y->max),
                    std::min(x->min, y->min));

}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  int n, q;
  std::cin >> n >> q;
  char e;
  int x, y;
  array = std::vector<long long>(n);
  s = std::vector<node*>(4 * n);
  for (int i = 0; i < n; i++) {
    std::cin >> array[i];
  }
  tree(0, 0, n - 1);
  for (int i = 0; i < q; i++) {
    std::cin >> e;
    std::cin >> x >> y;
    if (e == '?') {
      std::cout << maxmult(0, 0, n - 1, x - 1, y - 1)->mult << std::endl;
    } else {
      mod(0, 0, n - 1, x - 1, y);
    }
  }
  return 0;
}