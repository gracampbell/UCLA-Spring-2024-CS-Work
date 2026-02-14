#ifndef square_hpp
#define square_hpp

#include <iostream>
#include <vector>
#include <unordered_set>

class Square {
public:
    Square(size_t n);

    const unsigned int&  get(size_t i, size_t j) const;
    unsigned int& set(size_t i, size_t j);

    void print() const;

    bool is_magic() const;
    void see_magic_potential(); // tries its best to be const

private:
    const size_t size;
    std::vector<unsigned int> data;
    const unsigned int magic_total;

    bool row_has_magic_total(size_t row) const;

    /**
     This is a function to help accomplish the goal of see_magic_potential.


     To implement see_magic_potential,
     we'll look at the positions in the square one-by-one,
     possibly placing values within them, left-to-right, top-to-bottom.
     We'll refer to these positions as "slots".

     For faster lookup, we'll store the values the square has used already
     in an unordered set call used_up.

     In order to consider the next slot we'll use recursion
     calling help_see_magic_potential(used_up, slots_considered + 1);


     When slots_considered is equal to the total number of slots,
     we should check if the square is a magic square and if so, print it.

     Otherwise, we should determine if the slot under consideration is empty
     (recall that a user may have used the member function Square::set).

     If empty, i.e. the slot has no value,
      - we should try every possible value which is not already a part of used_up
        in the current slot, and try to solve the magic square for each value we insert
        by repeating the process with slots_considered replaced by slots_considered + 1
        and with the newly chosen number added to used_up;
      - and afterwards, so that see_magic_potential returns data to its initial state,
        for each value that we placed in the square,
        we should remove that value from the square and used_up.

     Otherwise,
      - we should skip over the current slot and
        try solving the magic square by looking at the next slot.


     Finally, an important optimization... if a row was just filled,
     we should check that the row has a magic total.
     Without this optimization,
     the code will be very slow for 4 x 4 squares,
     even those with a diagonal filled in.


     @param used_up : an ordered set keeping track of the values already in the square
     @param slots_considered : the number of slots considered so far going from left-to-right, top-to-bottom
    */
    void help_see_magic_potential(std::unordered_set<unsigned int>& used_up,
                                  size_t slots_considered);
};

#endif /* square_hpp */
