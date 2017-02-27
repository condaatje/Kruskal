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
double nanoconv = 1000000000;

class Result {
public:
    Result(string graph_type, double vertices, double nanoseconds, double weight) {
        this->graph_type = graph_type;
        this->vertices = vertices;
        this->nanoseconds = nanoseconds;
        this->weight = weight;
    }
    string graph_type;
    double vertices;
    double nanoseconds;
    double weight;
};

void run_tests();
vector<Result> calculate_basic();
vector<Result> calculate_square();
vector<Result> calculate_cube();
vector<Result> calculate_hypercube();
void print_result(Result r);
void print_result_vector(vector<Result> r);
void print_strings(vector<string> strs);
double k(int n);

int main(int argc, const char * argv[]) {
    run_tests();
    
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
    
    vector<Result> r1 = calculate_basic();
    vector<Result> r2 = calculate_square();
    vector<Result> r3 = calculate_cube();
    vector<Result> r4 = calculate_hypercube();
    
    print_result_vector(r1);
    print_result_vector(r2);
    print_result_vector(r3);
    print_result_vector(r4);
    
    cout << nn << "We made it." << nn;

    
    // TODO multithreading. Going to be a lot going on.
    // At least 5 trials per size for each type of graph.
    // We've got 4 cores so that works pretty nicely.
    
    return 0;
}

vector<Result> calculate_basic() {
    vector<Result> results;
    auto begin = high_resolution_clock::now();
    // n = 128; 256; 512; 1024; 2048; 4096; 8192; 16384; 32768; 65536; 131072;
    
    int n = 1024;
    Basic_Graph g;
    g.initialize_random(n);
    double weight = kruskal_basic(&g, k(n)); // TODO tighter/dynamic
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end-begin).count();
    
    Result r("Basic", n, duration, weight);
    
    results.push_back(r);
    // 4 minutes without --Ofast
    // 1.5 minutes with
    
    return results;
}

vector<Result> calculate_square() {
    vector<Result> results;
    
    auto begin = high_resolution_clock::now();
    int n = 1024;
    
    // n = 128; 256; 512; 1024; 2048; 4096; 8192; 16384; 32768; 65536; 131072;
    Square_Graph g;
    g.initialize_random(n);
    double weight = kruskal_euclid(&g, k(n)); // TODO tighter/dynamic
    
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end-begin).count();
    
    // 4 minutes without --Ofast
    // 1.5 minutes with
    // TODO free.
    
    Result r("Square", n, duration, weight);
    
    results.push_back(r);
    return results;
}

vector<Result> calculate_cube() {
    vector<Result> results;
    auto begin = high_resolution_clock::now();
    
    // n = 128; 256; 512; 1024; 2048; 4096; 8192; 16384; 32768; 65536; 131072;
    int n = 1024;
    Cube_Graph g;
    g.initialize_random(n);
    double weight = kruskal_euclid(&g, k(n)); // TODO tighter/dynamic
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end-begin).count();
    
    // 6 minutes without -Ofast
    Result r("Cube", n, duration, weight);

    results.push_back(r);
    return results;
}

vector<Result> calculate_hypercube() {
    vector<Result> results;
    
    auto begin = high_resolution_clock::now();
    
    // n = 128; 256; 512; 1024; 2048; 4096; 8192; 16384; 32768; 65536; 131072;
    int n = 1024;
    
    Hypercube_Graph g;
    g.initialize_random(n);
    double weight = kruskal_euclid(&g, k(n)); // TODO tighter/dynamic
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end-begin).count();
    
    Result r("HyperCube", n, duration, weight);
    results.push_back(r);

    return results;
}

void print_strings(vector<string> strs) {
    for(int i = 0; i < strs.size(); i++) {
        cout << strs[i] << nn;
    }
    cout << nn;
}

void print_result(Result r) {
    cout << r.graph_type  << " Graph, "
         << r.vertices    << " vertices: "
         << r.weight      << " MST weight, "
         << r.nanoseconds/nanoconv << " seconds " << nn;
}

void print_result_vector(vector<Result> r) {
    for(int i = 0; i < r.size(); i++){
        print_result(r[i]);
    }
    // cout << nn;
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


// Bounding function (TODO think more about this)
double k(int n) {
    return 1000.0 / ((double) n);
}






