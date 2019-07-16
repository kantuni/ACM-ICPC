#include <bits/stdc++.h>
using namespace std;

typedef vector<char> vc;
typedef vector<vc> vvc;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
typedef vector<vb> vvb;

vvc G; // grid
vvb V; // visited
vii l; // land
queue<ii> q;

void check(int i, int j) {
  bool oof = i >= 0 and i < G.size() and j >= 0 and j < G[0].size();
  if (oof and G[i][j] != 'W' and !V[i][j]) {
    q.push(ii(i, j));
    V[i][j] = true;
  }
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    G.resize(n, vc(m));
    V.resize(n, vb(m, false));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> G[i][j];
        if (G[i][j] == 'L') {
          l.push_back(ii(i, j));
        }
      }
    }
    int ans = 0;
    for (int i = 0; i < l.size(); i++) {
      int li = l[i].first, lj = l[i].second;
      if (!V[li][lj]) {
        q.push(l[i]);
        V[li][lj] = true;
        while (!q.empty()) {
          int fi = q.front().first, fj = q.front().second;
          check(fi - 1, fj);
          check(fi + 1, fj);
          check(fi, fj - 1);
          check(fi, fj + 1);
          q.pop();
        }
        ans++;
      }
    }
    cout << ans << endl;
    G.clear();
    V.clear();
    l.clear();
  }
  return 0;
}
