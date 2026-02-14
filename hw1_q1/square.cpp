
#include "square.hpp"
#include <vector>
#include <unordered_set>
#include <iostream>

using namespace std;

// constructor (1)

Square::Square(size_t n)
: size (n), data (n * n, 0), magic_total(n * (n * n + 1) / 2) {}



// definition (2)
const unsigned int& Square::get(size_t i, size_t j) const {
    return data [i * size + j ];
}

//definition (3)
unsigned int& Square::set(size_t i, size_t j) {
    return data [i * size + j ];
    }

// definition (4)
void Square::print() const {
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            unsigned int numAtLoc = get(i, j);
            if (numAtLoc == 0) {
                cout << "* " ;
            }
            else {
                cout << numAtLoc << " ";
            }
        }
        cout <<endl;
    }
    cout <<endl;
}

//definition (5)
bool Square::is_magic() const {

    unordered_set<unsigned int> set;
    for (unsigned int g : data) {
        if (g !=0) {
            
            set.insert(g);
        }
    }
    
    if (set.size()!= size * size) {
        return false;
    }
   
      for (size_t i = 0; i < size; ++i) {
          unsigned int rTotal = 0;
          for (size_t j = 0; j < size; ++j) {
              rTotal += get(i, j);
          }
          if (rTotal != magic_total) {
              return false;
          }
      }

      for (size_t j = 0; j < size; ++j) {
          unsigned int cTotal = 0;
          for (size_t i = 0; i < size; ++i) {
              cTotal += get(i, j);
          }
          if (cTotal != magic_total) {
              return false;
          }
      }

     
      unsigned int oneDTotal = 0;
      for (size_t i = 0; i < size; ++i) {
          oneDTotal += get(i, i);
      }
    
      
      unsigned int twoDTotal = 0;
      for (size_t i = 0; i < size; ++i) {
          twoDTotal += get(i, size - 1 - i);
      }
    return oneDTotal == magic_total && twoDTotal == magic_total;
     
}


//definition (6)
bool Square::row_has_magic_total(size_t row) const {
  
    unsigned int total = 0;
    for (size_t j = 0; j < size; ++j) {
        total += get(row, j);
    }
    return total == magic_total;
}


//definititon(7)
void Square::see_magic_potential() {
    unordered_set<unsigned int> used_up;
    for (unsigned int el : data) {
        if (el != 0) {
            used_up.insert(el);
        }
    }
    help_see_magic_potential(used_up, 0);
    
}

//definition(8)
  

void Square::help_see_magic_potential(unordered_set<unsigned int>& used_up, size_t slots_considered) {
      if (slots_considered == data.size()) {
          if (is_magic()) {
              print();
          }
          return;
      }

      if (data[slots_considered] != 0) {
          help_see_magic_potential(used_up, slots_considered + 1);
          return;
      }

      for (unsigned int num = 1; num <= size * size; ++num) {
          if (!used_up.contains(num)) {
                  data[slots_considered] = num;
                  used_up.insert(num);
                  help_see_magic_potential(used_up, slots_considered + 1);
                  used_up.erase(num);
                  data[slots_considered] = 0;
              }
          }
  
  }








