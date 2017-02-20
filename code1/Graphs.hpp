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


class Basic_Graph {
private:
    vector< vector<double> > edges; //TODO float? smaller.
public:
    void initialize_random(int num_vertices);
    double distance(int vertex1, int vertex2);
    double average_weight();
};


class Square_Graph {
private:
    vector<Point2D> vertices;
public:
    void initialize_random(int num_vertices);
};



class Cube_Graph {
private:
    vector<Point3D> vertices;
public:
    void initialize_random(int num_vertices);
};

class Hypercube_Graph {
    vector<Point4D> vertices;
public:
    void initialize_random(int num_vertices);
};



#endif /* Graphs_hpp */






