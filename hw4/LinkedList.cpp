#include "LinkedList.hpp"




LinkedList::LinkedList() : first(nullptr), last(nullptr) {}

LinkedList::LinkedList(std::initializer_list<int> il) : LinkedList() {
    for (int i : il) {
        push_back(i);
    }
}






void swap(LinkedList& li1, LinkedList& li2) {
    std::swap(li1.first, li2.first);
    std::swap(li1.last,  li2.last);
}
LinkedList::LinkedList(LinkedList&& other) : LinkedList() {
    swap(*this, other);
}





LinkedList::~LinkedList() {
    node* n = first;
    while (n) {
        node* next = n->next;
        delete n;
        n = next;
    }
}




LinkedList::node::node(int v) : val(v), prev(nullptr), next(nullptr) {}

















void LinkedList::push_back(int val) {
    node* n = new node(val);

    if (last) {
        n->prev = last;
        last->next = n;
    }
    else {
        first = n;
    }

    last = n;
}


void LinkedList::push_front(int val) {
    node* n = new node(val);
    if (first) {
        n->next = first;
        first->prev = n;
    } else {
        last = n;
    }
    first = n;
}








void LinkedList::pop_back() {
    if (!last) {
        return;
    }

    if (first == last) {
        delete last;
        first = nullptr;
        last = nullptr;
    }
    else {
        node* new_last = last->prev;
        delete last;

        last = new_last;
        last->next = nullptr;
    }
}


void LinkedList::pop_front() {
    if (!first) {
        return;
    }

    if (first == last) {
        delete first;
        first = nullptr;
        last = nullptr;
    }
    else {
        node* new_first = first->next;
        new_first->prev = nullptr;
        delete first;
        first = new_first;
    }
}


















LinkedList::iterator LinkedList::insert(iterator it, int val) {
    if (it.container != this) {
        return it;
    }
    
    if (it.curr == first) {
         push_front(val);    // commented out until push_front is defined
        return iterator(this, first);
    }
    if (it.curr == nullptr) {
        push_back(val);
        return iterator(this, last);
    }


    node* n = new node(val);

    n->prev = it.curr->prev;
    n->next = it.curr;

    it.curr->prev->next = n;
    it.curr->prev = n;

    return iterator(this, n);
}

LinkedList::iterator LinkedList::erase(iterator it) {
    if (it.container != this) {
        return it;
    }

    if (it.curr == nullptr) {
        return iterator(this, nullptr);
    }

    if (it.curr == first) {
         pop_front();    // commented out until pop_front is defined
        return iterator(this, first);
    }
    if (it.curr == last) {
        pop_back();
        return iterator(this, nullptr);
    }


    it.curr->prev->next = it.curr->next;
    it.curr->next->prev = it.curr->prev;

    node* next = it.curr->next;
    delete it.curr;

    return iterator(this, next);
}












// below are iterator class constructors and operators and stuff - ALL GIVEN
//constructor
LinkedList::iterator::iterator (const LinkedList* ll, node* n) : container(ll), curr(n) {}

// ++operator
LinkedList::iterator& LinkedList::iterator::operator++() {
    if (curr) { curr = curr->next; }
    return *this;
}

//defrefrence operator
int& LinkedList::iterator::operator*() const { return curr->val; }

//not equal operator
bool operator!=(const LinkedList::iterator& it1, const LinkedList::iterator& it2) {
    return (it1.curr != it2.curr) || (it1.container != it2.container);
}










// below here are the constructors and operators for const iterator
//constructors - 1 GIVEN
LinkedList::const_iterator::const_iterator(const iterator& it) : container(it.container), curr(it.curr) {}

LinkedList::const_iterator::const_iterator(const LinkedList* ll, const node* n) : container(ll), curr(n) {}

//++ operator
LinkedList::const_iterator& LinkedList::const_iterator::operator++() {
    if (curr) curr = curr->next;
    return *this;
}

// dereference
const int& LinkedList::const_iterator::operator*() const { return curr->val;}

//not equal operator
bool operator!=(const LinkedList::const_iterator& it1, const LinkedList::const_iterator& it2) {
    return (it1.curr != it2.curr) || (it1.container != it2.container);
}







// below here are the constructors and operators for reverse iterator
//constructor
LinkedList::reverse_iterator::reverse_iterator(const LinkedList* ll, node* n) : container(ll), curr(n) {}

//++ operator
LinkedList::reverse_iterator& LinkedList::reverse_iterator::operator++() {
    if (curr) curr = curr->prev;
    return *this;
}

// dereference
int& LinkedList::reverse_iterator::operator*() const { return curr->val;}

//not equal operator
bool operator!=(const LinkedList::reverse_iterator& it1, const LinkedList::reverse_iterator& it2) {
    return (it1.curr != it2.curr) || (it1.container != it2.container);
}













// below here are the constructors and operators for const reverse iterator
//constructors
LinkedList::const_reverse_iterator::const_reverse_iterator(const reverse_iterator& it) : container(it.container), curr(it.curr) {}

LinkedList::const_reverse_iterator::const_reverse_iterator(const LinkedList* ll, const node* n) : container(ll), curr(n) {}

//++ operator
LinkedList::const_reverse_iterator& LinkedList::const_reverse_iterator::operator++() {
    if (curr) curr = curr->prev;
    return *this;
}

// dereference
const int& LinkedList::const_reverse_iterator::operator*() const {return curr->val;}

//not equal operator
bool operator!=(const LinkedList::const_reverse_iterator& it1, const LinkedList::const_reverse_iterator& it2) {
    return (it1.curr != it2.curr) || (it1.container != it2.container);
}



//begin, end, rbegin and rend


LinkedList::iterator LinkedList::begin() {return iterator(this, first);}

LinkedList::iterator LinkedList::end() {return iterator(this, nullptr);}

LinkedList::const_iterator LinkedList::begin() const {return const_iterator(this, first);}

LinkedList::const_iterator LinkedList::end() const {return const_iterator(this, nullptr);}

LinkedList::reverse_iterator LinkedList::rbegin() {return reverse_iterator(this, last);}

LinkedList::reverse_iterator LinkedList::rend() {return reverse_iterator(this, nullptr);}

LinkedList::const_reverse_iterator LinkedList::rbegin() const {return const_reverse_iterator(this, last);}

LinkedList::const_reverse_iterator LinkedList::rend() const {return const_reverse_iterator(this, nullptr);}


// copy constructor
LinkedList::LinkedList(const LinkedList& other) : first(nullptr), last(nullptr) {
    for (int val : other) {
        push_back(val);
    }
}

//copy assignment
LinkedList& LinkedList::operator=(LinkedList other) {
    while (first) {
        pop_front();
    }

    for (int val : other) {
        push_back(val);
    }

    return *this;
}
