#include <iostream>
#include <map>
#include <utility>

using namespace std;

std::map<pair<int, int> , unsigned long long> memo;
const int kGridSize = 20;
unsigned long long FindPaths(int i, int j) {
  unsigned long long num_paths = 0;
  if (  (i == kGridSize && j == kGridSize - 1)
      ||(i == kGridSize - 1 && j == kGridSize)) {
    num_paths = 1;
  } else if (i == kGridSize) {
    auto key_1 = make_pair(i, j+1);
    if (memo.find(key_1) != memo.end()) {
      num_paths = memo[key_1];
    } else {
      num_paths =  FindPaths(i, j + 1);
      memo[key_1] = num_paths;
    }
  } else if (j == kGridSize) {
    auto key_1 = make_pair(i + 1, j);
    if (memo.find(key_1) != memo.end()) {
      num_paths = memo[key_1];
    } else {
      num_paths =  FindPaths(i + 1, j);
      memo[key_1] = num_paths;
    }
  } else {
    auto key_1 = make_pair(i, j + 1);
    auto key_2 = make_pair(i + 1, j);
    unsigned long long paths_1 = 0;
    unsigned long long paths_2 = 0;

    if (memo.find(key_1) != memo.end()) {
      paths_1= memo[key_1];
    } else {
      paths_1 =  FindPaths(i, j + 1);
      memo[key_1] = paths_1;
    }

    if (memo.find(key_2) != memo.end()) {
      paths_2 = memo[key_2];
    } else {
      paths_2 =  FindPaths(i + 1, j);
      memo[key_2] = paths_2;
    }
    num_paths = paths_1 + paths_2;
  }
  return num_paths;
}

int main() {
  unsigned long long num_paths = FindPaths(0, 0);
  cout << "Number of paths possible is " << num_paths << "\n";
  return 0;
}
