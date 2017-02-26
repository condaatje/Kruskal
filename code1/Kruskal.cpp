//
//  Kruskal.cpp
//  code1
//
//  Created by Eagle on 2/25/17.
//  Copyright © 2017 Ondaatje124. All rights reserved.
//

#include "Kruskal.hpp"
#include "Union_Find.hpp"
#include "Graphs.hpp"
#include <vector>
#include <iostream>
#include <assert.h>


using namespace std;

bool edgeCompare (Edge a, Edge b) { return (a.weight < b.weight); }

double kruskal(Graph * g, double bound) {
    // kruskal's algorithm takes in a graph, and calculates the MST.
    // in this case, we will use it to return the weight of the MST it finds.
    // although for testing we may want to examine the actual tree. tbd.
    
    // 1: Sort the edges.
    // We are allowed to simply do this with a library function
    // 2: for every vertex, make a new set (MAKESET)
    // 3: for every edge (in increasing order)
    // If they aren't in the same set, union them together.
    // There's a certain point where we can stop the algorithm as an optimization, check lecture vid.
    
    // TODO maybe don't add edges to the union find if they are super huge?
    // This can be tested for correctness by asserting that the
    // MST is always the same if your remove edges of weight > x (or enough to not bias the average)
    
    Union_Find uf; //TODO allocate with sizing.
    
    vector<Edge> edges;
    
    for(int i = 0; i < g->num_vertices; i++) {
        for(int j = i; j < g->num_vertices; j++) {
            double w = g->weight(i, j);
            if (w < bound) { // TODO dynamic
                Edge e;
                e.v1 = i;
                e.v2 = j;
                e.weight = w;
                edges.push_back(e);
            } else {
                if (w > 3) { // hypercube should max at 2.something
                    assert(false); // TODO cleanup.
                }
            }
        }
        uf.makeset(i); // Insert the vertex into the union find.
    }
    
    sort(edges.begin(), edges.end(), edgeCompare); // TODO test sort.
    
    double total = 0;
    int mst_count = 0;
    for(int i = 0; i < edges.size(); i++) {
        Edge e = edges[i];
        if (uf.find(e.v1) != uf.find(e.v2)) {
            uf.onion(e.v1, e.v2);
            total = total + e.weight;// we aren't recording the MST, just its weight
            mst_count = mst_count + 1;
            if (mst_count >= g->num_vertices - 1) {//edges is v-1
                break;
            }
        }
    }
    
    // vector<Node *> backend = uf.raw();
    if (mst_count < g->num_vertices - 1) {
        // this works to check whether we've got all the vertices.
        
        // Bad fail. Something wrong with the algo or graph.
        if(bound > 1) {assert(false);}
        
        uf.clean();
        
        // iterative deepening, doubling keeps the worst-case speedy
        // TODO talk about how this is still poly/fast.
        // TODO check for tail-recursion. and speed.
        return kruskal(g, bound * 2);
    }
    
    
    uf.clean();
    return total;
}
