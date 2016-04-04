// This program is taken from exceptional c++ by Herb Sutter.
//

#include <iostream>
#include <complex>
using namespace std;

class Base {
 public:
  virtual void f(int);
  virtual void f(double);
  virtual void g(int i = 10);
};

void Base::f(int) {
  cout << "Base::f(int)" << endl;
}

void Base::f(double) {
  cout << "Base::f(double)" << endl;
}

void Base::g(int i ) {
  cout << i << endl;
}

class Derived : public Base {
 public:
  void f(complex<double>);
  void g(int i = 20);
};

// Derived::f does not overload Base::f, it hides them
// => Base::f(int) and Base::f(double) are not visible in the scope
void Derived::f(complex<double>) {
  cout << "Derived::f(complex)" << endl;
}

void Derived::g(int i) {
  cout << "Derived::g() " << i << endl;
}

int main() {
  Base b;
  Derived d;
  Base *pb = new Derived;
  b.f(1.0);
  d.f(1.0);
  // This is special because there is no function in the derived class
  // use for f except f(complex<double>). f(complex<double>) is not a virtual
  // function though. So, the overload resolution is done on the static type
  // (here Base) not the dynamic type (here Derived)
  pb->f(1.0);

  b.g();
  d.g();
  pb->g();
  delete pb;

  return 0;
}
