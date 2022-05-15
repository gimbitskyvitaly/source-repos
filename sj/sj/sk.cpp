#include <iostream>
#include <set>
#include <vector>
#include<algorithm>
int main() {
  std::set<char> j;
  std::vector<char> s;
  std::string x, a;
  std::cin >> x;
  for (int i = 0; i < x.size(); i++) {
    j.insert(x[i]);
  }
  std::cin >> a;
  for (int i = 0; i < a.size(); i++) {
    s.push_back(a[i]);
  }
  int e = 0;
  for (auto x : s) {
    if (j.find(x) != j.end()) {
      e++;
    }
  }
  std::cout << e;
  return 0;
}