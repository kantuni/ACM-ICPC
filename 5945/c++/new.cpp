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
  
  cout << w(0, 2) << endl;
  cout << r(0, 1) << endl;

  return 0;
}
