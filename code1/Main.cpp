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
#include "Union_Find.hpp"
#include "Graphs.hpp"
#include "Tests.hpp"
#include "Kruskal.hpp"

const char nn = '\n';
using namespace std; // somewhat frowned upon, but fine as long as nobody is dumb and collides with std...
using namespace chrono;
double nanoconv = 1000000000;
vector<int> VERTEX_SPEC = {128, 256, 512, 1024};//, 2048, 4096, 8192, 16384, 32768, 65536, 131072};

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

void calculate_basic(vector<Result> * r, int trials);
void calculate_square(vector<Result> * r, int trials);
void calculate_cube(vector<Result> * r, int trials);
void calculate_hypercube(vector<Result> * r, int trials);

void print_result(Result r);
void print_result_vector(vector<Result> r);
void print_avg(vector<Result> r);
void print_strings(vector<string> strs);

double k(int n);


int main(int argc, const char * argv[]) {
    run_tests();
    
    auto begin = high_resolution_clock::now();
    
    // Results buffers.
    vector<Result> r1;
    vector<Result> r2;
    vector<Result> r3;
    vector<Result> r4;
    
    cout << "Spawning..." << nn;
    
    thread t1a (calculate_basic, &r1, 3);
    thread t1b (calculate_basic, &r1, 3); // push_back is threadsafe.
    thread t2a (calculate_square, &r2, 3);
    thread t2b (calculate_square, &r2, 3);
    thread t3 (calculate_cube, &r3, 6);
    thread t4 (calculate_hypercube, &r4, 6);
    
    cout << "Threaded." << nn << nn;
    
    t1a.join();
    t1b.join();
    t2a.join();
    t2b.join();
    t3.join();
    t4.join();
    
    cout << nn << endl;

    print_avg(r1);
    print_avg(r2);
    print_avg(r3);
    print_avg(r4);
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end-begin).count();
    
    cout << nn << "We made it." << nn << nn;
    cout << "Full run: " << (duration / nanoconv) / 60 << " minutes" << nn;
    return 0;
}


void calculate_basic(vector<Result> * results, int trials) {
    for(int i = 0; i < VERTEX_SPEC.size(); i++) {
        for(int j = 0; j < trials; j++) {
            auto begin = high_resolution_clock::now();
            
            int n = VERTEX_SPEC[i];
            Basic_Graph g;
            g.initialize_random(n);
            double weight = kruskal_basic(&g);
            
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end-begin).count();
            
            Result r("Basic", n, duration, weight);
            results->push_back(r);
        }
    }
    
    cout << "Finished a Basic run, " << trials << " trials. " << nn;
    // 4 minutes without --Ofast
    // 1.5 minutes with
}


void calculate_square(vector<Result> * results, int trials) {
    for(int i = 0; i < VERTEX_SPEC.size(); i++) {
        for(int j = 0; j < trials; j++) {
            auto begin = high_resolution_clock::now();
            
            int n = VERTEX_SPEC[i];
            Square_Graph g;
            g.initialize_random(n);
            double weight = kruskal_euclid(&g, k(n)); // TODO tighter/dynamic
            
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end-begin).count();
            
            Result r("Square", n, duration, weight);
            results->push_back(r);
        }
    }
    cout << "Finished a Square run, " << trials << " trials. " << nn;
}


void calculate_cube(vector<Result> * results, int trials) {
    for(int i = 0; i < VERTEX_SPEC.size(); i++) {
        for(int j = 0; j < trials; j++) {
            auto begin = high_resolution_clock::now();
            
            int n = VERTEX_SPEC[i];
            Cube_Graph g;
            g.initialize_random(n);
            double weight = kruskal_euclid(&g, k(n)); // TODO tighter/dynamic
            
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end-begin).count();
            
            Result r("Cube", n, duration, weight);
            results->push_back(r);
        }
    }
    
    cout << "Finished a Cube run, " << trials << " trials. " << nn;
}


void calculate_hypercube(vector<Result> * results, int trials) {
    for(int i = 0; i < VERTEX_SPEC.size(); i++) {
        for(int j = 0; j < trials; j++) {
            auto begin = high_resolution_clock::now();
            
            int n = VERTEX_SPEC[i];
            Hypercube_Graph g;
            g.initialize_random(n);
            double weight = kruskal_euclid(&g, k(n)); // TODO tighter/dynamic
            
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end-begin).count();
            
            Result r("HyperCube", n, duration, weight);
            results->push_back(r);
        }
    }
    
    cout << "Finished a HyperCube run, " << trials << " trials. " << nn;
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
    << r.nanoseconds/nanoconv << " seconds" << nn;
}


void print_result_vector(vector<Result> r) {
    for(int i = 0; i < r.size(); i++){
        print_result(r[i]);
    }
}

void print_avg(vector<Result> r) {
    // Not efficient but correct.
    // These are small vectors and I don't want to implement a dictionary.
    
    for(int i = 0; i < VERTEX_SPEC.size(); i++) {
        Result avg(r[0].graph_type, i, 0, 0);
        // TODO make sure not to mix graph types between vectors. (enforce)
        double div = 0.0;
        
        for(int j = 0; j < r.size(); j++){
            if(r[j].vertices == VERTEX_SPEC[i]) {
                avg.weight += r[j].weight;
                avg.nanoseconds += r[j].nanoseconds;
                div += 1;
            }
        }
        avg.vertices = VERTEX_SPEC[i];
        avg.nanoseconds = avg.nanoseconds / div;
        avg.weight = avg.weight / div;
        
        print_result(avg);
    }
}

void run_tests() {
    cout << "Testing..." << nn;
    
    test_kruskal();
    test_union_find();
    
    cout << "Tests Passed!!!" << nn << nn;
}


// Bounding function (TODO think more about this)
double k(int n) {
    return 15000.0 / ((double) n);
}






