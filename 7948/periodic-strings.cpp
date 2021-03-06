#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  while (getline(cin, s)) {
    if (s.size() == 0) {
      continue;
    }
    // a
    if (s.size() == 1) {
      cout << 1 << endl;
      continue;
    }
    set<char> sc;
    for (char c: s) {
      sc.insert(c);
    }
    // aaa
    if (sc.size() == 1) {
      cout << 1 << endl;
      continue;
    }
    if (sc.size() == s.size()) {
      cout << s.size() << endl;
      continue;
    }
    // abba, abccab, ...
    for (int k = 2; k <= s.size(); k++) {
      if (s.size() % k == 0) {
        vector<string> subs;
        string tmp;
        for (int i = 0; i < s.size(); i++) {
          if (i > 0 && i % k == 0) {
            subs.push_back(tmp);
            tmp = "";
          }
          tmp += s[i];
        }
        subs.push_back(tmp);
        bool periodic = true;
        for (int i = 1; i < subs.size(); i++) {
          string cur = subs[i - 1];
          cur = cur[cur.size() - 1] + cur;
          cur = cur.substr(0, cur.size() - 1);
          if (subs[i] != cur) {
            periodic = false;
            break;
          }
        }
        if (periodic) {
          cout << k << endl;
          break;
        }
      }
    }
  }
  return 0;
}
