#include "square.hpp"

using namespace std;




    int main() {
    
        Square s(3);
        s.set(2, 0) = 8;


    //    Square s(4);
    //    s.set(0, 0) = 1;
    //    s.set(1, 1) = 13;
    //    s.set(2, 2) = 11;
    //    s.set(3, 3) = 9;

        s.print();
        s.see_magic_potential();
        s.print();

        return 0;
    }

