#ifndef polynomial_hpp
#define polynomial_hpp


#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <sstream>
#include <initializer_list>
// #include <utility>


/*
 This is a class for creating instances of polynomials.

   - A polynomial (over the real numbers)
     is an expression of the following form.

     a_0 + a_1*x + a_2*x^2 + a_3*x^3 + ... + a_N*x^N

     Here, a_0, a_1, ..., a_N are real numbers.
     a_i is called the coefficient of x^i.

   - The degree of a polynomial is given by the highest power of x,
     i.e. the largest i such that a_i != 0.

   - For example,
       degree(1 + x^2) = 2
       degree(2*x + 3*x^3) = 3
       degree(4) = 0

     By convention, we say degree(0) = 0

   - Single terms like 5 * x^6 are called monomials.

     A polynomial where the coefficient of the highest power of x is 1
     is called a monic polynomial, e.g. 8 + x^2.

     Combining these bits of terminology, x^8 is an example of a monic monomial.


 We store the coefficients of a polynomial
 in member variable called coeff, a vector of doubles.

 coeff is carefully maintained so that
   - coeff.size() > 0
   - when coeff.size() > 1, coeff[coeff.size() - 1] != 0


 The default constructor creates the 0 polynomial, stored using the vector { 0 }.
 There's a constructor for making degree 0 polynomials from doubles.
 There's a constructor for making monic monomials.
 Finally, we can specify the coefficients using an initializer list.


 We can index the polynomial conveniently to access and update its coefficients.

 We have defined how to cast a polynomial to a size_t
 in such a way that this gives the degree of the polynomial.

 We have defined < and > to compare degrees.
 We have defined == and != to test for equality.
 We have prevented <= and >= from being used for comparison.

 We have defined how to evaluate a polynomial using a double.

 We have implemented all the usual arithmetic operations:
 + (unary and binary), - (unary and binary), *, /, %
 +=, -+, *=, /=, %=, ++ (pre and post), -- (pre and post).

 Finally, we have defined operator<<.
*/
class Polynomial {
public:
    Polynomial();                              // make the 0 polynomial
    Polynomial(double);                        // make a degree 0 polynomial
    explicit Polynomial(size_t);               // make a monic monomial
    Polynomial(std::initializer_list<double>); // specify coefficients a_0, a_1, a_2, ..., a_N
                                               // to construct a_0 + a_1*x + a_2*x^2 + ... + a_N*x^N

    double  operator[](size_t) const;  // access coefficients
    double& operator[](size_t);        // modify coefficients
    double  at        (size_t) const;  // access coefficients w/ index check
    double& at        (size_t);        // modify coefficients w/ index check

    operator size_t() const;           // degree(p)
    double operator()(double x) const; // evaluate p(x)

    Polynomial& operator++();   // ++p;
    Polynomial& operator--();   // --p;

    Polynomial operator++(int); // p++;
    Polynomial operator--(int); // p--;

    Polynomial operator+() const;
    Polynomial operator-() const;

    Polynomial& operator+=(const Polynomial&);
    Polynomial& operator-=(const Polynomial&);
    Polynomial& operator*=(const Polynomial&);
    Polynomial& operator/=(const Polynomial&);
    Polynomial& operator%=(const Polynomial&);

    std::string format_monomial(size_t i) const;

private:
    mutable std::vector<double> coeff;
    void delete_unnecessary_0s() const;

    friend Polynomial operator*(const Polynomial&, const Polynomial&);
    friend Polynomial operator/(      Polynomial , const Polynomial&);
};

bool operator< (const Polynomial&, const Polynomial&);
bool operator> (const Polynomial&, const Polynomial&);
bool operator==(const Polynomial&, const Polynomial&);
bool operator!=(const Polynomial&, const Polynomial&);

bool operator<=(const Polynomial&, const Polynomial&) = delete;
bool operator>=(const Polynomial&, const Polynomial&) = delete;

Polynomial operator+(      Polynomial , const Polynomial&);
Polynomial operator-(      Polynomial , const Polynomial&);
Polynomial operator*(const Polynomial&, const Polynomial&);
Polynomial operator/(      Polynomial , const Polynomial&);
Polynomial operator%(      Polynomial , const Polynomial&);

std::ostream& operator<<(std::ostream&, const Polynomial&);

#endif /* polynomial_hpp */
