#include <iostream>
#include <regex>
#include <map>

using namespace std;

int L;
vector<string> words;
map<string, pair<int, int>> memo;

/**
 * Define w(i, j) as the width of the line containing words i through j, inclusive,
 * plus one blank space between each pair of words.
 *
 * @param i starting position
 * @param j ending position
 * @return w(i, j) value or 0
 */
int w(int i, int j) {
  int width = 0;

  // out of bounds
  if (j + 1 > words.size()) {
    return 0;
  }

  for (int k = 0; k < words.size(); ++k) {
    if (k >= i && k <= j) {
      // length of a word + blank space between each pair of words
      width += words[k].length() + 1;
    }
  }

  // remove the last blank space
  width -= 1;

  return (width > 0 && width <= L) ? width : 0;
}

int main() {
  L = 6;
  words = {"See", "if", "we", "care."};
  cout << w(0, 1) << endl;

  //while (true) {
  //  words.clear();
  //  memo.clear();
  //
  //  // read L
  //  scanf("%d", &L);
  //
  //  // a value of zero indicates the end of input
  //  if (L == 0) {
  //    break;
  //  }
  //
  //  // max number of lines
  //  int number_of_lines = 250;
  //
  //  // read paragraphs
  //  while (number_of_lines >= 0) {
  //    cout << number_of_lines << endl;
  //    string line;
  //    getline(cin, line);
  //    cout << "Line length: " << line.length() << endl;
  //
  //    // terminate by an empty line
  //    if (line.length() == 0) {
  //      break;
  //    }
  //
  //    // split words
  //    regex re("\\s+");
  //    sregex_token_iterator it(line.begin(), line.end(), re, -1);
  //    sregex_token_iterator it_end;
  //    while (it != it_end) {
  //      // add words from the new the line
  //      words.push_back(it->str());
  //      ++it;
  //    }
  //
  //    --number_of_lines;
  //  }
  //
  //  if (words.size() < 3) {
  //    cout << words[0] << endl;
  //    cout << "===" << endl;
  //    continue;
  //  }
  //
  //}

  return 0;
}