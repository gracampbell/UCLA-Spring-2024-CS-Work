#include <iostream>
#include "rational.hpp"
int main() {
Rational sixth(1, 6);
std::cout << std::boolalpha;
std::cout << (sixth + sixth + sixth + sixth + sixth + sixth == Rational(1));
std::cout << std::endl;
return 0;
}
