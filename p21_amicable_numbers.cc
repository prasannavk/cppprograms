#include <iostream>
#include <vector>
#include <set>
#include <cmath>

using std::vector;
using std::cout;
using std::set;

vector<int> FindDiv(int num) {
  vector<int> divisors;
  for (int i = 1; i <= num/2; ++i) {
    if (num % i == 0) {
      divisors.push_back(i);
    }
  }
  return divisors;
}

int TestAmicable(int first_num, set<int> &amicable_nums) {
  auto it = amicable_nums.find(first_num);
  if (it != amicable_nums.end()) {
    return first_num;
  }
  auto div_1 = FindDiv(first_num);
  int sum_1 = 0;
  for (auto i : div_1) {
    sum_1 += i;
  }
  if (sum_1 == first_num) {
    return 0;
  }
  int sum_2 = 0;
  auto div_2 = FindDiv(sum_1);
  
  for (auto i : div_2) {
    sum_2 += i;
  }
  if (sum_2 == first_num) {
    // found an amicable num
    amicable_nums.insert(first_num);
    amicable_nums.insert(sum_1);
    return first_num;
  } else {
    return 0;
  }
}

#if 0
int SumOfProperDivisors(int n) {
  int r = 0;
  int sum = 0;
  int f = 0;
  int step = 0;
  if (n == 1) {
    return 0;
  } else {
    r = floor(sqrt(n));
  }
  // first take into account for the case that n is a perfect square
  if (r*r == n) {
    sum = 1 + r;
    r = r - 1;
  } else {
    sum = 1;
  }
  if (n%2 == 1) {
    f = 3;
    step = 2;
  } else {
    f = 2;
    step = 1;
  }
  while (f <= r) {
    if (n % f == 0) {
      sum = sum + f + n/f;
      f = f + step;
    }
  }
  return sum;
}

int TestAmicableFast(int first_num) {
  int second_num = SumOfProperDivisors(first_num);
  if (second_num > first_num) {
    if (SumOfProperDivisors(second_num) == first_num) {
      return first_num + second_num;
    }
  }
  return 0;
}
#endif
int main(int argc, char *argv[]) {
#if 0
  vector<int> divisors = FindDiv(220);
  for (auto div : divisors) {
    cout << div << "\n";
  }
#endif

  set<int> amicable_nums;
  int sum = 0;
  for (int i = 2; i < 10000; ++i) {
    sum += TestAmicable(i, amicable_nums);
    // sum += TestAmicableFast(i);
  }
  cout << "sum is " << sum << "\n";
  return 0;
}
