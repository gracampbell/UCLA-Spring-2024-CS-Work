#include "rational.hpp"
#include <iostream>
#include <cassert>
using namespace std;



Rational::Rational()                   : num(   0), den(   1) {}
Rational::Rational(int _num)           : num(_num), den(   1) {}
Rational::Rational(int _num, int _den) : num(_num), den(_den) {
    assert(den != 0);
    make_den_pos();
    simplify();
}

/**
This member function makes sure that
the denominator of a rational number is positive,
a convenient choice.
*/
void Rational::make_den_pos() {
    if (den < 0) {
        num *= -1;
        den *= -1;
    }
}

/**
This member function simplifies a rational number.
It does so by computing the highest common factor
of the numerator and denominator and dividing
the numerator and denominator by it.

To compute the highest common factor,
the Euclidean algorithm is used.
Do not worry if you don't know the Euclidean algorithm.
*/
void Rational::simplify() {
    int a = abs(num);
    int b = abs(den);

    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    num /= a;
    den /= a;
}


std::ostream& operator<<(std::ostream& out, const Rational& r) {
    
    if (r.den == 1) {
        out << r.num ;
    }
    else
        out << r.num << '/' << r.den ;
    
    return out;
    
}




std::istream& operator>>(std::istream& in, Rational& r) {
    int num;
    int den;

    char forwardslash;

    in >> num >> forwardslash >> den;

    if (forwardslash != '/') {
        in.setstate(std::ios_base::failbit);
    }
    if (in) {
        r = Rational(num, den);
    }

    return in;
}


Rational& Rational::operator+=(const Rational& other) {
    num = num * other.den + den * other.num;
    den *= other.den;
    simplify(); 
    return *this;
}

Rational& Rational::operator-=(const Rational& other) {
    num = num * other.den - den * other.num;
    den *= other.den;
    simplify();
    return *this;
}

Rational& Rational::operator*=(const Rational& other) {
    num *= other.num;
    den *= other.den;
    simplify();
    return *this;
}

Rational& Rational::operator/=(const Rational& other) {
    assert(den!=0 && other.num !=0);
    num *= other.den;
    den *= other.num;
    simplify();
    return *this;
}

Rational operator+(Rational r1, const Rational& r2) {
    return r1+=r2;
}

Rational operator-(Rational r1, const Rational& r2) {
    return r1-=r2;
}

Rational operator*(Rational r1, const Rational& r2){
    return r1*=r2;
}

Rational operator/(Rational r1, const Rational& r2){
    return r1/=r2;
}


bool operator ==(const Rational& r1,const Rational& r2) {
    return (r1.num * r2.den == r1.den * r2.num);
}

bool operator <(const Rational& r1,const Rational& r2) {
    return (r1.num * r2.den < r1.den * r2.num);
    
}

bool operator!=(const Rational& r1, const Rational& r2) {
    return !(r1 == r2);
}
           
bool operator >(const Rational& r1, const Rational& r2){
    return r2 < r1;
}

bool operator<=(const Rational& r1, const Rational& r2){
    return !(r2 < r1);
}


bool operator>=(const Rational& r1, const Rational& r2){
    return !(r1 < r2);
}


Rational::operator double() const {
    return static_cast<double>(num) / static_cast<double>(den);
}
