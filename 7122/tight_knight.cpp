#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n, m, i, j, k, l, c, x, y;
  vector<tuple<int, int>> obstacles;

  while (true) {
    cin >> n >> m >> i >> j >> k >> l >> c;

    // end of input
    if (n == 0) {
      // print out obstacles
      for (auto o: obstacles) {
        cout << get<0>(o) << " " << get<1>(o) << endl;
      }

      break;
    }

    // remove old obstacles
    obstacles.clear();

    while (c > 0) {
      cin >> x >> y;
      obstacles.emplace_back(x, y);
      c--;
    }
  }

  return 0;
}