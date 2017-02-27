#include <vector>
#include <random>
#include <iostream>
#include <assert.h>
#include "Union_Find.hpp"
#include "Graphs.hpp"

using namespace std;

// set up random generator
random_device rd;
default_random_engine gen(rd()); //TODO check what the fastest random number generator is in cpp.
uniform_real_distribution<> dis(0, 1);

bool edgeCompare (Edge a, Edge b) { return (a.weight < b.weight); }


/////////////////////////BASIC GRAPH/////////////////////////

void Basic_Graph::initialize_specific(int num_vertices, vector<Edge> egs) {
    this->num_vertices = num_vertices;
    this->edges = egs;
}

void Basic_Graph::initialize_random(int num_vertices) {
    // this takes in a number of vertices, and creates a random,
    // complete, undirected graph.
    // Complete graphs on n vertices, where the weight of each edge
    // is a real number chosen uniformly at random on [0, 1].
    
    this->num_vertices = num_vertices;
    this->graph_type = "Basic";
    
    double bound = 1000.0 / (double) num_vertices;
    
    for(int i = 0; i < num_vertices; i++) {
        // set random weights for each edge
        for(int j = i; j < num_vertices; j++) {
            double w = dis(gen);
            if (w < bound) { // TODO dynamic
                Edge e(i, j, w);
                this->edges.push_back(e);
                // most of the execution cost. still not bad though.
            }
            if (w > 1) {
                assert(false);
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

void Square_Graph::initialize_specific(vector<Point2D> points) {
    this->vertices = points;
    this->num_vertices = (int) points.size();
    this->graph_type = "Square";
}

void Square_Graph::initialize_random(int num_vertices) {
    // Complete graphs on n vertices, where the vertices are points chosen uniformly
    // at random inside the unit square. (That is, the points are (x,y), with x and y each a real number
    // chosen uniformly at random from [0, 1].) The weight of an edge is just the Euclidean distance between its endpoints.
    //vertices.resize(num_vertices);
    this->num_vertices = num_vertices;
    this->graph_type = "Square";
    
    for(int i = 0; i < num_vertices; i++) {
        this->vertices.push_back(Point2D(dis(gen), dis(gen)));
    }
}

double Square_Graph::weight(int vertex1, int vertex2) {
    double xdist = abs(vertices[vertex1].x - vertices[vertex2].x);
    double ydist = abs(vertices[vertex1].y - vertices[vertex2].y);
    double step2 = (xdist * xdist) + (ydist * ydist);
    
    // ideally the compiler cleans this all up but we can mess with it in post.
    return pow(step2, 0.5);
}


/////////////////////////CUBE GRAPH/////////////////////////

void Cube_Graph::initialize_specific(vector<Point3D> points) {
    this->vertices = points;
    this->num_vertices = (int) points.size();
    this->graph_type = "Cube";
}

void Cube_Graph::initialize_random(int num_vertices) {
    // Complete graphs on n vertices, where the vertices are points chosen
    // uniformly at random inside the unit cube (3 dimensions) and hypercube (4 dimensions).
    // As with the unit square case above, the weight of an edge is just the Euclidean distance between its endpoints.
    
    //vertices.resize(num_vertices);
    this->num_vertices = num_vertices;
    this->graph_type = "Cube";
    
    for(int i = 0; i < num_vertices; i++) {
        vertices.push_back(Point3D(dis(gen), dis(gen), dis(gen)));
    }
}

double Cube_Graph::weight(int vertex1, int vertex2) {
    double xdist = abs(vertices[vertex1].x - vertices[vertex2].x);
    double ydist = abs(vertices[vertex1].y - vertices[vertex2].y);
    double zdist = abs(vertices[vertex1].z - vertices[vertex2].z);
    
    double step2 = (xdist * xdist) + (ydist * ydist) + (zdist * zdist);
    
    return pow(step2, 0.5);
}



/////////////////////////HYPERCUBE GRAPH/////////////////////////

void Hypercube_Graph::initialize_specific(vector<Point4D> points) {
    this->vertices = points;
    this->num_vertices = (int) points.size();
    this->graph_type = "HyperCube";
}

void Hypercube_Graph::initialize_random(int num_vertices) {
    // Complete graphs on n vertices, where the vertices are points chosen
    // uniformly at random inside the unit cube
    // (3 dimensions) and hypercube (4 dimensions).
    
    // As with the unit square case above,
    // the weight of an edge is just the Euclidean distance between its endpoints.
    
    //vertices.resize(num_vertices);
    this->num_vertices = num_vertices;
    this->graph_type = "HyperCube";
    
    for(int i = 0; i < num_vertices; i++) {
        vertices.push_back(Point4D(dis(gen), dis(gen), dis(gen), dis(gen)));
    }
}

double Hypercube_Graph::weight(int vertex1, int vertex2) {
    double idist = abs(vertices[vertex1].i - vertices[vertex2].i);
    double jdist = abs(vertices[vertex1].j - vertices[vertex2].j);
    double kdist = abs(vertices[vertex1].k - vertices[vertex2].k);
    double ldist = abs(vertices[vertex1].l - vertices[vertex2].l);
    
    //TODO fast squares etc. (shifts)
    
    double step2 = (idist * idist) + (jdist * jdist)
                 + (kdist * kdist) + (ldist * ldist);
    
    return  pow(step2, 0.5);
}








