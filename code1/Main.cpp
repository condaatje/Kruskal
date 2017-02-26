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
#include <chrono>
#include <vector>
#include "Union_Find.hpp"
#include "Graphs.hpp"
#include "Tests.hpp"
#include "Kruskal.hpp"

const char nn = '\n';
using namespace std;
using namespace chrono;


void run_tests();

int main(int argc, const char * argv[]) {
    run_tests();
    
    Basic_Graph g1;
    Square_Graph g2;
    Cube_Graph g3;
    Hypercube_Graph g4;
    
    //g1.initialize_random(256);
    //g2.initialize_random(256);
    //g3.initialize_random(256);
    //g4.initialize_random(256);
    
    
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
    
    
    
    cout << "Calculating Basic..." << nn;
    auto begin = high_resolution_clock::now();
    
    // n = 128; 256; 512; 1024; 2048; 4096; 8192; 16384; 32768; 65536; 131072;
    g1.initialize_random(131072);
    double g1_weight = kruskal_basic(&g1, 0.01); // TODO tighter/dynamic
    cout << "MST weight: " << g1_weight << nn;
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end-begin).count();
    double nanoconv = 1000000000;
    cout << (duration / nanoconv) / 60 << " minutes" << nn << nn;
    // 4 minutes without --Ofast
    // 1.5 minutes with
    // TODO free.
    
    
    cout << "Calculating Square..." << nn;
    begin = high_resolution_clock::now();
    g2.initialize_random(131072);
    double g2_weight = kruskal_euclid(&g2, 0.01); // TODO tighter/dynamic
    cout << "MST weight: " << g2_weight << nn;
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end-begin).count();
    cout << (duration / nanoconv) / 60 << " minutes" << nn << nn;
    // 6 minutes without -Ofast
    // 0.55 minutes with
    
    
    cout << "Calculating Cube..." << nn;
    begin = high_resolution_clock::now();
    g3.initialize_random(131072);
    double g3_weight = kruskal_euclid(&g3, 0.04); // TODO tighter/dynamic
    cout << "MST weight: " << g3_weight << nn;
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end-begin).count();
    cout << (duration / nanoconv) / 60 << " minutes" << nn << nn;
    // 0.57 min
    
    cout << "Calculating HyperCube..." << nn;
    begin = high_resolution_clock::now();
    g4.initialize_random(131072);
    double g4_weight = kruskal_euclid(&g4, 0.1); // TODO tighter/dynamic
    cout << "MST weight: " << g4_weight << nn;
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end-begin).count();
    cout << (duration / nanoconv) / 60 << " minutes" << nn << nn;
    // 0.66 min
    
    cout << nn << "We made it." << nn;

    
    // TODO multithreading. Going to be a lot going on.
    // At least 5 trials per size for each type of graph.
    // We've got 4 cores so that works pretty nicely.
    
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






