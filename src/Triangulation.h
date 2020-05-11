#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <iostream>
#include "Triangle.h"

class Triangulation
{
public:
    Triangulation(){}
    ~Triangulation(){}

    Triangle *triangle;
    Node     *node;
    Edge     *edge;

    void triangulate();

};

#endif // TRIANGULATION_H
