//
//  tests.cpp
//  code1
//
//  Created by Eagle on 2/20/17.
//  Copyright © 2017 Ondaatje124. All rights reserved.
//

#include "Tests.hpp"
#include "Union_Find.hpp"
#include "Graphs.hpp"
#include <assert.h>
#include <vector>
#include <cmath>

using namespace std;

void test_union_find() {
    
    // Union Find //
    Union_Find uf;
    
    uf.makeset(0);
    uf.makeset(1);
    uf.makeset(2);
    uf.makeset(3);
    uf.makeset(4);
    uf.makeset(5);
    
    vector<Node *> backend = uf.raw(); // Note - only pull raw once the vector sizing is done.
    uf.onion(1, 0); // set node 0 as the parent of node 1      0
    assert(backend[0]->rank == 1); //                        ./ \.
    uf.onion(2, 0); // set node 0 as the parent of node 2    1   2
    assert(backend[0]->parent == backend[0]);
    assert(backend[1]->parent == backend[0]);
    assert(backend[2]->parent == backend[0]);
    
    uf.onion(4, 3); // set node 3 as parent of 4          3
    uf.onion(5, 4); // set node 4 as parent of 5           \.
    assert(backend[5]->parent->parent == backend[3]); //    4 <- 5
    
    uf.onion(4, 2); // should link tree root 0 with tree root 3
    assert(backend[3]->parent == backend[0]);
    
    // find(4) should compress so that only 5 doesn't point to 0,
    Node * n1 = uf.find(4); // and return a pointer to the root of 4's tree (which is 0)
    assert(n1 == backend[0]);
    assert(backend[4]->parent == backend[0]);
    assert(backend[5]->parent != backend[0]); //TODO understand why this points to 3 and confirm that's acceptable behavior.
    
    uf.find(5); // then it gets flattened.
    assert(backend[5]->parent == backend[0]);
    
    // TODO protect against bad input? might actually be good to get a hard fail to debug for now.
    //uf.onion(14, 124);
    
    uf.clean(); // TODO replace w deinit?
}


void test_graph1() {
    // TODO hook this up to command-u
    // TODO write some damn good tests.
    // TODO abstraction pass.
    
    
    
    // 1D Graph //
    Basic_Graph g1;
    g1.initialize_random(256);
    assert(std::abs(g1.average_weight() - 0.5) < 0.01);
    
    // TODO not comprehensive
    assert(g1.distance(1,2) >= 0);
    assert(g1.distance(1,2) <= 1);
    
    
}
