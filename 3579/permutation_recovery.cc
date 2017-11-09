#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int main() {
  while (true) {
    int n;
    cin >> n;
    
    if (n == 0)
      break;
    
    vi p(n), a(n);
    
    for (int i = 0; i < n; i++) {
      p[i] = i + 1;
      cin >> a[i];
    }
    
    /*
    // print answer
    for (int i = 0; i < n; i++) {
      if (i != 0) cout << ",";
      cout << p[i];
    }
    cout << "\n";
    */
  }
  
  return 0;
}
