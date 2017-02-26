//
//  Graphs.hpp
//  code1
//
//  Created by Eagle on 2/20/17.
//  Copyright © 2017 Ondaatje124. All rights reserved.
//

#ifndef Graphs_hpp
#define Graphs_hpp

#include "Union_Find.hpp"
#include <vector>

struct Point1D { //TODO necessary?
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

struct Edge {
    int v1;
    int v2;
    double weight;
};

bool edgeCompare (Edge a, Edge b);

// Abstract Class
class Graph {
public:
    int num_vertices;
    virtual void initialize_random(int num_vertices) =0;
    virtual double weight(int x, int y) =0;
};

class Basic_Graph: public Graph {
public:
    vector<Edge> edges;
    void initialize_random(int num_vertices);
    double weight(int x, int y);
    double average_weight();
};


class Square_Graph: public Graph {
private:
    vector<Point2D> vertices;
public:
    void initialize_random(int num_vertices);
    double weight(int vertex1, int vertex2);
};


class Cube_Graph: public Graph {
private:
    vector<Point3D> vertices;
public:
    void initialize_random(int num_vertices);
    double weight(int vertex1, int vertex2);
};


class Hypercube_Graph: public Graph {
    vector<Point4D> vertices;
public:
    void initialize_random(int num_vertices);
    double weight(int vertex1, int vertex2);
};

#endif /* Graphs_hpp */






