#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <iterator>
#include <algorithm>
using std::cout;
using std::vector;

std::vector<long long int> prime_numbers;
std::vector<long long int> other_prime_list;

// this is the prime number family we are looking for. It has to be of size 8.
struct PrimeNumberFamily {
  int size;
  vector<int> index_list;
  vector<long long int> prime_family_list;
};

// a canon number is the repeated digits replaced with 1
std::map<int, PrimeNumberFamily> canon_number_to_family;

// this is the map from index numbers of a k-digit number to a list of prime
// numbers that have the same indexes repeated
std::map<int, vector<long long int> > indexes_to_prime_numbers;

struct Metadata {
  int repeating_digit;
  vector<int> index_list;
}; 

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

// index_list for say 83647 is 54321 - it's the digit's place in a crazy ad-hoc format
bool IsDigitRepeating(long long int prime_number, std::map<int, Metadata> *digit_map, long long int *canon_number) { 
  bool is_repeated = false;
  int digit_index = 1;
  canon_number = 0;
  while (prime_number !=0) {
    int digit  = prime_number % 10;
    if (digit_map->find(digit) != digit_map->end()) {
      is_repeated = true;
      Metadata &digit_meta = (*digit_map)[digit];
      digit_meta.repeating_digit = digit;
      digit_meta.index_list.push_back(digit_index);

      // TODO: Need to handle 2 different digits repeating
      canon_number = canon_number*10 + 1;
    } else {
      Metadata digit_meta;
      digit_meta.repeating_digit = digit;
      vector<int> index_list_local;
      index_list_local.push_back(digit_index);
      digit_meta.index_list = index_list_local;
      (*digit_map)[digit] = digit_meta;

      canon_number = canon_number*10 + digit;
    }
    prime_number /= 10;
    digit_index++;
  }
  return is_repeated;
}

int main() {
  int prime_num_counter = 0;

  // std::cout << "prime 2" << std::endl;
  prime_numbers.push_back(2);
  long long int current_num = 3;

  long long int begin_number = 10000;
  long long int end_number = 99999; 
  long int max = 2;
  while (current_num < end_number) {
    if (TestPrime(current_num)) {
      // std::cout << "prime " << current_num << std::endl;
      prime_numbers.push_back(current_num);
      if (current_num > begin_number && current_num < end_number) {
        other_prime_list.push_back(current_num);
        std::map<int, Metadata> digit_map;
        long long int canon_number = 0;
        if (IsDigitRepeating(current_num, &digit_map, &canon_number)) {
          cout << current_num << "\n";
          // There could be 2 digits repeating
          for (auto& kv : digit_map) {
            cout << kv.first << " has value " << "\n";
            copy(kv.second.index_list.begin(), kv.second.index_list.end(), std::ostream_iterator<int>(cout, ","));
            cout << "\n";
          
            int indexes_as_single_num = 0;
            vector<int> indexes_of_repeating_digit = kv.second.index_list;
            for (auto index : indexes_of_repeating_digit) {
              indexes_as_single_num = indexes_as_single_num*10 + index;
            }
            if (indexes_to_prime_numbers.find(indexes_as_single_num) == indexes_to_prime_numbers.end()) {
              std::vector<long long int> temp_vec;
              temp_vec.push_back(current_num);
              indexes_to_prime_numbers[indexes_as_single_num] = temp_vec;
            } else {
              std::vector<long long int> &prime_num_vec = indexes_to_prime_numbers[indexes_as_single_num];
              prime_num_vec.push_back(current_num);
            }

            // make the map for canon number
            if (canon_number_to_family.find(canon_number) == canon_number_to_family.end()) {
              PrimeNumberFamily pfamily;

              canon_number_to_family[canon_number] = temp;
            } else {
            }


          }
        }
      }
    }
    current_num += 2; 
  }
  cout <<"-------------------------\n";
  for (auto kv : indexes_to_prime_numbers) {
    cout << kv.first << " has prime_number list size " << kv.second.size() << "\n";
#if 0
    if (kv.first == 23) {
      cout << "\n";
      copy(kv.second.begin(), kv.second.end(), std::ostream_iterator<int>(cout, ","));
      cout << "\n"; 
    }
#endif
  }
   

  return 0;
}
