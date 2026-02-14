#include <iostream>
#include <utility>
#include "string.hpp"
#include <vector>




/*
 This struct is close to useless because it has no member variables.
 However, it will allow us to see the contexts in which
 certain operators and constructors are used.
*/
struct C {
    C()           { std::cout << "default constructor" << std::endl; }
    C(const C& p) { std::cout << "copy constructor"    << std::endl; }

    C& operator=(const C& p) { std::cout << "copy assignment" << std::endl; return *this; }

    ~C() { std::cout << "destructor" << std::endl; }
};

C returning_default_C() { return C(); }


/*
 This struct is close to useless because it has no member variables.
 However, it will allow us to see the contexts in which
 certain operators and constructors are used.

 It is different from C in that it has
 a move constructor and a move assignment operator.
*/
struct M {
    M()           { std::cout << "default constructor" << std::endl; }
    M(const M& p) { std::cout << "copy constructor"    << std::endl; }
    M(M&& p)      { std::cout << "move constructor"    << std::endl; }

    M& operator=(const M& p) { std::cout << "copy assignment" << std::endl; return *this; }
    M& operator=(M&& p)      { std::cout << "move assignment" << std::endl; return *this; }

    ~M() { std::cout << "destructor" << std::endl; }
};

M returning_default_M() { return M(); }




/*
 We'll use these later to show that returning a const value is bad.
*/
basic::string f() {
    return basic::string("for moving");
}
const basic::string g() {
    return basic::string("for moving");
}




int main() {
    /*
     RECALL
     In the previous snippets we discussed...

      - value categories: l-values and
        r-values (which consist of x-values and pr-values)

      - l-value references (&),
        the references you learned about ages ago.

        An l-value reference cannot bind to an r-value
        unless it is an l-value reference ***to const***.

      - r-value references (&&).

        An r-value reference can only bind to r-values.

      - std::move, which converts an l-value to an x-value.
    */




    /*
     WHY DO WE CARE?
      - The copy assignment operator and
        the copy constructor often involve copying heap data.
        For large containers this will be time-consuming.

      - An r-value is more temporary in nature than an l-value.
        Therefore, we would like to steal an r-value's data
        because this will be less time-consuming than copying it.

      - r-value references allow us to overload
        operator= and our constructors to
        respond to r-values more appropriately.

        This way, we can define
        move assignment and move construction
        in such a way that we avoid expensive copying,
        instead, stealing data.
    */




    /*
     OVERLOAD RESOLUTION EXAMPLE
     The following examples do not give useful move semantics
     (both of the structs involved have no member variables).
     However, the examples do demonstrate how various lines of code
     make use of the operators that we're interested in defining.

     The struct C only has copy construction and copy assignment defined,
     but M has move construction and move assignment defined as well.
    */

    C c0;                          std::cout << std::endl; // Default constructs c0.
    C c1(c0);                      std::cout << std::endl; // Copy constructs c1 using c0.
    c1 = c0;                       std::cout << std::endl; // Copy assignment used: c1.operator=(c0).
    c1 = C();                      std::cout << std::endl;
    /*
     The function call is c1.operator=(C()).
     Copy assignment - C::operator=(const C&) - is used.

     C() is a pr-value, but this is okay:
     the argument-to-parameter assignment is
         const C& p = C();
     and an l-value reference to const is allowed to bind to an r-value.
    */
    C c2 = returning_default_C();  std::cout << std::endl;
    /*
     This line looks like a copy needs to be made somewhere.
     However, compilers are clever and the C++ standard now demands
     that copy elision is performed whenever possible.

     In this case, copy elision takes place:
     the compiler sees that the function returns a default constructed C
     and that this value is used to initialize a new instance of C;
     it optimizes by default constructing c2.
    */
    std::swap(c1, c2);             std::cout << std::endl;
    /*
     std::swap and std::move are found in <utility> and
     std::swap makes use of the std::move function.

     The function call above executes the following code:
     {
         C c3(std::move(c1));
         c1 = std::move(c2);
         c2 = std::move(c3);
     }

     std::move(c1) is an x-value, hence an r-value, but
     the copy constructor C::C(const C&) is used first.
     The argument-to-parameter assignment is
         const C& p = std::move(c1);
     Again, this is okay because
     an l-value reference to const is allowed to bind to an r-value.

     After that, two copy assignments are used.
     std::move(c2) and std::move(c3) are x-values, hence r-values,
     but copy assignments are used similarly to when we investigated c1 = c0.
    */
    std::cout << std::endl;


    M m0;                          std::cout << std::endl; // Default constructs m0.
    M m1(m0);                      std::cout << std::endl; // Copy constructs m1 using m0.
    m1 = m0;                       std::cout << std::endl; // Copy assignment used: m1.operator=(m0).
    m1 = M();                      std::cout << std::endl;
    /*
     The line c1 = C(); executed in an unsatisfying way.
      - it default constructed an instance of C,
      - copied it to c1,
      - and then the original default constructed object was destroyed.

     For m1 = M(), the function call is m1.operator=(M()).
     We have two candidates:
      - copy assignment - M::operator=(const M&)
      - move assignment - M::operator=(M&&)

      - In the first case, the argument-to-parameter assignment would be
            const M& p = M();
      - In the second case, the argument-to-parameter assignment would be
            M&& p = M();

     Both are acceptable, but an r-value reference is a better fit for
     referencing an r-value, and so M::operator=(M&&) is used.

     The line m1 = M(); executes in a much more satisfying way:
      - it default constructs an instance of M,
      - m1 ***steals*** the data of this new instance of M,
      - the stolen-from object is destroyed.

     In a real-world example,
     such stealing would be much less costly than copying.
    */
    M m2 = returning_default_M();  std::cout << std::endl;
    /*
     Since returning_default_M() is a pr-value,
     one might hope for the previous line to use a move constructor.
     However, copy elision takes place: m2 is default constructed.

     Due to copy elision, it can seem difficult to find
     natural examples where a move constructor is used.
     However, std::swap provides a frequently occurring example...
    */
    std::swap(m1, m2);             std::cout << std::endl;
    /*
     The function call above executes the following code:
     {
         M m3(std::move(m1));
         m1 = std::move(m2);
         m2 = std::move(m3);
     }

     We have two candidates for executing M m3(std::move(m1));
      - copy constructor - M::M(const M&)
      - move constructor - M::M(M&&)

      - In the first case, the argument-to-parameter assignment would be
            const M& p = std::move(m1);
      - In the second case, the argument-to-parameter assignment would be
            M&& p = std::move(m1);

     Both are acceptable, but an r-value reference is a better fit for
     referencing an r-value, and so M::M(M&&) is used.

     After that, two move assignments are used.
     std::move(c2) and std::move(c3) are x-values, hence r-values,
     so M::operator=(M&&) is a better fit than M::operator=(const M&).
    */




    /*
     THINKING ABOUT std::move...
     The code involved in std::swap(m1, m2) gives a good way to think
     about lines involving std::move. std::move is giving permission
     to ruin the value of the object to which it is applied.

     M m3(std::move(m1)); // construct m3 using m1;
                          // allow stealing from m1;
                          // consequently, allow ruining m1's value.

     m1 = std::move(m2);  // assign to m1 using m2
                          // allow stealing from m2;
                          // consequently, allow ruining m2's value.

     m2 = std::move(m3);  // assign to m2 using m3
                          // allow stealing from m3;
                          // consequently, allow ruining m3's value.

     In the above three lines of code, we say
     "m1 is the moved-from object",
     "m2 is the moved-from object",
     "m3 is the moved-from object", respectively.

     When we write our move constructors and move assignment operators,
     we should adhere to the C++ convention:
     a moved-from object will always be kept in a valid state.

     If we write

     std::vector<int> v1(888);
     std::vector<int> v2(std::move(v1));

     the moved-from object v1 is guaranteed to be in valid state,
     that is, it is a valid std::vector<int>.
     This is to ensure that there are no problems
     when v1 goes out of scope and its destructor is called.
    */
    std::cout << std::endl;




    /*
     STRING EXAMPLE
     Now we've seen an abstract example
     showing how the function calls are resolved,
     we can see a more useful example
     where our move constructor and move assignment operator
     lead to more a more efficient class.
    */
    basic::string s1("str1");
    basic::string s2("STRING2");
    const basic::string c("const");


    basic::string copy(s1);
    basic::string move(std::move(s1));
    std::cout << copy << ' ' << move << ' ' << s1.size() << std::endl << std::endl;
    // The moved-from object s1 is storing the empty string.
    // Although it has been stolen from, it is in a valid state!


    copy = s2;
    move = std::move(s2);
    std::cout << copy << ' ' << move << ' ' << s2 << std::endl << std::endl;
    // The moved-from object s2 is storing move's old data.
    // Although it has been stolen from, it is in a valid state!

    // Note: it seems common for compilers to implement
    // std::string::operator=(std::string&&)
    // in such a way that the moved-from object is the empty string;
    // we have not done this for our basic::string::operator=(basic::string&&).


    move = std::move(c);
    std::cout << move << ' ' << c << std::endl << std::endl;
    // A const object cannot be moved-from
    // since that would violate 'const'.


    s1 = "test"; std::cout << s1 << std::endl << std::endl;
    s1 = 't';    std::cout << s1 << std::endl << std::endl;
    // basic::string::operator=(const char*) and basic::string::operator=(char)
    // implicitly make use of basic::string::operator=(basic::string&&).


    move = f();
    std::cout << move << std::endl << std::endl;
    // f() is a pr-value and so basic::string::operator=(basic::string&&) is used.

    move = g();
    std::cout << move << std::endl << std::endl;
    // g() returns a const value and so
    // basic::string::operator=(basic::string&&) cannot be used.
    // DO NOT RETRUN A CONST VALUE! Doing so prevents move semantics.


    std::cout << std::endl;


    return 0;
}




/*
 DEFAULT MOVE SEMANTICS
 We've now discussed the Big 5:
  - destructor
  - copy constructor
  - copy assignment
  - move constructor
  - move assignment

 Sometimes the compiler will provide some of these for free.
 For our Polynomial and Rational classes,
 the Big 5 we obtained for free did the correct things.
 This is why we didn't bother defining them.
 However, managing memory on the heap
 made it necessary to think about copying more carefully.

 Slide 137 of Mike Lindstrom's operator overloading slides
 shows that we lose move semantics as soon as we define
 any of the Big 5. Normally, rather than remembering his table,
 for every class I write, I either define 0 or all 5 of the Big 5:
  - 0 when not explicitly managing memory on the heap;
  - all 5 when explicitly managing memory on the heap.

 We understood what a compiler-generated copy constructor looks like.
 We should do the same for the rest of the Big 5.
 The struct com_big_5 demonstrates what a compiler generates for us.
*/

struct com_big_5 {
    int i;
    std::vector<int> v;

    com_big_5()                   : i(  0), v(  0) {}
    com_big_5(const com_big_5& m) : i(m.i), v(m.v) {}
    // Recall the compiler-generated copy constructor just copies each member variable.
    // Something we can say more explicitly now: m.v is an l-value,
    // so v(m.v) will use std::vector<int>'s copy constructor.

    // The compiler-generated copy assignment operator does something similar.
    com_big_5& operator=(const com_big_5& m) {
        i = m.i;            // i and m.i are fundamental types, so m.i will be copied.
        v = m.v;            // m.v is an l-value, so copy assignment will be used.
        return *this;
    }

    // The compiler-generated move assignment operator uses std::move in order
    // to make use of move assignment for its member variables of class-type.
    com_big_5& operator=(com_big_5&& m) {
        i = m.i;            // i and m.i are fundamental types, so m.i will be copied.
        v = std::move(m.v); // std::move(m.v) is an r-value, so move assignment will be used.
        return *this;
    }

    // Similarly, the compiler-generated move constructor uses std::move in order
    // to make use of move construction for its member variables of class-type.
    com_big_5(com_big_5&& m) : i(m.i), v(std::move(m.v)) {}

    // The compiler-generated destructor does not do anything.
    // The destructors for the member variables are called automatically.
    ~com_big_5() {}
};
