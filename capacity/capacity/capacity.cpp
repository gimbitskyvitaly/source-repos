#include<iostream>
#include<map>
#include<vector>
#include<math.h>
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
double maxx(double x, double a) {
  if (x > a) {
    return x;
  } else {
    return a;
  }
}
double minx(double x, double a) {
  if (x < a) {
    return x;
  } else {
    return a;
  }
}
std::vector<float> ncpux;
std::vector<float> nmemx;
double maxxa(std::vector<float> a, int e, int typee) {
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
long long testId, a, b, pkoeff, q, n;
double d;
long long* id;
int* dcpu;
int* dmem;
int totalneedcpu = 0;
int totalneedmem = 0;
double needcpu(int e) {
  int x = 0;
  int u;
  if (e >= n) {
    u = n;
  } else {
    u = e + 1;
  }
  for (int i = 0; i < u; i++) {
    x += dcpu[i];
  }
  return 100.0 * x / pkoeff;
}
double needmem(int e) {
  int x = 0;
  int u;
  if (e >= n) {
    u = n;
  } else {
    u = e + 1;
  }
  for (int i = 0; i < u; i++) {
    x += dmem[i];
  }
  return 100.0 * x / pkoeff;
}
double needcpux(int e) {
  int x = 0;
  int u;
  if (e >= n) {
    u = n;
  } else {
    u = e + 1;
  }
  for (int i = 0; i < u; i++) {
    x += maxx(0, dcpu[i]);
  }
  return 100.0 * x / pkoeff;
}
double needmemx(int e) {
  int x = 0;
  int u;
  if (e >= n) {
    u = n;
  } else {
    u = e + 1;
  }
  for (int i = 0; i < u; i++) {
    x += maxx(0, dmem[i]);
  }
  return 100.0 * x / pkoeff;
}
int m;
std::map<int, long long> tidmap;
std::map<int, long long> tcpumap;
std::map<int, long long> tmemmap;
std::map<int, long long> tprimap;
std::map<int, int>::iterator it;
double ucpu(int x, int a, double ncpu) {
    if (ncpu <= 0) {
    return 0;
  }
    double e = (100000.0 * minx(1, tcpumap[x] / ncpu )) * (n - a) /
         (tprimap[x] * (n - a) + b + a * 0.5 * tcpumap[x] / ncpu);
  return e;
}
double umem(int x, int a, double nmem) {
  if (nmem <= 0) {
    return 0;
  }
  double e = (100000.0 * minx(1, tmemmap[x] / nmem)) * ( n -a) /
         (tprimap[x] * (n - a) + b + a * 0.5 * tmemmap[x] / nmem);
  return e;
}
double ucpumem(int x, int a, int ncpu, int nmem) {
  return ucpu(x, a, ncpu) + umem(x, a, nmem);
}
long long adding(s e) {
  long long sum = 0;
  for (it = e.servertypex.begin(); it != e.servertypex.end(); it++) {
    sum += it->second;
  }
  sum *= b;
  sum += a;
  return sum;
}
long long operating(int a, int q) { return tprimap[a] * (n - q); }
long long cost( std::vector<s> e) {
  long long sum = 0;
  for (int i = 0; i < e.size(); i++) {
    sum += adding(e[i]);
    for (it = (e[i]).servertypex.begin(); it != (e[i]).servertypex.end(); it++) {
      sum += (it->second * operating(it->first, (e[i]).t));
    }
  }
  return sum;
}
int main() {
  std::cin >> testId >> a >> b >> pkoeff >> d >> q;
  id = new long long[q];
  for (int i = 0; i < q; i++) {
    std::cin >> id[i];
    std::cin >> tcpumap[id[i]];
    std::cin >> tmemmap[id[i]];
    std::cin >> tprimap[id[i]];
  }
  std::cin >> n;
  dcpu = new int[n];
  dmem = new int[n];
  double totalcpu = 0;
  double totalmem = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> dcpu[i];
    totalcpu += dcpu[i] * (n - i);
    std::cin >> dmem[i];
    totalmem += dmem[i] * (n - i);
  }
  std::vector<s> typex;
  std::map<int, int> a;
  double cpumemx = 0;
  double curcpu = 0;
  double curmem = 0;
  double ncpu, nmem;
  int ucpuid, umemid, ucpumemid;
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
    if (ncpux[i] - curcpu > 0 || nmemx[i] - curmem > 0){
        ins = i;
      ncpu = ceil(maxxa(ncpux, i, i + d)) - curcpu;
        nmem = ceil(maxxa(nmemx, i, i + d)) - curmem;
        while (ncpu > 0 || nmem > 0) {
            for (int e = 0; e < q; e++) {
            if (ucpumem(id[e], i, ncpu, nmem) > cpumemx) {
                cpumemx = ucpumem(id[e], i, ncpu, nmem);
                ucpumemid = id[e];
              }
          }
            ex = minx(maxx(1, ceil(ncpu / tcpumap[ucpumemid])),
                      maxx(1, ceil(nmem / tmemmap[ucpumemid])));
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
  std::cout << cost( typex) << std::endl;
  std::cout << m << std::endl;
  for (int i = 0; i < typex.size(); i++) {
    std::cout << (typex[i]).t << " " << (typex[i]).k << " ";
    for (it = (typex[i]).servertypex.begin();
         it != (typex[i]).servertypex.end(); it++) {
        std::cout << it->first << " " << it->second
                  << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}