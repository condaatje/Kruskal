// 60951527
// ./randmst 0 numpoints numtrials dimension

// ========== Approach ========== //
// Step 3: Start to worry about space. how can we avoid 64gigs mem?
    // don't add edges above a certain weight. This can be tested for accuracy.
    // also can have a complete algo for this - loosen the bound if necessary (can't find a solution? run again with more relaxed boundary)

// Hint: note that the two algorithms discussed in lecture
// will always return a valid MST. If your programs cannot run to completion,
// then you know you have failed to find an MST. So if we eliminate vertices and
// the algorithm finishes, it didn't actually have to use the vertex it seems...

// vector is allowed, qsort is allowed.
// No pre-built hashtables, but you can make your own. Shouldn't have to though.

// Instructors say it's ok if the algo takes 10min+ to run. Just shouldn't take hours.

#include <iostream>
#include <vector>
#include "Union_Find.hpp"
#include "Graphs.hpp"
#include "Tests.hpp"
#include "Kruskal.hpp"

const char nn = '\n';
using namespace std;

void run_tests();

int main(int argc, const char * argv[]) {
    run_tests();
    
    Basic_Graph g1;
    Square_Graph g2;
    Cube_Graph g3;
    Hypercube_Graph g4;
    
    g1.initialize_random(256);
    g2.initialize_random(256);
    g3.initialize_random(256);
    g4.initialize_random(256);
    
    
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
    
    
    return 0;
}



void run_tests() {
    cout << "Testing..." << nn;
    test_basic_graph();
    test_square_graph();
    test_cube_graph();
    test_hypercube_graph();
    test_kruskal();
    test_union_find();
    cout << "Tests Passed!!!" << nn << nn;
}






