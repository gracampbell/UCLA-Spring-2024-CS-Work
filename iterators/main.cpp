#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <initializer_list>




// For later...
struct reverse {
    int* p;

    reverse(int* _p) : p(_p) {}

    operator int*()       {      return p;     }
    reverse& operator++() { --p; return *this; }
};

struct const_reverse {
    const int* p;

    const_reverse(const int* _p) : p(_p) {}

    operator const int*()       {      return p;     }
    const_reverse& operator++() { --p; return *this; }
};


// For later...
struct v_wrap {
    std::vector<int> v;

    v_wrap(std::vector<int> _v)           : v(std::move(_v)) {}
    v_wrap(std::initializer_list<int> il) : v(il)            {}

          int* begin()       { return v.data();            }
    const int* begin() const { return v.data();            }
          int* end()         { return v.data() + v.size(); }
    const int* end()   const { return v.data() + v.size(); }

          reverse rbegin()       { return       reverse(v.data() + v.size() - 1); }
    const_reverse rbegin() const { return const_reverse(v.data() + v.size() - 1); }
          reverse rend()         { return       reverse(v.data()            - 1); }
    const_reverse rend()   const { return const_reverse(v.data()            - 1); }
};




int main() {
{
    /*
     'auto'

     In the discussion which follows,
     we'll need a new keyword: 'auto'.

     The 'auto' keyword is used for declarations.
     It automatically detects the return type of
     the right-hand side of the initializing expression.

      - We won't think about how 'auto' interacts with &&.

      - Unless we add the & symbol,
        'auto' will not make a reference.

      - For non-references, unless we type 'const',
        'auto' will not make a 'const' type.

      - 'auto'-deduced references will be reference to const
         - when we type 'const' or
         - when the variable being assigned from is marked 'const'.
    */
    int        v   = 0;    // value
    int&       r   = v;    // reference
    const int  c_v = 0;    // const value
    const int& r_c = v;    // reference to const


    auto        v1 = r;    // int
    auto&       r1 = v;    // int&

    const auto  v2 = r;    // const int
    const auto& r2 = v;    // const int&

    auto        v3 = c_v;  // int
    auto&       r3 = c_v;  // const int&

    auto        v4 = r_c;  // int
    auto&       r4 = r_c;  // const int&


    std::cout << v1 << v2 << v3 << v4 << r1 << r2 << r3 << r4 << std::endl;
}
{
    /*
     RANGE-BASED FOR LOOPS
     Iterators are like pointers,
     but often have less functionality.

     A good motivation for iterators is that
     they enable range-based for loops, so
     let's talk about range-based for loops.

     Here's a common example...
    */
    std::vector<int> v {1, 2, 3, 4, 5, 6, 7, 8};

    for (int val : v) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    /*
     What's the generic syntax for a range-based for loop?

     for ([const] type [&] el : container) {
         loop body
     }

     The type should be the same as the elements of the container (**).
     [const] and [&] indicate that 'const' and '&' are optional.

     The range-based for loop is an abbreviation for the follow code (*).

     {
         auto end = container.end();

         for (auto it = container.begin(); it != end; ++it) {
             [const] type [&] el = *it;

             loop body
         }
     }

     In the case of the example, we obtain the following equivalent code.
    */
{
    auto end = v.end();

    for (auto it = v.begin(); it != end; ++it) {
        int val = *it;
        std::cout << val << ' ';
    }
}
    std::cout << std::endl;
}
{
    /*
     ITERATORS
     Now that we've seen how a range-based for loop is executed,
     there are some natural questions:
      - what's the type of 'it', v.begin(), and v.end()?
      - why can we use operator!=, operator++, and operator*?
    */

    // For a std::vector<int>,
    // the return type of the member functions begin and end is
    // std::vector<int>::iterator.
    std::vector<int> v {1, 2};
    std::vector<int>::iterator beg_v = v.begin();
    std::vector<int>::iterator end_v = v.end();

    // There's an operator
    // bool operator!=(std::vector<int>::iterator, std::vector<int>::iterator)
    std::cout << std::boolalpha;
    std::cout << (beg_v != beg_v) << std::endl;
    std::cout << (beg_v != end_v) << std::endl;

    // There are also operators
    // int& std::vector<int>::iterator::operator*() and
    // std::vector<int>::iterator& std::vector<int>::iterator::operator++()
    std::vector<int>::iterator it = beg_v;
    *it = 8; ++it;
    *it = 9; ++it;

    it = beg_v;
    std::cout << *it << std::endl; ++it;
    std::cout << *it << std::endl; ++it;

    // By this point we have seen that
    // v.begin() is like a pointer to the start of the vector and
    // v.end() is like a pointer just beyond the last element of the vector
    std::cout << (it != end_v) << std::endl;
    // std::cout << *it           << std::endl;

    // Just like we have pointers to const,
    // we have const_iterators.
    const std::vector<int> c_v {1, 2};
    std::vector<int>::const_iterator beg_c_v = c_v.begin();
    std::vector<int>::const_iterator end_c_v = c_v.end();

    // When dereferenced, we cannot make assignments.
    // *beg_c_v = 0;
    // *end_c_v = 1;

    std::cout << *beg_c_v << ' ' << *(--end_c_v) << std::endl;

    /*
     We've seen the most basic functionality of
     std::vector<int>::iterator and std::vector<int>::const_iterator.
     In 10B, this will be the functionality we care about most since it
     enables range-based for loops.

     However, std::vector<int>::iterators have much more functionality.
     They're called random-access iterators. You can read more here...
     https://www.cplusplus.com/reference/iterator/RandomAccessIterator/
     In addition to what we already noted,
     you'll find the following are supported:
      - comparison operators: ==, <, >, <=, >=,
      - pointer arithmetic: post ++, pre and post --, +=, -=, +, -
      - offset dereference operator [], dereferencing and member access ->
    */
    std::vector<std::string> v_s = { "Hello", "bye bye" };
    std::cout << (v_s.begin() + 2 == v_s.end()) << std::endl;
    std::cout <<  v_s.begin()->size()           << std::endl;
}
{
    /*
     REVERSE ITERATORS
     We also have reverse iterators,
     so that we can easily loop through containers backwards.
    */
    std::vector<int>         v {1, 2, 4, 8};
    const std::vector<int> c_v {1, 2, 4, 8};

    for (auto it = v.begin(), end = v.end(); it != end; ++it) {
        int val = *it;
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    for (auto it = v.rbegin(), end = v.rend(); it != end; ++it) {
        int val = *it;
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    std::vector<int>::reverse_iterator         v_beg_r =   v.rbegin();
    std::vector<int>::reverse_iterator         v_end_r =   v.rend();
    std::vector<int>::const_reverse_iterator c_v_beg_r = c_v.rbegin();
    std::vector<int>::const_reverse_iterator c_v_end_r = c_v.rend();

    std::cout <<   *v_beg_r << ' ' <<   *(--v_end_r) << std::endl;
    std::cout << *c_v_beg_r << ' ' << *(--c_v_end_r) << std::endl;
}
{
    /*
     OUR OWN ITERATORS
     For a range-based for loop to work,
     we have have to define member functions
     begin and end which return a type for which
     operator!=, operator++, and operator* make sense.

     The shortest example I can provide is given by v_wrap.
     v_wrap wraps a std::vector<int>. In this case,
     we can be really lazy and have begin and end
     return the appropriate int*s.

     To make rbegin and rend work, we have to return a different type.
     I've defined reverse and const_reverse as quickly as possible.
     We've inheritted many operations from int* and const int*
     by defining the appropriate conversion operators.
     We've then defined ++ so that it does -- on the underlying pointer.
     This is very hacky and not very good:
     as it stands, it = it + 1; undoes ++it;

     Overall, by being lazy, we've provided more functionality than
     we should. For example, we can print our iterators,
     whereas one cannot print a std::vector<int>::iterator.

     Before we handle things better, we should learn about nested classes.
    */
    v_wrap v {1, 2, 3, 4, 5, 6};

    for (int i : v) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    for (auto it = v.rbegin(), end = v.rend(); it != end; ++it) {
        int val = *it;
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    auto it = v.rbegin();
    ++it; it = it + 1;
    std::cout << (it == v.rbegin()) << std::endl;
    std::cout <<  it                << std::endl;
}
    /*
     WHY NOT jUST USE POINTERS?
     std::vectors store their data contiguously,
     so pointer arithmetic gives us all we need
     to iterate through std::vectors.

     However, we will study linked lists and binary search trees.
     These data structures will not store their data contiguously
     and so iteration is a more complicated procedure. For this
     reason, it makes sense to define a class to do the work for us.
    */
    return 0;
}


/*
 (*) In order to be completely correct...

 When the container in a range-based for loop is a C-style array
 the range-based for loop will be parsed as follows...

 {
     type* end = container + sizeof(container) / sizeof(type);

     for (type* p = container; p != end; ++p) {
        [const] type [&] el = *p;

        loop body
     }
 }

 When the container in a range-based for loop
 does not have member functions begin and end,
 but suitable free functions are available,
 the range-based for loop will be parsed as follows...

 {
     auto stop = end(container);

     for (auto it = begin(container); it != stop; ++it) {
         [const] type [&] el = *it;

         loop body
     }
 }


 (**) Due to optimizations that are made
      in the implementation of std::vector<bool>
      it is surprisingly difficult to edit
      the elements in a std::vector of bools
      using a range-based for loop.

      std::vector<bool> v{0};
      for (auto&& b : v) {
          b = 1;
      }
      std::cout << v[0] << std::endl;

      You have to wait until PIC 10C to understand this!
*/
