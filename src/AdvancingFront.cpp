#include "AdvancingFront.h"

void AdvancingFront::buildMesh()
{
    // initialize variable
    int front[NMAXNODE][3];
    int activate[NMAXNODE];
    int counterFront = edge->size();
    int frontSize = edge->size();

    int nodCounter = node->size();
    int edgCounter = edge->size();
    int elmCounter = 0;

    // copy initial geometry inside front
    buildFront(frontSize, front, edge);

//    for(int ifront = 0; ifront < frontSize; ifront++)
//    {
//        std::cout << front[ifront][0] << " " << front[ifront][1] << " " << front[ifront][2] << std::endl;
//    }

    // UPDATE EDGE AFTER BUILDING NEW ONE

    //begin frontal triangulation
    int N = frontSize - 8;
    int k = 0;
    while(counterFront > N && k < 100){

        std::cout<< "LOOP : " << k <<std::endl;
        k++;
        //remove all angle < PI/2
        for(int ifront = 0; ifront < frontSize && counterFront > N; ifront++)
        {
            if(activate[ifront] != 1){

                //find the row with the smallest edge
                int     prevPos = front[ifront][1];
                int     currPos = front[ifront][0];
                int     nextPos = front[ifront][2];
                int prevprevPos = front[prevPos][1];
                int nextnextPos = front[nextPos][2];

                //take current edge
                int prevprevEdge = front[prevprevPos][0];
                int     prevEdge = front[prevPos][0];
                int     currEdge = front[currPos][0];
                int     nextEdge = front[nextPos][0];
                int nextnextEdge = front[nextnextPos][0];

                //get edge node
                int prevprevNode = edge->getNode(prevprevEdge, 0);
                int     prevNode = edge->getNode(prevEdge, 0);
                int     currNode = edge->getNode(currEdge, 0);
                int     nextNode = edge->getNode(nextEdge, 0);
                int nextnextNode = edge->getNode(nextnextEdge, 0);

                //compare angle on currNode0 and currNode1
                double u[2] = { node->getX(currNode) - node->getX(prevNode), node->getY(currNode) - node->getY(prevNode) };
                double v[2] = { node->getX(nextNode) - node->getX(currNode), node->getY(nextNode) - node->getY(currNode) };
                double currAngle = angle(&u[0], &v[0]);

                if(currAngle <= 0.5*PI)
                {
                    std::cout << "Angle < PI/2 founded" << std::endl;

                    //empty circle test
                    for(int i=0; i<frontSize; i++)
                    {
                        if(activate[ifront] != 1)
                        {

                        }
                    }

                    int isInside = 0;
                    double minDistance = 9999.9;
                    int indexInside = 0;

                    std::vector<int> edgeInside;
                    minDistance = 9999.9;

                    for(int i=0; i<edge->size(); i++)
                    {
                        int node0 = edge->getNode(i,0);
                        int node1 = edge->getNode(i,1);

        //                std::cout << " edge" << i << " (" << node0 <<","<< node1 << ")" << std::endl;

                        if(node0 != currNode0 && node0 != currNode1 && node0 != node->size())
                        {

                            double x = node->getX(node0) - node->getX(node->size());
                            double y = node->getY(node0) - node->getY(node->size());
                            double R = .5*edge->length(currPos);

                            if(triangle->inCircle(currNode0, currNode1, node->size(), node0) || x*x + y*y < R*R)
                            {
        //                        std::cout << "      test : " << node0 << " is inside (" << currNode0 << "," << currNode1 << "," << node->size() << ") ?**" << std::endl;
                                isInside = 1;

                                if(node->distance(currNode0, node0) <= minDistance + 5.e-8)
                                {
                                    minDistance = node->distance(currNode0, node0);
                                    indexInside = node0;
                                    edgeInside.push_back(i);
        //                            std::cout << i << " ** " << std::endl;

                                }

                            }

                        }

                        if(node1 != currNode0 && node1 != currNode1 && node1 != node->size())
                        {
                            double x = node->getX(node1) - node->getX(node->size());
                            double y = node->getY(node1) - node->getY(node->size());
                            double R = .5*edge->length(currPos);

                            if(triangle->inCircle(currNode0, currNode1, node->size(), node1) || x*x + y*y < R*R)
                            {
        //                        std::cout << "      test : " << node1 << " is inside (" << currNode0 << "," << currNode1 << "," << node->size() << ") ?---" << std::endl;
                                isInside = 1;

                                if(node->distance(currNode0, node1) <= minDistance)
                                {
                                    minDistance = node->distance(currNode0, node1);
                                    indexInside = node1;
                                    edgeInside.push_back(i);
        //                            std::cout << i << "----" << std::endl;

                                }

                            }

                        }




                    }

                    if(isInside == 1)
                    {

                    }



                    edge->set(edgCounter, prevNode, nextNode, EMPTY, elmCounter, EMPTY, currNode);
//                    edge->print(edgCounter);
                    triangle->set(elmCounter, currEdge, edgCounter, prevEdge);

                    //update front
                    activate[prevPos] = 1; // prevPos de-activated
                    activate[currPos] = 1; // currPos de-activated
                    counterFront-=2;

                    edge->set(prevEdge, edge->getNode(prevEdge,0), edge->getNode(prevEdge,1) , elmCounter, edge->getRightElement(prevEdge), nodCounter, edge->getRightNode(prevEdge));
                    edge->set(currEdge, edge->getNode(currEdge,0), edge->getNode(currEdge,1) , elmCounter, edge->getRightElement(currEdge), nodCounter, edge->getRightNode(currEdge));


                    front[edgCounter][0] = edgCounter;      //new edge
                    front[edgCounter][1] = front[prevPos][1]; //prev prevPos
                    front[edgCounter][2] = front[currPos][2]; //next currPos
                    counterFront++;

                    front[prevprevPos][0] = front[prevprevPos][0];      //new edge
                    front[prevprevPos][1] = front[prevprevPos][1]; //prev prevPos
                    front[prevprevPos][2] = edgCounter; //next currPos

                    front[nextPos][0] = front[nextPos][0];      //new edge
                    front[nextPos][1] = edgCounter; //prev prevPos
                    front[nextPos][2] = front[nextPos][2]; //next currPos

                    frontSize++;


                    //increment counter elm
                    edgCounter++;
                    elmCounter++;

                    //update mesh structure
                    edge->setSize(edgCounter);
                    triangle->setSize(elmCounter);


                    writeElement(elmCounter-1);


                    for(int ifront = 0; ifront < frontSize; ifront++)
                    {
                        if(activate[ifront] != 1){
                            std::cout << front[ifront][0] << " " << front[ifront][1] << " " << front[ifront][2] << std::endl;
                        }
                    }

                    std::cout<<counterFront<<std::endl;

                }
                else
                {
//                    std::cout << "***No angle < PI/2 founded" << std::endl;
                }

            }

        }

//        std::cout<<counterFront<<std::endl;

        if(counterFront > N){

            //find the row with the smallest edge
            int     currPos = findSmallestEdgeIndex(frontSize, front, &activate[0]);
            int     prevPos = front[currPos][1];
            int     nextPos = front[currPos][2];
            int prevprevPos = front[prevPos][1];
            int nextnextPos = front[nextPos][2];

            //take current edge
            int prevprevEdge = front[prevprevPos][0];
            int     prevEdge = front[prevPos][0];
            int     currEdge = front[currPos][0];
            int     nextEdge = front[nextPos][0];
            int nextnextEdge = front[nextnextPos][0];

            //get edge node
            int     prevprevNode = edge->getNode(prevprevEdge, 0);
            int         prevNode = edge->getNode(prevEdge, 0);
            int         currNode = edge->getNode(currEdge, 0);
            int         nextNode = edge->getNode(nextEdge, 0);
            int     nextnextNode = edge->getNode(nextnextEdge, 0);
            int nextnextnextNode = edge->getNode(nextnextEdge, 1);

    //        std::cout << "  ifront = " << ifront << std::endl;
            std::cout << "  edge" << prevEdge << " (" << prevNode << "," << currNode << ")" << std::endl;
            std::cout << "  edge" << currEdge << " (" << currNode << "," << nextNode << ")" << std::endl;
            std::cout << "  edge" << nextEdge << " (" << nextNode << "," << nextnextNode << ")" << std::endl;

            //compare angle on currNode0 and currNode1
            double u1[2] = { node->getX(currNode) - node->getX(prevNode), node->getY(currNode) - node->getY(prevNode) };
            double v1[2] = { node->getX(nextNode) - node->getX(currNode), node->getY(nextNode) - node->getY(currNode) };
//            std::cout << " u1 " << u1[0] <<  " " << u1[1] << std::endl;
//            std::cout << " v1 " << v1[0] <<  " " << v1[1] << std::endl;
            double currAngle = angle(u1, v1);

            double u2[2] = { node->getX(nextNode) - node->getX(currNode), node->getY(nextNode) - node->getY(currNode) };
            double v2[2] = { node->getX(nextnextNode) - node->getX(nextNode), node->getY(nextnextNode) - node->getY(nextNode) };
//            std::cout << " u2 " << u2[0] <<  " " << u2[1] << std::endl;
//            std::cout << " v2 " << v2[0] <<  " " << v2[1] << std::endl;
            double nextAngle = angle(u2, v2);



            if(0.5*PI < currAngle && currAngle <= 2*PI*ONETHIRD)
            {

                std::cout << "      case B : PI/2 < currAngle < 2PI/3" << std::endl;

                //Build the new node
                double d1 =   node->distance(prevprevNode, prevNode);
                double d2 = 2*node->distance(prevNode, currNode);
                double d3 = 2*node->distance(currNode, nextNode);
                double d4 =   node->distance(nextNode, nextnextNode);
                double R = (d1 + d2 + d3 + d4) / 6.0;

                node->set(nodCounter, node->getX(currNode)+R, node->getY(currNode));

                double v[2] = {node->getX(nextNode) - node->getX(currNode), node->getY(nextNode) - node->getY(currNode)};
                double w[2] = {node->getX(currNode) - node->getX(nodCounter), node->getY(currNode) - node->getY(nodCounter)};
                double a2 = angle(&w[0], &v[0]);

                double x = node->getX(nodCounter) - node->getX(currNode);
                double y = node->getY(nodCounter) - node->getY(currNode);

                double xnew = x * cos(0.5*currAngle + 2*PI-a2) - y * sin(0.5*currAngle + 2*PI-a2) + node->getX(currNode);
                double ynew = x * sin(0.5*currAngle + 2*PI-a2) + y * cos(0.5*currAngle + 2*PI-a2) + node->getY(currNode);
                node->set(nodCounter, xnew, ynew);


                edge->set(edgCounter, currNode, nodCounter, elmCounter, elmCounter+1, prevNode, nextNode);
    //            edge->print(edgCounter);

                edge->set(edgCounter+1, prevNode, nodCounter, EMPTY, elmCounter, EMPTY, currNode);
    //            edge->print(edgCounter+1);


                edge->set(edgCounter+2, nodCounter, nextNode, EMPTY, elmCounter+1, EMPTY, currNode);
    //            edge->print(edgCounter+2);


                triangle->set(elmCounter, prevEdge, edgCounter, edgCounter+1);
                triangle->set(elmCounter+1, currEdge, edgCounter+2, edgCounter);

                //update front
                activate[currPos] = 1; // currPos de-activated
                activate[prevPos] = 1; // currPos de-activated
                activate[edgCounter] = 1; // currPos de-activated
                counterFront-=2;

                edge->set(prevEdge, edge->getNode(prevEdge,0), edge->getNode(prevEdge,1) , elmCounter, edge->getRightElement(prevEdge), nodCounter, edge->getRightNode(prevEdge));
                edge->set(currEdge, edge->getNode(currEdge,0), edge->getNode(currEdge,1) , elmCounter+1, edge->getRightElement(currEdge), nodCounter, edge->getRightNode(currEdge));


                //new 2
                front[edgCounter+1][0] = edgCounter+1;
                front[edgCounter+1][1] = front[prevPos][1];
                front[edgCounter+1][2] = edgCounter+2;
                counterFront++;

                //new 3
                front[edgCounter+2][0] = edgCounter+2;
                front[edgCounter+2][1] = edgCounter+1;
                front[edgCounter+2][2] = front[currPos][2];
                counterFront++;

                //prevprevPos
                front[prevprevPos][0] = front[prevprevPos][0]; //unchanged
                front[prevprevPos][1] = front[prevprevPos][1]; //unchanged
                front[prevprevPos][2] = edgCounter+1;        //next new Edge

                //nextPos
                front[nextPos][0] = front[nextPos][0]; //unchanged
                front[nextPos][1] = edgCounter+2;      //prev new Edge
                front[nextPos][2] = front[nextPos][2]; //unchanged

                frontSize+=3;


                //increment counter elm
                nodCounter++;
                edgCounter+=3;
                elmCounter+=2;

                //update mesh structure
                node->setSize(nodCounter);
                edge->setSize(edgCounter);
                triangle->setSize(elmCounter);

                writeElement(elmCounter-1);




            }
            else if(0.5*PI < nextAngle && nextAngle <= 2*PI*ONETHIRD )
            {

                std::cout << "      case B : PI/2 < nextAngle < 2PI/3" << std::endl;

                //Build the new node
                double d1 =   node->distance(prevNode, currNode);
                double d2 = 2*node->distance(currNode, nextNode);
                double d3 = 2*node->distance(nextNode, nextnextNode);
                double d4 =   node->distance(nextnextNode, nextnextnextNode);
                double R = (d1 + d2 + d3 + d4) / 6.0;


                node->set(nodCounter, node->getX(nextNode)+R, node->getY(nextNode));

                double v[2] = {node->getX(nextnextNode) - node->getX(nextNode), node->getY(nextnextNode) - node->getY(nextNode)};
                double w[2] = {node->getX(nextNode) - node->getX(nodCounter), node->getY(nextNode) - node->getY(nodCounter)};
                double a2 = angle(&w[0], &v[0]);

                double x = node->getX(nodCounter) - node->getX(nextNode);
                double y = node->getY(nodCounter) - node->getY(nextNode);

                double xnew = x * cos(0.5*nextAngle + 2*PI-a2) - y * sin(0.5*nextAngle + 2*PI-a2) + node->getX(nextNode);
                double ynew = x * sin(0.5*nextAngle + 2*PI-a2) + y * cos(0.5*nextAngle + 2*PI-a2) + node->getY(nextNode);
                node->set(nodCounter, xnew, ynew);


                edge->set(edgCounter, nextNode, nodCounter, elmCounter, elmCounter+1, currNode, nextnextNode);
    //            edge->print(edgCounter);

                edge->set(edgCounter+1, currNode, nodCounter, EMPTY, elmCounter, EMPTY, nextNode);
    //            edge->print(edgCounter+1);


                edge->set(edgCounter+2, nodCounter, nextnextNode, EMPTY, elmCounter+1, EMPTY, nextNode);
    //            edge->print(edgCounter+2);


                triangle->set(elmCounter, currEdge, edgCounter, edgCounter+1);
                triangle->set(elmCounter+1, nextEdge, edgCounter+2, edgCounter);


                //update front
                activate[currPos] = 1; // currPos de-activated
                activate[nextPos] = 1; // currPos de-activated
                activate[edgCounter] = 1; // currPos de-activated
                counterFront-=2;

                edge->set(currEdge, edge->getNode(currEdge,0), edge->getNode(currEdge,1) , elmCounter, edge->getRightElement(currEdge), nodCounter, edge->getRightNode(currEdge));
                edge->set(nextEdge, edge->getNode(nextEdge,0), edge->getNode(nextEdge,1) , elmCounter+1, edge->getRightElement(nextEdge), nodCounter, edge->getRightNode(nextEdge));


                //new 2
                front[edgCounter+1][0] = edgCounter+1;
                front[edgCounter+1][1] = front[prevPos][0];
                front[edgCounter+1][2] = edgCounter+2;
                counterFront++;

                //new 3
                front[edgCounter+2][0] = edgCounter+2;
                front[edgCounter+2][1] = edgCounter+1;
                front[edgCounter+2][2] = front[nextPos][2];
                counterFront++;

                //prevPos
                front[prevPos][0] = front[prevPos][0]; //unchanged
                front[prevPos][1] = front[prevPos][1]; //unchanged
                front[prevPos][2] = edgCounter+1;        //next new Edge

                //nextnextPos
                front[nextnextPos][0] = front[nextnextPos][0]; //unchanged
                front[nextnextPos][1] = edgCounter+2;      //prev new Edge
                front[nextnextPos][2] = front[nextnextPos][2]; //unchanged

                frontSize+=3;


                //increment counter elm
                nodCounter++;
                edgCounter+=3;
                elmCounter+=2;

                //update mesh structure
                node->setSize(nodCounter);
                edge->setSize(edgCounter);
                triangle->setSize(elmCounter);

                writeElement(elmCounter-1);

            }
            else if(2*PI*ONETHIRD <= currAngle && 2*PI*ONETHIRD <= nextAngle)
            {

                std::cout << "      case C : 2PI/3 < alpha ==> Create equilateral triangle" << std::endl;

                //Build the new element
                double x = node->getX(nextNode) - node->getX(currNode);
                double y = node->getY(nextNode) - node->getY(currNode);

                double xnew = x * cos(PI*ONETHIRD) - y * sin(PI*ONETHIRD) + node->getX(currNode);
                double ynew = x * sin(PI*ONETHIRD) + y * cos(PI*ONETHIRD) + node->getY(currNode);
                node->set(nodCounter, xnew, ynew);

                edge->set(edgCounter  , currNode, nodCounter , EMPTY, elmCounter+1, EMPTY, nextNode);
                edge->set(edgCounter+1, nodCounter , nextNode, EMPTY, elmCounter+1, EMPTY, currNode);

                triangle->set(elmCounter, currEdge, edgCounter+1, edgCounter);

                //update front
                activate[currPos] = 1; // currPos de-activated
                counterFront--;
                edge->set(currEdge, edge->getNode(currEdge,0), edge->getNode(currEdge,1) , elmCounter, edge->getRightElement(currEdge), nodCounter, edge->getRightNode(currEdge));

                //new 1
                front[edgCounter][0] = edgCounter;
                front[edgCounter][1] = front[currPos][1];
                front[edgCounter][2] = edgCounter+1;
                counterFront++;

                //new 2
                front[edgCounter+1][0] = edgCounter+1;
                front[edgCounter+1][1] = edgCounter;
                front[edgCounter+1][2] = front[currPos][2];
                counterFront++;

                //prevPos
                front[prevPos][0] = front[prevPos][0]; //unchanged
                front[prevPos][1] = front[prevPos][1]; //unchanged
                front[prevPos][2] = edgCounter;        //next new Edge

                //nextPos
                front[nextPos][0] = front[nextPos][0]; //unchanged
                front[nextPos][1] = edgCounter+1;      //prev new Edge
                front[nextPos][2] = front[nextPos][2]; //unchanged

                frontSize+=2;

                //increment counter elm
                nodCounter++;
                edgCounter+=2;
                elmCounter++;

                //update mesh structure
                node->setSize(nodCounter);
                edge->setSize(edgCounter);
                triangle->setSize(elmCounter);

                writeElement(elmCounter-1);



            }
            else if(isnan(currAngle) || isnan(nextAngle))
            {
                std::cout << "currAngle is " << currAngle*180/PI << std::endl;
                std::cout << "nextAngle is " << nextAngle*180/PI << std::endl;

//                std::cout << node->getX(prevprevNode[0]) << " " << node->getY(prevprevNode[0]) << std::endl;
//                std::cout << node->getX(prevNode[0]) << " " << node->getY(prevNode[0]) << std::endl;
//                std::cout << node->getX(currNode[0]) << " " << node->getY(currNode[0]) << std::endl;
//                std::cout << node->getX(nextNode[0]) << " " << node->getY(nextNode[0]) << std::endl;
//                std::cout << node->getX(nextnextNode[0]) << " " << node->getY(nextnextNode[0]) << std::endl;


                break;
            }


            for(int ifront = 0; ifront < frontSize; ifront++)
            {
                if(activate[ifront] != 1){
                    std::cout << front[ifront][0] << " " << front[ifront][1] << " " << front[ifront][2] << std::endl;
                }
            }
            std::cout<<counterFront<<std::endl;

        }

    }

    writeMesh();

    std::cout << "-------------------------------------------------------------------" << std::endl;

//    for (int i = 0; i < triangle->size(); i ++ ){
//        std::cout << "T" << i << " : " << triangle->getNode(i, 0) << " " << triangle->getNode(i, 1) << " " << triangle->getNode(i, 2) << std::endl;
////        std::cout << triangle->getEdge(i, 0) << " " << triangle->getEdge(i, 1) << " " << triangle->getEdge(i, 2) << std::endl;
//        edge->print(triangle->getEdge(i, 0));
//        edge->print(triangle->getEdge(i, 1));
//        edge->print(triangle->getEdge(i, 2));


//    }

}

void AdvancingFront::buildFront(int size, int arrfront[NMAXNODE][3], Edge *edge)
{
    for(int i; i < size; i++){
        arrfront[i][0] = edge->getCurrent(i);
        arrfront[i][1] = edge->getPrevious(i);
        arrfront[i][2] = edge->getNext(i);
    }
}

int AdvancingFront::findSmallestEdgeIndex(int size, int arrfront[][3], int *arrActive)
{
    double min      = 9999.9 ;
    int    minIndex = 0;

    for(int i = 0; i < size; i++)
    {
        if(arrActive[i] != 1)
        {
//            std::cout << edge->length(arrfront[i][0]) << std::endl;

            if(edge->length(arrfront[i][0]) < min - 1.e-8)
            {

                min      = edge->length(arrfront[i][0]);
                minIndex = i;
            }
        }


    }

    return minIndex;
}


int AdvancingFront::findEdgeAndNodeInsidePotentialTriangle(int front[][3], int *activate, int frontSize, int currEdge, int n0, int n1, std::vector<int> &edgeIn, int &nodeIn)
{
    //test if another node is inside the potential equilateral triangle
    int    isInside = 0;
    double minDistance = 9999.9;

    for(int i=0; i < frontSize && activate[i] != 1; i++)
    {
        int node0 = edge->getNode(front[i][0],0);
        int node1 = edge->getNode(front[i][0],1);

        if( (node0 != n0 && node0 != n1 && node0 != node->size()) && (node1 != n0 && node1 != n1 && node1 != node->size()) )
        {
            double x = node->getX(node0) - node->getX(node->size());
            double y = node->getY(node0) - node->getY(node->size());
            double R = .5*edge->length(currEdge);

            if(triangle->inCircle(n0, n1, node->size(), node0) || x*x + y*y < R*R)
            {

                if(node->distance(n0, node0) <= minDistance + 5.e-8)
                {
                    minDistance = node->distance(n0, node0);
                    nodeIn = node0;
                    edgeIn.push_back(front[i][0]);
                }

            }

            x = node->getX(node1) - node->getX(node->size());
            y = node->getY(node1) - node->getY(node->size());
            R = .5*edge->length(currEdge);

            if(triangle->inCircle(n0, n1, node->size(), node1) || x*x + y*y < R*R)
            {
                isInside = 1;

                if(node->distance(n0, node1) <= minDistance)
                {
                    minDistance = node->distance(n0, node1);
                    nodeIn = node1;
                    edgeIn.push_back(front[i][0]);
                }

            }

        }

    }

//    std::cout<< "nearest node is " << nodeIn << std::endl;
    return isInside;
}


double AdvancingFront::angle(double *vec_u, double *vec_v)
{

    double ez       = cross_product(vec_u, vec_v);
    double cosTheta = (dot_product(vec_u, vec_v)) / (norm(vec_u) * norm(vec_v));
    double x;

    if ( -1.0+1.e-8 < cosTheta &&  cosTheta < -1.0-1.e-8)
    {
        x = -1.0;
    }
    else if(1.0-1.e-8 < cosTheta  &&  cosTheta < 1.0+1.e-8)
    {
        x = 1.0;
//        std::cout << "enculé" << std::endl;
    }
    else
    {
        x = cosTheta;
//        std::cout << "batard" << std::endl;
//        std::cout << 1.0-1.e-16 << " < " << cosTheta  << " < " << 1.0+1.e-16 << std::endl;
    }


//    else if ((dot_product(vec_u, vec_v)) / (norm(vec_u) * norm(vec_v)) > 1.0) x = 1.0 ;

    double theta0 = acos(x);


//    std::cout << "dot_product = " << dot_product(vec_u, vec_v) << std::endl;
//    std::cout << "norm_u = " << norm(vec_u) << std::endl;
//    std::cout << "norm_v = " << norm(vec_v) << std::endl;
//    std::cout << "cos(theta) = " << (dot_product(vec_u, vec_v)) / (norm(vec_u) * norm(vec_v)) << std::endl;
//    std::cout << "theta = " << acos(x) << " " << x << std::endl;



    if( - 1.e-16 < theta0 && theta0 < 1.e-16 ){
//        std::cout << "return PI";
        return PI;
    }
    else if( PI - 1.e-16 < theta0 && theta0 < PI + 1.e-16){
//        std::cout << "return 0.0";
        return 0.0;
    }
    else if( ez >= 0.0){
//        std::cout << "return PI-theta";
        return PI - theta0;
    }
    else if( ez < 0.0){
//        std::cout << "return PI+theta";
        return PI + theta0;
    }

}

double AdvancingFront::dot_product(double *vec_u, double *vec_v){

    return vec_u[0]*vec_v[0] + vec_u[1]*vec_v[1];
}
double AdvancingFront::cross_product(double *vec_u, double *vec_v){

    return vec_u[0]*vec_v[1] - vec_u[1]*vec_v[0];
}

double AdvancingFront::norm(double *vec){

    return sqrt( (vec[0]*vec[0]) + (vec[1]*vec[1]) );

}

void AdvancingFront::writeElement(int ielm)
{
    const std::string path = "../output/testMesh" + std::to_string(ielm) + ".vtk";
    std::ofstream geoOut;
    geoOut.open(path.c_str(), std::ios::out ); //ouverture du fichier en mode ecriture
    geoOut  << std::setiosflags (std::ios::scientific) << std::setprecision(5);

    geoOut << "# vtk DataFile Version 3.0" << std::endl;
    geoOut << "testMesh" + std::to_string(ielm) << std::endl;
    geoOut << "ASCII" << std::endl;
    geoOut << "DATASET POLYDATA" << std::endl;
    geoOut << "POINTS " << node->size() << " float"<< std::endl;

    for (int i = 0; i < node->size(); i ++ ){
         geoOut  << node->getX(i) << " " << node->getY(i) << " " << 0.0 << std::endl;
    }

    geoOut << std::endl;
    geoOut << "VERTICES " << node->size() << " " << 2*node->size() << std::endl;

    for (int i = 0; i < node->size(); i ++ ){
         geoOut << 1 << " " << i << std::endl;

    }

    geoOut << std::endl;
    geoOut << "LINES " << edge->size() << " " << 3*edge->size() << std::endl;

    for (int i = 0; i < edge->size(); i ++ ){
         geoOut << 2 << " " << edge->getNode(i,0) << " " << edge->getNode(i,1) << std::endl;

    }

}

void AdvancingFront::writeMesh()
{

    const std::string path = "../output/testMesh_Finale.vtk";
    std::ofstream geoOut;
    geoOut.open(path.c_str(), std::ios::out ); //ouverture du fichier en mode ecriture
    geoOut  << std::setiosflags (std::ios::scientific) << std::setprecision(5);

    geoOut << "# vtk DataFile Version 3.0" << std::endl;
    geoOut << "testMesh_finale" << std::endl;
    geoOut << "ASCII" << std::endl;
    geoOut << "DATASET UNSTRUCTURED_GRID" << std::endl;
    geoOut << "POINTS " << node->size() << " float"<< std::endl;

    for (int i = 0; i < node->size(); i ++ ){
         geoOut  << node->getX(i) << " " << node->getY(i) << " " << 0.0 << std::endl;
    }

//    geoOut << std::endl;
//    geoOut << "VERTICES " << node->size() << " " << 2*node->size() << std::endl;

//    for (int i = 0; i < node->size(); i ++ ){
//         geoOut << 1 << " " << i << std::endl;

//    }

//    geoOut << std::endl;
//    geoOut << "LINES " << edge->size() << " " << 3*edge->size() << std::endl;

//    for (int i = 0; i < edge->size(); i ++ ){
//         geoOut << 2 << " " << edge->getNode(i,0) << " " << edge->getNode(i,1) << std::endl;

//    }

    geoOut << std::endl;
    geoOut << "CELLS " << triangle->size() << " " << 4*triangle->size() << std::endl;

    for (int i = 0; i < triangle->size(); i ++ ){
        geoOut << 3 << " " << triangle->getNode(i, 0) << " " << triangle->getNode(i, 1) << " " << triangle->getNode(i, 2) << std::endl;

    }


    geoOut << std::endl;
    geoOut << "CELL_TYPES " << triangle->size() << std::endl;
    for (int i = 0; i < triangle->size(); i ++ ){
         geoOut << 5 << std::endl;

    }

    geoOut << std::endl;
    geoOut << "CELL_DATA " << triangle->size() << std::endl;
    geoOut << "SCALARS INSIDE float" << std::endl;
    geoOut << "LOOKUP_TABLE default " << std::endl;

    for (int i = 0; i < triangle->size(); i ++ ){
         geoOut << i << std::endl;

    }

}
