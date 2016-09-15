#include <iostream>
#include <iterator>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
std::vector<int> prime_numbers;

void DispVector(vector<int> inp) {
  copy(inp.begin(), inp.end(), std::ostream_iterator<int>(cout, ","));
  cout << "\n";
}

// Prime number testing uses a global variable called prime_numbers that keeps
// the set of prime numbers looked at so far
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

int CountPrimeFactors(int n, vector<int> *prime_factors) {
  if (n==1 || n == 2 || n == 3)
    return 1;

  int sqrt_n = sqrt(n);
  for (auto prime_num : prime_numbers) {
    if (prime_num > n/2) {
      return prime_factors->size();
    }
    int inter = n;
    while (inter % prime_num == 0 && inter != 1) {
      prime_factors->push_back(prime_num);
      inter = inter/prime_num;
    }
  }
}

int Factorial(int n) {
  if (n < 0) {
    std::cerr << "Error! only positive numbers have factorials\n";
    return -1;
  }
  if (n == 0 || n == 1) {
    return 1;
  }
  return n * Factorial(n - 1);
}

vector<vector<int>> GetCombinations(vector<int> base, int r) {
  int n = base.size();
  std::vector<bool> v(n);
  std::fill(v.end() - r, v.end(), true);

  int num_combinations = Factorial(n) / (Factorial(n - r) * Factorial(r));
  vector<vector<int>> generated_combinations(num_combinations, std::vector<int>(r, 0));

  int across_combinations_count = 0;
  do {
    int within_combination_count = 0;
    for (int i = 0; i < n; ++i) {
      if (v[i]) {
        generated_combinations[across_combinations_count][within_combination_count] = base[i];
        std::cout << (i + 1) << " ";
        within_combination_count++;
      }
    }
    std::cout << "\n";
    across_combinations_count++;
  } while (std::next_permutation(v.begin(), v.end()));
}

int main() {
  int prime_num_counter = 0;
  int current_num = 2;

  prime_numbers.resize(10001);
  while (prime_num_counter != 100) {
    if (TestPrime(current_num)) {
      // std::cout << "prime " << current_num << std::endl;
      ++prime_num_counter;
      prime_numbers[prime_num_counter - 1] = current_num;
    } else {
      std::vector<int> prime_factors; 
      int count_pf = CountPrimeFactors(current_num, &prime_factors);
      std::cout << current_num << " has a prime factor count of "
                << count_pf << std::endl;
      std::cout << "Prime factors are : " << std::endl;
      DispVector(prime_factors);
    }
    ++current_num;
  }
  std::cout << "10001st prime is " << current_num - 1 << std::endl;
  return 0;
}
