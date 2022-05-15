#include<iostream>
#include<vector>
#include<algorithm>
std::string word;
std::vector<std::string> tryes;
std::vector<std::string> ans;
int yellow(char x, std::string trye, std::string a) {
  int e = 0;
  for (int i = 0; i < a.size(); i++) {
    if (trye[i] == x && (a[i] == 'G' || a[i] == 'Y')) {
      e++;
    }
  }
      return e;
}
char e(std::string x, std::string a) {
  for (int i = 0; i < x.size(); i++) {
    if (word[i] == x[i]) {
      if (a[i] != 'G') {
        return 'N';
      }
    } else {
      if (a[i] == 'G') {
        return 'N';
      }else if (a[i] == 'Y') {
        if (yellow(x[i], x, a) > std::count(word.begin(), word.end(), x[i])) {
          return 'N';
        }
      } else if (a[i] == 'W') {
        if (yellow(x[i], x, a) < std::count(word.begin(), word.end(), x[i])) {
          return 'N';
        }
      }
    }
  }
  return 'Y';
}
int main() {
  int t, n;
  std::cin >> t;
  for (int i = 0; i < t; i++) {
    std::cin >> word;
    std::cin >> n;
    tryes = std::vector<std::string>(n);
    ans = std::vector<std::string>(n);
    for (int j = 0; j < n; j++) {
      std::cin >> tryes[j];
    }
    for (int j = 0; j < n; j++) {
      std::cin >> ans[j];
    }
    for (int j = 0; j < n; j++) {
      std::cout << e(tryes[j], ans[j]);
    }

    std::cout << std::endl;
  }
  return 0;
}