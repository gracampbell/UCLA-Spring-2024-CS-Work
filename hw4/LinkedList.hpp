#ifndef LinkedList_hpp
#define LinkedList_hpp




#include <utility>
#include <initializer_list>




class LinkedList {
public:
    LinkedList();
    LinkedList(std::initializer_list<int>);
    LinkedList(const LinkedList&);

    LinkedList(LinkedList&&);
    LinkedList& operator=(LinkedList);

    ~LinkedList();


    void push_front(int);
    void push_back(int);
    void pop_front();
    void pop_back();


    class iterator;
    class const_iterator;
    class reverse_iterator;
    class const_reverse_iterator;


    iterator insert(iterator, int);
    iterator erase (iterator);


    iterator       begin();
    iterator       end();
    const_iterator begin() const;
    const_iterator end()   const;

    reverse_iterator       rbegin();
    reverse_iterator       rend();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend()   const;


private:
    class node {
        node(int);

        int val;
        node* prev;
        node* next;
        
        friend LinkedList;
    };

    node* first;
    node* last;


    friend void swap(LinkedList&, LinkedList&);
};




class LinkedList::iterator {
public:
    iterator(const LinkedList*, node*);

    iterator& operator++();
    int& operator*() const;

private:
    const LinkedList* container;
    node* curr;

    friend LinkedList;
    friend bool operator!=(const iterator&, const iterator&);
};


class LinkedList::const_iterator {
public:
    const_iterator(const iterator&);
    const_iterator(const LinkedList*, const node*);

    const_iterator& operator++();
    const int& operator*() const;

private:
    const LinkedList* container;
    const node* curr;

    friend bool operator!=(const const_iterator&, const const_iterator&);
};




class LinkedList::reverse_iterator {
public:
    reverse_iterator(const LinkedList*, node*);

    reverse_iterator& operator++();
    int& operator*() const;

private:
    const LinkedList* container;
    node* curr;

    friend const_reverse_iterator;
    friend bool operator!=(const reverse_iterator&, const reverse_iterator&);
};


class LinkedList::const_reverse_iterator {
public:
    const_reverse_iterator(const reverse_iterator&);
    const_reverse_iterator(const LinkedList*, const node*);

    const_reverse_iterator& operator++();
    const int& operator*() const;

private:
    const LinkedList* container;
    const node* curr;

    friend bool operator!=(const const_reverse_iterator&, const const_reverse_iterator&);
};




#endif /* LinkedList_hpp */
