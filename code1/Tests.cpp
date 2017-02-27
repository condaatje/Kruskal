
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
    cout << "Testing Kruskal's..." << nn;
    
    vector<Edge> egs;
    egs.push_back(Edge(0,1, 0.2));
    egs.push_back(Edge(0,2, 0.7));
    egs.push_back(Edge(0,3, 0.3));
    egs.push_back(Edge(1,2, 0.25));
    egs.push_back(Edge(1,3, 0.5));
    egs.push_back(Edge(2,3, 0.1));
    Basic_Graph g1;
    g1.initialize_specific(4, egs);
    assert(kruskal_basic(&g1, 0.5) == 0.1 + 0.2 + 0.25);
    cout << "Basic OK." << nn;
    
    vector<Point2D> points2D;
    points2D.push_back(Point2D(0.25, 0.9));
    points2D.push_back(Point2D(0.0, 0.5));
    points2D.push_back(Point2D(0.6, 0.6));
    points2D.push_back(Point2D(0.9, 0.5));
    points2D.push_back(Point2D(0.5, 0.1));
    Square_Graph g2;
    g2.initialize_specific(points2D);
    assert(abs(g2.weight(0, 1) - 0.47) < 0.01);
    double mst_w2 = kruskal_euclid(&g2, 0.5); //Iterative deepening needed for <2,4>
    assert(abs(mst_w2 - 1.76) < 0.01);
    cout << "Square OK." << nn;
    
    vector<Point3D> points3D;
    points3D.push_back(Point3D(0.25, 0.9, 0));
    points3D.push_back(Point3D(0.0, 0.5, 0));
    points3D.push_back(Point3D(0.6, 0.6, 0));
    points3D.push_back(Point3D(0.9, 0.5, 0));
    points3D.push_back(Point3D(0.5, 0.1, 0));
    Cube_Graph g3;
    g3.initialize_specific(points3D);
    assert(abs(g3.weight(0, 1) - 0.47) < 0.01);
    double mst_w3 = kruskal_euclid(&g3, 0.5);
    assert(abs(mst_w3 - 1.76) < 0.01);
    cout << "Cube OK." << nn;

    vector<Point4D> points4D;
    points4D.push_back(Point4D(0.25, 0.9, 0, 0));
    points4D.push_back(Point4D(0.0, 0.5, 0, 0));
    points4D.push_back(Point4D(0.6, 0.6, 0, 0));
    points4D.push_back(Point4D(0.9, 0.5, 0, 0));
    points4D.push_back(Point4D(0.5, 0.1, 0, 0));
    Hypercube_Graph g4;
    g4.initialize_specific(points4D);
    assert(abs(g4.weight(0, 1) - 0.47) < 0.01);
    double mst_w4 = kruskal_euclid(&g4, 0.5);
    assert(abs(mst_w4 - 1.76) < 0.01);
    cout << "HyperCube OK." << nn;
    
    cout << "Kruskal's Passed." << nn;
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
    
    // hard fail to debug for now.
    // uf.onion(14, 124);
    
    uf.clean();
}

