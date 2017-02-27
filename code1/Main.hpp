
#ifndef Main_h
#define Main_h

#include "Graphs.hpp"
#include <string.h>


int main(int argc, const char * argv[]);

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

#endif /* Main_h */
