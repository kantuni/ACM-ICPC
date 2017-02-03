#include <iostream>
#include <regex>
#include <map>

using namespace std;

int main() {
  int L;
  vector<string> words;
  map<string, pair<int, int>> memo;

  while (true) {
    words.clear();
    memo.clear();

    cin >> L;
    // BTDT: ignore the first empty line
    // caused by cin >> L
    cin.ignore(1);

    // a value of zero indicates the end of input
    if (L == 0) {
      break;
    }

    // max number of lines
    int number_of_lines = 250;

    // read paragraphs
    while (number_of_lines >= 0) {
      cout << number_of_lines << endl;
      string line;
      getline(cin, line);

      // terminate by an empty line
      if (line.length() == 0) {
        break;
      }

      // split words
      regex re("\\s+");
      sregex_token_iterator it(line.begin(), line.end(), re, -1);
      sregex_token_iterator it_end;
      while (it != it_end) {
        // add words from new the line
        words.push_back(it->str());
        ++it;
      }

      --number_of_lines;
    }

    for (string word : words) {
      cout << word << " ";
    }
    cout << endl;
  }

  return 0;
}