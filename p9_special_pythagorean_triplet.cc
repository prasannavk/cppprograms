#include <iostream>

using std::cout;
using std::endl;

int main() {
  int a, b, c;
  for (a = 1; a < 1000; a++) {
    for (b = 1; b < 1000; b++) {
      for (c = 1; c < 1000; c++) {
        if (a*a + b*b == c*c && a+b+c == 1000) {
          cout << "found it !\n";
          cout << "a = " << a << endl;
          cout << "b = " << b << endl;
          cout << "c = " << c << endl;
          cout << "abc = " << a*b*c << endl;
          break;
        }
      }
    }
  }
  return 0;
}
