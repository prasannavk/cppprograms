#include <iostream>
#include <iterator>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
std::vector<int> prime_numbers;

void DispVector(vector<int> inp) {
  copy(inp.begin(), inp.end(), std::ostream_iterator<int>(cout, ","));
  cout << "\n";
}

// Prime number testing uses a global variable called prime_numbers that keeps
// the set of prime numbers looked at so far
int TestPrime(long int n) {
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

int ComputePrimeFactors(long int n, vector<int> *prime_factors, int *num_unique_prime_factors) {
  if (n==1 || n == 2 || n == 3)
    return 1;

  *num_unique_prime_factors = 0;
  int sqrt_n = sqrt(n);
  for (auto prime_num : prime_numbers) {
    if (prime_num > n/2) {
      return prime_factors->size();
    }
    int inter = n;
    if (inter % prime_num == 0) {
      (*num_unique_prime_factors)++;
    }
    while (inter % prime_num == 0 && inter != 1) {
      prime_factors->push_back(prime_num);
      inter = inter/prime_num;
    }
  }
}

long long int Factorial(int n) {
  if (n < 0) {
    std::cerr << "Error! only positive numbers have factorials\n";
    return -1;
  }
  if (n == 0 || n == 1) {
    return 1;
  }
  return static_cast<long long int>(n) * Factorial(n - 1);
}

vector<vector<int>> GetCombinations(vector<int> base, int r) {
  int n = base.size();
  //cout << "r " << r << "\n";
  //cout << "n " << n << "\n";
  std::vector<bool> v(n);
  std::fill(v.end() - r, v.end(), true);

  long long int numerator = 1;
  for (int i = 0; i < r; ++i) {
    numerator *= (n-i);
  }
  //cout << "numerator " << numerator << "\n";
  long long int denominator = Factorial(r);
  //cout << "denominator " << denominator << "\n";
  int num_combinations = numerator/denominator;
  vector<vector<int>> generated_combinations(num_combinations, vector<int>(r, 0));

  // Debug
  // cout << "num_combinations " << num_combinations << "\n";
  //cout << "r " << r << "\n";
  //cout << "n " << n << "\n";
  // cout << "Factorial(n) " << Factorial(n) << "\n";
  // cout << "Factorial(n - r) " << Factorial(n - r) << "\n";
  // cout << "Factorial(r) " << Factorial(r) << "\n";

  int across_combinations_count = 0;
  do {
    int within_combination_count = 0;
    for (int i = 0; i < n; ++i) {
      if (v[i]) {
        // cout << "within_combination_count " << within_combination_count << "\n";
        generated_combinations[across_combinations_count][within_combination_count] = base[i];
        // std::cout << base[i] << " ";
        within_combination_count++;
        
      }
    }
    // std::cout << "\n";
    // std::cout << "updating across_combinations_count to " << across_combinations_count + 1 << "\n";
    across_combinations_count++;
  } while (std::next_permutation(v.begin(), v.end()));
  return generated_combinations;
}
int current_tri_index = 3;
int current_tri_num = 6;

void UpdateCurrentTriNum() {
  current_tri_index++;
  current_tri_num = (current_tri_index * (current_tri_index + 1)) / 2;
}

bool CheckTriangleNum(int current_num) {
  // cout << "current_tri_index " << current_tri_index << "\n";
  // cout << "current_num " << current_num << "\n";
  if (current_num == current_tri_num) {
    UpdateCurrentTriNum();
    return true;
  }
  return false;
}

int main() {
  int prime_num_counter = 0;
  // long int current_num = 6;
  long int current_num = 2;
  prime_numbers.resize(100001);
  TestPrime(current_num);
  prime_num_counter++;
  prime_numbers[prime_num_counter - 1] = current_num;
  current_num++;
  TestPrime(current_num);
  prime_num_counter++;
  prime_numbers[prime_num_counter - 1] = current_num;
  current_num = 5;
  TestPrime(current_num);
  prime_num_counter++;
  prime_numbers[prime_num_counter - 1] = current_num;
  current_num = 6;

  // loop through current_num to figure out the first number that has greater than 500 divisors
  while (prime_num_counter != 100000) {
    int num_divisors = 0;
    if (TestPrime(current_num)) {
      // std::cout << "prime " << current_num << std::endl;
      ++prime_num_counter;
      prime_numbers[prime_num_counter - 1] = current_num;
    } else {
      
      if (!CheckTriangleNum(current_num)) {
        ++current_num;
        continue;
      }
      /*
      if (current_num < 1000) {
        ++current_num;
        continue;
      }
      */
      
      std::vector<int> prime_factors; 
      int num_unique_prime_factors = 0;
      int count_pf = ComputePrimeFactors(current_num, &prime_factors, &num_unique_prime_factors);
      // std::cout << current_num << " has a prime factor count of "
      //           << count_pf << std::endl;
      // std::cout << "Prime factors for " << current_num << " are : " << std::endl;
      // DispVector(prime_factors);
      if (prime_factors.size() == 1) {
        std::cout << "Current number is not a prime number and has only one extra factor\n";
        ++current_num;
        continue;
      }
      num_divisors = num_unique_prime_factors + 2;
      for (int r = 2; r <= prime_factors.size(); ++r) {
        vector<vector<int>> n_choose_r = GetCombinations(prime_factors, r);
        // cout << "ok done computing the combinations\n";
        // cout << "size of n_choose_r is " << n_choose_r.size() << "\n";
        // map for duplicate product removal
        std::map<int, int> pdcts_encountered;
        // cout << "Non prime divisors for " << current_num << "\n";
        for (auto combination : n_choose_r) {
          int pdct = 1;
          for (auto combination_elem : combination) {
            // cout << combination_elem << " ";
            pdct *= combination_elem;
          }
          if (pdcts_encountered.find(pdct) != pdcts_encountered.end()) {
            // so pdct was already computed. don't count it as a divisor again.
            continue;
          }
          if (pdct < current_num) {
            pdcts_encountered[pdct] = 1;
            ++num_divisors;
            // printing out divisor
            // cout << pdct << " ";
          }
        }
        // cout << "\n";
      }
      if (num_divisors > 100) {
        std::cout << "Num divisors of " << current_num << " is " << num_divisors << "\n";
      }
      if (num_divisors > 500) {
        break;
      }
    }
    ++current_num;
  }
  // std::cout << "10001st prime is " << current_num - 1 << std::endl;
  return 0;
}
