#include <bits/stdc++.h>
using namespace std;

int main() {
  while (true) {
    int n;
    cin >> n;
    cin.ignore();
    if (n == 0) {
      break;
    }
    vector<string> lines;
    for (int i = 0; i < n; i++) {
      string line;
      getline(cin, line);
      lines.push_back(line);
    }
    int start = 0;
    for (int i = 0; i < lines.size(); i++) {
      bool found = false;
      for (int j = start; j < lines[i].size(); j++) {
        if (lines[i][j] == ' ') {
          found = true;
          start = j;
          break;
        }
      }
      if (!found) {
        start = max(start, (int) lines[i].size());
      }
    }
    cout << start + 1 << endl;
  }
  return 0;
}
