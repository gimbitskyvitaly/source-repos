#include<iostream>
#include<vector>
long long n, m;
long long** a;
long long** e;
long long** c;
std::vector<long long> p;
void divide(std::vector<long long> &x) {
  for (int i = 0; i < x.size(); i++) {
    if (x[i] % 2 == 0) {
      x[i] /= 2;
    }
    else {
      x[i] = (x[i] - 1) / 2;
      x[i + 1] += 10;
    }
    if (x[0] == 0) {
      x.erase(x.begin());
      i--;
    }
  }
}
long long** multiply(long long** x, long long** a) {
  long long s = 0;
  long long** l = new long long*[n];
  for (int i = 0; i < n; i++) {
    l[i] = new long long[n];
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      s = 0;
      for (int k = 0; k < n; k++) {
        s += x[i][k] * a[k][j];
        s = s % m;
      }
      l[i][j] = s;
    }
  }
  return l;
}
long long** power(std::vector<long long> p) {
  while (p.empty() == false) {
    if (p[p.size() - 1] % 2 == 1) {
      e = multiply(e, a);

        p[p.size() - 1]--;
    }
    else {
      a = multiply(a, a);
      divide(p);
    }
  }

  return e;
}
int main() {
  std::string s;
  std::cin >> n >> m >> s;
  for (int i = 0; i < s.size(); i++) {
    p.push_back(s[i] - '0');
  }
  a = new long long*[n];
  e = new long long*[n];
  c = new long long*[n];
  for (int i = 0; i < n; i++) {
    a[i] = new long long[n];
    e[i] = new long long[n];
    c[i] = new long long[n];
  }
  for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
      std::cin >> a[i][j];
      if (i == j) {
        e[i][j] = 1;
      }
      else {

          e[i][j] = 0;
      }
    }
  }
  e = power(p);
  for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
      std::cout << e[i][j] % m << " ";
    }
      std::cout << std::endl;
  }
  return 0;
}