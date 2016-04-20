#include <iostream>
#include <vector>
#include <deque>
#include <cmath>
#include <map>
#include <iterator>
#include <algorithm>
#include <cassert>
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

// index_list for say 83647 is [5,4,3,2,1] - it's the digit's place in a crazy ad-hoc format
bool IsDigitRepeating(long long int prime_number, std::map<int, Metadata> *digit_map) {
  bool is_repeated = false;
  int digit_index = 1;
  std::deque<int> canon_number_digit_queue;
  std::vector<int> actual_digit_vector;
  while (prime_number !=0) {
    int digit  = prime_number % 10;
    if (digit_map->find(digit) != digit_map->end()) {
      is_repeated = true;
      Metadata &digit_meta = (*digit_map)[digit];
      digit_meta.repeating_digit = digit;
      if (digit_meta.index_list.size()==1) {
        // if this is just the second occurrence of the repetition
        // need to go back and set the previous instance of this digit
        // to 1 as well
        // There have been digit_index - 1 digits that are in the canon_number_digit_queue.
        // 10007  
        int count_from_right = digit_meta.index_list[0];
        int index_to_update = canon_number_digit_queue.size() - count_from_right;
        canon_number_digit_queue[index_to_update] = 1;
      }
      digit_meta.index_list.push_back(digit_index);

      // TODO: Need to handle 2 different digits repeating
      canon_number_digit_queue.push_front(1);
    } else {
      Metadata digit_meta;
      digit_meta.repeating_digit = digit;
      vector<int> index_list_local;
      index_list_local.push_back(digit_index);
      digit_meta.index_list = index_list_local;
      (*digit_map)[digit] = digit_meta;

      canon_number_digit_queue.push_front(digit);
    }
    actual_digit_vector.push_back(digit);
    prime_number /= 10;
    digit_index++;
  }
  return is_repeated;
}

void FindCanonNumber(long long int prime_number,
    std::map<int, Metadata> digit_map,
    int repeating_digit, long long int *canon_number) {
  int digit_index = 1;
  std::deque<int> canon_number_digit_queue;
  while (prime_number != 0) {
    int digit = prime_number % 10;
    bool found = false;
    for (auto ind : digit_map[repeating_digit].index_list) {
      if (digit_index == ind) {
        found = true;
        break;
      }
    }
    if (found) {
      canon_number_digit_queue.push_front(1);
    } else {
      canon_number_digit_queue.push_front(digit);
    }
    prime_number /= 10;
    digit_index++;
  }

  // the canon_number_digit_queue's first element contains the highest power of
  // ten's coefficient.
  for (auto canon_digit: canon_number_digit_queue) {
    *canon_number = (*canon_number)*10 + canon_digit;
  }
  for (auto ind : digit_map[repeating_digit].index_list) {
    *canon_number = (*canon_number)*10 + ind;
  }
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
        if (IsDigitRepeating(current_num, &digit_map)) {
          cout << "Checking current number " << current_num << "\n";
          // There could be 2 digits repeating
          for (auto& kv : digit_map) {
            if (kv.second.index_list.size() < 2) {
              continue;
            }

            long long int canon_number = 0;
            int repeating_digit = kv.first;
            cout << repeating_digit << " has value " << "\n";
            copy(kv.second.index_list.begin(), kv.second.index_list.end(), std::ostream_iterator<int>(cout, ","));
            cout << "\n";
            FindCanonNumber(current_num, digit_map, repeating_digit, &canon_number);

            vector<int> indexes_of_repeating_digit = kv.second.index_list;
            // make the map for canon number
            if (canon_number_to_family.find(canon_number) == canon_number_to_family.end()) {
              cout << "Canon number " << canon_number << " not found. Adding new number\n";
              PrimeNumberFamily pfamily;
              pfamily.size = 1;
              pfamily.index_list = indexes_of_repeating_digit;
              std::vector<long long int> initial_list;
              initial_list.push_back(current_num);
              pfamily.prime_family_list = initial_list;

              canon_number_to_family[canon_number] = pfamily;
            } else {
              PrimeNumberFamily &pfamily_ref = canon_number_to_family[canon_number];
              pfamily_ref.size++;
              // assuming that the same canon number would result from same indexes of repeating digit
              // asserting the same
              cout << "current number is " << current_num << "\n";
              cout << "canon number is " << canon_number << "\n";
              cout << "current number's repeating digits indexes\n";
              copy(indexes_of_repeating_digit.begin(), indexes_of_repeating_digit.end(), std::ostream_iterator<int>(cout, ","));
              cout << "\nthe repeating indexes array in the map for similar numbers\n";
              copy(pfamily_ref.index_list.begin(), pfamily_ref.index_list.end(), std::ostream_iterator<int>(cout, ","));
              cout << "\nsimilar numbers are:\n";
              copy(pfamily_ref.prime_family_list.begin(), pfamily_ref.prime_family_list.end(), std::ostream_iterator<int>(cout, ","));
              cout << "\n";
              int i = 0;

              for (auto ind : indexes_of_repeating_digit) {
                assert(ind == pfamily_ref.index_list[i]);
                ++i;
              }
              pfamily_ref.prime_family_list.push_back(current_num);
            }
          }
          cout << "---------------------------\n";
        }
      }
    }
    current_num += 2; 
  }
  cout <<"-------------------------\n";
  for (auto kv : canon_number_to_family) {
    PrimeNumberFamily &pfamily_ref = kv.second;
    if (pfamily_ref.prime_family_list.size()  > 5) {
      cout << "canon number " << kv.first << " has list of size " << pfamily_ref.prime_family_list.size() << "\n";
      copy(pfamily_ref.prime_family_list.begin(), pfamily_ref.prime_family_list.end(), std::ostream_iterator<int>(cout, ","));
      cout << "\n";
    }
  }
   

  return 0;
}
