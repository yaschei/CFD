#include "Triangle.h"

void Triangle::set(int i, int e0, int e1, int e2){
    _e0[i] = e0;
    _e1[i] = e1;
    _e2[i] = e2;
}

int Triangle::getEdge(int i, int ei) const
{
    if(ei==0){
        return _e0[i];
    }
    else if(ei==1){
        return _e1[i];
    }
    else{
        return _e2[i];
    }
}

int Triangle::getEdgeNode(int i, int ei, int ni) const
{
    if(ei==0){
        return edge->getNode(_e0[i], ni);
    }
    else if(ei==1){
        return edge->getNode(_e1[i], ni);
    }
    else{
        return edge->getNode(_e2[i], ni);
    }
}

void Triangle::setSize(int size)
{
    _size = size;
}
