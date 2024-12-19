#include "Graph.h"
#include <vector>
#include <queue>
#include <limits>

//https://www.programiz.com/dsa/fibonacci-heap

///*****************************************
// * AQUI DEFINO LOS METODOS
// * AQUI SE PROGRAMA LO QUE HACEN C/U
// ****************************************/

Graph::Graph() {
  numNodes = 0;
  numEdges = 0;
  nodeExpl = 0;
  adjList.clear();
  
}

// tipo garbage collector
Graph::~Graph() {
  numNodes = 0;
  numEdges = 0;
  nodeExpl = 0;
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

    //std::cout << line << std::endl;
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
      adjList.resize(numNodes + 1);
      i++;
      continue;
    }

    if(i == 2){
      std::vector<int> result;
      split(line, result);
      nodeExpl = result[0];
      i++;
      continue;
    }
    
    std::vector<int> result;
    
    //Validacion de entrada

    try{
      split(line, result);
    } catch (const std::invalid_argument &ia){
      std::cout << "Argumento invalido" << std::endl;
      exit(-1);
    } catch (...){
      std::cout << "Error" << std::endl;
      exit(-1);
    }

    //cargar los datos del grafo

    int nodo1 = result[0];
    int nodo2 = result[1]; 
    int peso = result[2];

    adjList[nodo1].push_back({nodo2,peso});
    
    //i++;
    //continue;
  }
  
}

int Graph::getStartNode(){
  return nodeExpl;
}

int Graph::getNumNodes(){
  return numNodes;
}

void Graph::printGraph() {
  std::cout << "-------------------------" << std::endl;
  std::cout << "numNode: " << numNodes << " | "
            << "numEdges: " << numEdges << std::endl;
  std::cout << "Nodo Inicio: " << nodeExpl << std::endl;
  std::cout << "-------------------------" << std::endl;
  std::cout << "LISTA ADJ" << std::endl;
  std::cout << "-------------------------" << std::endl;
  //O(n)
  for (int nodeU = 1; nodeU <= numNodes; nodeU++) {
    std::cout << nodeU << " --> [";
    //O(m)
    for (int j = 0; j < (int)adjList[nodeU].size(); j++) {
      std::cout << "(" << adjList[nodeU][j].first << "," << adjList[nodeU][j].second << ")";
    }
    std::cout << "]" << std::endl;
  }
  std::cout << "-------------------------" << std::endl;
}

std::vector<int> Graph::dijkstraMinHeap(int start){
  
  int n = numNodes;
  std::vector<int> distances(n+1, std::numeric_limits<int>::max()); // Vector de distancias
  distances[start] = 0; // La distancia al nodo inicial es 0
  
  // Priority queue configurada como min heap (distancia, nodo)
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> min_heap;
  min_heap.emplace(0, start);
  
  while (!min_heap.empty()) {
    auto [current_distance, current_node] = min_heap.top();
    min_heap.pop();
    
    // Si la distancia actual es mayor a la almacenada, ignorar
    if (current_distance > distances[current_node]) {
      continue;
    }
    
    // Explorar los vecinos
    for (const auto& neighbor : adjList[current_node]) {
      int v = neighbor.first;
      int weight = neighbor.second;
      
      // Relajación de la arista
      if (distances[current_node] + weight < distances[v]) {
	distances[v] = distances[current_node] + weight;
	min_heap.emplace(distances[v], v);
      }
    }
  }
  
  return distances;
}

std::vector<int> Graph::dijkstraFibHeap(int start){
  
  int n = numNodes; //tamaño del grafo
  std::vector<int> distances(n, std::numeric_limits<int>::max()); // Vector de distancias
  std::vector<int> parents(n, -1);
  FibonacciHeap heap;
  std::unordered_map<int, FibonacciNode*> nodeMap; //priority queue
  
  distances[start] = 0;
  nodeMap[start] = heap.insert(start, 0);
  
  while (!heap.isEmpty()) {
    FibonacciNode* minNode = heap.extractMin();
    int u = minNode->key;
    std::cout << "Procesando nodo: " << u << "\n";
    

    for (const auto& neighbor : adjList[u]) {
      
      int v = neighbor.first;
      int weight = neighbor.second;

      std::cout << "Explorando vecino: " << v << " con peso: " << weight << "\n";
      std::cout << "Distancia actual: " << distances[u] << ", Nueva distancia: " << distances[u] + weight << "\n";
            
      if (distances[u] + weight < distances[v]) {
	
	distances[v] = distances[u] + weight;
	parents[v] = u;
	
	if (nodeMap.find(v) == nodeMap.end()) {
	  nodeMap[v] = heap.insert(v, distances[v]);
	} else {
	  heap.decreaseKey(nodeMap[v], distances[v]);
	}
      }
    }
  }
  
  return distances;
  
}

std::vector<int> Graph::dijkstra(int start) {

  int n = numNodes; //tamaño del grafo
  
  std::vector<int> distances(n+1, std::numeric_limits<int>::max()); // Vector de distancias
  distances[start] = 0; // La distancia al nodo inicial es 0
  
  // Cola de prioridad para procesar los nodos (distancia, nodo)
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
  pq.emplace(0, start);
  
  while (!pq.empty()) {
    auto [current_distance, current_node] = pq.top();
    pq.pop();
    
    // Explorar los vecinos
    for (const auto& neighbor : adjList[current_node]) {
      int v = neighbor.first;
      int weight = neighbor.second;
      
      // Relajación de la arista
      if (distances[current_node] + weight < distances[v]) {
	distances[v] = distances[current_node] + weight;
	pq.emplace(distances[v], v);
      }
    }
  }
  
  return distances;
}
