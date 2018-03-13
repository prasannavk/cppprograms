#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  // number of test cases
  int num_test_cases;
  //scanf("%d", &num_test_cases);
  cin >> num_test_cases;

  vector<uint64_t> values;
  
  for (int i = 0; i < num_test_cases; ++i) {
    vector<int> cents_per_char(128, 0);
    char ch;
    int num_paid_chars = 0;
    cin >> num_paid_chars;
    for (int k = 0; k < num_paid_chars; ++k) {
      // cout << k << "\n";
      // scanf("%c %d", &ch, &(cents_per_char[(int)ch]));
      cin >> ch >> cents_per_char[(int)ch];
    }
    int num_lines = 0;
    cin >> num_lines;
    cin.ignore(1, '\n');
    uint64_t value_article = 0;
    for (int p = 0; p < num_lines; ++p) {
      string line_str;
      std::getline(std::cin, line_str);
      for (int j = 0; j < line_str.size(); ++j) {
        value_article += cents_per_char[(int)line_str[j]];
      }
    }
    values.push_back(value_article);
  }

  std::cout << std::fixed << std::showpoint;
  std::cout << std::setprecision(2);
  for (int i = 0; i < num_test_cases; ++i) {
    float value_in_dollars = static_cast<float>(values[i]) / 100.0;
    cout << value_in_dollars << "$\n";
  }
  return 0;
}
