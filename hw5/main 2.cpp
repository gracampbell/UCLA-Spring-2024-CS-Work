#include <iostream>
#include "bst.hpp"


int main() {

    Tree t;
    t.insert("Red");
    t.insert("Orange");
    t.insert("Yellow");
    t.insert("Green");
    t.insert("Blue");
    t.insert("Indigo");
    t.insert("Violet");

    for (size_t i = 0; i < 8; ++i) {
        for (const std::string& val : t) { std::cout << val << ' '; }
        std::cout << std::endl;

        t.erase(t.begin());
    }


    Tree for_explaining_inc;

    for_explaining_inc.insert("i");
    for_explaining_inc.insert("h");
    for_explaining_inc.insert("g");
    for_explaining_inc.insert("a");
    for_explaining_inc.insert("f");
    for_explaining_inc.insert("e");
    for_explaining_inc.insert("d");
    for_explaining_inc.insert("b");
    for_explaining_inc.insert("c");
    for_explaining_inc.insert("o");
    for_explaining_inc.insert("j");
    for_explaining_inc.insert("k");
    for_explaining_inc.insert("l");
    for_explaining_inc.insert("n");
    for_explaining_inc.insert("m");
    for_explaining_inc.insert("q");
    for_explaining_inc.insert("p");

    for (const std::string& val : for_explaining_inc) { std::cout << val << ' '; }
    std::cout << std::endl;

    {
        auto it = for_explaining_inc.end();
        auto begin = for_explaining_inc.begin();

        while (it != begin) {
            --it;
            std::cout << *it << ' ';
        }
        std::cout << std::endl;
    }

    /*
     Because of how we loop in reverse,
     the value of --for_explaining_inc.begin()
     does not matter.

     You should not worry yourself about this
     when solving the homework: just let it be
     Tree::iterator(this, nullptr).
    */

    return 0;
}
