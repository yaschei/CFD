#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Edge.h"

class Triangle
{
public:
    Triangle(){}
    ~Triangle(){}

    Edge *edge;

    void set(int i, int e0, int e1, int e2);
    void setSize(int size);

    int getEdge(int i, int ei) const;
    int getEdgeNode(int i, int ei, int ni) const;


private:

    int _size;
    int _e0 [NMAXNODE];
    int _e1 [NMAXNODE];
    int _e2 [NMAXNODE];
};

#endif // TRIANGLE_H
