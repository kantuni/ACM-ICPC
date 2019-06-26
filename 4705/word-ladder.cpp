#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
#define INF (int) 1e7

bool transform(string a, string b) {
  if (a.size() < b.size()) {
    return transform(b, a);
  }
  int m = a.size(), n = b.size();
  if (m - n >= 2) {
    return false;
  }
  int miss = 0;
  if (m == n) {
    for (int i = 0; i < m; i++) {
      if (a[i] != b[i]) {
        miss++;
      }
    }
  } else {
    int j = 0;
    for (int i = 0; i < m && j < n; i++) {
      if (a[i] != b[j]) {
        miss++;
      } else {
        j++;
      }
    }
  }
  return miss <= 1;
}

int main() {
  while (true) {
    int n;
    cin >> n;
    
    if (n == 0) {
      break;
    }
    
    set<string> s;
    for (int i = 0; i < n; i++) {
      string w;
      cin >> w;
      s.insert(w);
    }
    
    vector<string> words(s.begin(), s.end());
    n = words.size();
    
    vvi D(n, vi(n, INF));
    for (int i = 0; i < n; i++) {
      D[i][i] = 0;
    }
    
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (transform(words[i], words[j])) {
          D[i][j] = 1;
          D[j][i] = 1;
        }
      }
    }
    
    // Floyd-Warshall
    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
        }
      }
    }
    
    int diameter = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (D[i][j] != INF) {
          diameter = max(diameter, D[i][j]);
        }
      }
    }
    cout << diameter + 1 << endl;
  }
  
  return 0;
}
