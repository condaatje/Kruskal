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
// Step 1: Create Graph Class
// There must be a method through which I can easily and efficiently create a random graph
// in each of the three manners
// How to represent/access vertices and edges?
// What's the fastest? What's the most space efficient? Which is more important?


// Step 2: ????



#include <iostream>
#include <chrono>
#include <assert.h>
#include <thread>
#include <vector>
#include <random>


const char nn = '\n';
using namespace std; // somewhat frowned upon, but fine as long as nobody is dumb and collides with std...

// Complete graph: all possible n choose 2 edges must be present in the graph.

// set up random generator
random_device rd;
default_random_engine gen(rd()); //TODO check what the fastest random number generator is in cpp.
uniform_real_distribution<> dis(0, 1);

class Point2D {
public:
    int x;
    int y;
};

class Point3D {
public:
    int x;
    int y;
    int z;
};

class Point4D {
public:
    int i;
    int j;
    int k;
    int l;
};

class Basic_Graph {
    vector<vector<float>> edges;
    
public:
    void initialize_random(int num_vertices) {
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
            // quick resize (TODO figure out how to do this once before each average cycle, not once per intit)
            // set random weights for each edge
            for(int j = 0; j < num_vertices; j++) {
                edges[i][j] = dis(gen);
            }
        }
    }
};



class Square_Graph {
    vector<Point2D> vertices;
    
public:
    void initialize_random(int num_vertices) {
        // Complete graphs on n vertices, where the vertices are points chosen uniformly
        // at random inside the unit square. (That is, the points are (x,y), with x and y each a real number
        // chosen uniformly at random from [0, 1].) The weight of an edge is just the Euclidean distance between its endpoints.
        vertices.resize(num_vertices);
        
        for(int i = 0; i < num_vertices; i++) {
            vertices[i].x = dis(gen);
            vertices[i].y = dis(gen);
        }
    }
};


class Cube_Graph {
    vector<Point3D> vertices;
    
public:
    void initialize_random(int num_vertices) {
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
};


class Hypercube_Graph {
    vector<Point4D> vertices;
public:
    void initialize_random(int num_vertices) {
        // Complete graphs on n vertices, where the vertices are points chosen
        // uniformly at random inside the unit cube (3 dimensions) and hypercube (4 dimensions).
        // As with the unit square case above, the weight of an edge is just the Euclidean distance between its endpoints.
    
        vertices.resize(num_vertices);
        
        for(int i = 0; i < num_vertices; i++) {
            vertices[i].i = dis(gen);
            vertices[i].j = dis(gen);
            vertices[i].k = dis(gen);
            vertices[i].l = dis(gen);
        }
    }
};





int main(int argc, const char * argv[]) {
    //vector<int> v = {7, 5, 16, 8};
    //auto testData = std::unique_ptr<unsigned char[]>{ new unsigned char[16000] };
    //std::vector< std::vector< float > > item ( 2, std::vector<float> ( 2, 0 ) );
    Basic_Graph g1;
    Square_Graph g2;
    Cube_Graph g3;
    Hypercube_Graph g4;
    
    //g1.initialize_random(131072); //will certainly fail until I find a better way to save memory.
    g1.initialize_random(8192);
    
    // fast and no n^2 space
    g2.initialize_random(131072);
    g3.initialize_random(131072);
    g4.initialize_random(131072);
    
    cout << "TODO ALL" << nn;
    return 0;
}




//http://www.cs.fsu.edu/~myers/cop3330/notes/dma.html
//http://en.cppreference.com/w/cpp/container/vector
//http://en.cppreference.com/w/cpp/memory/unique_ptr
//http://www.cplusplus.com/forum/beginner/12409/
//http://www.cplusplus.com/reference/vector/vector/
//http://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
//http://en.cppreference.com/w/cpp/numeric/random










