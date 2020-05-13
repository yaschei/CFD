#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>

#include "Node.h"
#include "Edge.h"

class Triangle
{
public:
    Triangle(){}
    ~Triangle(){}

    Node *node;
    Edge *edge;

    void set(int i, int e0, int e1, int e2);
    void setSize(int size);

    int size() const {return _size;}
    int getNode(int i, int ni) const;
    int getNodeX(int i, int ni) const;
    int getNodeY(int i, int ni) const;

    int getEdge(int i, int ei) const;
    int getEdgeNode(int i, int ei, int ni) const;

    bool inCircle(int n0, int n1, int n2, int nodTest);
    bool isAreaPositive(int n0, int n1, int n2);

private:

    int _size;
    int _edge [NMAXNODE][3];
};

#endif // TRIANGLE_H
