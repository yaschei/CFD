#include "Edge.h"

void Edge::setSize(int size)
{
    _size = size;
}

void Edge::set(int i, int n0, int n1)
{
    _n0[i] = n0;
    _n1[i] = n1;
}

void Edge::set(int i, int current, int previous, int next)
{
    _current[i]  = current;
    _previous[i] = previous;
    _next[i]     = next;
}

void Edge::set(int i, int n0, int n1, int elmLeft, int elmRigth, int nodLeft, int nodRight)
{
    _n0           [i] = n0;
    _n1           [i] = n1;
    _leftElement  [i] = elmLeft;
    _rightElement [i] = elmRigth;
    _leftNode     [i] = nodLeft;
    _rightNode    [i] = nodRight;
}

void Edge::setLeftElement(int i, int elmLeft)
{
    _leftElement  [i] = elmLeft;
}

void Edge::setRightElement(int i, int elmRigth)
{
    _rightElement [i] = elmRigth;
}


int Edge::getNode(int i, int ni) const
{
    if(ni==0){
        return _n0[i];
    }
    else{
        return _n1[i];
    }
}

double Edge::getNodeX(int i, int ni) const
{
    if(ni==0){
        return node->getX(_n0[i]);
    }
    else{
        return node->getX(_n1[i]);
    }
}

double Edge::getNodeY(int i, int ni) const
{
    if(ni==0){
        return node->getY(_n0[i]);
    }
    else{
        return node->getY(_n1[i]);
    }
}

double Edge::length(int i)
{
    double x = node->getX(_n1[i]) - node->getX(_n0[i]);
    double y = node->getY(_n1[i]) - node->getY(_n0[i]);

    return sqrt(x*x + y*y);
}

void Edge::print(int i) const
{
    std::cout << "Edge"<< i << "={(" << getNode(i,0) << "," << getNode(i,1) << ")(" << getLeftElement(i) << "," << getRightElement(i) << ")("  << getLeftNode(i) << "," << getRightNode(i) << ")}" << std::endl;
}
