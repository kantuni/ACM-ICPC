#include <bits/stdc++.h>
using namespace std;

typedef vector<string> vs;

vs ps, rs, ms;
vs text;

bool isvowel(char c) {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

// without the first *
bool _match(string s, string p) {
  vs tms;
  for (int i = 0, j = 0; i < p.size(); i++, j++) {
    char pi = p[i], sj = s[j];
    
    // match the first *
    if (pi == '*') {
      string star = ms[ms.size() - 1];
      if (s.substr(j, star.size()) != star) {
        return false;
      }
      tms.push_back(star);
      j += star.size() - 1;
    }
    
    // given letter in l/u case
    else if (islower(pi)) {
      if (pi != tolower(sj)) {
        return false;
      }
      tms.push_back(string(1, sj));
    }
    
    // lower-case vowel
    else if (pi == 'V') {
      if (!islower(sj) || !isvowel(sj)) {
        return false;
      }
      tms.push_back(string(1, s[j]));
    }
    
    // lower-case consonant
    else if (pi == 'C') {
      if (!islower(sj) || isvowel(sj)) {
        return false;
      }
      tms.push_back(string(1, sj));
    }
  }
  
  ms.insert(ms.end(), tms.begin(), tms.end());
  return true;
}

bool match(string s, string p) {
  if (s.size() < p.size()) {
    return false;
  }
  if (p == "*") {
    ms.push_back(s);
    return true;
  }
  
  // replace digits here
  for (int i = 0; i < p.size(); i++) {
    if (p[i] >= '1' && p[i] <= '9') {
      int index = p[i] - '0';
      p[i] = p[index - 1];
    }
  }
  
  if (p[0] == '*') {
    // try to match subsets
    for (int i = 1; s.size() - i >= p.size() - 1; i++) {
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
  for (char c: r) {
    if (islower(c)) {
      w += c;
    } else {
      int index = c - '0';
      w += ms[index - 1];
    }
  }
  return w;
}

void solve() {
  for (auto line: text) {
    int start = -1;
    for (int i = 0; i < line.size(); i++) {
      if (isalpha(line[i])) {
        if (start == -1) {
          start = i;
        }
        if (i != line.size() - 1) {
          continue;
        }
      }
      
      if (start == -1) {
        continue;
      }
      
      // find words
      string w;
      if (i == line.size() - 1 && isalpha(line[i])) {
        w = line.substr(start, line.size() - start);
      } else {
        w = line.substr(start, i - start);
      }
      
      // match and replace
      for (int j = 0; j < ps.size(); j++) {
        if (match(w, ps[j])) {
          string r = replace(rs[j]);
          line.replace(start, w.size(), r);
          i += r.size() - w.size();
          ms.clear();
          break;
        }
        ms.clear();
      }
      start = -1;
    }
    cout << line << endl;
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
        
        if (tline.substr(0, 3) == "***") {
          exit = true;
        }
        
        if (tline == "" || tline.substr(0, 3) == "***") {
          solve();
          cout << "***" << endl;
          
          ps.clear();
          rs.clear();
          ms.clear();
          text.clear();
          break;
        }
        
        text.push_back(tline);
      }
      
      if (exit) {
        break;
      }
    }
  }
  
  
  return 0;
}
