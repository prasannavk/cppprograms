#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

void GenerateFibo() {
  long int t_n1 = 1;
  long int t_n2 = 1;

  long long int even_sum = 0;
  for (int i = 0; ; ++i) {
    long int fibo_new_term = t_n1 + t_n2;
    // cout << fibo_new_term<< endl;
    if (fibo_new_term > 4e6) {
      break;
    }
    if (fibo_new_term % 2 == 0) {
      even_sum += fibo_new_term;
    }
    t_n1 = t_n2;
    t_n2 = fibo_new_term;
  }
  cout << "Even sum is " << even_sum << endl;
}

int main() {
  GenerateFibo();
  return 0;
}
