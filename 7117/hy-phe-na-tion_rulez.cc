#include <bits/stdc++.h>
#define all(c) (c).begin(), (c).end()
using namespace std;

typedef vector<char> vc;
typedef vector<string> vs;

vs NA = {
  "qu", "tr", "br", "str", "st", 
  "sl", "bl", "cr", "ph", "ch"
};

bool isv(char c) {
  vc vowels = {'a', 'e', 'i', 'o', 'u', 'y'};
  return find(all(vowels), tolower(c)) != vowels.end();
}

bool isc(char c) {
  return c == ' ' || (tolower(c) >= 'a' && tolower(c) <= 'z' && !isv(c));
}

int main() {
  unordered_map<int, vs> memo;
  vs words;
  string w;
  
  while (cin >> w) {
    if (w == "===") {
      break;
    }
      
    words.push_back(w);
    memo[words.size() - 1] = {};
  }
  
  // replace NA characters with spaces
  for (int i = 0; i < words.size(); i++) {
    string &w = words[i];
    
    for (int j = 0; j < (int) w.size() - 1; j++) {
      if (j + 2 < w.size()) {
        string ccc = string(1, w[j]) + string(1, w[j + 1]) + string(1, w[j + 2]);
        string lccc = ccc;
        transform(all(lccc), lccc.begin(), ::tolower);
        
        if (lccc == "str") {
          memo[i].push_back(ccc);
          w[j] = ' ';
          w = w.substr(0, j + 1) + w.substr(j + 3);
        }
      }
      
      string cc = string(1, w[j]) + string(1, w[j + 1]);
      string lcc = cc;
      transform(all(lcc), lcc.begin(), ::tolower);
      
      if (find(all(NA), lcc) != NA.end()) {
        memo[i].push_back(cc);
        w[j] = ' ';
        w = w.substr(0, j + 1) + w.substr(j + 2);
      }
    }
  }
  
  // apply rules
  for (auto &w: words) {
    // 1. vccv -> vc-cv
    if (w.size() >= 4) {
      for (int i = 0; i <= (int) w.size() - 4; i++) {
        bool ok = isv(w[i]) && isc(w[i + 1]);
        ok = ok && isc(w[i + 2]) && isv(w[i + 3]);
        if (ok) {
          string cc = string(1, w[i + 1]) + string(1, w[i + 2]);
          string lcc = cc;
          transform(all(lcc), lcc.begin(), ::tolower);
          if (find(all(NA), lcc) == NA.end()) {
            w.insert(i + 2, "-");
          }
        }
      }
    }
    
    if (w.size() >= 3) {
      // 2. vcv -> v-cv, unless the second vowel is `e`
      for (int i = 0; i <= (int) w.size() - 3; i++) {
        bool ok = isv(w[i]) && isc(w[i + 1]);
        ok = ok && isv(w[i + 2]);
        ok = ok && !(tolower(w[i + 2]) == 'e' && i + 2 == w.size() - 1);
        if (ok) w.insert(i + 1, "-");
      }
    }
  }
  
  // put back NA characters
  for (int i = 0; i < words.size(); i++) {
    string &w = words[i];
    int k = 0;
    for (int j = 0; j < w.size(); j++) {
      if (w[j] == ' ') {
        string repl = memo[i][k];
        w = w.substr(0, j) + repl + w.substr(j + 1);
        k++;
      }
    }
  }
  
  for (auto w: words) {
    cout << w << "\n";
  }
  
  return 0;
}
