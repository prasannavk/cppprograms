#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

int main() {
  int num_test_cases = 0;
  scanf("%d", &num_test_cases);

  vector<map<string, int>> test_cases;
  vector<int> total_per_test_case;
  for (int k = 0; k < num_test_cases; ++k) {
    scanf("\n");
    
    map<string, int> species_names;
    string species_name;
    int total_species = 0;
    while (std::getline(std::cin, species_name)) {
      if (species_name.empty()) {
          break;
      }
      if (species_names.find(species_name) != species_names.end()) {
        species_names[species_name] += 1;
      } else {
        species_names[species_name] = 1;
      }
      total_species++;
    }
    test_cases.push_back(species_names);
    total_per_test_case.push_back(total_species);
  }

  for (int k = 0; k < num_test_cases; ++k) {
    map<string, int> species_names = test_cases[k];
    for (auto name : species_names) {
      float percentage = (float)name.second * 100/total_per_test_case[k];
      std::cout << std::fixed << std::showpoint;
      std::cout << std::setprecision(4);
      cout << name.first << " "
           << percentage << "\n";
    }
    if (k != num_test_cases - 1) {
      cout << "\n";
    }
  }
  return 0;
}
