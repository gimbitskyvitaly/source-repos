#include<iostream>
#include<map>
#include<math.h>
int main() {
  int n, m;
  int sum = 0;
  std::cin >> n >> m;
      int a, x;
      std::map<int, int> amap;
      std::map<int, int> xmap;
      for (int i = 0; i < n; i++) {
        std::cin >> a;
          if (amap.find(a) == amap.end()) {
            amap[a] = 1;
          } else {
            amap[a]++;
          }
      }
      for (int i = 0; i < m; i++) {
        std::cin >> x;
          if (xmap.find(x) == xmap.end()) {
            xmap[x] = 1;
          } else {
            xmap[x]++;
          }
      }
      std::map<int, int>::iterator i, it;
      for (i = amap.begin(); i != amap.end(); i++) {
        for (it = xmap.begin(); it != xmap.end(); it++) {
          x = i->second * it->second;
          a = abs(i->first - it->first);
          sum += x * (int)(sqrt(a));
        }
      }
      std::cout << sum;
  return 0;}