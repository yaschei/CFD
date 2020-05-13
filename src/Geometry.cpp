#include "Geometry.h"

int  Geometry::parseFile(std::string filename){

    std::string strTrash, boundaryCondition;
    int nPoints, nLoops, nSide_per_loop, nEdge_per_side, start, end, p1, p2;
    double x, y, boundary_value;
    int count = 0;

    const std::string path = "../data/"  + filename + ".txt";
    std:: ifstream inputFile;
    inputFile.open(path.c_str(), std::ios::in); //ouverture du fichier en mode lecture
    if (!inputFile)
    {
        std::cout << "Error unable to open input file " + filename + " in reading" << std::endl; // test de lecture
        return 1;
    }

    inputFile >> strTrash >> nPoints;
    node->setSize(nPoints);

    inputFile >> strTrash >> nLoops;

    // OUT loop
    inputFile >> strTrash >> nSide_per_loop;

    for (int iside = 0; iside < nSide_per_loop; iside++){

        inputFile >> strTrash >> nEdge_per_side >> start >> end >> boundaryCondition >> boundary_value >> strTrash >> strTrash >> strTrash >> strTrash >> strTrash >> strTrash;

        for(int ie = 0; ie < nEdge_per_side; ie++){

            if( ie > nEdge_per_side-2){

                p1 = start + ie;
                p2 = end;


            }
            else{

                p1 = start + ie;
                p2 = start + ie+1;

            }

            edge->set(count, p1, p2);
            edge->set(count, count, count-1, count+1);
            count +=1;
        }

    }

    //correct first and last edge of the OUT loop
    edge->set(0, 0, 1);
    edge->set(0      , 0, count-1, 1);
    edge->set(count-1, count-1, end);
    edge->set(count-1, count-1, count-2, 0);


    // IN loops
    if(nLoops > 1){

        for (int iloop = 1; iloop < nLoops; iloop++){

            inputFile >> strTrash >> nSide_per_loop;

            for (int iside = 0; iside < nSide_per_loop; iside++){

                inputFile >> strTrash >> nEdge_per_side >> start >> end >> boundaryCondition >> boundary_value >> strTrash >> strTrash >> strTrash >> strTrash >> strTrash >> strTrash;

                for(int ie = 0; ie < nEdge_per_side; ie++){

                    if( ie > nEdge_per_side-2){

                        p1 = start + ie;
                        p2 = end;

                    }
                    else{

                        p1 = start + ie;
                        p2 = start + ie+1;

                    }
                    edge->set(count, count, count+1);
                    edge->set(count, count, count-1, count+1);
                    count +=1;
                }

            }

        }

        //correct first edge of the IN loops
        edge->set(end, end, end+1);
        edge->set(end, end, count-1, end+1); //end of the side is the start of the side
        edge->set(count-1, count-1, end);
        edge->set(count-1, count-1, count-2, end); //last side node is count - 1

    }

    edge->setSize(count);

//    for(int ie=0;ie<edge->size();ie++){
//        std::cout << ie << " : " << edge->getNode(ie,0) << " " << edge->getNode(ie,1) << "||" << edge->getPrevious(ie) << " " << edge->getNext(ie) << std::endl;
//    }

   // Read all points
    for (int ipoint = 0; ipoint < nPoints; ipoint++){
        inputFile >> x >> y >> strTrash;
        node->set(ipoint, x, y);
    }

}
void Geometry::writeVTK(std::string filename){

    const std::string path = "../output/" + filename + ".vtk";
    std::ofstream geoOut;
    geoOut.open(path.c_str(), std::ios::out ); //ouverture du fichier en mode ecriture
    geoOut  << std::setiosflags (std::ios::scientific) << std::setprecision(5);

    geoOut << "# vtk DataFile Version 3.0" << std::endl;
    geoOut << filename << std::endl;
    geoOut << "ASCII" << std::endl;
    geoOut << "DATASET POLYDATA" << std::endl;
    geoOut << "POINTS " << node->size() << " float"<< std::endl;

    for (int i = 0; i < node->size(); i ++ ){
         geoOut  << node->getX(i) << " " << node->getY(i) << " " << 0.0 << std::endl;
    }

    geoOut << std::endl;
    geoOut << "LINES " << edge->size() << " " << 3*edge->size() << std::endl;

    for (int i = 0; i < edge->size(); i ++ ){
         geoOut << 2 << " " << edge->getNode(i,0) << " " << edge->getNode(i,1) << std::endl;

    }

}
