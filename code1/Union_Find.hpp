//
//  Union_Find.hpp
//  code1
//
//  Created by Eagle on 2/20/17.
//  Copyright © 2017 Ondaatje124. All rights reserved.
//

#ifndef Union_Find_hpp
#define Union_Find_hpp

#include <vector>

using namespace std;

class Node {
public:
    Node * parent;
    int rank;
    int value;
};

class Union_Find {
private:
    vector<Node *> sets; // this makes cleanup and testing much easier.
    Node * link(Node * a, Node * b);
public:
    Union_Find(int size);
    Union_Find();
    void makeset(int x);
    void onion(int x, int y);
    Node * find(int x);
    void clean();
    vector<Node *> raw();
};


#endif /* Union_Find_hpp */
