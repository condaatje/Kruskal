// 60951527
// ./randmst 0 numpoints numtrials dimension




// This will require implementing an MST algorithm,
// as well as procedures that generate the appropriate random graphs.


// For each type of graph, you must choose several values of n to test.
// n = 128; 256; 512; 1024; 2048; 4096; 8192; 16384; 32768; 65536; 131072,
// and larger values, if your program runs fast enough.
// For each value of n, you must run your code on several randomly chosen
// instances of the same size n, and compute the average value for your runs.


// Plot your values vs. n, and interpret your results by giving
// a simple function f(n) that describes your plot.

// For example, your answer might be f(n) = log(n) or f(n) = 1.5√n
// Try to make your answer as accurate as possible; this includes
// determining the constant factors as well as you can.
// On the other hand, please try to make sure your answer seems reasonable.





// ========== Approach ========== //
// Step 1: Create Graph Class for each type of graph implementation
    // Complete graph: all possible n choose 2 edges must be present in the graph.
    // What's the fastest? What's the most space efficient? Which is more important?


// At this point, I will not worry about space, and more about correctness.


// Step 2: MST Algorithm
    // Takes in a graph, returns length of MST
    // Prims or Kruskals? Lecture 6 should dive into Union find
    // and give you a better indication of which algorithm to use
    // Libraries for "sorting" are allowed
    //

// Step 3: Start to worry about space. how can we avoid 64gigs mem?


// Hint: note that the two algorithms discussed in lecture will always return a valid MST.
// If your programs cannot run to completion, then you know you have failed to find an MST.
// So if we eliminate vertices and the algorithm finishes, it didn't actually have to use the vertex it seems...

// vector is allowed, qsort is allowed.
// No pre-built hashtables

// Instructors say it's ok if the algo takes 10min+ to run. Just shouldn't take hours.

#include <iostream>
#include <vector>
#include "Union_Find.hpp"
#include "Graphs.hpp"
#include "Tests.hpp"

const char nn = '\n';
using namespace std;

// TODO subclass/interface the graphs so this can just take the superclass.
double kruskal(Basic_Graph) {
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
    
    
    
    
    
    
    
    
    
    
    // Function Kruskal(graph G(V,E))
    // set X
    // X = {}
    // E:= sort E by weight
    //
    // for u ∈ V
        // MAKESET(u) rof
    //
    // for (u, v) ∈ E (in increasing order) do
        // if FIND(u) ̸= FIND(v) do
            // X = X ∪ {(u, v)}
            // UNION(u,v)
    // rof
    // return(X )
    // end Kruskal
    
    return 1.0;
}


int main(int argc, const char * argv[]) {
    //vector<int> v = {7, 5, 16, 8};
    //auto testData = std::unique_ptr<unsigned char[]>{ new unsigned char[16000] };
    //std::vector< std::vector< float > > item ( 2, std::vector<float> ( 2, 0 ) );
    Basic_Graph g1;
    Square_Graph g2;
    Cube_Graph g3;
    Hypercube_Graph g4;
    
    //g1.initialize_random(131072); //will certainly fail until I find a better way to save memory.
    g1.initialize_random(256);
    
    // fast and no n^2 space
    g2.initialize_random(256);
    g3.initialize_random(256);
    g4.initialize_random(256);
    
    
    cout << "random distance? " << g1.distance(1, 2) << nn;
    cout << "Average Weight " << g1.average_weight() << nn << nn;
    
    cout << "Testing..." << nn;
    test_graph1();
    test_union_find();
    cout << "Tests Passed!!!" << nn;
    
    return 0;
}



