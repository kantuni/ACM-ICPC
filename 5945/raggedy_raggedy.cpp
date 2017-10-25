#include <bits/stdc++.h>
using namespace std;

int L;
vector<string> p;


int w(int i, int j) {
  int width = 0;
  for (int k = i - 1; k < j; k++) {
    width += p[k].size();
  }
  return width + (j - i);
}

int r(int i, int j) {
  if (w(i, j) > L) return -1;
  return (L - w(i, j)) * (L - w(i, j));
}

void populate(int i, int j);

int main() {
  while (true) {
    cin >> L; cin.ignore();
    if (L == 0) break;
    
    string line, word;
    while (getline(cin, line)) {
      if (line.size() == 0) break;
      istringstream iss(line);
      while (iss >> word) p.push_back(word);
    }
  }
  
  return 0;
}


