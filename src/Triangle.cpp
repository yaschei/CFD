#include "Triangle.h"

void Triangle::set(int index, int edge0, int edge1, int edge2){

    _edge[index][0] = edge0;
    _edge[index][1] = edge1;
    _edge[index][2] = edge2;

}

void Triangle::setSize(int size)
{
    _size = size;
}

int Triangle::getNode(int index, int icol) const
{
    if(icol == 0){
        if(edge->getLeftElement(_edge[index][icol]) == index){
            return edge->getNode(_edge[index][icol], 0);
        }
        else{
            return edge->getNode(_edge[index][icol], 1);
        }
    }
    else if(icol == 1){
        if(edge->getLeftElement(_edge[index][icol]) == index){
            return edge->getNode(_edge[index][icol], 0);
        }
        else{
            return edge->getNode(_edge[index][icol], 1);
        }
    }
    else{
        if(edge->getLeftElement(_edge[index][icol]) == index){
            return edge->getNode(_edge[index][icol], 0);
        }
        else{
            return edge->getNode(_edge[index][icol], 1);
        }
    }

}

int Triangle::getNodeX(int index, int icol) const
{
    if(icol == 0){
        if(edge->getLeftElement(_edge[index][icol]) == index){
            return edge->getNodeX(_edge[index][icol], 0);
        }
        else{
            return edge->getNodeX(_edge[index][icol], 1);
        }
    }
    else if(icol == 1){
        if(edge->getLeftElement(_edge[index][icol]) == index){
            return edge->getNodeX(_edge[index][icol], 0);
        }
        else{
            return edge->getNodeX(_edge[index][icol], 1);
        }
    }
    else{
        if(edge->getLeftElement(_edge[index][icol]) == index){
            return edge->getNodeX(_edge[index][icol], 0);
        }
        else{
            return edge->getNodeX(_edge[index][icol], 1);
        }
    }

}

int Triangle::getNodeY(int index, int icol) const
{
    if(icol == 0){
        if(edge->getLeftElement(_edge[index][icol]) == index){
            return edge->getNodeY(_edge[index][icol], 0);
        }
        else{
            return edge->getNodeY(_edge[index][icol], 1);
        }
    }
    else if(icol == 1){
        if(edge->getLeftElement(_edge[index][icol]) == index){
            return edge->getNodeY(_edge[index][icol], 0);
        }
        else{
            return edge->getNodeY(_edge[index][icol], 1);
        }
    }
    else{
        if(edge->getLeftElement(_edge[index][icol]) == index){
            return edge->getNodeY(_edge[index][icol], 0);
        }
        else{
            return edge->getNodeY(_edge[index][icol], 1);
        }
    }

}

int Triangle::getEdge(int index, int icol) const
{
    return _edge[index][icol];
}

int Triangle::getEdgeNode(int index, int iedge, int icol) const
{
    if(icol == 0){
        if(edge->getLeftElement(_edge[index][iedge]) == index){

            return edge->getNode(_edge[index][iedge], 0);
        }
        else{
            return edge->getNode(_edge[index][iedge], 1);
        }
    }
    else if(icol == 1){
        if(edge->getLeftElement(_edge[index][iedge]) == index){
            return edge->getNode(_edge[index][iedge], 1);
        }
        else{
            return edge->getNode(_edge[index][iedge], 0);
        }
    }

}

bool Triangle::inCircle(int n0, int n1, int n2, int nodTest)
{

    double ax = node->getX(n0);
    double ay = node->getY(n0);

    double bx = node->getX(n1);
    double by = node->getY(n1);

    double cx = node->getX(n2);
    double cy = node->getY(n2);

    double dx = node->getX(nodTest);
    double dy = node->getY(nodTest);

    double aa, ab, ac;
    double ba, bb, bc;
    double ca, cb, cc;

    aa = ax-dx; ab = ay-dy; ac = (ax-dx)*(ax-dx)+(ay-dy)*(ay-dy);
    ba = bx-dx; bb = by-dy; bc = (bx-dx)*(bx-dx)+(by-dy)*(by-dy);
    ca = cx-dx; cb = cy-dy; cc = (cx-dx)*(cx-dx)+(cy-dy)*(cy-dy);

    if(aa*(bb*cc - cb*bc) - ab*(ba*cc - ca*bc) + ac*(ba*cb - ca*bb) > 0.0){
        return true;
    }
    else{
        return false;
    }

}

bool Triangle::isAreaPositive(int n0, int n1, int n2)
{

    double ax = node->getX(n0);
    double ay = node->getY(n0);

    double bx = node->getX(n1);
    double by = node->getY(n1);

    double cx = node->getX(n2);
    double cy = node->getY(n2);

    if(0.5*( (bx-ax)*(cy-ay) - (cx-ax)*(by-ay) ) > 0.0){
        return true;
    }
    else{
        return false;
    }
}
