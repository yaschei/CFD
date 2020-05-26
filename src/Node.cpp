#include "Node.h"

void Node::set(int i, double x, double y)
{
    _x[i] = x;
    _y[i] = y;
}

void Node::setSize(int size)
{
    _size = size;
}

double Node::distance(int n0, int n1)
{
    return sqrt((_x[n1] - _x[n0])*(_x[n1] - _x[n0]) + (_y[n1] - _y[n0])*(_y[n1] - _y[n0]));
}
