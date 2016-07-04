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
std::map<long long int, PrimeNumberFamily> canon_number_to_family;

struct Metadata {
  int repeating_digit;
  vector<int> index_list;
}; 

vector<vector<int>> Concatenate(vector<vector<int>> a, vector<vector<int>> b) {
  if (a.empty()) {
    return b;
  }
  if (b.empty()) {
    return a;
  }
  vector<vector<int>> c = a;
  for (auto vec_int : b) {
    vector<int> temp = vec_int;
    c.push_back(temp);
  }
  return c;
}

void DispVector(vector<long long int> inp) {
  copy(inp.begin(), inp.end(), std::ostream_iterator<long long int>(cout, ","));
  cout << "\n";
}
void DispVector(vector<int> inp) {
  copy(inp.begin(), inp.end(), std::ostream_iterator<int>(cout, ","));
  cout << "\n";
}

// returns a vector of combinations of input list. The combinations of nCk
// where n is size of the vector and k is the number of elements chosen from the vector.
vector<vector<int>> GenerateCombinations(vector<int> inp_list, int k) {
#ifdef DEBUG
  // Debug display list
  cout << "input to Generate Combinations\n";
  DispVector(inp_list);
#endif

  assert(k>=1);
  if (k == 1) {
    vector<vector<int>> temp;
    for (auto elem : inp_list) {
      vector<int> single_elem_list(1, elem);
      temp.push_back(single_elem_list);
    }
    return temp;
  }
  if (inp_list.size() == k) {
    vector<vector<int>> temp;
    temp.push_back(inp_list);
    return temp;
  }
  assert(inp_list.size() > k);
  int elem = inp_list[0];
  vector<int> elem_removed = inp_list;
  // You either pick elem 
  elem_removed.erase(std::remove(elem_removed.begin(), elem_removed.end(), elem), elem_removed.end());
#ifdef DEBUG
  cout << " removed element " << elem << "\n";
  DispVector(elem_removed);
#endif
  std::vector<std::vector<int>> elem_picked_combo = GenerateCombinations(elem_removed, k - 1);
#ifdef DEBUG
  cout << "Displaying the output of GenerateCombinations for k = " << k -1 << "\n";
#endif
  for (auto &single_combo : elem_picked_combo) {
#ifdef DEBUG
    cout << "Elem picked combo output: \n";
    DispVector(single_combo);
#endif
    single_combo.push_back(elem);
#ifdef DEBUG
    cout << "Elem picked combo output after elem push back: \n";
    DispVector(single_combo);
#endif
  }
  // Or you don't pick elem 
  vector<vector<int>> elem_ignored_combo = GenerateCombinations(elem_removed, k);
#ifdef DEBUG
  for (auto &single_combo : elem_ignored_combo) {
    cout << "Elem ignored combo output: \n";
    DispVector(single_combo);
  }
#endif
  return Concatenate(elem_picked_combo, elem_ignored_combo);
}


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
    int repeating_digit, vector<int> index_combo,
    long long int *canon_number);

void FindCanonNumbers(long long int prime_number,
    std::map<int, Metadata> digit_map,
    int repeating_digit, vector<long long int> *canon_numbers, vector<vector<int>> *index_combos) {
  // vector<vector<int>> index_combos;
  // including the full size of repetition list
  for (int i = 2; i <= digit_map[repeating_digit].index_list.size(); ++i) {
#ifdef DEBUG
    cout << "Displaying input index list:\n";
    DispVector(digit_map[repeating_digit].index_list);
#endif
    vector<vector<int>> temp = GenerateCombinations(digit_map[repeating_digit].index_list, i);
    for (auto &combo : temp) {
      // sort
      std::sort(combo.begin(), combo.end());
    }
#ifdef DEBUG
    cout << "Displaying all the combinations obtained from index list\n";
    for (auto combos : temp) {
      DispVector(combos);
    }
#endif
    *index_combos = Concatenate(*index_combos, temp);
  }
  int j = 0;
  for (auto index_combo : *index_combos) {
    long long int canon_number = 0;
#ifdef DEBUG
    cout << "find canon number for index_combo \n";
    DispVector(index_combo);
#endif
    FindCanonNumber(prime_number,
      digit_map, repeating_digit, index_combo, &canon_number);
#ifdef DEBUG
    cout << "Canon Number found is " << canon_number << "\n";
#endif
    (*canon_numbers)[j] = canon_number;
    j++;
  }
}

void FindCanonNumber(long long int prime_number,
    std::map<int, Metadata> digit_map,
    int repeating_digit, vector<int> index_combo,
    long long int *canon_number) {
  std::deque<int> canon_number_digit_queue;
#ifdef DEBUG
  cout << "Printing the repeating digit's index list \n";
  DispVector(digit_map[repeating_digit].index_list);
  cout << "Printing index combo\n";
  DispVector(index_combo);
#endif
  int digit_index = 1;
  while (prime_number != 0) {
    int digit = prime_number % 10;
    bool found = false;
    // for (auto ind : digit_map[repeating_digit].index_list) {
    //  if (digit_index == ind) {
        for (auto allowed_ind : index_combo) {
          if (digit_index == allowed_ind) {
            found = true;
            break;
          }
        }
    //  }
    //}
    if (found) {
      canon_number_digit_queue.push_front(1);
      //break;
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
  std::sort(index_combo.begin(), index_combo.end());
  // for (auto ind : digit_map[repeating_digit].index_list) {
  for (auto ind : index_combo) {
    *canon_number = (*canon_number)*10 + ind;
  }
}
inline int Factorial(int x) {
  return (x == 1 ? x : x * Factorial(x - 1));
}

void TestCombinations() {
  vector<vector<int>> out = GenerateCombinations({5, 7, 12, 13, 6, 203}, 3);
  for (auto vec : out) {
    for (auto elem : vec) {
      cout << elem << " ";
    }
    cout << "\n";
  }
}

int main() {
#if 1
  int prime_num_counter = 0;

  // std::cout << "prime 2" << std::endl;
  prime_numbers.push_back(2);
  long long int current_num = 3;

  long long int begin_number = 100000;
  long long int end_number = 999999;
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

            int num_repeating_digits = kv.second.index_list.size();
            // we could consider any k of the n digits repeating to be replaceable
            // nC2 + nC3 ..nCn --> number of canon_numbers
            int num_canon_numbers = 1;  // 1 is added for nCn that is accounted in the looping
            for (int k = 2; k < num_repeating_digits; ++k) {
              num_canon_numbers += Factorial(num_repeating_digits)/(Factorial(k)*Factorial(num_repeating_digits-k));
            }
            vector<long long int> canon_numbers(num_canon_numbers, 0);
            int repeating_digit = kv.first;
#if 0
            cout << repeating_digit << " has value " << "\n";
            copy(kv.second.index_list.begin(), kv.second.index_list.end(), std::ostream_iterator<int>(cout, ","));
            cout << "\n";
#endif
            vector<vector<int>> index_combos;
            // canon_numbers and index_combos are parallel vectors
            FindCanonNumbers(current_num, digit_map, repeating_digit, &canon_numbers, &index_combos);
            cout << "canon numbers found :\n";
            DispVector(canon_numbers);

            vector<int> indexes_of_repeating_digit = kv.second.index_list;

            int canon_number_idx = 0;
            for (auto canon_number : canon_numbers) {
              // make the map for canon number
              if (canon_number_to_family.find(canon_number) == canon_number_to_family.end()) {
#if 0
                cout << "Canon number " << canon_number << " not found. Adding new number\n";
#endif
                PrimeNumberFamily pfamily;
                pfamily.size = 1;
                pfamily.index_list = index_combos[canon_number_idx];  // indexes_of_repeating_digit;
                std::vector<long long int> initial_list;
                initial_list.push_back(current_num);
                pfamily.prime_family_list = initial_list;

                canon_number_to_family[canon_number] = pfamily;
              } else {
                PrimeNumberFamily &pfamily_ref = canon_number_to_family[canon_number];
                pfamily_ref.size++;
                // assuming that the same canon number would result from same indexes of repeating digit
                // asserting the same
#if 0
                cout << "current number is " << current_num << "\n";
                cout << "canon number is " << canon_number << "\n";
                cout << "current number's repeating digits indexes\n";
                copy(indexes_of_repeating_digit.begin(), indexes_of_repeating_digit.end(), std::ostream_iterator<int>(cout, ","));
                cout << "\nthe repeating indexes array in the map for similar numbers\n";
                copy(pfamily_ref.index_list.begin(), pfamily_ref.index_list.end(), std::ostream_iterator<int>(cout, ","));
                cout << "\nsimilar numbers are:\n";
                copy(pfamily_ref.prime_family_list.begin(), pfamily_ref.prime_family_list.end(), std::ostream_iterator<int>(cout, ","));
                cout << "\n";
#endif
                int i = 0;

                for (auto ind : index_combos[canon_number_idx]) {
                  if (ind != pfamily_ref.index_list[i]) {
                    cout << " ind " << ind << "\n";
                    cout << " pfamily_ref.index_list[i] " << pfamily_ref.index_list[i] << "\n";

                    cout << "current number is " << current_num << "\n";
                    cout << "canon number is " << canon_number << "\n";
                    cout << "current number's repeating digits indexes\n";
                    copy(indexes_of_repeating_digit.begin(), indexes_of_repeating_digit.end(), std::ostream_iterator<int>(cout, ","));
                    cout << "\nthe repeating indexes array in the map for similar numbers\n";
                    copy(pfamily_ref.index_list.begin(), pfamily_ref.index_list.end(), std::ostream_iterator<int>(cout, ","));
                    cout << "\nsimilar numbers are:\n";
                    copy(pfamily_ref.prime_family_list.begin(), pfamily_ref.prime_family_list.end(), std::ostream_iterator<int>(cout, ","));
                    cout << "\n";
                  }
                  assert(ind == pfamily_ref.index_list[i]);
                  ++i;
                }
                pfamily_ref.prime_family_list.push_back(current_num);
              }
              canon_number_idx++;
            }  // end of for loop for different canon numbers
          }
          // cout << "---------------------------\n";
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
   

#endif
  return 0;
}
