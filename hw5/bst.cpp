#include "bst.hpp"




Tree::Tree() : root(nullptr) {}

void Tree::insert(std::string val) {
    if (root) {
        root->insert_node(new node(std::move(val)));
    }
    else {
        root = new node(std::move(val));
    }
}

Tree::node::node(std::string v) : val(std::move(v)), parent(nullptr), left(nullptr), right(nullptr) {}

void Tree::node::insert_node(node* n) {
    if (n->val < val) {
        if (left) {
            left->insert_node(n);
        }
        else {
            left = n;
            left->parent = this;
        }
    }
    else if (val < n->val) {
        if (right) {
            right->insert_node(n);
        }
        else {
            right = n;
            right->parent = this;
        }
    }
    else {
        delete n;
    }
}
























Tree::Tree(Tree&& other) : Tree() {
    swap(other);
}
Tree& Tree::operator=(Tree other) {
    swap(other);
    return *this;
}







void Tree::traverse_insert(node* n) {
    if (n) {
        insert(n->val);
        if (n->left)  { traverse_insert(n->left);  }
        if (n->right) { traverse_insert(n->right); }
    }
}








Tree::Tree(const Tree& other) : Tree() { traverse_insert(other.root); }










const std::string* Tree::iterator::operator->() const {
    return &(curr->val);
}









Tree::node* Tree::node::far_left() {
    node* n = this;

    while (n->left) {
        n = n->left;
    }
    return n;
}












Tree::iterator Tree::begin() const {
    if (root) {
        return iterator(this, root->far_left());
    }
    return iterator(this, nullptr);
}
Tree::iterator Tree::end() const {
    return iterator(this, nullptr);
}


// 6

// a

Tree::iterator& Tree::iterator::operator++() {
    if (!curr) {
        return *this;
    }

   


        if (curr->right) {
            curr = curr->right->far_left();
        } else {
            node* parent = curr->parent;
            while (parent && curr == parent->right) {
                curr = parent;
                parent = parent->parent;
            }
            curr = parent;
        }

        return *this;
    }



// b


Tree::iterator& Tree::iterator::operator--() {
    if (!curr) {
        if (container && container->root) {
            curr = container->root->far_right();
        }
        return *this;
    }

        if (curr->left) {
            curr = curr->left->far_right();
        } else {
            node* parent = curr->parent;
            while (parent && curr == parent->left) {
                curr = parent;
                parent = parent->parent;
            }
            curr = parent;
        }





    return *this;
}




void Tree::erase(iterator it) {
    if (!it.curr || (it.container != this)) {
        return;
    }


    if (it.curr->left) {
         it.curr->val = std::move(it.curr->left->far_right()->val);
        erase(--it);
        return;
    }
    if (it.curr->right) {
        it.curr->val = std::move(it.curr->right->far_left()->val);
        erase(++it);
        return;
    }
    if (it.curr == root) {
        delete root; root = nullptr;
        return;
    }


    if (it.curr->parent->left == it.curr) {
        it.curr->parent->left = nullptr;
    }
    else {
        it.curr->parent->right = nullptr;
    }
    delete it.curr;
    return;
}

// 1 find

bool Tree::find(const std::string& lookingFor) const {
    node* current = root;
    
    while (current) {
        if (lookingFor == current->val) {
            return true;
        } else if (lookingFor < current->val) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    return false;
}

// 2 swap member and non member funcctions

void Tree::swap(Tree& other) {
    std::swap(root, other.root);
}

void swap(Tree& treeOne, Tree& treeTwo) {
    treeOne.swap(treeTwo);
}

// 3 delete and deconstructor

void Tree::delete_tree(node* n) {
    if (!n) return;

    delete_tree(n->left);
    delete_tree(n->right);

    delete n;
}

Tree::~Tree() {
    delete_tree(root);
    root = nullptr;
}

// 4

// a constructor

Tree::iterator::iterator(const Tree* t, node* n)
    : container(t), curr(n) {}

// b derefrence

const std::string& Tree::iterator::operator*() const {
    return curr->val;
}

// c not equal

bool operator!=(const Tree::iterator& it1, const Tree::iterator& it2) {
    return it1.curr != it2.curr; // Compare node pointers
}

// d post increment

Tree::iterator Tree::iterator::operator++(int) {
    Tree::iterator old = *this;
    ++(*this);
    return old;
}

// e post decrement

Tree::iterator Tree::iterator::operator--(int) {
    Tree::iterator old = *this;
    --(*this);
    return old;
}

// 5 far right

Tree::node* Tree::node::far_right() {
    node* n = this;
    
   
    while (n->right) {
        n = n->right;
    }
    return n;
}


