#include <iostream>
#include "polynomial.hpp"

int main() {
    // CONSTRUCTORS
    Polynomial zero;
    Polynomial degree0(8.8);
    Polynomial monic_monial(static_cast<size_t>(8));
    Polynomial more_interesting {6, -5, 1};

    std::cout << zero             << ' ';
    std::cout << degree0          << ' ';
    std::cout << monic_monial     << ' ';
    std::cout << more_interesting << ' ';
    std::cout << std::endl;


    // operator[] AND at
    std::cout << more_interesting[1] << ' ';

    more_interesting[1] = 5;
    std::cout << more_interesting << std::endl;


    std::cout << more_interesting.at(1) << ' ';

    more_interesting.at(1) = -5;
    std::cout << more_interesting << std::endl;

    // more_interesting.at(3);


    // const Polynomial p {1, 2, 3, 4};
    // p[0] = 5;     std::cout << p << ' ';
    // p.at(0) = 6;  std::cout << p << std::endl;


    // operator size_t()
    std::cout << static_cast<size_t>(zero)             << ' ';
    std::cout << static_cast<size_t>(degree0)          << ' ';
    std::cout << static_cast<size_t>(monic_monial)     << ' ';
    std::cout << static_cast<size_t>(more_interesting) << ' ';
    std::cout << std::endl;


    // Leftovers
    more_interesting[4] = 8;
    std::cout << more_interesting << std::endl;

    more_interesting[4] = 0;
    std::cout << more_interesting << ' ' << static_cast<size_t>(more_interesting) << std::endl;


    // <, >, ==, !=
    std::cout << std::boolalpha;
    std::cout << (more_interesting < monic_monial) << ' ';
    std::cout << (zero != degree0)                 << ' ';
    std::cout << (more_interesting > monic_monial) << ' ';
    std::cout << (zero == degree0)                 << ' ';
    std::cout << std::endl;

    // more_interesting <= monic_monial;


    // operator()
    std::cout << more_interesting(2) << ' ';
    std::cout << more_interesting(3) << ' ';
    std::cout << more_interesting(4) << ' ';
    std::cout << std::endl << std::endl;
    // 2 and 3 are the roots of more_interesting
    // more_interesting(4) == 6 - 5 * 4 + 4^2 == 6 - 20 + 16 == 2


    // +, -, *, /, %
    Polynomial p1 {-4, 0, -2, 1};
    Polynomial p2 {-3, 1};

    std::cout << p1 << " + " << p2 << " = " << p1 + p2 << std::endl;
    std::cout << p1 << " - " << p2 << " = " << p1 - p2 << std::endl;
    std::cout << p1 << " * " << p2 << " = " << p1 * p2 << std::endl;
    std::cout << p1 << " / " << p2 << " = " << p1 / p2 << std::endl;
    std::cout << p1 << " % " << p2 << " = " << p1 % p2 << std::endl;
    std::cout << std::endl;


    // COMPARISON WITH THE common_operations_with_ints SNIPPET
    Polynomial a(8.0);
    Polynomial b(2.0);

    Polynomial& r1 = (a *= b);
    Polynomial& r2 = (a += b);
    Polynomial& r3 = (a /= b);
    Polynomial& r4 = (a -= b);
    Polynomial& r5 = ++a;
    std::cout << r1 << ' ' << r2 << ' ' << r3 << ' ' << r4 << ' ' << r5 << std::endl;

    Polynomial& r6 = --a;
    std::cout << r1 << ' ' << r2 << ' ' << r3 << ' ' << r4 << ' ' << r5 << ' ' << r6 << std::endl;

    Polynomial v1 = a++; std::cout << v1 << ' ' << a << std::endl;
    Polynomial v2 = a--; std::cout << v2 << ' ' << a << std::endl;

    std::cout << -a << ' ' << a << ' ' << +a << ' ' << a << std::endl;

    Polynomial c(8.0);
    Polynomial d(-3.0);
    std::cout <<  c + d << ' ' << c - d << ' ' << c * d << ' ' << c / d  << std::endl << std::endl;

    std::cout << std::boolalpha;
    std::cout << (c == c) << ' ' << (c == d) << std::endl;
    std::cout << (c != c) << ' ' << (c != d) << std::endl;
    std::cout << (c <  c) << ' ' << (c <  d) << std::endl;
    std::cout << (c >  c) << ' ' << (c >  d) << std::endl;
    // std::cout << (c <= c) << ' ' << (c <= d) << std::endl;
    // std::cout << (c >= c) << ' ' << (c >= d) << std::endl;
    std::cout << std::endl;


    return 0;
}
