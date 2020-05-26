#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <math.h>

#include "global.h"
#include "Node.h"

class Edge
{
public:
    Edge(){}
    ~Edge(){}

    Node *node;

    void   setSize(int size);
    int    size() const {return _size;}

    void   set(int i, int n0, int n1);
    void   set(int i, int current, int previous, int next);
    void   set(int i, int n0, int n1, int elmLeft, int elmRigth, int nodLeft, int nodRight);
    void   setLeftElement(int i, int elmLeft);
    void   setRightElement(int i, int elmRigth);

    int    getNode(int i, int ni) const;
    int    getLeftElement(int i)  const {return _leftElement[i];}
    int    getRightElement(int i) const {return _rightElement[i];}
    int    getLeftNode(int i)     const {return _leftNode[i];}
    int    getRightNode(int i)    const {return _rightNode[i];}

    double getNodeX(int i, int ni) const;
    double getNodeY(int i, int ni) const;

    int    getCurrent(int i) const {return _current[i];}
    int    getPrevious(int i) const {return _previous[i];}
    int    getNext(int i)     const {return _next[i];}

    double length(int i);

    void   print(int i) const;

private:

    int _size;

    int _n0                [NMAXNODE];
    int _n1                [NMAXNODE];
    int _leftElement       [NMAXNODE];
    int _rightElement      [NMAXNODE];
    int _leftNode          [NMAXNODE];
    int _rightNode         [NMAXNODE];
    int _boundaryCondition [NMAXNODE];

    int _current           [NMAXNODE];
    int _previous          [NMAXNODE];
    int _next              [NMAXNODE];



};

#endif // EDGE_H
