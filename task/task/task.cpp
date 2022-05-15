#include<iostream>
int main() {
  int l;
  std::cin >> l;
  int a;
  int x = 0;
  int j = 1;
  if ( l >= 3) {
    a = (l - 1) / 2;
    if (l % 2 == 0) {
      j = 2;
    }
    for (int i = j; i <= a; i += 2) {
      x++;
    }
    a = 3 * x;
    if (l % 3 == 0) {
      a -= 2;
    }
    std::cout << a;
  }
  else {
    std::cout << 0;
  }
  return 0;
}