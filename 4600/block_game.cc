#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<char> vc;
typedef vector<vc> vvc;

struct State {
  int dist;
  vvc board;
  vii pieces;
  string hash;
  
  State() {}
  State(vvc board, vii pieces) {
    this->board = board;
    this->pieces = pieces;
  }
};

string custom_hash(State &s) {
  string h;
  for (int i = 0; i < s.pieces.size(); i++)
    h += to_string(s.pieces[i].first) + to_string(s.pieces[i].second);
  return h;
}

bool can_move_left(State s, int pi, int c) {
  int i = s.pieces[pi].first, j = s.pieces[pi].second;
  bool three = j + 2 < 6 && s.board[i][j] == s.board[i][j + 2];
  bool two = j + 1 < 6 && s.board[i][j] == s.board[i][j + 1];
  bool horizontal = three || two;
  if (!horizontal) return false;
  if (three && (j - c < 0 || j + 2 - c >= 6)) return false;
  else if (two && (j - c < 0 || j + 1 - c >= 6)) return false;
  for (int k = 1; k <= c; k++)
    if (s.board[i][j - k] != '.')
      return false;
  return true;
}

State move_left(State s, int pi, int c) {
  int i = s.pieces[pi].first, j = s.pieces[pi].second;
  bool three = j + 2 < 6 && s.board[i][j] == s.board[i][j + 2];
  swap(s.board[i][j], s.board[i][j - c]);
  swap(s.board[i][j + 1], s.board[i][j + 1 - c]);
  if (three) swap(s.board[i][j + 2], s.board[i][j + 2 - c]);
  s.pieces[pi] = ii(i, j - c);
  return s;
}

bool can_move_right(State s, int pi, int c) {
  int i = s.pieces[pi].first, j = s.pieces[pi].second;
  bool three = j + 2 < 6 && s.board[i][j] == s.board[i][j + 2];
  bool two = j + 1 < 6 && s.board[i][j] == s.board[i][j + 1];
  bool horizontal = three || two;
  if (!horizontal) return false;
  if (three && j + 2 + c >= 6) return false;
  else if (two && j + 1 + c >= 6) return false;
  for (int k = 1; k <= c; k++)
    if (s.board[i][j + ((three) ? 2 : 1) + k] != '.')
      return false;
  return true;
}

State move_right(State s, int pi, int c) {
  int i = s.pieces[pi].first, j = s.pieces[pi].second;
  bool three = j + 2 < 6 && s.board[i][j] == s.board[i][j + 2];
  if (three) swap(s.board[i][j + 2], s.board[i][j + 2 + c]);
  swap(s.board[i][j + 1], s.board[i][j + 1 + c]);
  swap(s.board[i][j], s.board[i][j + c]);
  s.pieces[pi] = ii(i, j + c);
  return s;
}

bool can_move_up(State s, int pi, int c) {
  int i = s.pieces[pi].first, j = s.pieces[pi].second;
  bool three = i + 2 < 6 && s.board[i][j] == s.board[i + 2][j];
  bool two = i + 1 < 6 && s.board[i][j] == s.board[i + 1][j];
  bool vertical = three || two;
  if (!vertical) return false;
  if (three && (i - c < 0 || i + 2 - c >= 6)) return false;
  else if (two && (i - c < 0 || i + 1 - c >= 6)) return false;
  for (int k = 1; k <= c; k++)
    if (s.board[i - k][j] != '.')
      return false;
  return true;
}

State move_up(State s, int pi, int c) {
  int i = s.pieces[pi].first, j = s.pieces[pi].second;
  bool three = i + 2 < 6 && s.board[i][j] == s.board[i + 2][j];
  swap(s.board[i][j], s.board[i - c][j]);
  swap(s.board[i + 1][j], s.board[i + 1 - c][j]);
  if (three) swap(s.board[i + 2][j], s.board[i + 2 - c][j]);
  s.pieces[pi] = ii(i - c, j);
  return s;
}

bool can_move_down(State s, int pi, int c) {
  int i = s.pieces[pi].first, j = s.pieces[pi].second;
  bool three = i + 2 < 6 && s.board[i][j] == s.board[i + 2][j];
  bool two = i + 1 < 6 && s.board[i][j] == s.board[i + 1][j];
  bool vertical = three || two;
  if (!vertical) return false;
  if (three && i + 2 + c >= 6) return false;
  else if (two && i + 1 + c >= 6) return false;
  for (int k = 1; k <= c; k++)
    if (s.board[i + ((three) ? 2 : 1) + k][j] != '.')
      return false;
  return true;
}

State move_down(State s, int pi, int c) {
  int i = s.pieces[pi].first, j = s.pieces[pi].second;
  bool three = i + 2 < 6 && s.board[i][j] == s.board[i + 2][j];
  if (three) swap(s.board[i + 2][j], s.board[i + 2 + c][j]);
  swap(s.board[i + 1][j], s.board[i + 1 + c][j]);
  swap(s.board[i][j], s.board[i + c][j]);
  s.pieces[pi] = ii(i + c, j);
  return s;
}

bool can_exit(State &s) {
  int si = s.pieces[0].first, sj = s.pieces[0].second;
  for (int j = sj + 2; j < 6; j++)
    if (s.board[si][j] != '.')
      return false;
  return true;
}

int main() {
  while (true) {
    char s;
    cin >> s;
    
    if (s == '*')
      break;
    
    vvc B(6, vc(6));
    vii P(1);
    
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 6; j++) {
        cin >> B[i][j];
      }
    }
    
    // piece recognition
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 6; j++) {
        if (B[i][j] != '.') {
          bool s2 = j + 1 < 6 && B[i][j] == s && B[i][j + 1] == s;
          if (s2) {
            P[0] = ii(i, j);
            continue;
          }
          bool h2 = j + 1 < 6 && B[i][j] == B[i][j + 1] && j - 1 >= 0 && B[i][j - 1] != B[i][j];
          h2 = h2 || (j + 1 < 6 && B[i][j] == B[i][j + 1] && j - 1 < 0);
          bool h3 = j + 2 < 6 && B[i][j] == B[i][j + 2];
          bool v2 = i + 1 < 6 && B[i][j] == B[i + 1][j] && i - 1 >= 0 && B[i - 1][j] != B[i][j];
          v2 = v2 || (i + 1 < 6 && B[i][j] == B[i + 1][j] && i - 1 < 0);
          bool v3 = i + 2 < 6 && B[i][j] == B[i + 2][j];
          if (h2 || h3 || v2 || v3) P.push_back(ii(i, j));
        }
      }
    }
    
    unordered_set<string> memo;
    queue<State> q;
    
    State init(B, P);
    init.dist = 1;
    init.hash = custom_hash(init);
    q.push(init);
    memo.insert(init.hash);
    
    while (!q.empty()) {
      State front = q.front();
      if (can_exit(front)) {
        printf("%d\n", front.dist);
        break;
      }
      
      bool found = false;
      for (int i = 0; i < front.pieces.size(); i++) {
        for (int c = 1; c < 6; c++) {
          State branch;
          if (can_move_left(front, i, c)) {
            branch = move_left(front, i, c);
            string h = front.hash;
            h[2 * i + 1] = (char) ((int) h[2 * i + 1] - '0') - c + '0';
            if (memo.count(h) == 0) {
              branch.dist = front.dist + 1;
              branch.hash = h;
              q.push(branch);
              memo.insert(h);
              if (can_exit(branch)) {
                found = true;
                printf("%d\n", branch.dist);
                break;
              }
            }
          }
          
          if (can_move_right(front, i, c)) {
            branch = move_right(front, i, c);
            string h = front.hash;
            h[2 * i + 1] = (char) ((int) h[2 * i + 1] - '0') + c + '0';
            if (memo.count(h) == 0) {
              branch.dist = front.dist + 1;
              branch.hash = h;
              q.push(branch);
              memo.insert(h);
              if (can_exit(branch)) {
                found = true;
                printf("%d\n", branch.dist);
                break;
              }
            }
          }
          
          if (can_move_up(front, i, c)) {
            branch = move_up(front, i, c);
            string h = front.hash;
            h[2 * i] = (char) ((int) h[2 * i] - '0') - c + '0';
            if (memo.count(h) == 0) {
              branch.dist = front.dist + 1;
              branch.hash = h;
              q.push(branch);
              memo.insert(h);
              if (can_exit(branch)) {
                found = true;
                printf("%d\n", branch.dist);
                break;
              }
            }
          }
          
          if (can_move_down(front, i, c)) {
            branch = move_down(front, i, c);
            string h = front.hash;
            h[2 * i] = (char) ((int) h[2 * i] - '0') + c + '0';
            if (memo.count(h) == 0) {
              branch.dist = front.dist + 1;
              branch.hash = h;
              q.push(branch);
              memo.insert(h);
              if (can_exit(branch)) {
                found = true;
                printf("%d\n", branch.dist);
                break;
              }
            }
          }
        }
        
        // break for
        if (found) {
          break;
        }
      }
      
      // break while
      if (found) {
        break;
      }
      
      // leave this here
      q.pop();
    }
    
    if (q.empty()) {
      printf("-1\n");
    }
  }
  
  return 0;
}
