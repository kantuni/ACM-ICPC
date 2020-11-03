#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<vi> vvi;

struct Graph {
  struct Edge {
    int from;
    int to;
    double weight;
    
    bool operator < (const Edge &a) const {
      // hack: invert sign
      return weight >= a.weight;
    }
  };
  
  vector<Edge> edges;
  vvi cnn;
  
  // MST
  priority_queue<Edge> pq;
  vi taken;
  
  Graph(int n) {
    cnn.assign(n, vi());
    taken.assign(n, 0);
  }
  
  void addEdge(int s, int t, double w) {
    cnn[s].push_back(edges.size());
    edges.push_back({s, t, w});
    cnn[t].push_back(edges.size());
    edges.push_back({t, s, w});
  }
  
  void process(int u) {
    taken[u] = 1;
    for (auto ie: cnn[u]) {
      Edge e = edges[ie];
      if (!taken[e.to]) {
        pq.push(e);
      }
    }
  }
  
  double Prim() {
    double mstc = 0;
    process(0);
    while (!pq.empty()) {
      Edge top = pq.top(); pq.pop();
      if (!taken[top.to]) {
        process(top.to);
        mstc += top.weight;
      }
    }
    return mstc;
  }
};

int main() {
  while (true) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    vii points(n);
    for (int i = 0; i < n; i++) {
      int x, y;
      cin >> x >> y;
      points[i] = ii(x, y);
    }
    Graph g(1000);
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        double dx = points[i].first - points[j].first;
        double dy = points[i].second - points[j].second;
        g.addEdge(i, j, hypot(dx, dy));
      }
    }
    double ans = g.Prim();
    printf("%.2f\n", ans);
  }
  return 0;
}
