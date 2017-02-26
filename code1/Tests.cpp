//
//  tests.cpp
//  code1
//
//  Created by Eagle on 2/20/17.
//  Copyright © 2017 Ondaatje124. All rights reserved.
//

#include "Tests.hpp"
#include "Kruskal.hpp"
#include "Union_Find.hpp"
#include "Graphs.hpp"
#include <assert.h>
#include <vector>
#include <cmath>
#include <iostream>


using namespace std;
const char nn = '\n';


void test_kruskal() {
    //TODO actually test with example graphs.

    cout << "Testing Kruskal's..." << nn;
    Basic_Graph g1;
    g1.initialize_random(256);
    double g1_weight = kruskal_basic(&g1, 0.5);
    cout << g1_weight << nn;
    
    Square_Graph g2;
    g2.initialize_random(256);
    double g2_weight = kruskal_euclid(&g2, 0.5);
    cout << g2_weight << nn;
    
    Cube_Graph g3;
    g3.initialize_random(256);
    double g3_weight = kruskal_euclid(&g3, 0.5);
    cout << g3_weight << nn;
    
    Hypercube_Graph g4;
    g4.initialize_random(256);
    double g4_weight = kruskal_euclid(&g4, 0.5);
    cout << g4_weight << nn;
    
}

void test_union_find() {
    cout << "Testing Union-Find..." << nn;

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
    // and return a pointer to the root of 4's tree (which is 0)
    Node * n1 = uf.find(4);
    assert(n1 == backend[0]);
    assert(backend[4]->parent == backend[0]);
    
    // TODO understand why this points to 3 and confirm that's acceptable behavior.
    assert(backend[5]->parent != backend[0]);
    
    
    uf.find(5); // then it gets flattened.
    assert(backend[5]->parent == backend[0]);
    
    // TODO protect against bad input?
    // might actually be good to get a hard fail to debug for now.
    // uf.onion(14, 124);
    
    uf.clean(); // TODO replace w deinit?
}


void test_basic_graph() {
    cout << "Testing Basic Graph..." << nn;
    Basic_Graph g1;
    g1.initialize_random(256);
    double avg = g1.average_weight();
    
    assert(std::abs(avg - 0.5) < 0.01);
    
    // TODO actual tests
}

void test_square_graph() {
    // really need to test this to make sure we're putting out the right
    // weights for vertices.
    
    cout << "Testing Square Graph..." << nn;
    cout << "TODO" << nn;

}

void test_cube_graph() {
    cout << "Testing Cube Graph..." << nn;
    cout << "TODO" << nn;

}


void test_hypercube_graph() {
    cout << "Testing Hypercube Graph..." << nn;
    cout << "TODO" << nn;

}







