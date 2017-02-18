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
// Step 1: Create Graph Class for each type of graph implementation
    // Complete graph: all possible n choose 2 edges must be present in the graph.
    // What's the fastest? What's the most space efficient? Which is more important?


// At this point, I will not worry about space, and more about correctness.


// Step 2: MST Algorithm
    // Takes in a graph, returns length of MST
    // Prims or Kruskals? Lecture 6 should dive into Union find
    // and give you a better indication of which algorithm to use
    // Libraries for "sorting" are allowed
    //

// Step 3: Start to worry about space. how can we avoid 64gigs mem?






#include <iostream>
#include <chrono>
#include <assert.h>
#include <thread>
#include <vector>
#include <random>


const char nn = '\n';
using namespace std; // somewhat frowned upon, but fine as long as nobody is dumb and collides with std...

// set up random generator
random_device rd;
default_random_engine gen(rd()); //TODO check what the fastest random number generator is in cpp.
uniform_real_distribution<> dis(0, 1);

struct Point1D {
    double x;
};


struct Point2D {
    double x;
    double y;
};

struct Point3D {
    double x;
    double y;
    double z;
};

struct Point4D {
    double i;
    double j;
    double k;
    double l;
};

class Basic_Graph {
    vector<vector<double>> edges; //TODO float? smaller.
    
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
            // set random weights for each edge
            for(int j = 0; j < num_vertices; j++) {
                edges[i][j] = dis(gen);
            }
        }
    }
    
    double distance(int vertex1, int vertex2) {
        return edges[vertex1][vertex2];
        // TODO UNDIRECTED!!!!
    }
    
    double average_weight() {
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



class Node {
public:
    // shared_ptr<Node> parent; // ARC
    Node * parent; // be careful...
    int rank;
    int value;
    
};



class Union_Find {
    vector<Node> sets;

public:
    Union_Find(int size) {
        sets.resize(size); // TODO this will probably be shattered when I have to start doctoring space.
    }
    
    void makeset(int x) {
        // takes in a vertex. creates a set out of it solo.
        
        
        Node n; // TODO does this malloc?
        n.value = x;
        n.rank = 0;
        n.parent = &n;
        // n.parent = make_shared<Node>(n); // TODO research
        
        sets[x] = n;
    }
    
    // "union" is taken
    void onion(int x, int y) {
        // replace two sets containing x and y with their union.
        this->link(this->find(x), this->find(y)); // TODO check this.
    }
    
    Node * find(int x) {
        // TODO return the set containing element x
        
        // if x ̸= p(x) then
            // p(x) := FIND(p(x))
            // return( p(x))
        
        Node n = sets[x];
        
        if (n.parent->value != n.value) {
            n.parent = find(n.parent->value); // walk the node up the tree (flattens as it finds)
        }
        
        return n.parent;
    }
    
    Node * link(Node * a, Node * b) {
        // if rank(x) > rank(y) then x ↔ y
        // if rank(x) = rank(y) then rank(y) := rank(y) + 1
        // p(x) := y
        // return(y)
        
        
        // put the smaller rank tree as a child of the bigger rank tree
        if (a->rank > b->rank) {
            // swap pointers
            Node * temp_ptr = b;
            b = a;
            a = temp_ptr;
        }
        if (a->rank == b->rank) {
            a->rank = b->rank + 1;
        }
        
        a->parent = b;
        return b;
    }
    
    void clean() {
        // NOTE: check that this is right, but the way this is set up, everything is chill when the vector is wiped.
        
        for(int i = 0; i < sets.size(); i++) {
            
            //            for(Node * n = sets[i]; n->parent != n; n = n->parent) {
            //                // Ideally this doesn't get activated, because we're flat.
            //                cout << "TODO this shouldn't happen. If it does, need to free these guys: "
            //                     << n->value << nn;;
            //            }
            // cout << "Freeing node: " << sets[i].value << endl;
            // free(sets[i]);
        }
    }
    
    void print() {
        // TODO more functionality.
        cout << "Union Find string rep: " << sets.size() << endl;
    }
};




// TODO subclass/interface the graphs so this can just take the superclass.
double kruskal(Basic_Graph) {
    // kruskal's algorithm takes in a graph, and calculates the MST.
    // in this case, we will use it to return the weight of the MST it finds.
    
    // 1: Sort the edges.
        // We are allowed to simply do this with a library function
    // 2: for every vertex, make a new set (MAKESET)
    // 3: for every edge (in increasing order)
        // If they aren't in the same set, union them together.
    // There's a certain point where we can stop the algorithm as an optimization, check lecture vid.
    
    
    
    
    // Function Kruskal(graph G(V,E))
    // set X
    // X = {}
    // E:= sort E by weight
    //
    // for u ∈ V
        // MAKESET(u) rof
    //
    // for (u, v) ∈ E (in increasing order) do
        // if FIND(u) ̸= FIND(v) do
            // X = X ∪ {(u, v)}
            // UNION(u,v)
    // rof
    // return(X )
    // end Kruskal
    
    return 1.0;
}


void tests() {
    // TODO hook this up to command-u
    // TODO write some damn good tests.
    
    Basic_Graph g1;
    g1.initialize_random(8192);
    assert(abs(g1.average_weight() - 0.5) < 0.01);
    
    assert(g1.distance(1,2) >= 0);
    assert(g1.distance(1,2) <= 1);
    
    
    Union_Find uf(3);
    uf.makeset(0);
    uf.makeset(1);
    uf.makeset(2);
    uf.makeset(3);
    uf.clean();
    uf.print();
    
    
    cout << "Tests Passed!!!" << nn;
}


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
    
    cout << "random distance? " << g1.distance(1, 2) << nn;
    cout << "Average Weight " << g1.average_weight() << nn;
    
    cout << "TODO ALL" << nn;
    
    tests();
    
    return 0;
}




//http://www.cs.fsu.edu/~myers/cop3330/notes/dma.html
//http://en.cppreference.com/w/cpp/container/vector
//http://en.cppreference.com/w/cpp/memory/unique_ptr
//http://www.cplusplus.com/forum/beginner/12409/
//http://www.cplusplus.com/reference/vector/vector/
//http://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
//http://en.cppreference.com/w/cpp/numeric/random
//http://stackoverflow.com/questions/1074474/should-i-use-double-or-float
//http://www.acodersjourney.com/2016/05/top-10-dumb-mistakes-avoid-c-11-smart-pointers/








