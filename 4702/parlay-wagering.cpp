#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int init, wn;
    cin >> init >> wn;
    long double wager = 1.0 * init, mul, won, total = 0.0;
    bool lost = false;
    for (int j = 0; j < wn; j++) {
      int ml;
      string res;
      cin >> ml >> res;
      if (res == "Tie") {
        continue;
      } 
      if (lost || res == "Loss") {
        lost = true;
        total = 0;
        continue;
      }
      if (ml > 0) {
        mul = ml / 100.0;
      } else {
        mul = 100.0 / -ml;
      }
      mul = round(100000 * mul) / 100000;
      mul = trunc(mul * 1000) / 1000;
      won = mul * wager;
      won = trunc(won * 100) / 100;
      wager += won;
      if (total + won < 1e6) {
        total += won;
      } else {
        total = 1e6;
      }
    }
    if (!lost) {
      total += init;
    }
    stringstream stream;
    stream << fixed << setprecision(2) << total;
    string ans = stream.str();
    if (ans.size() == 10) {
      cout << "$1,000,000.00" << endl;
    } else if (ans.size() >= 7) {
      ans.insert(ans.end() - 6, ',');
      cout << "$" + ans << endl;
    } else {
      cout << "$" + ans << endl;
    }
  }
  return 0;
}
