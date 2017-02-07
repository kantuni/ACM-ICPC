#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

int L;
vector<string> words;

int w(int i, int j) {
  if (i < 0 || j >= words.size()) {
    return -1;
  }

  int width = 0;
  for (int k = i; k <= j; ++k) {
   width += words[k].length();
   if (k != j) {
    width += 1;
   }
  }

  return width;
}

int r(int i, int j) {
  if (i < 0 || j >= words.size()) {
   return -1;
  }

  if (w(i, j) < 0 || w(i, j) > L) {
    return -1;
  }

  return pow(L - w(i, j), 2);
}

int main() {
  L = 6;
  words = {"See", "if", "we", "care."};
  
  // cout << w(-1, 0) << endl;
  // cout << w(0, 4) << endl;
  cout << w(0, 2) << endl;
  cout << r(0, 1) << endl;

  /*

  while (true) { 
    scanf("%d", &L);
    
    if (L == 0) {
      break;
    }

    int lines = 250;
    while (lines > 0) {
      string line;
      getline(cin, line);
      
      if (line.length() == 0) {
        break;
      }

      
      
      // words.push_back(word);
      --lines;
    }
  }

  */

  return 0;
}
