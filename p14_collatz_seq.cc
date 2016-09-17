#include <iostream>
#include <map>
#include <limits>

using namespace std;
std::map<unsigned int, int> chain_map;

int FindCollatzChainLen(unsigned int num) {
  int len_chain = 0;
  if (num < 0) {
    cout << "No way in hell!\n";
    exit(0);
  }
  if (num == 1) {
    len_chain = 1;
  } else if (chain_map.find(num) != chain_map.end()) {
    len_chain = chain_map[num];
  } else if (num % 2 == 0) {
    len_chain = FindCollatzChainLen(num/2) + 1;
    chain_map[num] = len_chain;
  } else {
    len_chain = FindCollatzChainLen(3*num + 1) + 1;
    chain_map[num] = len_chain;
  }

  return len_chain;
}

int main() {
  int max = 0;
  unsigned int max_i = 0;
  for (int i = 1; i < 1000000; ++i) {
    int length_chain = FindCollatzChainLen(i);
    cout << i << " has " << length_chain << "\n";
    if (length_chain > max) {
      max = length_chain;
      max_i = i;
    }
  }
  cout << max_i << " has the longest CollatzChain of " << max << "\n";
  return 0;
}
