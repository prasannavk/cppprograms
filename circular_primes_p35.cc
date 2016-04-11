#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <cmath>

using std::vector;
using std::deque;
std::map<long int, int> circular_primes_counts;
std::vector<long int> prime_numbers;

int TestPrime(long int n) {
  // if (n==1 || n == 2 || n == 3)
  //   return 1;

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

  for (int i = prime_numbers.back() + 1; i<= sqrt_n; i+=2) {
    // std::cout << "factor i " << i << " for num " << n;
    if ((n % i)==0) {
      // std::cout << " succeeded " << std::endl;
      return 0;
    }
    // std::cout << " failed " << std::endl;
  }
  return 1;
}

// GenerateRotations will not generate rotations of single
// digit numbers as themselves
vector<long int> GenerateRotations(long int prime_num) {
  vector<long int> rotated_nums;
  // generate a vector of digits in reverse order
  deque<int> digits;
  while (prime_num != 0) {
    digits.push_front(prime_num % 10);
    prime_num /= 10;
  }

  int num_digits = digits.size();
  for (int start_index = 1; start_index < num_digits; ++start_index) {
    int running_index = start_index;
    int current_num = 0;
    int ctr = 0;
    while (ctr < num_digits) {
      current_num = 10*current_num + digits[running_index];
      running_index = (running_index + 1) % num_digits;
      ctr++;
    }
    rotated_nums.push_back(current_num);
  }
  return rotated_nums;
}

int main() {
  // 100 to 999,999

  int upper_limit = 1e6;
#if 1
  prime_numbers.push_back(2);
  for (long int i = 3; i < upper_limit; i+=2) {
    if (TestPrime(i)) {
      // std::cout << "prime " << i << std::endl;
      prime_numbers.push_back(i);
      circular_primes_counts[i] = 1;
    }
  }

  int count = 0;
  for (auto prime_num : prime_numbers) {
    auto rotations = GenerateRotations(prime_num);
    bool is_any_rotation_nonprime = false;
    // all rotations of the digits have to be themselves prime
    for (auto rotated_num : rotations) {
      if (circular_primes_counts.find(rotated_num) == circular_primes_counts.end()) {
        // not found
        is_any_rotation_nonprime = true;
        break;
      }
    }
    if (is_any_rotation_nonprime == false) {
      count++;
    }
  }
  // 2, 3, 5, 7 are not counted as circular primes in the above count
  // Adding 4 to the count.
  std::cout << "The count is " << count << std::endl;
#endif
   
#if 0
  // unit test for GenerateRotations
  vector<long int> x = GenerateRotations(11);
  for (auto num : x) {
    std::cout << num << std::endl;
  }
#endif
  return 0;
}
