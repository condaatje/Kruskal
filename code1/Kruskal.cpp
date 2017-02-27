
#include "Kruskal.hpp"
#include "Union_Find.hpp"
#include "Graphs.hpp"
#include <vector>
#include <iostream>
#include <assert.h>

using namespace std;
const char nn = '\n';


double kruskal_basic(Basic_Graph * g, double bound) {
    Union_Find uf;
    
    // Insert each vertex into the union find.
    for(int i = 0; i < g->num_vertices; i++) {
        uf.makeset(i);
    }

    sort(g->edges.begin(), g->edges.end(), edgeCompare);

    double total = 0.0;
    int mst_count = 0;
    for(int i = 0; i < g->edges.size(); i++) {
        Edge e = g->edges[i];
        if (uf.find(e.v1) != uf.find(e.v2)) {
            uf.onion(e.v1, e.v2);
            total = total + e.weight;// we aren't recording the MST, just its weight
            mst_count = mst_count + 1;
            if (mst_count >= g->num_vertices - 1) {//edges is v-1
                break;
            }
        }
    }
    
    // Restart with a looser bound if we can't find an MST (iterative deepening)
    if (mst_count < g->num_vertices - 1) {
        uf.clean();
        
        // TODO shouldn't really be any printing outside of main. Maybe only do if debug is on?
        cout << "had to reset on a graph of size " << g->num_vertices
        << " with bound of size " << bound << nn << endl;
        
        // Hard fail. Something wrong with the algo or graph.
        if(bound > 1) {assert(false);}
        
        
        // iterative deepening, doubling keeps the worst-case speedy
        // TODO talk about how this is still poly/fast.
        return kruskal_basic(g, bound * 2);
    }
    
    uf.clean();
    return total;
}


double kruskal_euclid(Graph * g, double bound) {
    // kruskal's algorithm takes in a graph, and calculates the MST.
    // in this case, we will use it to return the weight of the MST it finds.

    // 1: Sort the edges.
    // 2: for every vertex, make a new set (MAKESET)
    // 3: for every edge (in increasing order)
    // If its composite vertices aren't in the same set, link them.
    
    Union_Find uf;
    
    vector<Edge> edges;
    
    for(int i = 0; i < g->num_vertices; i++) {
        for(int j = i; j < g->num_vertices; j++) {
            double w = g->weight(i, j); // 98% of execution cost.
            if (w < bound) {
                Edge e(i, j, w);
                edges.push_back(e);
            } else {
                if (w > 3) { // hypercube should max at 2.something
                    assert(false); // TODO cleanup.
                }
            }
        }
        uf.makeset(i); // Insert the vertex into the union find.
    }
    
    sort(edges.begin(), edges.end(), edgeCompare);
    
    double total = 0.0;
    int mst_count = 0;
    for(int i = 0; i < edges.size(); i++) {
        Edge e = edges[i];
        if (uf.find(e.v1) != uf.find(e.v2)) {
            uf.onion(e.v1, e.v2);
            total = total + e.weight; // we aren't recording the MST, just its weight
            mst_count = mst_count + 1;
            if (mst_count >= g->num_vertices - 1) { // |V| - 1 edges
                break;
            }
        }
    }
    
    // Restart with a looser bound if we can't find an MST
    if (mst_count < g->num_vertices - 1) {
        uf.clean();
        
        // TODO shouldn't really be any printing outside of main. Maybe only do if debug is on?
        cout << "     Iterative deepening activated: "<< g->graph_type
             << " graph of size " << g->num_vertices
             << " with bound of " << bound << endl;
        
        // Hard fail. Something wrong with the algo or graph.
        if(bound > 1) { assert(false); }

        // iterative deepening, doubling keeps the worst-case speedy
        // TODO talk about how this is still poly/fast.
        return kruskal_euclid(g, bound * 2);
    }
    
    uf.clean();
    return total;
}
