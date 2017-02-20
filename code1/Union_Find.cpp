//
//  Union_Find.cpp
//  code1
//
//  Created by Eagle on 2/20/17.
//  Copyright © 2017 Ondaatje124. All rights reserved.
//

#include "Union_Find.hpp"
#include <iostream> //free()
#include <assert.h>
#include <vector>

using namespace std;

Node * Union_Find::link(Node * a, Node * b) {
    // if rank(x) > rank(y) then x ↔ y
    // if rank(x) = rank(y) then rank(y) := rank(y) + 1
    // p(x) := y
    // return(y)
    
    
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
    sets.resize(size); // TODO this will probably be shattered when I have to start doctoring space.
}

Union_Find::Union_Find() {}

void Union_Find::makeset(int x) {
    // takes in a vertex. creates a set out of it solo.
    
    Node * n = new Node();
    n->value = x;
    n->rank = 0;
    n->parent = n;
    // n.parent = make_shared<Node>(n); // TODO research. maybe use a weak pointer.
    
    if (sets.size() <= x) {
        sets.resize(x + 1); // TODO +1 handles 0 index, but watch out for other issues. Best to initialize with a suggested size.
    }
    sets[x] = n;
}

// "union" is taken
void Union_Find::onion(int x, int y) {
    // replace two sets containing x and y with their union.
    this->link(this->find(x), this->find(y)); // TODO check this.
}

Node * Union_Find::find(int x) {
    // TODO return the set containing element x
    
    // if x ̸= p(x) then
    // p(x) := FIND(p(x))
    // return( p(x))
    
    Node * n = sets[x];
    
    // TODO protect against bad input
    if (n->parent->value != n->value) {
        n->parent = find(n->parent->value); // walk the node up the tree (flattens as it finds)
    }
    
    return n->parent;
}

void Union_Find::clean() {// TODO just make a destructor
    // NOTE: check that this is right, but the way this is set up, everything is chill when the vector is wiped.
    
    for(int i = 0; i < sets.size(); i++) {
        
        //            for(Node * n = sets[i]; n->parent != n; n = n->parent) {
        //                // Ideally this doesn't get activated, because we're flat.
        //                cout << "TODO this shouldn't happen. If it does, need to free these guys: "
        //                     << n->value << nn;;
        //            }
        // cout << "Freeing node: " << sets[i].value << endl;
        free(sets[i]);
    }
}

vector<Node *> Union_Find::raw() {
    return sets;
};
