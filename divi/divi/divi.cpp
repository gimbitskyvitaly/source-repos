#include<iostream>
#include<map>
std::map<int, int> dn;
std::map<int, int> dk;
void p(int x, std::map<int, int> &d) {
  int a = 2;
  while (x != 1) {
    if (x % a == 0) {
      d[a]++;
      x = x / a;
    }
    else {
      a++;
    }
  }
}
int main() {
  int n;
  int k;
  std::cin >> k >> n;
  int nf = 1;
  int kf = 1;
  if (k >= n / 2) {
    for (int i = k + 1; i <= n; i++) {
      nf *= i % 1000000007;
      nf = nf % 1000000007;
    }
    for (int i = 1; i <= n - k; i++) {
      kf *= i % 1000000007;
      kf = kf % 1000000007;
    }
  }
  else {
    for (int i = n - k + 1; i <= n; i++) {
      nf *= i % 1000000007;
      nf = nf % 1000000007;
    }
    for (int i = 1; i <= k; i++) {
      kf *= i % 1000000007;
      kf = kf % 1000000007;
    }
  }
  for (int i = 0; i <= n; i++) {
    dn[i] = 0;
  }
  for (int i = 1; i <= k; i++) {
    dk[i] = 0;
  }
  p(nf, dn);
  p(kf, dk);
  for (auto x : dn) {
    if (x.second != 0) {
      std::cout << x.first << " " << x.second << std::endl;
    }
  }
  for (auto x : dk) {
      if (x.second != 0) {
      std ::cout << x.first << " " << x.second << std::endl;
        dn[x.first] -= x.second;
    }
  }
  int e = 0;
  for (auto x : dn) {
      if (x.second != 0) {
      e += x.second;
        std::cout << x.first << " " << x.second << std::endl;
    }
  }
  std::cout << (int)(std::pow(2, e)) % 1000000007;
  return 0;
}