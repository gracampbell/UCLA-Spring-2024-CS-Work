/*
 *  CharArrayList.cpp
 *  by Cooper Golemme, January 2023
 *
 *  COMP 15 HW 1 Cheshire ConCATenation
 *
 *  Implementation for CharArrayList functions
 *
 */

#include "CharArrayList.h"
#include <stdexcept>
#include <sstream>
#include <iostream>

using namespace std;
// Default constructor
CharArrayList::CharArrayList(){
    capacity = 0;
    num_items = 0;
    data = new char[capacity];
}
// Constructor from single char
CharArrayList::CharArrayList(char c){
    capacity = 1;
    num_items = 1;
    data = new char[capacity];
    data[0] = c;
}
// Constructor from array of chars
CharArrayList::CharArrayList(char arr[], int size){
    capacity = size;
    num_items = size;
    data = new char[capacity];
    for (int i = 0; i < size; i++){
        data[i] = arr[i];
    }
}
// Copy constructor, from another CharArrayList object 
CharArrayList::CharArrayList(const CharArrayList &other){
    *this = other;
}
// Destructor
CharArrayList::~CharArrayList(){
    delete [] data;
    data = nullptr;
}
// Assignment operator
CharArrayList& CharArrayList::operator=(const CharArrayList &other){
    // check if attempt to assign something to itself
    if (this == &other){
        return *this;
    }
    capacity = other.capacity;
    num_items = other.num_items;
    data = new char[capacity];

    for (int i = 0; i < num_items; i++){
        data[i] = other.data[i];
    }
    return *this;
}
/* isEmpty
* Purpose: to check if array list is empty
* Return: boolean true if number of items in the ArrayList is 0
*/
bool CharArrayList::isEmpty(){
    return num_items == 0;
}
/* clear
* Purpose: to change any ArrayList to an empty one
* Effects: capacity and num_items in Array List become 0
*/
void CharArrayList::clear(){
    num_items = 0;
    capacity = 0;
}
/* get_capacity
* Purpose: getter for private capacity attribute
* Return: int of class attribute capacity
* Used for testing, removed for final submission
*/
/*int CharArrayList::get_capacity(){
    return capacity;
}*/
/* size
* Purpose: getter for private size attribute
* Return: int for class attribute size
*/
int CharArrayList::size(){
    return num_items;
}
/* first
* Purpose: get first element of ArrayList
* Return: char of first element
* Errors: runtime error if list empty
*/
char CharArrayList::first(){
    // check if empty
    if (isEmpty()){
        throw runtime_error("cannot get first of empty ArrayList");
    }
    return data[0];

}
/* last
* Purpose: get last element of ArrayList
* Return: char of last element
* Errors: runtime error if list empty
*/
char CharArrayList::last(){
    // check if empty
    if (isEmpty()){
        throw runtime_error("cannot get last of empty ArrayList");
    }
    return data[num_items - 1];
}
/* elementAt
* Purpose: get the element of ArrayList at index
* Parameters: int index of desired element
* Return: char of element at index
* Errors: range error if index exceeds the bounds  [0, num_items)
*/
char CharArrayList::elementAt(int index){
    //check if invalid index
    if (index >= num_items or index < 0){
        std::stringstream ss;
        ss << "index (" << index << ") not in range " <<
            ") not in range [0.." << num_items << ")";
        throw range_error(ss.str());
    }
    return data[index];
}
/* toString
*  Purpose: display ArrayList as a string for reading purposes
*  Return: a string representing the data in ArrayList
*/
std::string CharArrayList::toString(){
    std::stringstream ss;
    ss << "[CharArrayList of size " << num_items;
    ss << " <<";
    for (int i = 0; i < num_items; i++){
        ss << data[i];
    }
    ss << ">>]";
    return ss.str();
}
/* toReverseString
*  Purpose: display ArrayList as a string in reverse order for reading purposes
*  Return: a string representing the reverse data in ArrayList
*/
std::string CharArrayList::toReverseString(){
    std::stringstream ss;
    ss << "[CharArrayList of size " << num_items;
    ss << " <<";

    for(int i = 0; i < num_items; i++){
        ss << data[num_items - i - 1];
    }
    ss << ">>]";
    return ss.str();
}
/* pushAtBack
*  Purpose: Add char C to the back of ArrayList
*  Parameter: char c for element to add
*  Changes: Expands ArrayList if there is not enough capacity to add element
*           Increases num_items by 1
*/
void CharArrayList::pushAtBack(char c){
    //check if more capacity is needed
    if (capacity == num_items){
        expand();
    }
    data[num_items] = c;
    num_items++;
}
/* expand
*  Purpose: dynamically allocate more space for ArrayList
*  Changes: capcity increases * 2 + 2
*/
void CharArrayList::expand(){
    capacity = capacity * 2 + 2;
    char *temp = new char[capacity];
    for (int i = 0; i < num_items; i++){
        temp[i] = data[i];
    }
    delete [] data;
    data = temp;
}
/* pushAtFront
*  Purpose: add element to front of ArrayList
*  Paramenter: char c, element to add to front
*  Changes: Expands ArrayList if not enough space to add
*           Increases num_items by 1
*/
void CharArrayList::pushAtFront(char c){
    // check if more capacity is needed
    if (capacity == num_items){
        expand();
    }
    for (int i = num_items; i > 0; i--){
        data[i] = data[i-1];
    }
    num_items++;
    data[0] = c;
}
/* insertAt
*  Purpose: insert char c into ArrayList at location (index)
*  Parameters: char c (element to add), int index (location to add to)
*  Changes: Expands ArrayList if not enough space to add
*           Increases num_items by 1
*  Exceptions: range_error if index not between [0, num_items)
*/
void CharArrayList::insertAt(char c, int index){
    // check invalid index
    if (index > num_items or index < 0){
        std::stringstream ss;
        ss << "index (" << index << ") not in range [0.." << num_items << "]";
        throw range_error(ss.str());
    }
    //check if more capacity is needed
    if (capacity == num_items){
        expand();
    }
    for (int i = num_items; i > index; i--){
        data[i] = data[i-1];
    }
    data[index] = c;
    num_items++;
}

/* insertInOrder
*  Purpose: insert char c to ArrayList in ascending alphabetical order
*  Parameters: char c (element to add)
*  Changes: Expands ArrayList if not enough space to add
*           Increases num_items by 1
*/
void CharArrayList::insertInOrder(char c){
    // checks if more capacity is needed
    if (capacity == num_items){
        expand();
    } 
    int insert_index = 0;
    for (int i = 0; i < num_items; i++){
        if (data[insert_index] < c){
            insert_index++;
        }
    }
    insertAt(c, insert_index);
}

/* popFromFront
*  Purpose: remove front of ArrayList
*  Changes: decrements num_items, shifts elements to the left one
*           Decreases num_items by 1
*  Exceptions: runtime_error if method called on empty list
*/
void CharArrayList::popFromFront(){
    // check if AL empty
    if (isEmpty()){
        throw std::runtime_error("cannot pop from empty ArrayList");
    }
    // for single element AL because single AL does not have data[1]
    if (num_items == 1){
        num_items--;
        return;
    }
    for (int i = 0; i < num_items; i++){
        data[i] = data[i+1];
    }
    num_items--;
}

/* popFromBack
*  Purpose: remove back of ArrayList
*  Changes: decrements num_items
*           Decreases num_items by 1
*  Exceptions: runtime_error if method called on empty list
*/
void CharArrayList::popFromBack(){
    // check if empty
    if (isEmpty()){
        throw std::runtime_error("cannot pop from empty ArrayList");
    }
    num_items--;
}

/* removeAt
*  Purpose: remove element of ArrayList at index
*  Parameters: int index for position of element to remove
*  Changes: decrements num_items, shifts elements past index to the left one
*           Decreases num_items by 1
*  Exceptions: runtime_error if index exceeds[0, num_item)
*/
void CharArrayList::removeAt(int index){
    // check invalid index
    if (index >= num_items or index < 0){
        std::stringstream ss;
        ss << "index (" << index << ") not in range [0.." << num_items << ")";
        throw range_error(ss.str());
    }
    // if single element list
    if (num_items == 1){
        num_items--;
        return;
    }
    for (int i = index; i < num_items; i++){
        data[i] = data[i+1];
    }
    num_items--;
}

/* replaceAt
*  Purpose: change value at index to char c
*  Parameters: char c (element to add), int index (position to replace element)
*  Exceptions: runtime_error if index exceeds[0, num_item)
*/
void CharArrayList::replaceAt(char c, int index){
    // check invalid index
    if (index >= num_items or index < 0){
        std::stringstream ss;
        ss << "index (" << index << ") not in range [0.." << num_items << ")";
        throw range_error(ss.str());
    }
    data[index] = c;
}

/* concatenate
*  Purpose: join two ArrayLists
*  Parameters: CharArrList pointer to another ArrayList
*  Changes: other is unchanged, this expands compacity and adds elements from  
*           other in sequential order to the end of this
*           increases num_items by other's num_items
*/
void CharArrayList::concatenate(CharArrayList *other){
    capacity += other->capacity;
    char *temp = new char[capacity];
    for (int i = 0; i < num_items; i++){
        temp[i] = data[i];
    }
    for (int j = 0; j < other->num_items; j++){
        temp[num_items + j] = other->data[j];
    }
    num_items += other->num_items;

    delete [] data;
    data = temp;
}
/* shrink
* Purpose: shrink dynamically allocated array to minimum necessary size
* Changes: Capacity of ArrayList becomes num_items
*/
void CharArrayList::shrink(){
    capacity = num_items;
    char *temp = new char[capacity];
    for (int i = 0; i < num_items; i++){
        temp[i] = data[i];
    }
    delete [] data;
    data = temp;
}