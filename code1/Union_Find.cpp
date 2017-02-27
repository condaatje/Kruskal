
#include "Union_Find.hpp"
#include <iostream>
#include <assert.h>
#include <vector>

using namespace std;

Node * Union_Find::link(Node * a, Node * b) {
    // put the smaller rank tree as a child of the bigger rank tree.
    // otherwise (equal rank), put second element as parent.
    if (a->rank > b->rank) {
        // swap pointers
        Node * temp_ptr = b;
        b = a;
        a = temp_ptr;
    }
    if (a->rank == b->rank) {
        // update the rank of the new parrent
        b->rank = b->rank + 1;
    }
    
    // a is child of b
    a->parent = b;
    return b;
}

Union_Find::Union_Find(int size) {
    // optimized init.
    sets.resize(size);
}

Union_Find::Union_Find() {}

void Union_Find::makeset(int x) {
    // takes in a vertex. creates a set out of it solo.
    
    Node * n = new Node();
    n->value = x;
    n->rank = 0;
    n->parent = n;
    
    if (sets.size() <= x) {
        sets.resize(x + 1); // +1 handles 0 index, but watch out for other issues.
        // Best to initialize with a suggested size.
    }
    sets[x] = n;
}

// "union" is taken
void Union_Find::onion(int x, int y) {
    // replace two sets containing x and y with their union.
    this->link(this->find(x), this->find(y));
}

Node * Union_Find::find(int x) {
    Node * n = sets[x];
    
    if (n->parent->value != n->value) {
        // walk the node up the tree (flattens as it finds)
        n->parent = find(n->parent->value);
    }
    
    return n->parent;
}

void Union_Find::clean() {
    // Normally I would just make a destructor,
    // but scoping is strange with iterative deepening.
    
    for(int i = 0; i < sets.size(); i++) {
        free(sets[i]);
    }
    sets.clear();
}

vector<Node *> Union_Find::raw() {
    return sets;
};
