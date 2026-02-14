/*
 * unit_tests.h
 *
 * CS 15 homework 1
 * by Tyler Calabrese, January 2021
 *
 * edited by: Milod Kazerounian, January 2022    
 * edited by: Cooper Golemme, January 2023
 *
 * Uses Matt Russell's unit_test framework to test the CharArrayList class.
 *
 * Instructions for using testing framework can be found at in CS 15's lab
 * 1 -- both in the spec and in the provided ArrayList_tests.h and Makefile.
 * More in-depth information for those who are curious as to how it works can
 * be found at http://www.github.com/mattrussell2/unit_test.
 */

#include "CharArrayList.h"
#include <cassert>

/********************************************************************\
*                       CHAR ARRAY LIST TESTS                        *
\********************************************************************/

/* To give an example of thorough testing, we are providing
 * the unit tests below which test the insertAt function. Notice: we have
 * tried to consider all of the different cases insertAt may be
 * called in, and we test insertAt in conjunction with other functions!
 *
 * You should emulate this approach for all functions you define.
 */

/******* Constructors *******/

// tests basic, default constructor
void basic_constructor(){
    CharArrayList test_list;
    assert (test_list.isEmpty());
}

// tests constructor from single char
void char_constructor_test(){
    CharArrayList test_list = CharArrayList('c');
    assert(!test_list.isEmpty());
}

// tests constructor from standard array of char
void arr_constructor_test(){
    char arr[3] = {'c', 'o','o'};
    CharArrayList test_list = CharArrayList(arr, 3);
    assert(!test_list.isEmpty());
}

// tests copy constructor; tests assignment operator
void char_arrList_constructor_single(){
    CharArrayList test_list1 = CharArrayList('c');
    CharArrayList test_list2 = test_list1;
    assert(!test_list2.isEmpty());
}
// tests assignment operator in copy constructor on large list.
void char_arrList_one_large(){
    CharArrayList test_list1;
    for (int i = 0;  i < 13; i++){
        test_list1.pushAtBack('a' + i);
    }
    CharArrayList test_list2 = test_list1;
    assert(test_list1.toString()== test_list2.toString());
}




/******* clear *******/

//clear test on single element AL
void clear_single(){
    CharArrayList test_list = CharArrayList('c');
    test_list.clear();
    assert(test_list.isEmpty());
}

//clear test on non-single element AL
void clear_nonsingle(){
    char arr[3] = {'c', 'o','o'};
    CharArrayList test_list = CharArrayList(arr, 3);
    test_list.clear();
    assert(test_list.isEmpty());
}


/******* toString *******/

// tests to string on empty AL
void toString_empty(){
    CharArrayList test_list;
     assert(test_list.toString() == 
        "[CharArrayList of size 0 <<>>]");
}

// tests to string on non-empty AL
void toString_non_empty(){
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);
    assert(test_list.toString() == 
        "[CharArrayList of size 8 <<abcdefgh>>]");
}


/******* toReverseString *******/

// tests to reverse string on empty AL
void toReverseString_empty(){
    CharArrayList test_list;
     assert(test_list.toReverseString() == 
        "[CharArrayList of size 0 <<>>]");
}

// tests to reverse string on non-empty AL
void toReverseString_non_empty(){
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);
    assert(test_list.toReverseString() == 
        "[CharArrayList of size 8 <<hgfedcba>>]");
}

// tests to reverse string on single elment Al
// should be the same as to string on single AL
void toReverseString_single(){
    CharArrayList test_list('c');
    assert(test_list.toReverseString() == test_list.toString());
}

// tests toReverseString of even palidrome
void toReverseString_Palidrome(){
    char arr[4] = {'p', 'o', 'o', 'p'};
    CharArrayList test_list(arr, 4);
    assert(test_list.toReverseString() == test_list.toString());
}

// tests toReverseString of odd palidrome
void toReverseString_odd_palidrome(){
    char arr[5] = {'p', 'o','r', 'o', 'p'};
    CharArrayList test_list(arr, 5);
    assert(test_list.toReverseString() == test_list.toString());
}


/******* pushBack *******/

// tests pushBack on empty AL
void pushB_empty(){
    CharArrayList test_list;
    test_list.pushAtBack('c');
    assert(test_list.size() != 0);
}

// tests pushBack on single element AL
void pushB_single(){
    CharArrayList test_list('a');
    test_list.pushAtBack('c');
    assert(test_list.size()== 2);
    assert(test_list.elementAt(1) == 'c');
    assert(test_list.elementAt(0) == 'a');
}

// test pushBack multiple times
void pushB_many_elements(){
    CharArrayList test_list('a');
    for(int i = 0; i < 1000; i++){
        if( i < 500) test_list.pushAtBack('c');
        else test_list.pushAtBack('f');
    }
    assert(test_list.size()== 1001);
    assert(test_list.elementAt(501) == 'f');
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1)== 'c');
}


/******* pushFront *******/

// tests pushFront on empty AL
void pushF_empty(){
    CharArrayList test_list;
    test_list.pushAtFront('c');
    assert(test_list.size() != 0);
}

// tests pushFront on single element AL
void pushF_single(){
    CharArrayList test_list('a');
    test_list.pushAtFront('c');
    assert(test_list.size()== 2);
    assert(test_list.first() == 'c');
    assert(test_list.last() == 'a');
}

// test pushFront multiple times
void pushF_many_elements(){
    CharArrayList test_list('a');
    for(int i = 0; i < 1000; i++){
        if( i < 500) test_list.pushAtFront('c');
        else test_list.pushAtFront('f');
    }
    assert(test_list.size()== 1001);
    assert(test_list.elementAt(501) == 'c');
    assert(test_list.last() == 'a');
    assert(test_list.first() == 'f');
}


/******* insertAt *******/

// Tests correct insertion into an empty AL.
// Afterwards, size should be 1 and element at index 0
// should be the element we inserted.
void insertAt_empty_correct() {
                                   CharArrayList test_list;
                                   test_list.insertAt('a', 0);
                                   assert(test_list.size() == 1);
                                   assert(test_list.elementAt(0) == 'a');
                               
}

// Tests incorrect insertion into an empty AL.
// Attempts to call insertAt for index larger than 0.
// This should result in an std::range_error being raised.
void insertAt_empty_incorrect() {
    
    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharArrayList test_list;
    try {
        // insertAt for out-of-range index
        test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
        // if insertAt is correctly implemented, a range_error will be thrown,
        // and we will end up here
        range_error_thrown = true;
        error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..0]");
    
}

// Tests correct insertAt for front of 1-element list.
void insertAt_front_singleton_list() {
    // initialize 1-element list
    CharArrayList test_list('a');

    // insert at front
    test_list.insertAt('b', 0);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'b');
    assert(test_list.elementAt(1) == 'a');
}

// Tests correct insertAt for back of 1-element list.
void insertAt_back_singleton_list() {

    // initialize 1-element list
    CharArrayList test_list('a');

    // insert at back
    test_list.insertAt('b', 1);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
}

// Tests calling insertAt for a large number of elements.
// Not only does this test insertAt, it also checks that
// array expansion works correctly.
void insertAt_many_elements() {
    CharArrayList test_list;

    // insert 1000 elements
    for (int i = 0; i < 1000; i++) {
        // always insert at the back of the list
        
        test_list.insertAt('a', i);
    }

    assert(test_list.size() == 1000);

    for (int i = 0; i < 1000; i++) {
        assert(test_list.elementAt(i) == 'a');
    }

}

// Tests insertion into front, back, and middle of a larger list.
void insertAt_front_back_middle() {

        char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
        CharArrayList test_list(test_arr, 8);

        // insertAt middle
        test_list.insertAt('z', 3);

        assert(test_list.size() == 9);
        assert(test_list.elementAt(3) == 'z');
        assert(test_list.toString() == 
        "[CharArrayList of size 9 <<abczdefgh>>]");

        // insertAt front
        test_list.insertAt('y', 0);

        assert(test_list.size() == 10);
        assert(test_list.elementAt(0) == 'y');
        assert(test_list.toString() == 
        "[CharArrayList of size 10 <<yabczdefgh>>]");

        // insertAt back
        test_list.insertAt('x', 10);

        assert(test_list.size() == 11);
        assert(test_list.elementAt(10) == 'x');
        assert(test_list.toString() == 
        "[CharArrayList of size 11 <<yabczdefghx>>]");

}

// Tests out-of-range insertion for a non-empty list.
void insertAt_nonempty_incorrect() {
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    try {
        test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..8]");
}


/******* insertInOrder *******/

// tests insertInOrder on Empty list
void insertInOrder_empty(){
    CharArrayList test_list;
    test_list.insertInOrder('c');
    assert(test_list.first() == 'c');
}

// tests insertInOrder in the middle of list
void insertInOrder_middle(){
    CharArrayList test_list;
    test_list.pushAtFront('d');
    test_list.pushAtFront('b');
    test_list.pushAtFront('a');

    test_list.insertInOrder('c');

    assert(test_list.elementAt(2)== 'c');
    assert(test_list.size() == 4);
    assert(test_list.first()== 'a');
    assert(test_list.last()== 'd');
}

// tests insertInOrder at front of list
void insertInOrder_front(){
    CharArrayList test_list;
    test_list.pushAtFront('d');
    test_list.pushAtFront('c');
    test_list.pushAtFront('b');

    test_list.insertInOrder('a');


    assert(test_list.size() == 4);
    assert(test_list.first()== 'a');
    assert(test_list.last()== 'd');

}

// tests insertInOrder to back of list
void insertInOrder_back(){
    CharArrayList test_list;
    test_list.pushAtFront('d');
    test_list.pushAtFront('c');
    test_list.pushAtFront('b');

    test_list.insertInOrder('e');


    assert(test_list.size() == 4);
    assert(test_list.first()== 'b');
    assert(test_list.last()== 'e');

}

// tests insertInOrder to list that already contains inserted element
void insertInOrder_same_element(){
    CharArrayList test_list;
    test_list.pushAtFront('d');
    test_list.pushAtFront('c');
    test_list.pushAtFront('b');

    test_list.insertInOrder('c');


    assert(test_list.size() == 4);
    assert(test_list.first()== 'b');
    assert(test_list.last()== 'd');

}


/******* pop front *******/

// tests popFront on empty list : should throw exception
void popFront_empty(){
    bool error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharArrayList test_list;
    try {
        // insertAt for out-of-range index
        test_list.popFromFront();
    }
    catch (const std::runtime_error &e) {
        // if insertAt is correctly implemented, a range_error will be thrown,
        // and we will end up here
        error_thrown = true;
        error_message = e.what();
    }

    // out here, we make our assertions
    assert(error_thrown);
    assert(error_message == "cannot pop from empty ArrayList");
}

// tests popFront on "normal" arrayList
void popFront_standard(){
    CharArrayList test_list;
    test_list.pushAtFront('d');
    test_list.pushAtFront('b');
    test_list.pushAtFront('a');
    test_list.pushAtFront('x');
    test_list.pushAtFront('y');

    test_list.popFromFront();


    assert(test_list.size() == 4);
    assert(test_list.first() == 'x');
    assert(test_list.last() == 'd');
}

// tests popFront on single element list
void popFront_one_element(){
    CharArrayList test_list;
    test_list.pushAtBack('a');
    test_list.popFromFront();

    assert(test_list.size()== 0);
    assert(test_list.isEmpty());
}

// tests popFront on list multiple times; checks if it works each time
void popFront_multiple(){
    CharArrayList test_list;
    for(int i = 0; i < 26; i++){
        test_list.pushAtFront('a'+ i);
    }    
    for(int i = 0; i < 25; i++){
        assert(test_list.size() == 26 - i);
        assert(test_list.first()== 'z' - i);
        test_list.popFromFront();
    }
    assert(test_list.size() == 1);
    assert(test_list.first()== 'a');
}


/******* popBack *******/

// tests popBack on empty list; should throw exception
void popBack_empty(){
    bool error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharArrayList test_list;
    try {
        // insertAt for out-of-range index
        test_list.popFromBack();
    }
    catch (const std::runtime_error &e) {
        // if insertAt is correctly implemented, a range_error will be thrown,
        // and we will end up here
        error_thrown = true;
        error_message = e.what();
    }

    // out here, we make our assertions
    assert(error_thrown);
    assert(error_message == "cannot pop from empty ArrayList");
}

// tests popBack on "normal" arrayList
void popBack_standard(){
    CharArrayList test_list;
    test_list.pushAtFront('d');
    test_list.pushAtFront('b');
    test_list.pushAtFront('a');
    test_list.pushAtFront('x');
    test_list.pushAtFront('y');

    test_list.popFromBack();


    assert(test_list.size() == 4);
    assert(test_list.first() == 'y');
    assert(test_list.last() == 'b');

}

// tests popBack on single element list
void popBack_one_element(){
    CharArrayList test_list;
    test_list.pushAtBack('a');
    test_list.popFromBack();

    assert(test_list.size() == 0);
    assert(test_list.isEmpty());
}

// tests popBack on list multiple times; checks if it works each time
void popBack_multiple(){
    CharArrayList test_list;
    for(int i = 0; i < 26; i++){
        test_list.pushAtFront('a'+ i);
    }    
    for(int i = 0; i < 25; i++){
        assert(test_list.size() == 26 - i);
        assert(test_list.last()== 'a' + i);
        test_list.popFromBack();
    }
    assert(test_list.size() == 1);
    assert(test_list.first()== 'z');
    assert(test_list.first() == test_list.last());
}


/******* removeAt *******/

// tests removeAt on single element list
void removeAt_single(){
    CharArrayList test_list('a');
    test_list.removeAt(0);
    assert(test_list.isEmpty());
}

// tests removeAt at the front of a larger list
void removeAt_big_list_front(){
    CharArrayList test_list;
    for(int i = 0; i < 26; i++){
        test_list.pushAtFront('a'+ i);
    } 
    test_list.removeAt(0);
    assert(test_list.size()== 25);
    assert(test_list.first() == 'y');
}

// tests removeAt at the back of a larger list
void removeAt_big_list_back(){
    CharArrayList test_list;
    for(int i = 0; i < 26; i++){
        test_list.pushAtFront('a'+ i);
    } 
    test_list.removeAt(25);
    assert(test_list.size()== 25);
    assert(test_list.first() == 'z');
    assert(test_list.last()== 'b');
}

// tests removeAt at the front, back and middle of a larger list
void removeAt_big_list_fbm(){
    CharArrayList test_list;
    for(int i = 0; i < 26; i++){
        test_list.pushAtBack('a'+ i);
    } 
    test_list.removeAt(6);
    test_list.removeAt(24);
    test_list.removeAt(0);

    assert(test_list.size()== 23);
    assert(test_list.first() == 'b');
    assert(test_list.last()== 'y');
    assert(test_list.elementAt(5) == 'h');
}

// tests removeAt with insertAt; should remove and insert at same index
void removeAt_add_remove(){
    CharArrayList test_list;
    for(int i = 0; i < 26; i++){
        test_list.pushAtBack('a'+ i);
    } 
    test_list.insertAt('p', 6);
    test_list.removeAt(6);
    assert(test_list.size()== 26);
    assert(test_list.first() == 'a');
    assert(test_list.last()== 'z');
    assert(test_list.elementAt(6) == 'g');
}

// tests removeAt if given incorrect index (too large); should throw 
// range_exception
void removeAt_incorrect(){
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    try {
        test_list.removeAt(42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..8)");

}

// tests removeAt on empty list; should throw range exception
void removeAt_empty(){
    CharArrayList test_list;
     bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    try {
        test_list.removeAt(0);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (0) not in range [0..0)");
}


/******* replaceAt *******/

// tests replaceAt incorrect index; throw range_error
void replaceAt_incorrect(){
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    try {
        test_list.replaceAt('a', 42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..8)");
}

// tests replaceAt correct index in middle of AL
void replaceAt_middle(){
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);
    test_list.replaceAt('c', 1);
    assert(test_list.elementAt(1)== 'c');
    assert(test_list.size() == 8);
}

// tests replaceAt at the last index of array list
void replaceAt_last_index(){
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);
    test_list.replaceAt('z', 7);
    assert(test_list.elementAt(7) == 'z');
    assert(test_list.size()== 8);
}

// tests replaceAt at the front of a list
void replaceAt_front(){
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);
    test_list.replaceAt('z', 0);
    assert(test_list.elementAt(0) == 'z');
    assert(test_list.size()== 8);
}


/******* concatenate *******/

// tests concatenate on two single element lists
void concatenate_small(){
    CharArrayList first_list('a');
    CharArrayList second_list('b');
    first_list.concatenate(&second_list);
    assert(first_list.size() == 2);
    assert(first_list.last()== 'b');
}

// tests concatenate on two larger lists of the same size
void concatenate_large(){
    CharArrayList first_list, second_list;
    for(int i = 0; i < 13; i++){
        first_list.pushAtBack('a'+ i);
    } 
    for(int i = 13; i < 26; i++){
        first_list.pushAtBack('a'+ i);
    } 
    first_list.concatenate(&second_list);
    assert(first_list.size() == 26);

}

// tests concatenate on different sized lists
void concatenate_different_sizes(){
    CharArrayList first_list, second_list;
    for(int i = 0; i < 13; i++){
        first_list.pushAtBack('a'+ i);
    } 
    second_list.pushAtBack('x');
     first_list.concatenate(&second_list);
    assert(first_list.size() == 14);
    assert(first_list.last() == 'x');
    first_list.insertInOrder('z');
    assert(first_list.last()== 'z');
}

// tests concatenate on two empty lists; resulting list should be empty
void concatenate_both_empty(){
    CharArrayList first_list, secondlist;
    first_list.concatenate(&secondlist);
    assert(first_list.isEmpty());
}

// tests concatenate with one large list and one empty; should not change 
//  larger list
void concatenate_one_empty(){
    CharArrayList first_list, second_list;
    for(int i = 0; i < 13; i++){
        first_list.pushAtBack('a'+ i);
    }
    first_list.concatenate(&second_list);
    assert(first_list.size() == 13);

}


/******* shrink *******/

// tests shrink on empty list
void shrink_empty(){
    CharArrayList test_list;
    test_list.shrink();
    assert(test_list.isEmpty());
    /* commented out for final solution 
    assert(test_list.get_capacity() == 0);
    */
}

// tests shrink on single element list where capacity > size
void shrink_single(){
    CharArrayList test_list;
    test_list.pushAtBack('a');
    test_list.shrink();
    /* commented out for final solution 
    assert(test_list.size() == test_list.get_capacity());
    */
}

// tests shrink on single element list where capacity = size
void shrink_single_small_capacity(){
    CharArrayList test_list('c');
    test_list.shrink();
    /* commented out for final solution 
    assert(test_list.size() == test_list.get_capacity());
    */
}

// tests shrink on Arraylist created from standard array
void shrink_from_basic_array(){
    char arr[6] = {'c', 'o','o', 'p', 'e', 'r'};
    CharArrayList test_list = CharArrayList(arr, 6);
    test_list.shrink();
    /* commented out for final solution 
    assert(test_list.size() == test_list.get_capacity());
    */
}

// tests shrink on large list with a lot of extra capacity
void shrink_big(){
    CharArrayList test_list;
    for(int i = 0; i < 13; i ++){
        test_list.pushAtBack('a');
    }
    test_list.shrink();
    /* commented out for final solution 
    assert(test_list.size() == test_list.get_capacity());
    */
}