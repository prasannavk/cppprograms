#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;
// This class is not a general implementation of BigInteger.
// It is very specific to solve the problem. So, it has only multiply with
// single digit number and summing of digits.
class BigInteger {
 public:
  BigInteger() {
    big_integer_ = {1};
  }
  BigInteger(const vector<int> &in) {
    big_integer_ = in;
  }
  // for now assume x is a single digit decimal number 
  vector<int> multiply(int x); 
  void Display() {
   for (auto a : big_integer_){
     cout << a;
   }
   cout << "\n";
  }

  int sum_digits() {
    int sum = 0;
    for (auto digit : big_integer_) {
      sum += digit;
    }
    return sum;
  }

 private:
  // The digits are stored as: most significant corresponds to index 0, least
  // significant corresponds to index N - 1
  std::vector<int> big_integer_;
};

vector<int> BigInteger::multiply(int x) {
  vector<int> result;
  int carry = 0;
  for (int i = big_integer_.size() - 1; i >= 0; --i) {
    int digit_multiply_result = big_integer_[i] * x;
    // cout << digit_multiply_result << endl;
    int current = digit_multiply_result % 10 + carry; 
    carry = digit_multiply_result / 10;
    // cout << "carry " << carry << endl; 
    result.push_back(current);
  }
  if (carry > 0) {
    result.push_back(carry);
  }

  std::reverse(std::begin(result), std::end(result));
  // cout << "size of result is " << result.size() << endl;
  big_integer_ = result;
  return result;
}

int main() {
  BigInteger power_of_2;
  power_of_2.Display();
  for (int i = 0; i < 1000; ++i) {
    power_of_2.multiply(2);
  }
  power_of_2.Display();
  cout << "\n\n";
  cout << "Sum of digits is " << power_of_2.sum_digits();
  return 0;
}
