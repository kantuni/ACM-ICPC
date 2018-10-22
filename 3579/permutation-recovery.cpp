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
      int count = 0;
      auto ith = find(p.begin(), p.end(), i + 1);
      for (auto it = p.begin(); it != ith; it++) {
        if (*it > *ith) {
          count++;
        }
      }
      if (count == a[i]) {
        continue;
      }
      if (count > a[i]) {
        int left = count - a[i];
        for (auto it = prev(ith); it != prev(p.begin()); it--) {
          if (*it > *ith) {
            left--;
          }
          if (left == 0) {
            swap(*it, *ith);
            break;
          }
        }
      }
      if (count < a[i]) {
        int left = a[i] - count;
        for (auto it = next(ith); it != p.end(); it++) {
          if (*it > *ith) {
            left--;
          }
          if (left == 0) {
            swap(*it, *ith);
            break;
          }
        }
      }
    }
    for (int i = 0; i < n; i++) {
      if (i != 0) {
        cout << ",";
      }
      cout << p[i];
    }
    cout << "\n";
  }
  return 0;
}
