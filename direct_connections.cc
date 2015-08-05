#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
struct City {
  long long int xcoord;
  long long int pi;
};

struct Block {
  int n;
  vector<City> cities; 
};

long long int GetAmountCable(const City &A, const City &B) {
  return std::max(A.pi, B.pi)*(std::abs(A.xcoord - B.xcoord)); 
}

long long int FindTotalCable(Block blk) {
  long long int total = 0;
  for (int i = 0; i < blk.n; ++i) {
    for (int j = i + 1; j < blk.n; ++j) {
      long long int cable_len = GetAmountCable(blk.cities[i], blk.cities[j]);
      total += cable_len;
    }
  }
  total %= 1000000007;
  return total;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int T = 0;
    cin >> T;
    vector<Block> blks(T);
    for (int i = 0; i < T; ++i) {
      Block b_new;
      // Each block contains 3 lines
      cin >> b_new.n;
      b_new.cities.resize(b_new.n);
      for (int j = 0; j < b_new.n; ++j) {
        City c_new;
        cin >> c_new.xcoord; 
        c_new.pi = 0;
        b_new.cities[j] = c_new;
      }
      for (int j = 0; j < b_new.n; ++j) {
        int pi;
        cin >> pi;
        b_new.cities[j].pi = pi;
      }
      blks[i] = b_new;
    }
  
    // Find amount of cable for each city for each block
    for (int i = 0; i < T; ++i) {
      long long int total_cable = FindTotalCable(blks[i]);
      cout << total_cable << endl;
    }
    
    
    return 0;
}

