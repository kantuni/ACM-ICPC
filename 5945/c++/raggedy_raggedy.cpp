#include <iostream>
#include <regex>
#include <unordered_map>

using namespace std;

int L;
int last_line_words;
vector<string> words;
unordered_map<string, pair<int, int> > memo;
string answer;

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

/**
 * Define the raggedness of a line containing words i though j as
 * r(i, j) = (L − w(i, j))²
 *
 * @param i starting position
 * @param j ending position
 * @return r(i, j) value
 */
int r(int i, int j) {
  return (int) pow(L - w(i, j), 2);
}

/**
 * Let C(i, k, last) denote minimum raggedness of a line k containing ith word ignoring last words.
 * Then C(i, k, last) = min(r(i, i) + C(i + 1, k + 1, last), r(i, i + 1) + C(i + 2, k + 1, last), ...)
 *
 * @param i    starting position
 * @param k    line number
 * @param last number of words used in the last line
 * @return a minimum total raggedness and an index of the minimum value (the winner)
 */
pair<int, int> c(int i, int k, int last) {
  vector<int> raggedness;

  // out of bounds
  if (i > words.size() - 1 - last) {
    return {0, -1};
  }

  int l = i;
  while (w(i, l) > 0 && l <= words.size() - 1 - last) {
    string key = to_string(l + 1) + ", " + to_string(k + 1);

    // add value to memo
    auto it = memo.find(key);
    if (it == memo.end()) {
      memo[key] = c(l + 1, k + 1, last);
    }

    // calculate all raggedness values for this c()
    raggedness.push_back(r(i, l) + memo[key].first);
    ++l;
  }

  // find a total minimum raggedness
  auto minimum = min_element(raggedness.begin(), raggedness.end());
  int index_of_min = (int) (minimum - raggedness.begin());
  // BTDT: * is because min_element returns an iterator
  memo[to_string(i) + ", " + to_string(k)] = {*minimum, index_of_min};

  return {*minimum, index_of_min};
}

/**
 * Calculate raggedness values with varying number of last words and
 * return the minimum of them.
 *
 * @return a minimum total raggedness and a number of last line words
 */
pair<int, int> minimize_total_raggedness() {
  // clean memo
  memo.clear();

  // set a minimum to a raggedness with 1 last word
  int last = 1, i = 2;
  int minimum = c(0, 0, last).first;

  int words_size = (int) words.size();

  while (i <= words_size) {
    // go as much as possible (all possible amounts of last words) to find a minimum
    // BTDT: 0 last words = all last words
    if (w(words_size - i, words_size - 1) > 0 && w(words_size - i, words_size - 1) <= L) {
      // clean memo
      memo.clear();

      // update minimum value
      if (minimum > c(0, 0, i).first) {
        minimum = c(0, 0, i).first;
        last = i;
      }
    }
    ++i;
  }

  // clean memo
  memo.clear();
  // call minimum once again to update memo
  c(0, 0, last);

  return {minimum, last};
}

/**
  * Build a string with a minimum total raggedness from a memo table
  *
  * @return a string with a minimum total raggedness
  */
string backtracking() {
  string mtr_result = "";

  // if all the words are on one line
  if (last_line_words == words.size()) {
    for (string word: words) {
      mtr_result += word + " ";
    }
    // remove a trailing space
    mtr_result = mtr_result.substr(0, mtr_result.length() - 1);
    return mtr_result;
  }

  // start with the first word, i.e. the last winner
  int i = 0, k = 0, winner_index;

  auto it = memo.find(to_string(i) + ", " + to_string(k));
  if (it != memo.end()) {
    winner_index = memo[to_string(i) + ", " + to_string(k)].second;
  } else {
    return mtr_result;
  }

  // -1 if c() is out of bounds
  while (winner_index > -1) {
    // add words to the appropriate line
    if (i + winner_index + 1 <= words.size()) {
      for (int l = 0; l < words.size(); ++l) {
        if (l >= i && l <= i + winner_index) {
          mtr_result += words[l] + " ";
        }
      }

      // remove a trailing space
      mtr_result = mtr_result.substr(0, mtr_result.length() - 1);
      // move to the next line
      mtr_result += "\n";
    }

    // move to the next winner
    i += winner_index + 1;
    k += 1;

    it = memo.find(to_string(i) + ", " + to_string(k));
    if (it != memo.end()) {
      winner_index = memo[to_string(i) + ", " + to_string(k)].second;
    } else {
      break;
    }
  }

  // if there are last line words
  if (last_line_words > 0 && last_line_words < words.size()) {
    for (int l = 0; l < words.size(); ++l) {
      if (l >= words.size() - last_line_words && l < words.size()) {
        mtr_result += words[l] + " ";
      }
    }
    // remove a trailing space
    mtr_result = mtr_result.substr(0, mtr_result.length() - 1);
  }

  // remove an empty line
  if (mtr_result.length() > 0 && mtr_result.at(mtr_result.length() - 1) == '\n') {
    mtr_result = mtr_result.substr(0, mtr_result.length() - 1);
  }

  return mtr_result;
}

int main() {
  L = 6;
  words = {"See", "if", "we", "care."};
  pair<int, int> mtr = minimize_total_raggedness();
  last_line_words = mtr.second;
  //answer = backtracking();
  //cout << answer << endl << "===" << endl;


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