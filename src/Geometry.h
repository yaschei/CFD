#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>
#include <fstream>
#include <iomanip>

#include "Node.h"
#include "Edge.h"

class Geometry
{
public:
    Geometry(){}
    ~Geometry(){}

    Node *node;
    Edge *edge;

    int  parseFile(std::string filename);
    void writeVTK(std::string filename);

private:



};

#endif // GEOMETRY_H
