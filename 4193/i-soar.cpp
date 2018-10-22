#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
#define EPS 1e-9

struct Point {
  ld x1, x2;
  
  Point(ld x1, ld x2) {
    this->x1 = x1;
    this->x2 = x2;
  }
  
  bool operator < (Point p) const {
    if (x1 < p.x1 + EPS) return true;
    return x2 > p.x2 - EPS;
  }
};

int main() {
  while (true) {
    ld L;
    cin >> L;
    
    if (!(L > 0))
      break;
    
    vector<Point> points;
    while (true) {
      ld x1, x2;
      cin >> x1 >> x2;
      
      if (x1 > x2 - EPS)
        break;
        
      Point p(x1, x2);
      points.push_back(p);
    }
    
    if (points.size() == 0) {
      printf("The total planting length is %.1Lf\n", L);
      continue;
    }
    
    ld dist = 0.0;
    sort(points.begin(), points.end());
    ld l = points[0].x1, r = points[0].x2;
    
    for (unsigned long long i = 1; i < points.size(); i++) {
      Point curr = points[i];
      if (l < curr.x1 + EPS && r > curr.x1 - EPS) {
        r = curr.x2 > r - EPS ? curr.x2 : r;
      } else {
        dist += r - l;
        l = curr.x1;
        r = curr.x2;
      }
    }
    
    ld ans = L - (dist + r - l);
    printf("The total planting length is %.1Lf\n", ans);
  }
  
  return 0;
}
