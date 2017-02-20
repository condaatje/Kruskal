//
//  Graphs.cpp
//  code1
//
//  Created by Eagle on 2/20/17.
//  Copyright © 2017 Ondaatje124. All rights reserved.
//

#include <vector>
#include <random>
#include <assert.h> //TODO get this out of here.
#include "Union_Find.hpp"
#include "Graphs.hpp"

using namespace std; // somewhat frowned upon, but fine as long as nobody is dumb and collides with std...

// set up random generator
random_device rd;
default_random_engine gen(rd()); //TODO check what the fastest random number generator is in cpp.
uniform_real_distribution<> dis(0, 1);




/////////////////////////BASIC GRAPH/////////////////////////

void Basic_Graph::initialize_random(int num_vertices) {
    // this takes in a number of vertices, and creates a random, complete, undirected graph.
    // Complete graphs on n vertices, where the weight of each edge is a real number chosen uniformly at random on [0, 1].
    // very slow, and much space for 131,072 vertices...
    
    edges.resize(num_vertices);
    
    //resize first?
    for(int i = 0; i < num_vertices; i++) {
        // quick resize (TODO figure out how to do this once before each average cycle, not once per intit)
        edges[i].resize(num_vertices);
    }
    
    for(int i = 0; i < num_vertices; i++) {
        // set random weights for each edge
        for(int j = 0; j < num_vertices; j++) {
            edges[i][j] = dis(gen);
        }
    }
}

double Basic_Graph::distance(int vertex1, int vertex2) {
    return edges[vertex1][vertex2];
    // TODO UNDIRECTED!!!!
}

double Basic_Graph::average_weight() {
    double acc = 0.1;
    for(int i = 0; i < edges.size(); i++) {
        for(int j = 0; j < edges.size(); j++) {
            
            
            //TODO check correctness? isn't this going to double count?
            acc += edges[i][j];
            if (acc < 0) {
                assert(false);
            }
        }
        //acc = acc / vertices.size();
    }
    
    
    // watch out for overflow
    acc = acc / edges.size();
    acc = acc / edges.size();
    return acc;
}





/////////////////////////SQUARE GRAPH/////////////////////////

void Square_Graph::initialize_random(int num_vertices) {
    // Complete graphs on n vertices, where the vertices are points chosen uniformly
    // at random inside the unit square. (That is, the points are (x,y), with x and y each a real number
    // chosen uniformly at random from [0, 1].) The weight of an edge is just the Euclidean distance between its endpoints.
    vertices.resize(num_vertices);
    
    for(int i = 0; i < num_vertices; i++) {
        vertices[i].x = dis(gen);
        vertices[i].y = dis(gen);
    }
}



/////////////////////////CUBE GRAPH/////////////////////////
void Cube_Graph::initialize_random(int num_vertices) {
    // Complete graphs on n vertices, where the vertices are points chosen
    // uniformly at random inside the unit cube (3 dimensions) and hypercube (4 dimensions).
    // As with the unit square case above, the weight of an edge is just the Euclidean distance between its endpoints.
    
    vertices.resize(num_vertices);
    
    for(int i = 0; i < num_vertices; i++) {
        vertices[i].x = dis(gen);
        vertices[i].y = dis(gen);
        vertices[i].z = dis(gen);
    }
}



/////////////////////////HYPERCUBE GRAPH/////////////////////////

void Hypercube_Graph::initialize_random(int num_vertices) {
    // Complete graphs on n vertices, where the vertices are points chosen
    // uniformly at random inside the unit cube
    // (3 dimensions) and hypercube (4 dimensions).
    
    // As with the unit square case above,
    // the weight of an edge is just the Euclidean distance between its endpoints.
    
    vertices.resize(num_vertices);
    
    for(int i = 0; i < num_vertices; i++) {
        vertices[i].i = dis(gen);
        vertices[i].j = dis(gen);
        vertices[i].k = dis(gen);
        vertices[i].l = dis(gen);
    }
}










