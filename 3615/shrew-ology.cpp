#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef vector<int> vi;

struct Shrew {
  string name;
  vi chs;
  
  Shrew(string n, string ch) {
    name = n;
    for (int i = 0; i < ch.size(); i++) {
      chs.push_back(ch[i] - '0');
    }
  }
  
  bool operator < (const Shrew &other) const {
    return name < other.name;
  }
};

int main() {
  string types;
  while (getline(cin, types)) {
    vector<Shrew> males, females, children;
    unordered_map<string, ull> memo;
    unordered_map<ull, vector<string> > cp;
    
    while (true) {
      string line;
      getline(cin, line);
      
      if (line == "***") {
        break;
      }
      
      istringstream iss(line);
      string name, gender, ch;
      iss >> name >> gender >> ch;
      Shrew temp(name, ch);
      
      if (gender == "M") {
        males.push_back(temp);
      } else {
        females.push_back(temp);
      }
    }
    
    while (true) {
      string line;
      getline(cin, line);
      
      if (line == "***") {
        break;
      }
        
      istringstream iss(line);
      string name, ch;
      iss >> name >> ch;
      Shrew temp(name, ch);
      children.push_back(temp);
      memo.insert(make_pair(ch, children.size() - 1));
    }
    
    sort(females.begin(), females.end());
    sort(males.begin(), males.end());
    
    for (ull i = 0; i < females.size(); i++) {
      vector<int> f = females[i].chs;
      for (ull j = 0; j < males.size(); j++) {
        vector<int> m = males[j].chs;
        vector<int> comb(types.size());
        
        for (int i = 0; i < types.size(); i++) {
          if (types[i] == 'R') {
            comb[i] = f[i] & m[i];
          } else {
            comb[i] = f[i] | m[i];
          }
        }
        
        string h = "";
        for (int i = 0; i < types.size(); i++) {
          h += to_string(comb[i]);
        }
        
        if (memo.count(h) > 0) {
          ull index = memo[h];
          cp[index].push_back(females[i].name + "-" + males[j].name);
        }
      }
    }
    
    for (ull i = 0; i < children.size(); i++) {
      cout << children[i].name << " by ";
      if (cp.count(i) > 0) {
        for (ull j = 0; j < cp[i].size(); j++) {
          cout << cp[i][j];
          if (j != cp[i].size() - 1) {
            cout << " or ";
          }
        }
      }
      cout << endl;
    }
    
    
    males.clear();
    females.clear();
    children.clear();
  }
  
  return 0;
}
