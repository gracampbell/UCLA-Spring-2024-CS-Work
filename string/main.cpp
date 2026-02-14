#include <iostream>
#include "string.hpp"
#include <utility>


basic::string f() {
    return basic::string("for moving");
}

const basic::string g() {
    return basic::string("for moving");
}


int main() {

    basic::string default_constructed;
    basic::string sl("string literal");
    basic::string eight_eights(8, '8');
    const basic::string c("const_ant");


    std::cout << default_constructed.size() << ' ';
    std::cout << sl.size()                  << ' ';
    std::cout << eight_eights.length()      << ' ';
    std::cout << c.length()                 << std::endl;


    sl[0] = 'S';
    sl[7] = 'L';
    std::cout << sl << ' ' << c[8] << std::endl << std::endl; // c[8] = '8';


    basic::string copy(sl);
    basic::string move(std::move(sl));
    std::cout << copy << ' ' << move << ' ' << sl.size() << std::endl << std::endl;


    copy = eight_eights;
    move = std::move(eight_eights);
    std::cout << copy << ' ' << move << ' ' << eight_eights << std::endl << std::endl;

    move = std::move(c); // can't 'move' a constant
    std::cout << move << ' ' << c << std::endl << std::endl;


    default_constructed = "string literal"; std::cout << default_constructed << std::endl << std::endl;
    default_constructed = '8';              std::cout << default_constructed << std::endl << std::endl;


    move = basic::string("for moving");
    std::cout << move << std::endl << std::endl;

    move = f();
    std::cout << move << std::endl << std::endl;

    move = g(); // it's bad to return a const value since it prevents 'moving'
    std::cout << move << std::endl << std::endl;

    move += copy; std::cout << std::endl;


    std::swap(move, copy); std::cout << std::endl;


    // std::swap is a templated function;
    // above, it executes as though it has the following definition...

    // void std::swap(basic::string& a, basic::string& b) {
    //     basic::string c(std::move(a));
    //     a = std::move(b);
    //     b = std::move(c);
    // }


    // By our definitions, this is the same as...

    // void std::swap(basic::string& a, basic::string& b) {
    //     basic::string c;
    //     std::swap(c.sz,  a.sz);
    //     std::swap(c.ptr, a.ptr);

    //     std::swap(a.sz,  b.sz);
    //     std::swap(a.ptr, b.ptr);

    //     std::swap(b.sz,  c.sz);
    //     std::swap(b.ptr, c.ptr);
    // }


    // Of course, it's a little less efficient
    // than our own basic::swap...

    basic::swap(move, copy);
    swap(move, copy);

    // The first function call is allowed because we wrote
    // void swap(string&, string&); outside the class interface,
    // but within the namespace.

    // The second relies on argument dependent lookup (ADL).
    // Because 'move' and 'copy' are instances of a class
    // belonging to the 'basic' namespace,
    // the compiler can deduce that basic::swap should be used
    // rather than std::swap.


    return 0;
}
