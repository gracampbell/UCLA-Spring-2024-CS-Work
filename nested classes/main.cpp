#include <iostream>


class Outer1 {                                             // define Outer1
public:
    void print_private_member() const {
        std::cout << private_member << std::endl;
    }
    struct Inner1 {                                        // define Outer1::Inner1 a 'member class' of Outer1
        void increment_private_member_of(Outer1& inst) const {
            ++inst.private_member;
        }
    };
    // friend Inner1;                                      // this is done by default
private:
    int private_member = 0;                                // okay to use (private) member variables
                                                           // in the interface before their declaration
};


class Outer2 {
private:
    struct Inner2 {                                        // define Outer2::Inner2
        void greeting() const {
            std::cout << "I'm a public member function ";
            std::cout << "of a private class (1)" << std::endl;
        }
    };
public:
    Inner2 get_default_inner() const {                     // not okay to use Inner2 before the declaration of Inner2
        return Inner2();                                   // not okay to use Inner2() before the definition of Inner2
    }
};


int main() {
    Outer1 a;
    Outer1::Inner1 b;                                      // to access Inner1, we need to use the scoping operator
    b.increment_private_member_of(a);                      // Inner1 is automatically granted friendship by Outer1
    a.print_private_member();

    // Outer2::Inner2 c = Outer2().get_default_inner();    // not allowed since Inner2 is a private member of Outer2
    auto d = Outer2().get_default_inner();                 // however, 'auto' can get past this restriction
    d.greeting();

    return 0;
}


// We can rewrite Outer2 and Inner2::Outer2
// separating declarations and definitions differently.

class Outer3 {                                             // define Outer3
private:
    struct Inner3;                                         // declare Outer3::Inner3
public:
    Inner3 get_default_inner() const;                      // declare Outer3::get_default_inner after Inner3 declaration
};

struct Outer3::Inner3 {                                    // define Outer3::Inner3
    void greeting() const;                                 // declare Outer3::Inner3::greeting
};

Outer3::Inner3 Outer3::get_default_inner() const {         // define Outer3::get_default_inner
    return Inner3();  // scoping not necessary             // must occur after definition of Outer3::Inner3
}

void Outer3::Inner3::greeting() const {                    // define Outer3::Inner3::greeting
    std::cout << "I'm a public member function ";
    std::cout << "of a private class (2)" << std::endl;
}
