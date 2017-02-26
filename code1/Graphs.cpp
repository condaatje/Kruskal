//
//  Graphs.cpp
//  code1
//
//  Created by Eagle on 2/20/17.
//  Copyright © 2017 Ondaatje124. All rights reserved.
//

#include <vector>
#include <random>
#include <iostream>
#include <assert.h> //TODO get this out of here.
#include "Union_Find.hpp"
#include "Graphs.hpp"

using namespace std; // somewhat frowned upon, but fine as long as nobody is dumb and collides with std...

// set up random generator
random_device rd;
default_random_engine gen(rd()); //TODO check what the fastest random number generator is in cpp.
uniform_real_distribution<> dis(0, 1);

bool edgeCompare (Edge a, Edge b) { return (a.weight < b.weight); }


/////////////////////////BASIC GRAPH/////////////////////////

void Basic_Graph::initialize_random(int num_vertices) {
    // this takes in a number of vertices, and creates a random, complete, undirected graph.
    // Complete graphs on n vertices, where the weight of each edge is a real number chosen uniformly at random on [0, 1].
    // very slow, and much space for 131,072 vertices...
    
    //edges.resize(num_vertices);
    
    this->num_vertices = num_vertices;
    
    //resize first?
    //    for(int i = 0; i < num_vertices; i++) {
    //        // quick resize (TODO figure out how to do this once before each average cycle, not once per intit)
    //        edges[i].resize(num_vertices);
    //    }
    
    double bound = 1000.0 / (double) num_vertices;
    
    for(int i = 0; i < num_vertices; i++) {
        // set random weights for each edge
        for(int j = i; j < num_vertices; j++) {
            // TODO this has to be pruned for 131072. just not a healthy size.
            // A. needs to be n choose 2 not n^2
            // B. lets eliminate large edges once we've figured out a good
            // value, but make sure that we're checking for correctness in
            // Kruskal's. How can we manage dropping edges without messing
            // up indexing etc?
            
            // edges[i][j] = dis(gen);
            double w = dis(gen);
            if (w < bound) { // TODO dynamic
                Edge e;
                e.v1 = i;
                e.v2 = j;
                e.weight = w;
                this->edges.push_back(e);
            } else {
                if (w > 3) { // hypercube should max at 2.something
                    assert(false); // TODO cleanup.
                }
            }
        }
    }
}

double Basic_Graph::weight(int vertex1, int vertex2) {
    assert(false); // TODO bad.
    return NULL;
}

double Basic_Graph::average_weight() {
    double acc = 0.0;
    double divisor = 0.0;
    
    for(int i = 0; i < this->edges.size(); i++) {
        acc += this->edges[i].weight;
        divisor += 1;
        if (acc <= 0 || divisor <= 0) { //check for overflow
            assert(false);
        }
    }
    
    return acc / divisor;
}





/////////////////////////SQUARE GRAPH/////////////////////////

void Square_Graph::initialize_random(int num_vertices) {
    // Complete graphs on n vertices, where the vertices are points chosen uniformly
    // at random inside the unit square. (That is, the points are (x,y), with x and y each a real number
    // chosen uniformly at random from [0, 1].) The weight of an edge is just the Euclidean distance between its endpoints.
    vertices.resize(num_vertices);
    this->num_vertices = num_vertices;
    
    for(int i = 0; i < num_vertices; i++) {
        vertices[i].x = dis(gen);
        vertices[i].y = dis(gen);
    }
}

double Square_Graph::weight(int vertex1, int vertex2) {
    double xdist = abs(vertices[vertex1].x - vertices[vertex2].x);
    double ydist = abs(vertices[vertex1].y - vertices[vertex2].y);
    
    //TODO fast squares etc. (shifts)
    
    double x2ply2 = (xdist * xdist) + (ydist * ydist);
    
    double dist = pow(x2ply2, 0.5);
    
    // ideally the compiler cleans this all up but we can mess with it in post.
    return dist;
}


/////////////////////////CUBE GRAPH/////////////////////////
void Cube_Graph::initialize_random(int num_vertices) {
    // Complete graphs on n vertices, where the vertices are points chosen
    // uniformly at random inside the unit cube (3 dimensions) and hypercube (4 dimensions).
    // As with the unit square case above, the weight of an edge is just the Euclidean distance between its endpoints.
    
    vertices.resize(num_vertices);
    this->num_vertices = num_vertices;
    
    for(int i = 0; i < num_vertices; i++) {
        vertices[i].x = dis(gen);
        vertices[i].y = dis(gen);
        vertices[i].z = dis(gen);
    }
}

double Cube_Graph::weight(int vertex1, int vertex2) {
    double xdist = abs(vertices[vertex1].x - vertices[vertex2].x);
    double ydist = abs(vertices[vertex1].y - vertices[vertex2].y);
    double zdist = abs(vertices[vertex1].z - vertices[vertex2].z);
    
    //TODO fast squares etc. (shifts)
    
    double x2ply2plz2 = (xdist * xdist) + (ydist * ydist) + (zdist * zdist);
    
    double dist = pow(x2ply2plz2, 0.5);
    
    // ideally the compiler cleans this all up but we can mess with it in post.
    return dist;
}



/////////////////////////HYPERCUBE GRAPH/////////////////////////

void Hypercube_Graph::initialize_random(int num_vertices) {
    // Complete graphs on n vertices, where the vertices are points chosen
    // uniformly at random inside the unit cube
    // (3 dimensions) and hypercube (4 dimensions).
    
    // As with the unit square case above,
    // the weight of an edge is just the Euclidean distance between its endpoints.
    
    vertices.resize(num_vertices);
    this->num_vertices = num_vertices;
    
    for(int i = 0; i < num_vertices; i++) {
        vertices[i].i = dis(gen);
        vertices[i].j = dis(gen);
        vertices[i].k = dis(gen);
        vertices[i].l = dis(gen);
    }
}

double Hypercube_Graph::weight(int vertex1, int vertex2) {
    double idist = abs(vertices[vertex1].i - vertices[vertex2].i);
    double jdist = abs(vertices[vertex1].j - vertices[vertex2].j);
    double kdist = abs(vertices[vertex1].k - vertices[vertex2].k);
    double ldist = abs(vertices[vertex1].l - vertices[vertex2].l);
    
    //TODO fast squares etc. (shifts)
    
    double x2ply2plz2 = (idist * idist) + (jdist * jdist) + (kdist * kdist) + (ldist * ldist);
    
    double dist = pow(x2ply2plz2, 0.5);
    
    // ideally the compiler cleans this all up but we can mess with it in post.
    return dist;
}








