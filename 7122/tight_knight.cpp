#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n, m, i, j, k, l, c, x, y;
  vector<pair<int, int>> obstacles;

  while (true) {
    cin >> n >> m >> i >> j >> k >> l >> c;

    // end of input
    if (n == 0) {
      // print out the obstacles
      for (auto o: obstacles) {
        cout << o.first << " " << o.second << endl;
      }
      break;
    }

    // remove old obstacles
    obstacles.clear();

    while (c--) {
      cin >> x >> y;
      obstacles.push_back({x, y});
    }
  }
  return 0;
}
