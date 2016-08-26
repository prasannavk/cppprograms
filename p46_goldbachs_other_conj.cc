#include <iostream>
#include <vector>
#include <cmath>

using std::cout;
using std::vector;

std::vector<int> prime_numbers;

int TestPrime(int n) {
  if (n==1 || n == 2 || n == 3)
    return 1;

  int sqrt_n = sqrt(n);
  for (auto prime_num : prime_numbers) {
    if (prime_num > sqrt_n) {
      // none of the prime numbers till sqrt of n is a factor of n
      return 1;
    }
    if (n % prime_num == 0) {
      return 0;
    }
  }

  for(int i = prime_numbers.back() + 1; i<= sqrt_n; i+=2) {
    // std::cout << "factor i " << i << " for num " << n;
    if((n % i)==0) {
      // std::cout << " succeeded " << std::endl;
      return 0;
    }
    // std::cout << " failed " << std::endl;
  }
  return 1;
}

int main() {
  int prime_num_counter = 0;
  int current_num = 3;

  std::cout << "prime 2" << std::endl;
  ++prime_num_counter;
  prime_numbers.push_back(2);
  while (1) {
    if (TestPrime(current_num)) {
      std::cout << "prime " << current_num << std::endl;
      ++prime_num_counter;
      prime_numbers.push_back(current_num);
    } else {
      // this number is composite
      std::cout << "composite " << current_num << std::endl;
      bool smallest_non_expressible_flag = true;
      for (auto prime_num : prime_numbers) {
        for (int i = 1;; ++i) {
          int sum = prime_num + 2*i*i;
          if (sum == current_num) {
            // the current odd composite number is expressible
            smallest_non_expressible_flag = false;
            break;
          } else if (sum > current_num) {
            break;
          }
        }
        if (smallest_non_expressible_flag == false) {
          // it is expressible - no need to search for more 
          break;
        }
      }
      if (smallest_non_expressible_flag == true) {
        cout << "Smallest number that is not expressible is " << current_num
             << std::endl;
        break;
      } else {
        cout << current_num << " is expressible\n";
      }
    }
    current_num += 2; 
  }
  return 0;
}
