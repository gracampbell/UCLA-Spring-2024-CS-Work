#include "polynomial.hpp"

Polynomial::Polynomial()                                 : coeff(1,  0)    {               }
Polynomial::Polynomial(double a0)                        : coeff(1, a0)    {               }
Polynomial::Polynomial(size_t n)                         : coeff(n + 1, 0) { coeff[n] = 1; }
Polynomial::Polynomial(std::initializer_list<double> il) : coeff(il)       {
    if (coeff.size() == 0) {
        coeff.push_back(0);
    }
    delete_unnecessary_0s();
}
void Polynomial::delete_unnecessary_0s() const
{
    for (size_t len = coeff.size(); len > 1 && coeff[len - 1] == 0; --len) {
        coeff.pop_back();
    }
}

double Polynomial::operator[](size_t i) const {
    if (i >= coeff.size()) {
        return 0;
    }
    return coeff[i];
}
double& Polynomial::operator[](size_t i)       {
    if (i >= coeff.size()) {
        coeff.resize(i + 1);
    }
    return coeff[i];
}
double  Polynomial::at(size_t i) const { return coeff.at(i); }
double& Polynomial::at(size_t i)       { return coeff.at(i); }

Polynomial::operator size_t() const {
    // in case a user assigned 0 to coeff[coeff.size() - 1]
    delete_unnecessary_0s();
    return coeff.size() - 1;
}

bool operator<(const Polynomial& p1, const Polynomial& p2) {
    return static_cast<size_t>(p1) < static_cast<size_t>(p2);
}
bool operator>(const Polynomial& p1, const Polynomial& p2) {
    return p2 < p1;
}
bool operator==(const Polynomial& p1, const Polynomial& p2) {
    if (p1 < p2 || p2 < p1) {
        return false;
    }
    for (size_t i = 0, N = p1; i <= N; ++i) {
        if (p1[i] != p2[i]) {
            return false;
        }
    }
    return true;
}
bool operator!=(const Polynomial& p1, const Polynomial& p2) {
    return !(p1 == p2);
}

double Polynomial::operator()(double x) const {
    double poly_eval_at_x = 0;
    double x_to_the_i = 1;

    for (size_t i = 0, N = coeff.size(); i < N; ++i) {
        poly_eval_at_x += coeff[i] * x_to_the_i;
        x_to_the_i *= x;
    }

    return poly_eval_at_x;
}

Polynomial& Polynomial::operator++() {
    ++coeff[0];
    return *this;
}
Polynomial& Polynomial::operator--() {
    --coeff[0];
    return *this;
}
Polynomial Polynomial::operator++(int) {
    Polynomial pre_increment(*this); // using implicitly defined copy constructor
    ++(*this);
    return pre_increment;
}
Polynomial Polynomial::operator--(int) {
    Polynomial pre_decrement(*this); // using implicitly defined copy constructor
    --(*this);
    return pre_decrement;
}
Polynomial Polynomial::operator+() const {
    return *this;
}
Polynomial Polynomial::operator-() const {
    Polynomial copy(*this); // using implicitly defined copy constructor
    for (double& val : copy.coeff) { val *= -1; }
    return copy;
}

Polynomial& Polynomial::operator+=(const Polynomial& other) {
    const size_t N = other.coeff.size();

    if (coeff.size() < N) {
        coeff.resize(N);
    }

    for (size_t i = 0; i < N; ++i) {
        coeff[i] += other.coeff[i];
    }

    delete_unnecessary_0s();
    return *this;
}
Polynomial& Polynomial::operator-=(const Polynomial& other) {
    const size_t N = other.coeff.size();

    if (coeff.size() < N) {
        coeff.resize(N);
    }

    for (size_t i = 0; i < N; ++i) {
        coeff[i] -= other.coeff[i];
    }

    delete_unnecessary_0s();
    return *this;
}
Polynomial operator+(Polynomial p1, const Polynomial& p2) { return p1 += p2; }
Polynomial operator-(Polynomial p1, const Polynomial& p2) { return p1 -= p2; }

Polynomial operator*(const Polynomial& p1, const Polynomial& p2) {
    Polynomial p;

    // multiplication by 0 gives 0
    if (p1 == p || p2 == p) { return p; }

    const size_t degree_p1 = p1;
    const size_t degree_p2 = p2;

    // make space for a degree degree_p1 + degree_p2 polynomial
    p.coeff.resize(degree_p1 + degree_p2 + 1);

    for (size_t i = 0; i <= degree_p1; ++i) {
        for (size_t j = 0; j <= degree_p2; ++j) {
            p.coeff[i + j] += p1.coeff[i] * p2.coeff[j];
            // could write p[i + j] += p1[i] * p2[j],
            // but what's written avoids a few function calls
        }
    }
    p.delete_unnecessary_0s();
    // this is necessary because pow(2, -538)
    // is a non-zero double that squares to give 0;
    // one can think of this as cleanup for rounding errors

    return p;
}
Polynomial operator/(Polynomial f, const Polynomial& g) {
    Polynomial aux;

    // cannot divide by 0
    assert(g != aux);

    const size_t degree_f = f;
    const size_t degree_g = g;

    // dividing by a polynomial of larger degree gives 0
    if (degree_f < degree_g) { return aux; }

    //   if f(x) = a_M x^M + ... and
    //      g(x) = b_N x^N + ...,
    // then we store (a_M / b_N) x^{M-N}
    aux.coeff.resize(degree_f - degree_g + 1);
    aux.coeff[degree_f - degree_g] = f.coeff[degree_f] / g.coeff[degree_g];

    // when degree_f == degree_g, (a_M / b_N) is the answer
    if (degree_f == degree_g) { return aux; }

    // otherwise, subtracting aux * g from f should lower the degree
    f -= aux * g;

    // however, there could be rounding errors
    f[degree_f] = 0;
    f.delete_unnecessary_0s();

    // we can now calculate the division recursively
    // (this trick is known as the "division algorithm")
    return aux + f / g;
}
Polynomial& Polynomial::operator*=(const Polynomial& other) { return *this = *this * other; }
Polynomial& Polynomial::operator/=(const Polynomial& other) { return *this = *this / other; }

Polynomial& Polynomial::operator%=(const Polynomial& other) {
    *this -= (*this / other) * other;

    // there could be rounding errors
    for (size_t i = other, N = *this; i <= N; ++i) {
        coeff[i] = 0;
    }
    delete_unnecessary_0s();

    return *this;
}
Polynomial operator%(Polynomial p1, const Polynomial& p2) { return p1 %= p2; }

std::string Polynomial::format_monomial(size_t i) const {
    std::ostringstream formatted;
    double coeff_i = coeff[i];

    if (coeff_i < 0) { coeff_i *= -1;
                       formatted << "- "; }
    else             { formatted << "+ "; }

    if            (i == 0) { formatted << coeff_i;         }
    else if (coeff_i != 1) { formatted << coeff_i << "*";  }

    if (i > 0) { formatted << "x";      }
    if (i > 1) { formatted << "^" << i; }

    return formatted.str();
}

std::ostream& operator<<(std::ostream& out, const Polynomial& p) {
    const size_t degree = p;


    if (degree == 0) {
        if (p[0] >= 0) {
            out << "(+ " << +p[0] << ')';
        }
        else {
            out << "(- " << -p[0] << ')';
        }
        return out;
    }


    size_t i = 0;

    while (p[i] == 0) { ++i; }
    out << '(' << p.format_monomial(i);

    while (++i <= degree) {
        if (p[i] != 0) {
            out << ' ' << p.format_monomial(i);
        }
    }
    out << ')';


    return out;
}
