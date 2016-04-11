#include <iostream>
#include <cmath>
#include <vector>

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
  int current_num = 2;

  prime_numbers.resize(10001);
  while (prime_num_counter != 10001) {
    if (TestPrime(current_num)) {
      // std::cout << "prime " << current_num << std::endl;
      ++prime_num_counter;
      prime_numbers[prime_num_counter - 1] = current_num;
    }
    ++current_num;
  }
  std::cout << "10001st prime is " << current_num - 1 << std::endl;
  return 0;
}
