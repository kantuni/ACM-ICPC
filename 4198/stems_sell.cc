#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef vector<string> vs;

vs ps, rs, ms;
vs text;

bool isvowel(char c) {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

bool isword(string w) {
  for (ull i = 0; i < w.size(); i++) {
    bool lower = w[i] >= 'a' && w[i] <= 'z';
    bool upper = w[i] >= 'A' && w[i] <= 'Z';
    if (!lower && !upper) return false;
  }
  return true;
}

// without *
bool _match(string s, string p) {
  bool ok = true;
  for (ull i = 0; i < p.size(); i++) {
    // digit
    if (p[i] >= '1' && p[i] <= '9') {
      int index = p[i] - '0';
      p[i] = p[index - 1];
    }
    // given letter
    if (p[i] >= 'a' && p[i] <= 'z') {
      if (p[i] != tolower(s[i])) {
        ok = false;
        break;
      }
    }
    // vowel
    else if (p[i] == 'V') {
      if (!isvowel(s[i])) {
        ok = false;
        break;
      }
    }
    // consonant
    else if (p[i] == 'C') {
      if (isvowel(s[i])) {
        ok = false;
        break;
      }
    }
  }
  
  if (!ok) return false;
  for (auto c: s) {
    ms.push_back(string(1, c));
  }
  return true;
}

bool match(string s, string p) {
  if (s.size() < p.size()) return false;
  if (p == "*") {
    ms.push_back(s);
    return true;
  }
  
  if (p[0] == '*') {
    // try to match subsets
    for (ull i = 1; s.size() - i >= p.size() - 1; i++) {
      ms.push_back(s.substr(0, i));
      if (_match(s.substr(i), p.substr(1))) {
        return true;
      }
      ms.pop_back();
    }
  }
  return _match(s, p);
}

string replace(string r) {
  string w = "";
  for (ull i = 0; i < r.size(); i++) {
    if (r[i] >= 'a' && r[i] <= 'z') {
      w += r[i];
    } else {
      int index = r[i] - '0';
      w += ms[index - 1];
    }
  }
  return w;
}

void solve() {
  for (auto &line: text) {
    istringstream iss(line);
    string word;
    vs words;
    
    while (iss >> word) {
      words.push_back(word);
    }
    
    for (ull i = 0; i < words.size(); i++) {
      if (!isword(words[i])) continue;
      
      for (ull j = 0; j < ps.size(); j++) {
        if (match(words[i], ps[j])) {
          words[i] = replace(rs[j]);
        }
        ms.clear();
      }
    }
    
    for (ull i = 0; i < words.size(); i++) {
      cout << words[i];
      if (i != words.size() - 1) cout << " ";
    }
    cout << "\n";
  }
}

int main() {
  while (true) {
    string line;
    getline(cin, line);
    
    if (line != "") {
      istringstream iss(line);
      string p, arrow, r;
      iss >> p >> arrow >> r;
      ps.push_back(p);
      rs.push_back(r);
    } else {
      bool exit = false;
      while (true) {
        string tline;
        getline(cin, tline);
        
        if (tline[0] == '*' && tline[1] == '*' && tline[2] == '*') {
          exit = true;
        }
        
        if (tline == "" || (tline[0] == '*' && tline[1] == '*' && tline[2] == '*')) {
          solve();
          cout << "***\n";
          
          ps.clear();
          rs.clear();
          text.clear();
          break;
        }
        
        text.push_back(tline);
      }
      
      if (exit)
        break;
    }
  }
  
  
  return 0;
}
