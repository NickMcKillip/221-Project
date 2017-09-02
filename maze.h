//
//  maze.h
//  maze
//
//  Created by Nick Mckillip on 8/1/17.
//  Copyright © 2017 Nick Mckillip. All rights reserved.
//
#include <vector>
#include <list>
#include <math.h>
using namespace std;
struct mazeNode{
    mazeNode(bool north, bool east, bool south, bool west, int p, int msize);
    int pos;
    bool n, s, e, w;
    std::list<int> adj;
    friend ostream& operator << (ostream &out, const mazeNode &node);
};

ostream& operator << (ostream &out, const mazeNode &node)
{
    list<int>::const_iterator i;
    out << node.pos;
    for (i = node.adj.begin(); i!= node.adj.end(); ++i)
        out << " -> " << *i;
    return out;
}

mazeNode::mazeNode(bool north, bool east, bool south, bool west, int p, int msize):
n(north), pos(p), e(east), s(south), w(west)
{
    if (north)
        adj.push_back(pos-sqrt(msize));
    if (east)
        adj.push_back(pos+1);
    if (south)
        adj.push_back(pos+sqrt(msize));
    if (west)
        adj.push_back(pos-1);
}
struct mazeVec{
    std::vector<mazeNode> maze;
    //std::vector<mazeNode> maze;
    //construct nodes with nsew
    //assign nodes pointers
    void insert(bool n, bool e, bool s, bool w, int p, int size);
};

void mazeVec::insert(bool n, bool e, bool s, bool w, int p, int size)
{
    mazeNode temp(n,e,s,w,p,size);
    maze.push_back(temp);
}
