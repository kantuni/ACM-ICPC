#include <bits/stdc++.h>
using namespace std;

bool periodic(string &s, int k) {
  for (int i = k; i < s.size(); i += k) {
    string prv = s.substr(i - k, k);
    string tmp = prv.back() + prv.substr(0, prv.size() - 1);
    string cur = s.substr(i, k);
    if (tmp != cur) {
      return false;
    }
  }
  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  while (cin >> s) {
    for (int k = 1; k <= s.size(); k++) {
      if (periodic(s, k)) {
        cout << k << endl;
        break;
      }
    }
  }
  return 0;
}
