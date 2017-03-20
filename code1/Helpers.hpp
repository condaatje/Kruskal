//
//  Helpers.hpp
//  code1
//
//  Created by Eagle on 2/27/17.
//  Copyright © 2017 Ondaatje124. All rights reserved.
//

#ifndef Helpers_hpp
#define Helpers_hpp

#include <stdio.h>
#include <vector>
#include <string.h>

using namespace std;


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

double nanoconv = 1000000000;
vector<int> VERTEX_SPEC = {128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072};



void run_tests();

void calculate_basic(vector<Result> * r, int trials, vector<int> numpoints);
void calculate_square(vector<Result> * r, int trials, vector<int> numpoints);
void calculate_cube(vector<Result> * r, int trials, vector<int> numpoints);
void calculate_hypercube(vector<Result> * r, int trials, vector<int> numpoints);

void print_result(Result r, int numtrials);
void print_result_vector(vector<Result> r);
void print_avg(vector<Result> r, int numtrials, vector<int> numpoints);
void print_strings(vector<string> strs);

int dim_translate(string s);

void full_blast();

double k(int n);


#endif /* Helpers_hpp */
