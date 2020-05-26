#include "AdvancingFront.h"

AdvancingFront::AdvancingFront()
{

}

void AdvancingFront::mesh()
{
    Edge *front = new Edge();
    front->node = node;

    //init size
    front->setSize(edge->size());
    triangle->setSize(0);

    int activate[1000];
    double minAngle;

    //copy edge from geometry
    for(int i=0; i<front->size(); i++)
    {
        front->set(i, edge->getCurrent(i), edge->getPrevious(i), edge->getNext(i));
    }



//    while(front->size() < front->size()+1)
    for(int k=0; k<3; k++)
    {
        //Select the smallest edge
        int indexMin = 0;
        double min   = edge->length(indexMin);

        for(int i=0; i<front->size(); i++)
        {

            if(edge->length(front->getCurrent(i)) < min && activate[i] != 1)
            {
                min      = edge->length(front->getCurrent(i));
                indexMin = i;
            }

        }

        int currPos   = front->getCurrent(indexMin);
        int currNode0 = edge->getNode(currPos, 0);
        int currNode1 = edge->getNode(currPos, 1);

        int prevPos   = front->getPrevious(indexMin);
        int prevNode0 = edge->getNode(prevPos, 0);
        int prevNode1 = edge->getNode(prevPos, 1);

        int nextPos   = front->getNext(indexMin);
        int nextNode0 = edge->getNode(nextPos, 0);
        int nextNode1 = edge->getNode(nextPos, 1);

        if(edge->getLeftElement(currPos) != EMPTY)
        {
            currNode0 = edge->getNode(currPos, 1);
            currNode1 = edge->getNode(currPos, 0);
        }
        if(edge->getLeftElement(prevPos) != EMPTY)
        {
            prevNode0 = edge->getNode(prevPos, 1);
            prevNode1 = edge->getNode(prevPos, 0);
        }
        if(edge->getLeftElement(nextPos) != EMPTY)
        {
            nextNode0 = edge->getNode(nextPos, 1);
            nextNode1 = edge->getNode(nextPos, 0);
        }

        //calc angle on currNode0
        double u1[2] = { node->getX(currNode0) - node->getX(prevNode0), node->getY(currNode0) - node->getY(prevNode0) };
        double v1[2] = { node->getX(nextNode0) - node->getX(currNode0), node->getY(nextNode0) - node->getY(currNode0) };

        //calc angle on currNode1
        double u2[2] = { node->getX(currNode1) - node->getX(currNode0), node->getY(currNode1) - node->getY(currNode0) };
        double v2[2] = { node->getX(nextNode1) - node->getX(currNode1), node->getY(nextNode1) - node->getY(currNode1) };

        if(angle(&u2[0], &v2[0]) < angle(&u1[0], &v1[0]))
        {
            currPos   = front->getNext(indexMin);
            currNode0 = edge->getNode(currPos, 0);
            currNode1 = edge->getNode(currPos, 1);

            prevPos   = front->getCurrent(indexMin);
            prevNode0 = edge->getNode(prevPos, 0);
            prevNode1 = edge->getNode(prevPos, 1);

            nextPos   = front->getNext(currPos);
            nextNode0 = edge->getNode(nextPos, 0);
            nextNode1 = edge->getNode(nextPos, 1);

            if(edge->getLeftElement(currPos) != EMPTY)
            {
                currNode0 = edge->getNode(currPos, 1);
                currNode1 = edge->getNode(currPos, 0);
            }
            if(edge->getLeftElement(prevPos) != EMPTY)
            {
                prevNode0 = edge->getNode(prevPos, 1);
                prevNode1 = edge->getNode(prevPos, 0);
            }
            if(edge->getLeftElement(nextPos) != EMPTY)
            {
                nextNode0 = edge->getNode(nextPos, 1);
                nextNode1 = edge->getNode(nextPos, 0);
            }

            minAngle = angle(&u2[0], &v2[0]);

        }
        else
        {
            minAngle = angle(&u1[0], &v1[0]);
        }

        std::cout << "  previous edge" << prevPos << " (" << prevNode0 << "," << prevNode1 << ") left element is : " << edge->getLeftElement(prevPos) << std::endl;
        std::cout << "  current  edge" << currPos << " (" << currNode0 << "," << currNode1 << ") left element is : " << edge->getLeftElement(currPos) << std::endl;
        std::cout << "  next     edge" << nextPos << " (" << nextNode0 << "," << nextNode1 << ") left element is : " << edge->getLeftElement(nextPos) << std::endl;








        if(minAngle <= 0.5*PI) // if the angle at current position is < pi/2
        {
            std::cout << "      case A : alpha < PI/2" << std::endl;

            //test if there is another point inside circumcenter
            int isInside = 0;
            for(int i=0; i<node->size(); i++)
            {
                if(i != currNode0 && i != currNode1 && i != prevNode0)
                {
                    if(triangle->inCircle(currNode0, currNode1, prevNode0, i))
                    {
                        std::cout << "      ***node : " << i << " is inside the triangle(" << currNode0 << "," << currNode1 << "," << prevNode0 << ")" << std::endl;
                        isInside = 1;
                    }
                }

            }

            if(isInside == 1)
            {




            }
            else
            {

                //build new edges----------
                edge->set(edge->size(), currNode1, prevNode0, triangle->size(), EMPTY, currNode0, EMPTY);
                edge->setSize(edge->size()+1);

                //update base edge
                if(edge->getLeftElement(currPos) != EMPTY)
                {
                    edge->setRightElement(currPos, triangle->size());
                }
                else
                {
                    edge->setLeftElement(currPos, triangle->size());
                }

                //update prev edge
                if(edge->getLeftElement(prevPos) != EMPTY)
                {
                    edge->setRightElement(prevPos, triangle->size());
                }
                else
                {
                    edge->setLeftElement(prevPos, triangle->size());
                }

                //build new triangle-------
                triangle->set(triangle->size(), currPos, edge->size()-1, prevPos);
                triangle->setSize(triangle->size()+1);

                //display
                std::cout << "          --> create ";
                edge->print(edge->size()-1);

                std::cout << "          --> create ";
                triangle->print(triangle->size()-1);

                std::cout << "          --> update ";
                edge->print(currPos);

                std::cout << "          --> update ";
                edge->print(prevPos);

                //update front
                activate[currPos] = 1;
                activate[prevPos] = 1;

                std::cout << "              --> update front" << currPos << " : ***de-activated" << std::endl;
                std::cout << "              --> update front" << prevPos << " : ***de-activated" << std::endl;


                front->set(nextPos  , nextPos, edge->size()-1, front->getNext(nextPos));
                std::cout << "              --> update front" << nextPos << " : (" << front->getCurrent(nextPos) << "," << front->getPrevious(nextPos) << "," << front->getNext(nextPos) << ")" << std::endl;

                front->set(front->size()  , edge->size()-1, front->getPrevious(prevPos), nextPos);
                front->setSize(front->size()+1);

                std::cout << "              --> update front" << front->size()-1 << " : (" << front->getCurrent(front->size()-1) << "," << front->getPrevious(front->size()-1) << "," << front->getNext(front->size()-1) << ")" << std::endl;

            }
        }
        else if(0.5*PI < minAngle && minAngle < 2*PI*ONETHIRD)
        {

            std::cout << "      case B : PI/2 < alpha < 2PI/3" << std::endl;

            //Build the new node
            double x = node->getX(currNode1) - node->getX(currNode0);
            double y = node->getY(currNode1) - node->getY(currNode0);

            double xnew = x * cos(0.5*minAngle) - y * sin(0.5*minAngle) + node->getX(currNode0);
            double ynew = x * sin(0.5*minAngle) + y * cos(0.5*minAngle) + node->getY(currNode0);
            node->set(node->size(), xnew, ynew);

            //test if there is another point inside circumcenter
            int isInside = 0;
            int minDistance = 9999.9;
            int indexInside = 0;

            for(int i=0; i<node->size(); i++)
            {
                if(i != currNode0 && i != currNode1 && i != node->size())
                {

                    double x = node->getX(i) - node->getX(node->size());
                    double y = node->getY(i) - node->getY(node->size());
                    double R = .5*edge->length(currPos);

                    if(triangle->inCircle(currNode0, currNode1, node->size(), i) || x*x + y*y < R*R)
                    {
//                        std::cout << "      test : " << i << "(" << currNode0 << "," << currNode1 << "," << node->size() << ")" << std::endl;
                        isInside = 1;
                        if(node->distance(currNode0, i) < minDistance)
                        {
//                            std::cout << node->distance(currNode0, i) << std::endl;
                            minDistance = node->distance(currNode0, i);
                            indexInside = i;
                        }

                    }
                }

            }

            if(isInside == 1)
            {

                //build new edges----------
                edge->set(edge->size(), currNode1, indexInside, triangle->size(), EMPTY, currNode0, EMPTY);
                edge->setSize(edge->size()+1);

                edge->set(edge->size(), indexInside, currNode0, triangle->size(), EMPTY, currNode1, EMPTY);
                edge->setSize(edge->size()+1);

                edge->set(edge->size(), indexInside, prevNode0, triangle->size()+1, EMPTY, prevNode1, EMPTY);
                edge->setSize(edge->size()+1);

                //update base edge
                if(edge->getLeftElement(currPos) != EMPTY)
                {
                    edge->setRightElement(currPos, triangle->size());
                }
                else
                {
                    edge->setLeftElement(currPos, triangle->size());
                }

                //build new triangle-------
                triangle->set(triangle->size(), currPos, edge->size()-3, edge->size()-2);
                triangle->setSize(triangle->size()+1);

                triangle->set(triangle->size(), edge->size()-2, edge->size()-1, prevPos);
                triangle->setSize(triangle->size()+1);

                //display
                std::cout << "          --> create ";
                edge->print(edge->size()-3);

                std::cout << "          --> create ";
                edge->print(edge->size()-2);

                std::cout << "          --> create ";
                edge->print(edge->size()-1);

                std::cout << "          --> create ";
                triangle->print(triangle->size()-2);

                std::cout << "          --> create ";
                triangle->print(triangle->size()-1);

                std::cout << "          --> update ";
                edge->print(currPos);

                std::cout << "          --> update ";
                edge->print(prevPos);


                //update front
                activate[currPos] = 1;
                activate[prevPos] = 1;
                activate[front->size()+1] = 1;

                std::cout << "              --> update front" << currPos << " : ***de-activated" << std::endl;
                std::cout << "              --> update front" << prevPos << " : ***de-activated" << std::endl;
                std::cout << "              --> update front" << front->size()+1 << " : ***de-activated" << std::endl;


                front->set(front->size()  , edge->size()-3, edge->size()-1             , nextPos);
                front->set(front->size()+1, edge->size()-2, prevPos                    , edge->size()-2);
                front->set(front->size()+2, edge->size()-1, front->getPrevious(prevPos), edge->size()-3);
                front->setSize(front->size()+3);

                front->set(nextPos        , front->getCurrent(nextPos), front->getCurrent(front->size()-3), front->getNext(nextPos));


                std::cout << "              --> update front" << nextPos << " : (" << front->getCurrent(nextPos) << "," << front->getPrevious(nextPos) << "," << front->getNext(nextPos) << ")" << std::endl;
                std::cout << "              --> update front" << front->size()-3 << " : (" << front->getCurrent(front->size()-3) << "," << front->getPrevious(front->size()-3) << "," << front->getNext(front->size()-3) << ")" << std::endl;
                std::cout << "              --> update front" << front->size()-1 << " : (" << front->getCurrent(front->size()-1) << "," << front->getPrevious(front->size()-1) << "," << front->getNext(front->size()-1) << ")" << std::endl;



            }
            else
            {

                //create new node----------
                std::cout << "      --> triangle(" << currNode0  << "," << currNode1 << "," << node->size() << ")" << std::endl;
                std::cout << "          --> create node" << node->size() << " : (" << xnew << "," << ynew << ")" << std::endl;

                //build new edges----------
                edge->set(edge->size(), currNode1, node->size(), triangle->size(), EMPTY, currNode0, EMPTY);
                edge->setSize(edge->size()+1);

                edge->set(edge->size(), node->size(), currNode0, triangle->size(), EMPTY, currNode1, EMPTY);
                edge->setSize(edge->size()+1);

                edge->set(edge->size(), node->size(), prevNode0, triangle->size()+1, EMPTY, prevNode1, EMPTY);
                edge->setSize(edge->size()+1);

                //update node size
                node->setSize(node->size()+1);

                //update base edge
                if(edge->getLeftElement(currPos) != EMPTY)
                {
                    edge->setRightElement(currPos, triangle->size());
                }
                else
                {
                    edge->setLeftElement(currPos, triangle->size());
                }

                //update prev edge
                if(edge->getLeftElement(prevPos) != EMPTY)
                {
                    edge->setRightElement(prevPos, triangle->size()+1);
                }
                else
                {
                    edge->setLeftElement(prevPos, triangle->size()+1);
                }

                //build new triangle-------
                triangle->set(triangle->size(), currPos, edge->size()-3, edge->size()-2);
                triangle->setSize(triangle->size()+1);

                triangle->set(triangle->size(), edge->size()-2, edge->size()-1, prevPos);
                triangle->setSize(triangle->size()+1);

                //display
                std::cout << "          --> create ";
                edge->print(edge->size()-3);

                std::cout << "          --> create ";
                edge->print(edge->size()-2);

                std::cout << "          --> create ";
                edge->print(edge->size()-1);

                std::cout << "          --> create ";
                triangle->print(triangle->size()-2);

                std::cout << "          --> create ";
                triangle->print(triangle->size()-1);

                std::cout << "          --> update ";
                edge->print(currPos);

                std::cout << "          --> update ";
                edge->print(prevPos);


                //update front
                activate[currPos] = 1;
                activate[prevPos] = 1;
                activate[front->size()+1] = 1;

                std::cout << "              --> update front" << currPos << " : ***de-activated" << std::endl;
                std::cout << "              --> update front" << prevPos << " : ***de-activated" << std::endl;
                std::cout << "              --> update front" << front->size()+1 << " : ***de-activated" << std::endl;


                front->set(front->size()  , edge->size()-3, edge->size()-1             , nextPos);
                front->set(front->size()+1, edge->size()-2, prevPos                    , edge->size()-2);
                front->set(front->size()+2, edge->size()-1, front->getPrevious(prevPos), edge->size()-3);
                front->setSize(front->size()+3);

                front->set(nextPos        , front->getCurrent(nextPos), front->getCurrent(front->size()-3), front->getNext(nextPos));


                std::cout << "              --> update front" << nextPos << " : (" << front->getCurrent(nextPos) << "," << front->getPrevious(nextPos) << "," << front->getNext(nextPos) << ")" << std::endl;
                std::cout << "              --> update front" << front->size()-3 << " : (" << front->getCurrent(front->size()-3) << "," << front->getPrevious(front->size()-3) << "," << front->getNext(front->size()-3) << ")" << std::endl;
                std::cout << "              --> update front" << front->size()-1 << " : (" << front->getCurrent(front->size()-1) << "," << front->getPrevious(front->size()-1) << "," << front->getNext(front->size()-1) << ")" << std::endl;


            }

        }
        else if(2*PI*ONETHIRD <= minAngle)
        {
            std::cout << "      case C : 2PI/3 < alpha " << std::endl;

            //Build the new node
            double x = node->getX(currNode1) - node->getX(currNode0);
            double y = node->getY(currNode1) - node->getY(currNode0);

            double xnew = x * cos(PI*ONETHIRD) - y * sin(PI*ONETHIRD) + node->getX(currNode0);
            double ynew = x * sin(PI*ONETHIRD) + y * cos(PI*ONETHIRD) + node->getY(currNode0);
            node->set(node->size(), xnew, ynew);

            //test if there is another point inside circumcenter
            int isInside = 0;
            double minDistance = 9999.9;
            int indexInside = 0;

//            for(int i=0; i<node->size(); i++)
//            {
//                if(i != currNode0 && i != currNode1 && i != node->size())
//                {

//                    double x = node->getX(i) - node->getX(node->size());
//                    double y = node->getY(i) - node->getY(node->size());
//                    double R = .5*edge->length(currPos);

//                    if(triangle->inCircle(currNode0, currNode1, node->size(), i) || x*x + y*y < R*R)
//                    {
////                        std::cout << "      test : " << i << "(" << currNode0 << "," << currNode1 << "," << node->size() << ")" << std::endl;
//                        isInside = 1;
//                        if(node->distance(currNode0, i) < minDistance)
//                        {
////                            std::cout << node->distance(currNode0, i) << std::endl;
//                            minDistance = node->distance(currNode0, i);
//                            indexInside = i;
//                        }

//                    }
//                }

//            }

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

                std::cout << "      ***edge : " << edgeInside[0] << " and " << edgeInside[1]  << " is inside the triangle(" << currNode0 << "," << currNode1 << "," << prevNode0 << ")" << std::endl;
                std::cout << "      ***node : " << indexInside << " is inside the triangle(" << currNode0 << "," << currNode1 << "," << prevNode0 << ")" << std::endl;

                //build new edges----------
                edge->set(edge->size(), currNode1, indexInside, triangle->size(), EMPTY, currNode0, EMPTY);
                edge->setSize(edge->size()+1);

                edge->set(edge->size(), indexInside, currNode0, triangle->size(), EMPTY, currNode1, EMPTY);
                edge->setSize(edge->size()+1);

                //update base edge
                if(edge->getLeftElement(currPos) != EMPTY)
                {
                    edge->setRightElement(currPos, triangle->size());
                }
                else
                {
                    edge->setLeftElement(currPos, triangle->size());
                }

                //build new triangle-------
                triangle->set(triangle->size(), currPos, edge->size()-2, edge->size()-1);
                triangle->setSize(triangle->size()+1);

                //display
                std::cout << "          --> create ";
                edge->print(edge->size()-2);

                std::cout << "          --> create ";
                edge->print(edge->size()-1);

                std::cout << "          --> create ";
                triangle->print(triangle->size()-1);

                std::cout << "          --> update ";
                edge->print(currPos);

                std::cout << "          --> update ";
                edge->print(prevPos);


                //update front
                activate[currPos] = 1;

                front->set(front->size()  , edge->size()-2            , edgeInside[0]                  , nextPos);
                front->set(front->size()+1, edge->size()-1            , prevPos                        , edgeInside[1]);
                front->setSize(front->size()+2);

                front->set(prevPos        , front->getCurrent(prevPos), front->getPrevious(prevPos)     , front->getCurrent(front->size()-1));
                front->set(nextPos        , front->getCurrent(nextPos), front->getCurrent(front->size()-2), front->getNext(nextPos));

                front->set(edgeInside[0]        , front->getCurrent(edgeInside[0]), front->getPrevious(edgeInside[0])     , edge->size()-2);
                front->set(edgeInside[1]        , front->getCurrent(edgeInside[1]), edge->size()-1, front->getNext(edgeInside[1]));


                std::cout << "              --> update front" << currPos << " : ***de-activated" << std::endl;
                std::cout << "              --> update front" << prevPos << " : (" << front->getCurrent(prevPos) << "," << front->getPrevious(prevPos) << "," << front->getNext(prevPos) << ")" << std::endl;
                std::cout << "              --> update front" << nextPos << " : (" << front->getCurrent(nextPos) << "," << front->getPrevious(nextPos) << "," << front->getNext(nextPos) << ")" << std::endl;
                std::cout << "              --> update front" << edgeInside[0] << " : (" << front->getCurrent(edgeInside[0]) << "," << front->getPrevious(edgeInside[0]) << "," << front->getNext(edgeInside[0]) << ")" << std::endl;
                std::cout << "              --> update front" << edgeInside[1] << " : (" << front->getCurrent(edgeInside[1]) << "," << front->getPrevious(edgeInside[1]) << "," << front->getNext(edgeInside[1]) << ")" << std::endl;


                std::cout << "              --> update front" << front->size()-2 << " : (" << front->getCurrent(front->size()-2) << "," << front->getPrevious(front->size()-2) << "," << front->getNext(front->size()-2) << ")" << std::endl;
                std::cout << "              --> update front" << front->size()-1 << " : (" << front->getCurrent(front->size()-1) << "," << front->getPrevious(front->size()-1) << "," << front->getNext(front->size()-1) << ")" << std::endl;





            }
            else
            {
                //create new node----------
                std::cout << "      --> triangle(" << currNode0  << "," << currNode1 << "," << node->size() << ")" << std::endl;
                std::cout << "          --> create node" << node->size() << " : (" << xnew << "," << ynew << ")" << std::endl;

                //build new edges----------
                edge->set(edge->size(), currNode1, node->size(), triangle->size(), EMPTY, currNode0, EMPTY);
                edge->setSize(edge->size()+1);

                edge->set(edge->size(), node->size(), currNode0, triangle->size(), EMPTY, currNode1, EMPTY);
                edge->setSize(edge->size()+1);

                //update node size
                node->setSize(node->size()+1);

                //update base edge
                if(edge->getLeftElement(currPos) != EMPTY)
                {
                    edge->setRightElement(currPos, triangle->size());
                }
                else
                {
                    edge->setLeftElement(currPos, triangle->size());
                }

                //build new triangle-------
                triangle->set(triangle->size(), currPos, edge->size()-2, edge->size()-1);
                triangle->setSize(triangle->size()+1);

                //display
                std::cout << "          --> create ";
                edge->print(edge->size()-2);

                std::cout << "          --> create ";
                edge->print(edge->size()-1);

                std::cout << "          --> create ";
                triangle->print(triangle->size()-1);

                std::cout << "          --> update ";
                edge->print(currPos);

                std::cout << "          --> update ";
                edge->print(prevPos);


                //update front
                activate[currPos] = 1;
                std::cout << "              --> update front" << currPos << " : ***de-activated" << std::endl;

                front->set(front->size()  , edge->size()-2            , edge->size()-1                  , nextPos);
                front->set(front->size()+1, edge->size()-1            , prevPos                         , edge->size()-2);
                front->setSize(front->size()+2);

                if(edge->getRightElement(nextPos) == OUT)
                {
                    activate[prevPos] = 1;
                    std::cout << "              --> update front" << nextPos << " : ***de-activated" << std::endl;
                }
                else
                {
                    front->set(prevPos        , front->getCurrent(prevPos), front->getPrevious(prevPos)     , front->getCurrent(front->size()-1));
                    std::cout << "              --> update front" << prevPos << " : (" << front->getCurrent(prevPos) << "," << front->getPrevious(prevPos) << "," << front->getNext(prevPos) << ")" << std::endl;

                }
                if(edge->getRightElement(nextPos) == OUT){
                    activate[nextPos] = 1;
                    std::cout << "              --> update front" << nextPos << " : ***de-activated" << std::endl;
                }
                else
                {
                    front->set(nextPos        , front->getCurrent(nextPos), front->getCurrent(front->size()-2), front->getNext(nextPos));
                    std::cout << "              --> update front" << nextPos << " : (" << front->getCurrent(nextPos) << "," << front->getPrevious(nextPos) << "," << front->getNext(nextPos) << ")" << std::endl;
                }





                std::cout << "              --> update front" << front->size()-2 << " : (" << front->getCurrent(front->size()-2) << "," << front->getPrevious(front->size()-2) << "," << front->getNext(front->size()-2) << ")" << std::endl;
                std::cout << "              --> update front" << front->size()-1 << " : (" << front->getCurrent(front->size()-1) << "," << front->getPrevious(front->size()-1) << "," << front->getNext(front->size()-1) << ")" << std::endl;




            }

        }
        else
        {
            std::cout << "***ERROR no case was found" << indexMin << std::endl;
        }


        const std::string path = "../output/testMesh" + std::to_string(k) + ".vtk";
        std::ofstream geoOut;
        geoOut.open(path.c_str(), std::ios::out ); //ouverture du fichier en mode ecriture
        geoOut  << std::setiosflags (std::ios::scientific) << std::setprecision(5);

        geoOut << "# vtk DataFile Version 3.0" << std::endl;
        geoOut << "testMesh" + std::to_string(k) << std::endl;
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


    delete front;

}

void AdvancingFront::buildFront(int size, int arrfront[NMAXNODE][3], Edge *edge)
{
    for(int i; i < size; i++){
        arrfront[i][0] = edge->getCurrent(i);
        arrfront[i][1] = edge->getPrevious(i);
        arrfront[i][2] = edge->getNext(i);
    }
}

int AdvancingFront::findSmallestEdgeIndex(int size, int arrfront[][3])
{
    double min      = 9999.9;
    int    minIndex = -1;

    for(int i = 0; i < size; i++)
    {
        if(edge->length(arrfront[i][0]) < min )
        {
            min      = edge->length(arrfront[i][0]);
            minIndex = i;
        }

    }

    return minIndex;
}

void AdvancingFront::buildMesh()
{
    // initialize variable
    int front[NMAXNODE][3];
    int frontSize = edge->size();

    int nodCounter = node->size();
    int edgCounter = edge->size();
    int elmCounter = 0;

    // copy initial geometry inside front
    buildFront(frontSize, front, edge);

    //begin frontal triangulation
    int N = 1;
    for(int ifront = 0; ifront < N; ifront++)
    {

        int currPos = findSmallestEdgeIndex(frontSize, front);
        int prevPos = front[currPos][1];
        int nextPos = front[currPos][2];

        int currEdge = front[currPos][0];
        int prevEdge = front[prevPos][0];
        int nextEdge = front[nextPos][0];



        std::cout << "  previous edge" << prevEdge << std::endl; //<< " (" << prevNode0 << "," << prevNode1 << ") left element is : " << edge->getLeftElement(prevPos) << std::endl;
        std::cout << "  current  edge" << currEdge << std::endl; //<< " (" << currNode0 << "," << currNode1 << ") left element is : " << edge->getLeftElement(currPos) << std::endl;
        std::cout << "  next     edge" << nextEdge << std::endl; //<< " (" << nextNode0 << "," << nextNode1 << ") left element is : " << edge->getLeftElement(nextPos) << std::endl;



    }





}



double AdvancingFront::angle(double *vec_u, double *vec_v)
{

    double ez     = cross_product(vec_u, vec_v);
    double theta0 = acos((dot_product(vec_u, vec_v)) / (norm(vec_u) * norm(vec_v)));

    if( - 1e-16 < theta0 && theta0 < 1e-16 ){
        return PI;
    }
    else if( PI - 1e-16 < theta0 && theta0 < PI + 1e-16){
        return 0.0;
    }
    else if( ez >= 0.0){
        return PI - theta0;
    }
    else if( ez < 0.0){
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
