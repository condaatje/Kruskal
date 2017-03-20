//
//  Helpers.cpp
//  code1
//
//  Created by Eagle on 2/27/17.
//  Copyright © 2017 Ondaatje124. All rights reserved.
//

#include "Helpers.hpp"
#include <thread>
#include <stdio.h>
#include <chrono>
#include <iostream>
#include "Graphs.hpp"
#include "Kruskal.hpp"
#include "Tests.hpp"

bool DBUG = false;

using namespace std;
using namespace chrono;

const char nn = '\n';


void full_blast() {
    auto begin = high_resolution_clock::now();
    
    // Results buffers.
    vector<Result> r1;
    vector<Result> r2;
    vector<Result> r3;
    vector<Result> r4;
    
    cout << "Spawning..." << nn;
    
    thread t1a (calculate_basic, &r1, 3, VERTEX_SPEC);
    thread t1b (calculate_basic, &r1, 3, VERTEX_SPEC); // push_back is threadsafe.
    thread t2a (calculate_square, &r2, 3, VERTEX_SPEC);
    thread t2b (calculate_square, &r2, 3, VERTEX_SPEC);
    thread t3 (calculate_cube, &r3, 6, VERTEX_SPEC);
    thread t4 (calculate_hypercube, &r4, 6, VERTEX_SPEC);
    
    cout << "Threaded." << nn << nn;
    
    t1a.join();
    t1b.join();
    t2a.join();
    t2b.join();
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
