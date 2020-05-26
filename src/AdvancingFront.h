#ifndef ADVANCINGFRONT_H
#define ADVANCINGFRONT_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#include "global.h"
#include "Node.h"
#include "Edge.h"
#include "Triangle.h"

class AdvancingFront
{
public:
    AdvancingFront();

    Node     *node;
    Edge     *edge;
    Triangle *triangle;

    void mesh();

    void buildFront(int size, int arrfront[][3], Edge *edge);
    int  findSmallestEdgeIndex(int size, int arrfront[][3]);





    void buildMesh();



    int testcaseA();
    int testcaseB();
    int testcaseC();

    double angle(double *vec_u, double *vec_v);
    double dot_product(double *vec_u, double *vec_v);
    double cross_product(double *vec_u, double *vec_v);
    double norm(double *vec);

};

#endif // ADVANCINGFRONT_H
