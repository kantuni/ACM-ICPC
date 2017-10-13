#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> num;

bool is_palindrome() {
  for (int i = 0; i < num.size() / 2; i++)
    if (num[i] != num[num.size() - 1 - i])
      return false;
  return true;
}

int main() {
  while (1) {
    string line;
    cin >> line;
    
    if (line == "0") {
      break;
    }
    
    for (int i = 0; i < line.size(); i++) {
      num.push_back(line[i] - '0');
    }
    
    int current = num.size() - 1;
    int counter = 0;
    
    while (!is_palindrome()) {
      while (num[current] == 9) {
        for (int i = current; i < num.size(); i++) {
          num[i] = 0;
        }
        current--;
      }
      num[current] += 1;
      current = num.size() - 1;
      counter++;
    }
    
    num.clear();
    cout << counter << "\n";
  }
  
  return 0;
}
