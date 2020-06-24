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
    geometry->parseFile("Carre2");
    geometry->writeVTK("testGeo");

////    advFront->mesh();
///
//    node->set(0, 1.64, 0.40);
//    node->set(1, 5.34, 1.54);
//    node->set(2, 5.98, 3.51);

//    double d1 = node->distance(0,1);
//    double d2 = node->distance(1,2);

//    double R = d1 + d2 / 2.0;

//    std::cout << d1 << " " << d2 << " " << R << std::endl;

//    node->set(3, 5.34+4.90, 1.54);

//    double u[2] = {node->getX(1) - node->getX(0), node->getY(1) - node->getY(0)};
//    double v[2] = {node->getX(2) - node->getX(1), node->getY(2) - node->getY(1)};
//    double w[2] = {node->getX(1) - node->getX(3), node->getY(1) - node->getY(3)};


//    double a1 = advFront->angle(&u[0], &v[0]);
//    double a2 = advFront->angle(&w[0], &v[0]);
//    double theta = acos((advFront->dot_product(v, w)) / (advFront->norm(w) * advFront->norm(v)));

//    std::cout << a1*180/PI << " " << a2*180/PI << " " << theta*180/PI << std::endl;

//    double x = node->getX(3) - node->getX(1);
//    double y = node->getY(3) - node->getY(1);

//    double xnew = x * cos(0.5*a1 + 2*PI-a2) - y * sin(0.5*a1 + 2*PI-a2) + node->getX(1);
//    double ynew = x * sin(0.5*a1 + 2*PI-a2) + y * cos(0.5*a1 + 2*PI-a2) + node->getY(1);
//    node->set(4, xnew, ynew);

//    std::cout << node->getX(3) << " " << node->getY(3) << std::endl;
//    std::cout << node->getX(4) << " " << node->getY(4) << std::endl;

    advFront->buildMesh();







    cout << "END program" << endl;
    return 0;
}
