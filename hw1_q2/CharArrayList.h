/*
 *  CharArrayList.h
 *  Cooper Golemme
 *  January, 2023
 *
 *  COMP 15 HW 1 Cheshire ConCATenation
 *
 *  Definition of CharArrayList member variables and desired functionality
 *  Purpose: to create a data sructure to store char data that can dynamically 
 *           expand and contract to fit user needs.
 *           
 */
#ifndef CHAR_ARRAY_LIST_H
#define CHAR_ARRAY_LIST_H

#include <string>

class CharArrayList {
    public:
        // constructors
        CharArrayList();
        CharArrayList(char c);
        CharArrayList(char arr[], int size);
        CharArrayList(const CharArrayList &other);
        // destructor
        ~CharArrayList();

        // Assignment operator
        CharArrayList &operator=(const CharArrayList &other);

        // other
        bool isEmpty();
        void clear();
        
        // display functions
        std::string toString();
        std::string toReverseString();
        // add functions
        void pushAtBack(char c);
        void pushAtFront(char c);
        void insertAt(char c, int index);
        void insertInOrder(char c);
        // remove | replace functions
        void popFromFront();
        void popFromBack();
        void removeAt(int index);
        void replaceAt(char c, int index);
        // other
        void concatenate(CharArrayList *other);
        void shrink();

        // getters
        char first();
        char last();
        /* removed for final submission */
        //int get_capacity();
        int size();
        char elementAt(int index);

    
    private:
        char *data;
        int capacity;
        int num_items;

        // helper functions
        void expand();
        
};

#endif
