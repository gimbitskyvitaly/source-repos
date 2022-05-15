#include <math.h>
#include <iostream>
#include <map>
#include <vector>
class s {
 public:
  int t;
  long long k;
  std::map<int, int> servertypex;
  s(long long q, long long a) {
    t = q;
    k = a;
  }
  s(int q, long long a, std::map<int, int> x) {
    t = q;
    k = a;
    servertypex = x;
  }
};
std::vector<float> ncpux;
std::vector<float> nmemx;
inline double maxx(double x, double a) {
  if (x > a) {
    return x;
  }
  else {
    return a;
  }
}
inline double minx(double x, double a) {
  if (x < a) {
    return x;
  }
  else {
    return a;
  }
}
inline double maxxa(std::vector<float> a, int e, int typee) {
  double x = 0;
  int te;
  if (typee > a.size()) {
    te = a.size();
  } else {
    te = typee + 1;
  }
  for (int i = e; i < te; i++) {
    if (a[i] > x) {
      x = a[i];
    }
  }
  return x;
}
int testId, q, n;
double a, b, pkoeff;
double d;
int* id;
double* dcpu;
double* dmem;
int totalneedcpu = 0;
int totalneedmem = 0;
int m;
std::map<int, int> tcpumap;
std::map<int, int> tmemmap;
std::map<int, int> tprimap;
std::map<int, int>::iterator it;
inline double ucpu(int x, int i, double ncpu) {
  if (ncpu <= 0) {
    return 0;
  }
  double e = (100000.0 * minx(1, tcpumap[x] / ncpu)) * (n - i) /
             (tprimap[x] * (n - i) + b);
  return e;
}
inline double umem(int x, int i, double nmem) {
  if (nmem <= 0) {
    return 0;
  }
  double e = (100000.0 * minx(1, tmemmap[x] / nmem)) * (n - i) /
             (tprimap[x] * (n - i) + b);
  return e;
}
inline double ucpumem(int x, int a, int ncpu, int nmem) {
  return ucpu(x, a, ncpu) + umem(x, a, nmem);
}
inline long long adding(s e) {
  long long sum = 0;
  for (it = e.servertypex.begin(); it != e.servertypex.end(); it++) {
    sum += it->second;
  }
  sum *= b;
  sum += a;
  return sum;
}
inline long long operating(int a, int q) { return tprimap[a] * (n - q); }
inline long long cost(std::vector<s> e) {
  long long sum = 0;
  for (int i = 0; i < e.size(); i++) {
    sum += adding(e[i]);
    for (it = (e[i]).servertypex.begin(); it != (e[i]).servertypex.end();
         it++) {
      sum += (it->second * operating(it->first, (e[i]).t));
    }
  }
  return sum;
}
double xex;
int main() {
  std::cin >> testId >> a >> b >> pkoeff >> d >> q;
  id = new int[q];
  for (int i = 0; i < q; i++) {
    std::cin >> xex;
    id[i] = xex;
    std::cin >> tcpumap[xex];
    std::cin >> tmemmap[xex];
    std::cin >> tprimap[xex];
  }
  std::cin >> n;
  dcpu = new double[n];
  dmem = new double[n];
  double totalcpu = 0;
  double totalmem = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> dcpu[i];
    std::cin >> dmem[i];
  }
  std::vector<s> typex;
  std::map<int, int> a;
  double cpumemx = 0;
  double curcpu = 0;
  double curmem = 0;
  double ncpu, nmem;
  int ucpumemid;
  double ucpux = 0;
  double umemx = 0;
  double ucpumemx = 0;
  float xe = 0;
  float xa = 0;
  for (int i = 0; i < n; i++) {
    xe += ceil(dcpu[i] * 100.0 / pkoeff);
    xa += ceil(dmem[i] * 100.0 / pkoeff);
    ncpux.push_back(xe);
    nmemx.push_back(xa);
  }
  int ins = -d;
  int ux;
  int ex;
  for (int i = 0; i < n; i++) {
    if (i - ins >= d) {
      if (ncpux[i] - curcpu > 0 || nmemx[i] - curmem > 0) {
        ins = i;
        ncpu = ceil(maxxa(ncpux, i, i + d)) - curcpu;
        nmem = ceil(maxxa(nmemx, i, i + d)) - curmem;
        while (ncpu > 0 || nmem > 0) {
          for (int e = 0; e < q; e++) {
            xex = ucpumem(id[e], i, ncpu, nmem);
            if (xex > cpumemx) {
              cpumemx = xex;
              ucpumemid = id[e];
            }
          }
          ex = minx(maxx(0, ncpu / tcpumap[ucpumemid]),
                    maxx(0, nmem / tmemmap[ucpumemid])) +
               1;
          if (a.find(ucpumemid) == a.end()) {
            a[ucpumemid] = ex;
          } else {
            a[ucpumemid] += ex;
          }
          curcpu += ex * tcpumap[ucpumemid];
          curmem += ex * tmemmap[ucpumemid];
          ncpu -= ex * tcpumap[ucpumemid];
          nmem -= ex * tmemmap[ucpumemid];
          cpumemx = 0;
        }
        typex.push_back(*(new s(i, a.size(), a)));
        a.clear();
      }
    }
  }
  m = typex.size();
  std::cout << cost(typex) << std::endl;
  std::cout << m << std::endl;
  for (int i = 0; i < typex.size(); i++) {
    std::cout << (typex[i]).t << " " << (typex[i]).k << " ";
    for (it = (typex[i]).servertypex.begin();
         it != (typex[i]).servertypex.end(); it++) {
      std::cout << it->first << " " << it->second << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}