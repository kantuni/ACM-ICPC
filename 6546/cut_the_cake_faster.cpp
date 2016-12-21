#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Point {
  public:
    long double x;
    long double y;

    Point(long double x, long double y) {
      this->x = x;
      this->y = y;
    }
};

class Line {
  public:
    long double m; // slope
    long double b; // y-intercept
    long double a; // x-intercept

    // create a line from 2 points
    Line(Point p, Point q) {
      this->m = (p.x == q.x) ? NAN : (p.y - q.y) / (p.x - q.x);
      this->b = (isnan(this->m)) ? NAN : p.y - this->m * p.x;
      this->a = (isnan(this->m)) ? p.x : ((this->m == 0) ? NAN : -this->b / this->m);
    }

    // create a line from a point and a slope
    Line(Point p, long double m) {
      this->m = m;
      this->b = (isnan(this->m)) ? NAN : p.y - this->m * p.x;
      this->a = (isnan(this->m)) ? p.x : ((isnan(this->m)) ? NAN : -this->b / this->m);
    }

    // create a line from a slope, a y-intercept, and an x-intercept
    Line(long double m, long double b, long double a) {
      this->m = m;
      this->b = b;
      this->a = a;
    }

    // check if 2 lines are parallel
    bool is_parallel(Line l) {
      return this->m == l.m;
    }

    // return a point of intersection of 2 lines
    Point point_of_intersection(Line l) {
      if (is_parallel(l)) {
        return Point(NAN, NAN);
      }

      long double x, y;
      if (!isnan(this->m) && !isnan(l.m)) {
        x = (l.b - this->b) / (this->m - l.m);
        y = this->m * x + this->b;
      } else if (isnan(this->m)) {
        x = this->a;
        y = l.m * x + l.b;
      } else {
        x = l.a;
        y = this->m * x + this->b;
      }

      return Point(x, y);
    }

    // drop a perpendicular from a point to a line
    Line perpendicular(Point p) {
      if (!isnan(this->m)) {
        // if the point is on the line
        if (p.y == this->m * p.x + this->b) {
          return Line(NAN, NAN, NAN);
        }

        if (this->m == 0) {
          // vertical line
          return Line(NAN, 0, p.x);
        } else {
          // line with a "negative reciprocal" slope
          return Line(p, -1. / this->m);
        }
      } else {
        // if the point is on the line
        if (p.x == this->a) {
          return Line(NAN, NAN, NAN);
        }
        // horizontal line
        return Line(0, p.y, 0);
      }
    }
};

class Circle {
  public:
    // TODO: use Point class instead
    long double x;
    long double y;
    long double r;

    // center.x, center.y, r
    Circle(long double x, long double y, long double r) {
      this->x = x;
      this->y = y;
      this->r = r;
    }

    // check if a point is inside the circle
    bool point_in_circle(Point p) {
      long double temp = powl(p.x - this->x, 2);
      temp += powl(p.y - this->y, 2);
      return temp < powl(this->r, 2);
    }

    // check if a line intersects the circle
    bool line_intersects_circle(Line l) {
      Line perpendicular = l.perpendicular(Point(this->x, this->y));
      // line through the center of the circle
      bool ltc = isnan(perpendicular.m) && isnan(perpendicular.b) && isnan(perpendicular.a);

      if (ltc) {
        return true;
      } else {
        Point intersection = l.point_of_intersection(perpendicular);
        return !isnan(intersection.x) && !isnan(intersection.y) && point_in_circle(intersection);
      }
    }
};


int main() {
  while (true) {
    long long r, x, y, n;
    cin >> r >> x >> y >> n;

    // end of input
    if (r == 0 && x == 0 && y == 0 && n == 0) {
      return 0;
    }

    long long count = 1;

    // no lines
    if (n == 0) {
      cout << count << endl;
      continue;
    }

    long long x1, y1, x2, y2;
    vector<Line> lines = {};
    Circle c = Circle(x, y, r);

    // construct lines
    while (n > 0) {
      cin >> x1 >> y1 >> x2 >> y2;
      Point p = Point(x1, y1);
      Point q = Point(x2, y2);
      Line l = Line(p, q);
      lines.push_back(l);
      n--;
    }

    vector<Line> processed_lines = {};
    for (auto &l: lines) {
      // only lines that intersect the circle
      if (c.line_intersects_circle(l)) {
        for (auto &pl: processed_lines) {
          // lines intersection point
          Point lip = l.point_of_intersection(pl);
          if (!isnan(lip.x) && !isnan(lip.y)) {
            // check if intersection point is inside the circle
            if (c.point_in_circle(lip)) {
              count++;
            }
          }
        }

        // count = # of intersections inside the circle + 1
        count++;

        // keep the processed lines that intersected the circle
        processed_lines.push_back(l);
      }
    }

    // print answer
    cout << count << endl;
  }
}
