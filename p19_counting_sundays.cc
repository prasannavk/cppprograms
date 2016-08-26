#include <iostream>
#include <vector>

// Handling on the divisible by 4 case here. As the problem asks for years
// within a century, I handle the century years as special cases.
bool is_leap(int year) {
  if (year % 4 == 0) {
    return true;
  }
  return false;
}

int main() {
  std::vector<int> days_in_month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  enum class Month {
    JAN = 0,
    FEB,
    MAR,
    APR,
    MAY,
    JUN,
    JUL,
    AUG,
    SEP,
    OCT,
    NOV,
    DEC
  };

  enum class Day {
    SUNDAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
  };

  int sunday_on_1st = 0;
  // January 1, 1900 is given to be a Monday
  Day curr_day = Day::MONDAY; 

  // Preprocess to get from January 1, 1900 to
  // January 1, 1901.
  // Also, note that 1900 is a century year that is not divisible by 400.
  // So, it is not a leap year.
  // At the end of the loop, curr_day would have the day for January 1, 1901.
  for (int month = 0; month < 12; ++month) {
    int day_of_week_idx = (static_cast<int>(curr_day) + days_in_month[month]) % 7;  
    curr_day = static_cast<Day>(day_of_week_idx);
  }

  int day_of_1st_current = static_cast<int>(curr_day);
  if (day_of_1st_current == 0) {
    sunday_on_1st++;
  }

  // Now the meat of the function.
  for (int year = 1; year < 100; ++year) {
    for (int month = 0; month < 12; ++month) {
      int days_current_month = days_in_month[month];
      if (is_leap(year) && month == static_cast<int>(Month::FEB)) {
        days_current_month++;
      }
      day_of_1st_current = (day_of_1st_current + days_current_month)%7;
      if (day_of_1st_current == static_cast<int>(Day::SUNDAY)) {
        sunday_on_1st++;
      }
    }
  }


  // Post-processing
  // At this point, it has already counted whatever day Jan 1, 2000 is.
  // So, we should go until only 11 months to get to Dec 1, 2000.
  for (int month = 0; month < 11; ++month) {
    int days_current_month = days_in_month[month];
    if (month == static_cast<int>(Month::FEB)) {
      days_current_month++;
    }
    day_of_1st_current = (day_of_1st_current + days_current_month)%7;
    if (day_of_1st_current == static_cast<int>(Day::SUNDAY)) {
      sunday_on_1st++;
    }
  }

  std::cout << "Number of times sunday occurs in the first of the month "
    << "from Jan 1, 1901 to Dec 31, 2000 is " << sunday_on_1st << "\n";
  return 0;
}
