#include "AdvancingFront.h"

AdvancingFront::AdvancingFront()
{

}

void AdvancingFront::mesh()
{
    Edge *front = new Edge();
    front->node = node;

    front->setSize(edge->size());
    triangle->setSize(0);

    //copy edge from geometry
    for(int i=0; i<front->size(); i++)
    {
        front->set(i, edge->getCurrent(i), edge->getPrevious(i), edge->getNext(i));
//        std::cout << i << " : " << front->getCurrent(i) << " " << front->getPrevious(i) << " " << front->getNext(i) << std::endl;
    }



//    while(front->size() < front->size()+1)
    for(int k=0; k<2; k++)
    {
        //Select the smallest edge
        int indexMin = 0;
        double min   = edge->length(indexMin);

        for(int i=0; i<front->size(); i++)
        {

            std::cout << front->getCurrent(i) << " : " << edge->length(front->getCurrent(i)) << std::endl;

            if(edge->length(front->getCurrent(i)) < min)
            {
                min      = edge->length(front->getCurrent(i));
                indexMin = front->getCurrent(i);
            }

        }

        int currPos = front->getCurrent(indexMin);
        int prevPos = front->getPrevious(currPos);
        int nextPos = front->getNext(currPos);

        std::cout << "  current  edge : " << currPos << std::endl;
        std::cout << "  previous edge : " << prevPos << std::endl;
        std::cout << "  next     edge : " << nextPos << std::endl;

        //test caseA
        double u[2] = { node->getX(currPos) - node->getX(prevPos), node->getY(currPos) - node->getY(prevPos) };
        double v[2] = { node->getX(nextPos) - node->getX(currPos), node->getY(nextPos) - node->getY(currPos) };

        if(angle(&u[0], &v[0]) < 0.5*PI) // if the angle at current position is < pi/2
        {
            std::cout << "      case A : alpha < PI/2" << std::endl;
            // --> close the triangle
            // --> remove current position
            // --> prevposition become the current
            // --> downsize frontSize

        }
        else if(0.5*PI < angle(&u[0], &v[0]) && angle(&u[0], &v[0]) < 2*PI*ONETHIRD)
        {
            std::cout << "      case B : PI/2 < alpha < 2PI/3" << std::endl;

        }
        else if(2*PI*ONETHIRD < angle(&u[0], &v[0]))
        {
            std::cout << "      case C : 2PI/3 < alpha " << std::endl;

            //Build the new node
            double x = edge->getNodeX(currPos,1) - edge->getNodeX(currPos,0);
            double y = edge->getNodeY(currPos,1) - edge->getNodeY(currPos,0);

            double xnew = x * cos(PI*ONETHIRD) - y * sin(PI*ONETHIRD) + edge->getNodeX(currPos,0);
            double ynew = x * sin(PI*ONETHIRD) + y * cos(PI*ONETHIRD) + edge->getNodeY(currPos,0);

            node->set(node->size(), xnew, ynew);

            //test triangle area to know if the edge support has to be inverted
            if(triangle->isAreaPositive(edge->getNode(currPos,0), edge->getNode(currPos,1), node->size()) == true)
            {
                //create new node----------
                std::cout << "      --> triangle area is positive" << std::endl;
                std::cout << "          --> create node" << node->size() << " : (" << xnew << "," << ynew << ")" << std::endl;

                //build new edges----------
                std::cout << "          --> create edge" << edge->size() << " : (" << edge->getNode(currPos,1) << "," << node->size() << ")" << std::endl;
                edge->set(edge->size(), edge->getNode(currPos,1), node->size(), triangle->size(), EMPTY, edge->getNode(currPos,0), EMPTY);
                edge->setSize(edge->size()+1);

                std::cout << "          --> create edge" << edge->size() << " : (" << node->size() << "," << edge->getNode(currPos,0) << ")" << std::endl;
                edge->set(edge->size(), node->size(), edge->getNode(currPos,0), triangle->size(), EMPTY, edge->getNode(currPos,1), EMPTY);
                edge->setSize(edge->size()+1);

                //update node size
                node->setSize(node->size()+1);
                //update base edge
                edge->setLeftElement(currPos, triangle->size());

                //build new triangle-------
                std::cout << "          --> create triangle" << triangle->size() << " : (" << currPos << "," << edge->size()-2 << "," << edge->size()-1 << ")" << std::endl;
                triangle->set(triangle->size(), currPos, edge->size()-2, edge->size()-1);
                triangle->setSize(triangle->size()+1);

                //update front
                front->set(front->size(), edge->size()-2, currPos, front->getNext(currPos));
                front->set(currPos,  edge->size()-1, front->getPrevious(currPos), edge->size()-2);
                std::cout << "          --> update currPos" << currPos << " : (" << front->getCurrent(currPos) << "," << front->getPrevious(currPos) << "," << front->getNext(currPos) << ")" << std::endl;
                std::cout << "          --> update currPos" << front->size() << " : (" << front->getCurrent(front->size()) << "," << front->getPrevious(front->size()) << "," << front->getNext(front->size()) << ")" << std::endl;

                front->setSize(front->size()+1);



            }
            else{

                //Build the new node
                double x = edge->getNodeX(currPos,0) - edge->getNodeX(currPos,1);
                double y = edge->getNodeY(currPos,0) - edge->getNodeY(currPos,1);

                double xnew = x * cos(PI*ONETHIRD) - y * sin(PI*ONETHIRD) + edge->getNodeX(currPos,1);
                double ynew = x * sin(PI*ONETHIRD) + y * cos(PI*ONETHIRD) + edge->getNodeY(currPos,1);

                node->set(node->size(), xnew, ynew);

                //create new node----------
                std::cout << "      --> triangle area is Negative" << std::endl;
                std::cout << "          --> create node" << node->size() << " : (" << xnew << "," << ynew << ")" << std::endl;

                //build new edges----------
                std::cout << "          --> create edge" << edge->size() << " : (" << edge->getNode(currPos,0) << "," << node->size() << ")" << std::endl;
                edge->set(edge->size(), edge->getNode(currPos,0), node->size(), triangle->size(), EMPTY, edge->getNode(currPos,1), EMPTY);
                edge->setSize(edge->size()+1);

                std::cout << "          --> create edge" << edge->size() << " : (" << node->size() << "," << edge->getNode(currPos,1) << ")" << std::endl;
                edge->set(edge->size(), node->size(), edge->getNode(currPos,1), triangle->size(), EMPTY, edge->getNode(currPos,0), EMPTY);
                edge->setSize(edge->size()+1);

                //update node size
                node->setSize(node->size()+1);
                //update base edge
                edge->setRightElement(currPos, triangle->size());

                //build new triangle-------
                std::cout << "          --> create triangle" << triangle->size() << " : (" << currPos << "," << edge->size()-2 << "," << edge->size()-1 << ")" << std::endl;
                triangle->set(triangle->size(), currPos, edge->size()-2, edge->size()-1);
                triangle->setSize(triangle->size()+1);

                //update front
                front->set(front->size(), edge->size()-2, currPos, front->getNext(currPos));
                front->set(currPos,  edge->size()-1, front->getPrevious(currPos), edge->size()-2);

                std::cout << "          --> update currPos" << currPos << " : (" << front->getCurrent(currPos) << "," << front->getPrevious(currPos) << "," << front->getNext(currPos) << ")" << std::endl;
                std::cout << "          --> update currPos" << front->size() << " : (" << front->getCurrent(front->size()) << "," << front->getPrevious(front->size()) << "," << front->getNext(front->size()) << ")" << std::endl;

                front->setSize(front->size()+1);

            }

        }
        else
        {
            std::cout << "***ERROR no case was found" << indexMin << std::endl;
        }

    }


    delete front;

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
