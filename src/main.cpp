#include <iostream>
#include <math.h>

#include "global.h"
#include "Node.h"
#include "Edge.h"
#include "Triangle.h"
#include "Geometry.h"
#include "AdvancingFront.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Begin program" << endl;

    Node     *node               = new Node();
    Edge     *edge               = new Edge();
    Triangle *triangle           = new Triangle();
    Geometry *geometry           = new Geometry();
    AdvancingFront *advFront     = new AdvancingFront();


    edge->node     = node;
    triangle->node = node;
    triangle->edge = edge;
    geometry->node = node;
    geometry->edge = edge;

    advFront->node     = node;
    advFront->edge     = edge;
    advFront->triangle = triangle;

    //Read custom geometry file and write it.
    geometry->parseFile("testGeo");
    geometry->writeVTK("testGeo");

    advFront->mesh();








    cout << "END program" << endl;
    return 0;
}
