#include <bits/stdc++.h>
#define EPS 1e-9
using namespace std;

struct Point {
  long double x1, x2;
  
  Point(long double x1, long double x2) {
    this->x1 = x1;
    this->x2 = x2;
  }
  
  bool operator < (Point p) const {
    if (x1 < p.x1 + EPS) {
      return true;
    }
    return x2 > p.x2 - EPS;
  }
};

int main() {
  while (true) {
    long double L;
    cin >> L;
    if (L <= 0) {
      break;
    }
    vector<Point> points;
    while (true) {
      long double x1, x2;
      cin >> x1 >> x2;
      if (x1 > x2 - EPS) {
        break;
      }
      Point p(x1, x2);
      points.push_back(p);
    }
    if (points.size() == 0) {
      printf("The total planting length is %.1Lf\n", L);
      continue;
    }
    long double dist = 0.0;
    sort(points.begin(), points.end());
    long double l = points[0].x1, r = points[0].x2;
    for (unsigned long long i = 1; i < points.size(); i++) {
      Point cur = points[i];
      if (l < cur.x1 + EPS && r > cur.x1 - EPS) {
        r = cur.x2 > r - EPS ? cur.x2 : r;
      } else {
        dist += r - l;
        l = cur.x1;
        r = cur.x2;
      }
    }
    long double ans = L - (dist + r - l);
    printf("The total planting length is %.1Lf\n", ans);
  }
  return 0;
}
