#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> MultiplyBigNum(const vector<int> &big_num, int multiplier) {
  int carry = 0;
  vector<int> result;
  for (int i = big_num.size() - 1; i >= 0; --i) {
    int intermediate = big_num[i] * multiplier + carry;
    int result_digit = intermediate % 10;
    result.push_back(result_digit);
    carry = intermediate / 10;
  }
  // convert the carry into individual digits.
  while (carry != 0) {
    int curr_digit = carry % 10;
    result.push_back(curr_digit);
    carry /= 10;
  }
  std::reverse(result.begin(), result.end());

  return result;
}

long long int FindSumDigits(int num) {
  vector<int> result;
  result.push_back(1);
  for (int i = 1; i <= num; ++i) {
    result = MultiplyBigNum(result, i);
  }

  long long int sum = 0;
  for (auto dig : result) {
    sum += dig;
  }
  return sum;
}

int main() {
  std::cout << FindSumDigits(10) << "\n";
  std::cout << FindSumDigits(100);

  return 0;
}
