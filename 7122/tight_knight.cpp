#include <bits/stdc++.h>
using namespace std;

#define UNVISITED -1
#define VISITED 1
#define OBSTACLE 2
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
typedef vector<vvii> vvvii;

int n, m, si, sj, ei, ej, c;
int dr[] = {-1, 1, -2, 2, -2, 2, -1, 1};
int dc[] = {-2, -2, -1, -1, 1, 1, 2, 2};
vvvii AdjList;
vvi color;


void print() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << i << " " << j << ": ";
      for (int k = 0; k < AdjList[i][j].size(); k++) {
        ii v = AdjList[i][j][k];
        cout << "(" << v.first << ", " << v.second << ") ";
      }
      cout << "\n";
    }
  }
}

void populate(int i, int j) {
  color[i][j] = VISITED;
  if (i == ei && j == ej) return;
  for (int k = 0; k < 8; k++) {
    int r = i + dr[k], c = j + dc[k];
    if (r >= 0 && r < n && c >= 0 && c < m) {
      if (color[r][c] != OBSTACLE)
        AdjList[i][j].push_back(ii(r, c));

      if (color[r][c] == UNVISITED)
        populate(r, c);
    }
  }
}

int main() {
  while (true) {
    cin >> n >> m >> si >> sj >> ei >> ej >> c;
    si--; sj--; ei--; ej--;
    if (n == 0) break;
    
    AdjList.assign(n, vvii(m));
    color.assign(n, vi(m, UNVISITED));
    
    while (c--) {
      int x, y;
      cin >> x >> y;
      color[x - 1][y - 1] = OBSTACLE;
    }
    
    // create graph
    populate(si, sj);
    print();
  }
  
  return 0;
}
