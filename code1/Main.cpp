// 60951527
// ./randmst 0 numpoints numtrials dimension


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


#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <assert.h>
#include "Union_Find.hpp"
#include "Graphs.hpp"
#include "Main.hpp"
#include "Tests.hpp"
#include "Kruskal.hpp"

bool DBUG = false;

const char nn = '\n';
using namespace std; // somewhat frowned upon, but fine as long as nobody is dumb and collides with std...
using namespace chrono;
double nanoconv = 1000000000;
vector<int> VERTEX_SPEC = {128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072};



void run_tests();

void calculate_basic(vector<Result> * r, int trials, vector<int> numpoints);
void calculate_square(vector<Result> * r, int trials, vector<int> numpoints);
void calculate_cube(vector<Result> * r, int trials, vector<int> numpoints);
void calculate_hypercube(vector<Result> * r, int trials, vector<int> numpoints);

void print_result(Result r, int numtrials);
void print_result_vector(vector<Result> r);
void print_avg(vector<Result> r, int numtrials, vector<int> numpoints);
void print_strings(vector<string> strs);

int dim_translate(string s);

void full_blast();

double k(int n);


int main(int argc, const char * argv[]) {
    if(argc != 5) {
        cout << "Usage: ./randmst <flag> <numpoints> <numtrials> <dimension> "
             << endl;
        cout << "Flags: " << nn << "     0 - Staff, 1 - Full Blast, 2 - Test"
             << endl;
        return 1;
    }
    
    int flag = atoi(argv[1]);
    
    if (flag == 1) {
        DBUG = true;
        full_blast();
    }
    else if (flag == 2) {
        DBUG = true;
        run_tests();
    }
    
    else if (flag == 0) {
        DBUG = false;
        // Staff reqs.
        
        // ./randmst 0 numpoints numtrials dimension
        int numpoints = atoi(argv[2]);
        int numtrials = atoi(argv[3]);
        int dimension = atoi(argv[4]);
        
        if (dimension == 0) {
            vector<Result> r;
            calculate_basic(&r, numtrials, {numpoints});
            print_avg(r, numtrials, {numpoints});
        }
        else if (dimension == 2) {
            vector<Result> r;
            calculate_square(&r, numtrials, {numpoints});
            print_avg(r, numtrials, {numpoints});
        }
        else if (dimension == 3) {
            vector<Result> r;
            calculate_cube(&r, numtrials, {numpoints});
            print_avg(r, numtrials, {numpoints});
        }
        else if (dimension == 4) {
            vector<Result> r;
            calculate_hypercube(&r, numtrials, {numpoints});
            print_avg(r, numtrials, {numpoints});
        }
        else {
            cout << "Error: Unrecognized dimension" << nn;
            return 2;
        }
    }
    else {
        cout << "Error: Unrecognized flag. " << nn;
        return 3;
    }
    
    return 0;
}


void full_blast() {
    auto begin = high_resolution_clock::now();
    
    // Results buffers.
    vector<Result> r1;
    vector<Result> r2;
    vector<Result> r3;
    vector<Result> r4;
    
    cout << "Spawning..." << nn;
    
    thread t1 (calculate_basic, &r1, 6, VERTEX_SPEC);
    thread t2 (calculate_square, &r2, 6, VERTEX_SPEC);
    thread t3 (calculate_cube, &r3, 6, VERTEX_SPEC);
    thread t4 (calculate_hypercube, &r4, 6, VERTEX_SPEC);
    
    cout << "Threaded." << nn << nn;
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    
    cout << nn << endl;
    
    print_avg(r1, 6, VERTEX_SPEC);
    print_avg(r2, 6, VERTEX_SPEC);
    print_avg(r3, 6, VERTEX_SPEC);
    print_avg(r4, 6, VERTEX_SPEC);
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end-begin).count();
    
    cout << nn << "We made it." << nn << nn;
    cout << "Full run: " << (duration / nanoconv) / 60 << " minutes" << nn;
}


void calculate_basic(vector<Result> * results, int trials, vector<int> numpoints) {
    for(int i = 0; i < numpoints.size(); i++) {
        for(int j = 0; j < trials; j++) {
            auto begin = high_resolution_clock::now();
            
            int n = numpoints[i];
            Basic_Graph g;
            g.initialize_random(n);
            double weight = kruskal_basic(&g);
            
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end-begin).count();
            
            Result r("Basic", n, duration, weight);
            results->push_back(r);
        }
    }
    if(DBUG) {
        cout << "Finished a Basic run, " << trials << " trials. " << nn;
    }
    // 4 minutes without --Ofast
    // 1.5 minutes with
}

// TODO combine these functions?
void calculate_square(vector<Result> * results, int trials, vector<int> numpoints) {
    for(int i = 0; i < numpoints.size(); i++) {
        for(int j = 0; j < trials; j++) {
            auto begin = high_resolution_clock::now();
            
            int n = numpoints[i];
            Square_Graph g;
            g.initialize_random(n);
            double weight = kruskal_euclid(&g, k(n));
            
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end-begin).count();
            
            Result r("Square", n, duration, weight);
            results->push_back(r);
        }
    }
    if(DBUG) {
        cout << "Finished a Square run, " << trials << " trials. " << nn;
    }
}


void calculate_cube(vector<Result> * results, int trials, vector<int> numpoints) {
    for(int i = 0; i < numpoints.size(); i++) {
        for(int j = 0; j < trials; j++) {
            auto begin = high_resolution_clock::now();
            
            int n = numpoints[i];
            Cube_Graph g;
            g.initialize_random(n);
            double weight = kruskal_euclid(&g, k(n));
            
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end-begin).count();
            
            Result r("Cube", n, duration, weight);
            results->push_back(r);
        }
    }
    if(DBUG) {
        cout << "Finished a Cube run, " << trials << " trials. " << nn;
    }
}


void calculate_hypercube(vector<Result> * results, int trials, vector<int> numpoints) {
    for(int i = 0; i < numpoints.size(); i++) {
        for(int j = 0; j < trials; j++) {
            auto begin = high_resolution_clock::now();
            
            int n = numpoints[i];
            Hypercube_Graph g;
            g.initialize_random(n);
            double weight = kruskal_euclid(&g, k(n));
            
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end-begin).count();
            
            Result r("HyperCube", n, duration, weight);
            results->push_back(r);
        }
    }
    if(DBUG) {
        cout << "Finished a HyperCube run, " << trials << " trials. " << nn;
    }
}


void print_strings(vector<string> strs) {
    for(int i = 0; i < strs.size(); i++) {
        cout << strs[i] << nn;
    }
    cout << nn;
}


void print_result(Result r, int numtrials) {
    if(DBUG == true) {
        cout << r.graph_type  << " Graph, "
        << r.vertices    << " vertices: "
        << r.weight      << " MST weight, "
        << r.nanoseconds/nanoconv << " seconds" << nn;
    }
    else {
        cout << r.weight << " " << r.vertices << " "
        << numtrials << " " << dim_translate(r.graph_type) << nn;
    }
}


void print_result_vector(vector<Result> r) {
    for(int i = 0; i < r.size(); i++){
        print_result(r[i], -1);
    }
}

void print_avg(vector<Result> r, int numtrials, vector<int> numpoints) {
    // Not efficient but correct.
    // These are small vectors and I don't want to implement a dictionary.
    
    for(int i = 0; i < numpoints.size(); i++) {
        Result avg(r[0].graph_type, numpoints[i], 0, 0);
        // WARNING make sure not to mix graph types between vectors. (enforce)
        // Alternatively, fix this so it's generalized. (TODO)
        
        double div = 0.0;
        
        for(int j = 0; j < r.size(); j++){
            if(r[j].vertices == (double) numpoints[i]) {
                avg.weight += r[j].weight;
                avg.nanoseconds += r[j].nanoseconds;
                div += 1;
            }
        }
        
        avg.vertices = numpoints[i];
        avg.nanoseconds = avg.nanoseconds / div;
        avg.weight = avg.weight / div;
        
        print_result(avg, numtrials);
    }
}

void run_tests() {
    cout << "Testing..." << nn;
    
    test_kruskal();
    test_union_find();
    
    cout << "Tests Passed!!!" << nn << nn;
}


// Bounding function (trial and error)
double k(int n) {
    return 15000.0 / ((double) n);
}

// TODO full program fix-up on ease-of-use with dimensionality.
// replace with enum?
int dim_translate(string s) {
    if (s == "Basic") {
        return 0;
    }
    else if (s == "Square") {
        return 2;
    }
    else if (s == "Cube") {
        return 3;
    }
    else if (s == "HyperCube") {
        return 4;
    }
    return -1;
}



