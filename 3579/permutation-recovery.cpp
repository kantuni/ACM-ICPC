#include <bits/stdc++.h>
using namespace std;

int main() {
  while (true) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    vector<int> p(n), a(n);
    for (int i = 0; i < n; i++) {
      p[i] = i + 1;
      cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
      int cnt = 0;
      auto ith = find(p.begin(), p.end(), i + 1);
      for (auto it = p.begin(); it != ith; it++) {
        if (*it > *ith) {
          cnt++;
        }
      }
      if (cnt > a[i]) {
        int left = cnt - a[i];
        for (auto it = prev(ith); it != prev(p.begin()); it--) {
          if (*it > *ith) {
            left--;
          }
          if (left == 0) {
            swap(*it, *ith);
            break;
          }
        }
      } else if (cnt < a[i]) {
        int left = a[i] - cnt;
        for (auto it = next(ith); it != p.end(); it++) {
          if (*it > *ith) {
            left--;
          }
          if (left == 0) {
            swap(*it, *ith);
            break;
          }
        }
      } else {
        continue;
      }
    }
    for (int i = 0; i < n; i++) {
      if (i != 0) {
        cout << ",";
      }
      cout << p[i];
    }
    cout << endl;
  }
  return 0;
}
