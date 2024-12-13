#include "Graph.h"

// https://www.geeksforgeeks.org/how-to-find-the-maximum-element-of-a-vector-using-stl-in-c/
// https://www.udacity.com/blog/2020/03/c-maps-explained.html
// https://stackoverflow.com/questions/1939953/how-to-find-if-a-given-key-exists-in-a-c-stdmap
// https://www.tutorialspoint.com/how-can-i-clear-console-using-cplusplus

//./main < TestCases/data.txt

///*****************************************
// * AQUI DEFINO LOS METODOS
// * AQUI SE PROGRAMA LO QUE HACEN C/U
// ****************************************/

Graph::Graph() {
  numNodes = 0;
  numEdges = 0;
  adjList.clear();
  
}

// tipo garbage collector
Graph::~Graph() {
  numNodes = 0;
  numEdges = 0;
  adjList.clear();
}

void Graph::split(std::string line, std::vector<int> &res) {
  size_t strPos = line.find(" ");
  size_t lastPos = 0;
  int value;
  while (strPos != std::string::npos) {
    // string to int
    value = stoi(line.substr(lastPos, strPos - lastPos));
    res.push_back(value);
    lastPos = strPos + 1;
    strPos = line.find(" ", lastPos);
  }
  res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

void Graph::loadGraph(std::istream &input) {
  
  //std::cout << "Cargando grafo...." << std::endl;

  std::string line;
  int i = 0;
  int index = 0;

  while(std::getline(input, line)){

    std::cout << line << std::endl;
    //omitir la primera linea por ser un comentario

    if (i == 0){
      i++;
      continue;
    }

    //leer numNodes & numEdges
    if(i == 1){
      std::vector<int> result;
      split(line, result);

      numNodes = result[0];
      numEdges = result[1];

      //hacer resize de la lista de adj

      i++;
      continue;
      
    }

    std::vector<int> result;
    
    //Validacion de entrada

    try{
      split(line, result);
    } catch (const std::invalid_argument &ia){
      std::cout << "Argumento invalido" << std::endl;
    } catch (...){
      std::cout << "Error" << std::endl;
      exit(-1);
    }

    //cargar los datos del grafo
    
  }
  
}

void Graph::printGraph() {
  std::cout << "-------------------------" << std::endl;
  std::cout << "numNode: " << numNodes << " | "
            << "numEdges: " << numEdges << std::endl;
  std::cout << "-------------------------" << std::endl;
  std::cout << "LISTA ADJ" << std::endl;
  std::cout << "-------------------------" << std::endl;
  
}

void Graph::dijkstraMinHeap(){
  std::cout << "Poner aqui implementacion DijkstraMinHeap" << std::endl;
}

void Graph::dijkstraFibHeap(){
  std::cout << "Poner aqui implementacion DijkstraFibHeap" << std::endl;
}
