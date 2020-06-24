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
    AdvancingFront(){}
    ~AdvancingFront(){}

    Node     *node;
    Edge     *edge;
    Triangle *triangle;

    void buildMesh();

    void buildFront(int size, int arrfront[][3], Edge *edge);
    int  findSmallestEdgeIndex(int size, int arrfront[][3], int *arrActive);
    int  findSmallestAngleIndex(int size, int arrfront[][3]);
    void getEdgeNode(int iedge, int *node);

    int testcaseA();
    int testcaseB();
    int testcaseC(int *currNode, int *prevNode, int *nextNode);


    double angle(double *vec_u, double *vec_v);
    double dot_product(double *vec_u, double *vec_v);
    double cross_product(double *vec_u, double *vec_v);
    double norm(double *vec);

    void createNodeByRotation(int nodeToRotate, int center, double angleRad);
    int findEdgeAndNodeInsidePotentialTriangle(int front[][3], int *activate, int frontSize, int currEdge, int n0, int n1, std::vector<int> &edgeIn, int &nodeIn);

    void writeElement(int ielm);
    void writeMesh();
};

#endif // ADVANCINGFRONT_H
