#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
typedef vector<vvii> vvvii;
#define UNVISITED -1
#define VISITED 1
#define OBSTACLE 2

int n, m, si, sj, ei, ej, c;
int dr[] = {-1, 1, -2, 2, -2, 2, -1, 1};
int dc[] = {-2, -2, -1, -1, 1, 1, 2, 2};
vvvii AdjList;
vvii parent;
vvi color, num, low;
set<ii> artics;
int timer;


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
      AdjList[i][j].push_back(ii(r, c));
      if (color[r][c] == UNVISITED)
        populate(r, c); 
    }
  }
}

void articulationPoints(int ui, int uj) {
  color[ui][uj] = VISITED;
  low[ui][uj] = num[ui][uj] = timer++;
  
  for (int k = 0; k < AdjList[ui][uj].size(); k++) {
    ii v = AdjList[ui][uj][k];
    int vi = v.first, vj = v.second;
    ii p = parent[vi][vj];
    
    if (color[vi][vj] == UNVISITED) {
      parent[vi][vj] = ii(ui, uj);
      articulationPoints(vi, vj);
      
      if (low[vi][vj] >= num[ui][uj]) {
        artics.insert(ii(ui, uj));
      }
      
      low[ui][uj] = min(low[ui][uj], low[vi][vj]);
    } else if (p.first != ui && p.second != uj) {
      low[ui][uj] = min(low[ui][uj], num[vi][vj]);
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
    
    timer = 0;
    parent.assign(n, vii(m));
    parent[si][sj] = ii(-1, -1);
    color.assign(n, vi(m, UNVISITED));
    num.assign(n, vi(m, 0));
    low.assign(n, vi(m, 0));
    
    // find articulation points
    articulationPoints(si, sj);
    
    int counter = 0;
    for (auto point : artics) {
      cout << point.first << " " << point.second << "\n";
      bool start = point.first == si && point.second == sj;
      bool end = point.first == ei && point.second == ej;
      if (!start && !end)
        counter++;
    }
    
    if (counter >= 1) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
    
    artics.clear();
  }
  
  return 0;
}
