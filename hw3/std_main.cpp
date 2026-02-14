#include <iostream>
#include <vector>
#include <utility>




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
    std::cout << std::boolalpha;
    std::cout << "--------------------------------------------\n" << std::endl;




{
    std::cout << "CONSTRUCTORS\n" << std::endl;

    const std::vector<int> default_constructed;
    std::cout <<       "siz == " <<  default_constructed.size()          << ' ';
    std::cout <<      " cap == " <<  default_constructed.capacity()      << ' ';
    std::cout <<      " ptr == " <<  default_constructed.data()          << ' ';
    std::cout << "  empty() == " <<  default_constructed.empty()         << std::endl;

    const std::vector<int> size_t_constructed(18);
    std::cout <<       "siz == " <<  size_t_constructed.size()           << ' ';
    std::cout <<       "cap == " <<  size_t_constructed.capacity()       << ' ';
    std::cout <<    "ptr[8] == " <<  size_t_constructed[8]               << ' ';
    std::cout <<  " empty() == " <<  size_t_constructed.empty()          << std::endl;

    const std::vector<int> size_t_w_val_constructed(38, 48);
    std::cout <<       "siz == " <<  size_t_w_val_constructed.size()     << ' ';
    std::cout <<       "cap == " <<  size_t_w_val_constructed.capacity() << ' ';
    std::cout <<   "ptr[28] == " <<  size_t_w_val_constructed[28]        << std::endl;

    const std::vector<int> init_list_constructed {58, 68, 78, 88, 98, 108};
    std::cout <<       "siz == " <<  init_list_constructed.size()        << ' ';
    std::cout <<      " cap == " <<  init_list_constructed.capacity()    << ' ';
    std::cout <<   " ptr[3] == " <<  init_list_constructed[3]            << std::endl;
}


    std::cout << "\n--------------------------------------------\n\n";


{
    std::cout << "OPERATIONS NOT REQUIRING MEMORY REALLOCATION " << std::endl;
    std::cout << "pop_back, clear, reserve, push_back, resize\n" << std::endl;

    std::vector<int> v {0, 1, 2, 3, 4, 5, 6, 7};
    print_info(v, 8);  // siz == 8, cap == 8

    int* ptr = &v[0];  // store copy of v.ptr

    v.pop_back();      // siz == 7, cap == 8, ptr unchanged
    v.pop_back();      // siz == 6, cap == 8, ptr unchanged
    v.pop_back();      // siz == 5, cap == 8, ptr unchanged
    v.pop_back();      // siz == 4, cap == 8, ptr unchanged
    print_info(v, 8);  // no elements changed

    v.clear();         // siz == 0, cap == 8, ptr unchanged
    print_info(v, 8);  // no elements changed

    v.resize(3);       // siz == 3, cap == 8, ptr unchanged
    print_info(v, 8);  // updated first 3 elements to 0

    v.resize(5, 88);   // siz == 5, cap == 8, ptr unchanged
    print_info(v, 8);  // updated next 2 elements to 88

    v.resize(2, 888);  // siz == 2, cap == 8, ptr unchanged
    print_info(v, 8);  // no elements updated

    v.resize(0);       // siz == 0, cap == 8, ptr unchanged
    print_info(v, 8);  // no elements updated

    v.push_back(11);   // siz == 1, cap == 8, ptr unchanged
    v.push_back(22);   // siz == 2, cap == 8, ptr unchanged
    v.push_back(33);   // siz == 3, cap == 8, ptr unchanged
    print_info(v, 8);  // first 3 elements updated to 11, 22, 33, respectively

    v.reserve(4);      // nothing changes since cap == 8 >= 4
    print_info(v, 8);  // no elements updated

    v.resize(6);       // siz == 6, cap == 8, ptr unchanged
    print_info(v, 8);  // updated next 3 elements to 0

    if (ptr == &v[0]) {
        std::cout << "no memory reallocations so far" << std::endl;
    }
}


    std::cout << "\n--------------------------------------------\n\n";


{
    std::cout << "OPERATIONS REQUIRING MEMORY REALLOCATION" << std::endl;
    std::cout << "reserve, push_back, resize\n"             << std::endl;

    std::vector<int> v;
    print_info(v, 0);


    int* ptr = v.data();  // store copy of v.ptr


    for (int i = 1; i <= 7; ++i) {
        v.push_back(i * 11);

        if (ptr != &v[0]) {
            std::cout << "there's been a memory reallocation" << std::endl;
            ptr = &v[0];
        }
        print_info(v, v.capacity());
    }


    v.reserve(10);     // ptr changed, capacity set to 10

    if (ptr != &v[0]) {
        std::cout << "there's been a memory reallocation" << std::endl;
        ptr = &v[0];
    }
    print_info(v, 10); // first 7 values are copied, last 3 values are uninitialized


    v.resize(16, 8);   // capacity doubled on XCode

    if (ptr != &v[0]) {
        std::cout << "there's been a memory reallocation" << std::endl;
        ptr = &v[0];
    }
    print_info(v, 20); // first 7 values copied, next 9 are 8s, last 4 are uninitialized


    v.resize(24);      // capacity doubled on XCode

    if (ptr != &v[0]) {
        std::cout << "there's been a memory reallocation" << std::endl;
        ptr = &v[0];
    }
    print_info(v, 0);  // first 16 values copied, next 8 are 0s, last 16 are uninitialized


    v.resize(81);      // capacity set to 81 on XCode (since 81 > 2 * 40)

    if (ptr != &v[0]) {
        std::cout << "there's been a memory reallocation" << std::endl;
        ptr = &v[0];
    }
    print_info(v, 0);  // first 24 values copied, next 57 are 0
}


    std::cout << "--------------------------------------------\n\n";


{
    std::cout << "SWAP, MOVE, COPY\n" << std::endl;

    std::vector<int> v1 { 1,  2,  3,   };
    std::vector<int> v2 {11, 22, 33, 44};

    v1.reserve(5);
    v2.reserve(6);

    std::cout << "v1 info..." << std::endl;
    print_info(v1, v1.capacity());
    int *p1 = &v1[0];

    std::cout << "v2 info..." << std::endl;
    print_info(v2, v2.capacity());
    int *p2 = &v2[0];




    v1.swap(v2);

    std::cout << "v1 info..." << std::endl;
    print_info(v1, v1.capacity());

    std::cout << "v2 info..." << std::endl;
    print_info(v2, v2.capacity());

    if ((p1 == &v2[0]) && (p2 == &v1[0])) {
        std::cout << "v1 and v2's resources have been swapped" << std::endl;
    }

    v1.swap(v2);
    std::cout << "v1 and v2 have been swapped back\n" << std::endl;




    std::vector<int> v3(std::move(v1));

    std::cout << "v1 info..." << std::endl;
    print_info(v1, v1.capacity()); // now the empty vector

    std::cout << "v3 info..." << std::endl;
    print_info(v3, v3.capacity());

    if ((v1.data() == nullptr) && (&v3[0] == p1)) {
        std::cout << "v3 stole v1's resources\n" << std::endl;
    }




    v1 = std::move(v3);

    std::cout << "v1 info..." << std::endl;
    print_info(v1, v1.capacity());

    if (&v1[0] == p1) {
        std::cout << "v1 stole v3's resources back\n" << std::endl;
    }




    std::vector<int> v4(v1);

    std::cout << "v4 info..." << std::endl;
    print_info(v4, v4.capacity()); // v4.siz == v4.cap == v1.siz




    v4 = v2;

    std::cout << "v4 info..." << std::endl;
    print_info(v4, v4.capacity()); // v4.siz == v2.siz




    int* p4 = &v4[0];

    v4 = v4;
    if (p4 == &v4[0]) {
        std::cout << "self-assignment does not allocate memory" << std::endl;
    }
}


    return 0;
}
