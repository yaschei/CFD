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
