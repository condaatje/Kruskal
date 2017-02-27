
#ifndef Graphs_hpp
#define Graphs_hpp

#include "Union_Find.hpp"
#include <vector>
#include <string>


class Point2D {
public:
    Point2D(double x, double y) {
        this->x = x;
        this->y = y;
    }
    double x;
    double y;
};


class Point3D {
public:
    Point3D(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    double x;
    double y;
    double z;
};


class Point4D {
public:
    Point4D(double i, double j, double k, double l) {
        this->i = i;
        this->j = j;
        this->k = k;
        this->l = l;
    }
    double i;
    double j;
    double k;
    double l;
};


class Edge {
public:
    Edge(int v1, int v2, double weight) {
        this->v1 = v1;
        this->v2 = v2;
        this->weight = weight;
    }
    int v1;
    int v2;
    double weight;
};


bool edgeCompare (Edge a, Edge b);


// Abstract Class (protocol)
class Graph {
public:
    string graph_type;
    int num_vertices;
    virtual void initialize_random(int num_vertices) =0;
    virtual double weight(int x, int y) =0;
};


class Basic_Graph: public Graph {
public:
    vector<Edge> edges;
    void initialize_random(int num_vertices);
    void initialize_specific(int num_vertices, vector<Edge> egs);
    double weight(int x, int y);
    double average_weight();
};


class Square_Graph: public Graph {
private:
    vector<Point2D> vertices;
public:
    void initialize_random(int num_vertices);
    void initialize_specific(vector<Point2D> points);
    double weight(int vertex1, int vertex2);
};


class Cube_Graph: public Graph {
private:
    vector<Point3D> vertices;
public:
    void initialize_random(int num_vertices);
    void initialize_specific(vector<Point3D> points);
    double weight(int vertex1, int vertex2);
};


class Hypercube_Graph: public Graph {
    vector<Point4D> vertices;
public:
    void initialize_random(int num_vertices);
    void initialize_specific(vector<Point4D> points);
    double weight(int vertex1, int vertex2);
};

#endif /* Graphs_hpp */
