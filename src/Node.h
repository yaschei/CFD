#ifndef NODE_H
#define NODE_H

#include "global.h"

class Node
{
public:
    Node(){}
    ~Node(){}

    void set(int i, double x, double y);
    void setSize(int size);

    double getX(int i) const {return _x[i];}
    double getY(int i) const {return _y[i];}
    int    size()   const {return _size;}

private:

    int    _size;
    double _x [NMAXNODE];
    double _y [NMAXNODE];

};

#endif // NODE_H
