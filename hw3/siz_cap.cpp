#include <iostream>
#include <vector>

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

int main() {
    std::vector<int> v;
    int* ptr = v.data();             // store a copy of the underlying pointer;
    print_info(v, v.capacity());     // see that v has 0 size and capacity

    for (int i = 1; i <= 9; ++i) {
        v.push_back(i * 11);         // we'll push_back 11, 22, 33, ..., 88, 99

        if (ptr != v.data()) {
            std::cout << "there's been a memory reallocation" << std::endl;
            ptr = v.data();
        }
        print_info(v, v.capacity()); // fine since we use *(v.data() + i) instead of v[i]
    }
    return 0;
}
