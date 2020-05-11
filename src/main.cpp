#include <iostream>
#include <math.h>

#include "global.h"
#include "Node.h"
#include "Edge.h"
#include "Triangle.h"
#include "Triangulation.h"
#include "Geometry.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;

    Node     *node               = new Node();
    Edge     *edge               = new Edge();
    Triangle *triangle           = new Triangle();
    Triangulation *triangulation = new Triangulation();
    Geometry *geometry           = new Geometry();


    edge->node              = node;
    triangle->edge          = edge;
    triangulation->triangle = triangle;
    triangulation->node     = node;
    triangulation->edge     = edge;

    geometry->node = node;
    geometry->edge = edge;

    geometry->parseFile("testGeo");
    geometry->writeVTK("testGeo");








    cout << "END Hello World!" << endl;
    return 0;
}
