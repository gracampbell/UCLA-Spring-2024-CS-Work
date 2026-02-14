/*
  In this HW, I do not mind what the copy assignment operator does to the capacity of the assigned-to vector.
  In particular, if v1 = v2 always results in v1.size() == v1.capacity(), that is totally fine.
  If you want to handle v1 = v2 in the way that this code demonstrates, that is also fine.
*/

#include <iostream>
#include <vector>
#include "vector.hpp"

void print_info(const std::vector<int>& v, size_t N) {
    std::cout << "             size: " << v.size()     << '\n';
    std::cout << "         capacity: " << v.capacity() << '\n';

    if (N < 10) { std::cout << ' '; }

    std::cout << "first " << N << " elements: ";

    for (size_t i = 0; i < N; ++i) {
        std::cout << *(v.data() + i) << ' ';
    }
    std::cout << '\n' << std::endl;
}

void print_info(const my::vector& v, size_t N) {
    std::cout << "             size: " << v.size()     << '\n';
    std::cout << "         capacity: " << v.capacity() << '\n';

    if (N < 10) { std::cout << ' '; }

    std::cout << "first " << N << " elements: ";

    for (size_t i = 0; i < N; ++i) {
        std::cout << *(v.data() + i) << ' ';
    }
    std::cout << '\n' << std::endl;
}

int main() {
{
    std::vector<int> v1(8);
    v1.reserve(888);

    std::vector<int> v2(v1);
    print_info(v2, v2.capacity());
}
{
    my::vector v1(8);
    v1.reserve(888);

    my::vector v2(v1);
    print_info(v2, v2.capacity());
}
{
    std::vector<int> v1(8);
    std::vector<int> v2;

    v1.reserve(888);
    v2.reserve(88);

    v2 = v1;
    print_info(v2, 8);
}
{
    my::vector v1(8);
    my::vector v2;

    v1.reserve(888);
    v2.reserve(88);

    v2 = v1;
    print_info(v2, 8);
}
    return 0;
}
