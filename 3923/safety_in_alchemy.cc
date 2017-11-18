#include <bits/stdc++.h>
using namespace std;

unordered_map<string, int> rs;
unordered_map<string, int> cs;

int solve() {
  
}

int main() {
  string line;
  while (getline(cin, line)) {
    if (line == "") continue;
    if (line == "ENDOFINPUT") break;
    
    istringstream iss(line);
    string c1, c2; int h;
    iss >> c1 >> c2 >> h;
    
    if (c1 == "0" && c2 == "0" && h == 0) {
      while (true) {
        string c; int a;
        cin >> c >> a;
        
        if (c == "0" && a == 0) {
          int ans = solve();
          printf("The temperature in the jar will change by at most %d degrees.\n", ans);
          rs.clear();
          cs.clear();
          break;
        }
        cs[c] = a;
      }
      continue;
    }
    rs[c1 + " + " + c2] = h;
  }
  
  return 0;
}
