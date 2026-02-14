#include "vector.hpp"









size_t my::vector::size()     const { return siz; }
size_t my::vector::capacity() const { return cap; }

bool my::vector::empty() const { return siz == 0; }


my::vector::vector() : siz(0), cap(0), ptr(nullptr) {}




my::vector::~vector() {
    delete[] ptr; 
}

const int&  my::vector::operator[](size_t i) const{
    return ptr[i];
}

int&  my::vector::operator[](size_t i){
    return ptr[i];
}

my::vector::vector(size_t n) : siz(n), cap(n), ptr(new int[n]) {}

my::vector::vector(size_t n, int num) : siz(n), cap(n), ptr(new int[n]) {
    for (size_t i = 0; i < n; ++i) {
        ptr[i] = num;
    }
}

my::vector::vector(std::initializer_list<int> inLi) : siz(inLi.size()), cap(inLi.size()), ptr(new int[inLi.size()]) {
    size_t i = 0;
    for (int num : inLi) {
        ptr[i++] = num;
    }
}


void my::vector::pop_back() { siz -= 1; }

void my::vector::clear() {
    siz = 0; 
}



void my::vector::reserve(size_t n) {
    if (n > cap) {
        new_capacity(n);
    }
}


void my::vector::push_back(int value) {
    if (siz == cap) {
            if (cap == 0) {
                new_capacity(1);
            } else {
                new_capacity(cap * 2);
            }
        }
        ptr[siz++] = value;
    }
    
    
    
    

void my::vector::resize(size_t n, int value) {
        if (n > cap) {
            size_t new_cap;
            if (cap * 2 >= n) {
                new_cap = cap * 2;
            } else {
                new_cap = n;
            }
            new_capacity(new_cap);
        }
        if (n > siz) {
            for (size_t i = siz; i < n; ++i) {
                ptr[i] = value;  // Only set new values if required
            }
        }
        siz = n;
    }


void my::vector::swap(vector& other) {
    std::swap(siz, other.siz);
    std::swap(cap, other.cap);
    std::swap(ptr, other.ptr);
    
}
    

my::vector::vector(vector&& other) : siz(other.siz), cap(other.cap), ptr(other.ptr) {
    other.siz = 0;
    other.cap = 0;
    other.ptr = nullptr;
}

my::vector& my::vector::operator=(vector&& other) {
    if (this != &other) {
        delete[] ptr;
        siz = other.siz;
        cap = other.cap;
        ptr = other.ptr;
        other.siz = 0;
        other.cap = 0;
        other.ptr = nullptr;
    }
    return *this;
}

my::vector::vector(const vector& other) : siz(other.siz), cap(other.siz), ptr(new int[other.siz]) {
    for (size_t i = 0; i < siz; ++i) {
        ptr[i] = other.ptr[i];
    }
}

my::vector& my::vector::operator=(const vector& other) {
    if (this != &other) {
        int* new_ptr = new int[other.cap];
        for (size_t i = 0; i < other.siz; ++i) {
            new_ptr[i] = other.ptr[i];
        }
        delete[] ptr;
        ptr = new_ptr;
        siz = other.siz;
        cap = other.siz;
    }
    return *this;
}







void my::vector::new_capacity(size_t n) {
    cap = n;
    int* new_ptr = new int[cap];

    for (size_t i = 0; i < siz; ++i) {
        new_ptr[i] = ptr[i];
    }
    delete[] ptr;

    ptr = new_ptr;
}




































































const int* my::vector::data() const { return ptr; }
      int* my::vector::data()       { return ptr; }


void my::swap(vector& v1, vector& v2) {
    v1.swap(v2);
}
