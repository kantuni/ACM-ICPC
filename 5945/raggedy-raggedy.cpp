#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
typedef vector<iii> viii;
typedef vector<viii> vviii;
typedef vector<vviii> vvviii;
#define UNVISITED -1
#define VISITED 1
#define INF (int) 1e9

int L, last;
vector<string> p, ans;
vvviii AdjList;
vvii parent;
vvi color, dist;
vii ts;

int w(int i, int j) {
  int width = 0;
  for (int k = i - 1; k < j; k++) {
    width += p[k].size();
  }
  return width + (j - i);
}

int r(int i, int j) {
  if (w(i, j) > L) return -1;
  return (L - w(i, j)) * (L - w(i, j));
}

void populate(int i, int j) {
  color[i][j] = VISITED;
  bool found = false;

  for (int k = j + 1; k <= p.size(); k++) {
    int w = r(j + 1, k);
    if (w != -1) {
      // ignore last line
      if (j >= p.size() - last + 1) {
        w = 0;
      }
      found = true;
      ii v = ii(j + 1, k);
      AdjList[i][j].push_back(iii(w, v));
      if (color[j + 1][k] == UNVISITED)
        populate(j + 1, k);
    }
  }
  
  // topological sort
  ts.push_back(ii(i, j));
  
  if (!found) {
    ii v = ii(p.size() + 1, p.size() + 1);
    AdjList[i][j].push_back(iii(0, v));
  }
}

void sssp() {
  reverse(ts.begin(), ts.end());
  ts.push_back(ii(p.size() + 1, p.size() + 1));
  
  for (int k = 0; k < ts.size(); k++) {
    int ui = ts[k].first, uj = ts[k].second;
    for (int l = 0; l < AdjList[ui][uj].size(); l++) {
      int w = AdjList[ui][uj][l].first;
      ii v = AdjList[ui][uj][l].second;
      int vi = v.first, vj = v.second;
      // relax
      if (dist[vi][vj] > dist[ui][uj] + w) {
        dist[vi][vj] = dist[ui][uj] + w;
        parent[vi][vj] = ii(ui, uj);
      }
    }
  }
}

void recover(int i, int j) {
  if (i == -1 && j == -1) return;
  
  if (i - 1 >= 0 && j - 1 < p.size()) {
    string s = "";
    for (int k = i - 1; k <= j - 1; k++) {
      if (k != i - 1) s += " ";
      s += p[k];
    }
    ans.push_back(s);
  }
  
  ii v = parent[i][j];
  recover(v.first, v.second);
}

int main() {
  while (true) {
    cin >> L; cin.ignore();
    if (L == 0) break;
    
    string line, word;
    while (getline(cin, line)) {
      if (line.size() == 0) break;
      istringstream iss(line);
      while (iss >> word) p.push_back(word);
    }
    
    int N = p.size() + 2;
    AdjList.assign(N, vviii(N));
    color.assign(N, vi(N, UNVISITED));
    dist.assign(N, vi(N, INF));
    dist[0][0] = 0;
    parent.assign(N, vii(N, ii(INF, INF)));
    parent[0][0] = ii(-1, -1);
    
    last = 0;
    for (int i = p.size(); i > 0; i--) {
      if (w(i, p.size()) <= L) {
        last = p.size() - i + 1;
      }
    }
    
    // create DAG
    populate(0, 0);
    
    // find the shortest path
    sssp();
    
    // recover the path
    recover(N - 1, N - 1);
    
    // print the path
    for (int i = ans.size() - 1; i >= 0; i--) {
      cout << ans[i] << "\n";
    }
    cout << "===" << "\n";
    
    // reset
    p.clear();
    ans.clear();
    ts.clear();
  }
  
  return 0;
}
