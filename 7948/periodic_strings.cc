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
      cout << 1 << "\n";
      continue;
    }
    
    set<char> sc;
    for (char c: s) {
      sc.insert(c);
    }
      
    // aaa
    if (sc.size() == 1) {
      cout << 1 << "\n";
      continue;
    }
    
    if (sc.size() == s.size()) {
      cout << s.size() << "\n";
      continue;
    }
    
    // abba, abccab, ...
    for (int k = 2; k <= s.size(); k++) {
      if (s.size() % k == 0) {
        vector<string> subs;
        string temp;
        for (int i = 0; i < s.size(); i++) {
          if (i > 0 && i % k == 0) {
            subs.push_back(temp);
            temp = "";
          }
          temp += s[i];
        }
        subs.push_back(temp);
        
        bool periodic = true;
        for (int i = 1; i < subs.size(); i++) {
          string curr = subs[i - 1];
          curr = curr[curr.size() - 1] + curr;
          curr = curr.substr(0, curr.size() - 1);
          if (subs[i] != curr) {
            periodic = false;
            break;
          }
        }
        
        if (periodic) {
          cout << k << "\n";
          break;
        }
      }
    }
  }
  
  return 0;
}
