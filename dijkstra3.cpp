#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <climits>

//ejemplo con fibonacci heap

// Clase para nodos en el Fibonacci Heap
class FibonacciNode {
public:
    int key;
    int distance;
    int degree;
    bool marked;
    FibonacciNode* parent;
    FibonacciNode* child;
    FibonacciNode* left;
    FibonacciNode* right;

    FibonacciNode(int k, int d)
        : key(k), distance(d), degree(0), marked(false),
          parent(nullptr), child(nullptr), left(this), right(this) {}
};

// Clase para el Fibonacci Heap
class FibonacciHeap {
private:
    FibonacciNode* minNode;
    int nodeCount;

    void mergeIntoRootList(FibonacciNode* a, FibonacciNode* b) {
        if (!a || !b) return;
        FibonacciNode* aRight = a->right;
        a->right = b;
        b->left = a;
        b->right = aRight;
        aRight->left = b;
    }

    void removeNodeFromList(FibonacciNode* node) {
        if (!node) return;
        node->left->right = node->right;
        node->right->left = node->left;
        node->left = node->right = node;
    }

    void link(FibonacciNode* y, FibonacciNode* x) {
        removeNodeFromList(y);
        y->parent = x;
        if (!x->child) {
            x->child = y;
            y->left = y->right = y;
        } else {
            mergeIntoRootList(x->child, y);
        }
        x->degree++;
        y->marked = false;
    }

    void consolidate() {
      std::vector<FibonacciNode*> degreeTable(ceil(log2(nodeCount)) + 1, nullptr);
      FibonacciNode* start = minNode;
      FibonacciNode* current = start;

      do {
	FibonacciNode* x = current;
	int degree = x->degree;
	while (degreeTable[degree]) {
	  FibonacciNode* y = degreeTable[degree];
	  if (x->distance > y->distance) std::swap(x, y);
	  link(y, x);
	  degreeTable[degree] = nullptr;
	  ++degree;
	}
	degreeTable[degree] = x;
	current = current->right;
      } while (current != start);
      
      minNode = nullptr;
      for (FibonacciNode* node : degreeTable) {
	if (node) {
	  if (!minNode || node->distance < minNode->distance) {
	    minNode = node;
	  }
	}
      }
    }
  
  void cut(FibonacciNode* node, FibonacciNode* parent) {
    removeNodeFromList(node);
    parent->degree--;
    mergeIntoRootList(minNode, node);
    node->parent = nullptr;
    node->marked = false;
  }
  
  void cascadingCut(FibonacciNode* node) {
    FibonacciNode* parent = node->parent;
    if (parent) {
      if (!node->marked) {
	node->marked = true;
      } else {
	cut(node, parent);
	cascadingCut(parent);
      }
    }
  }
  
public:
  FibonacciHeap() : minNode(nullptr), nodeCount(0) {}
  
  FibonacciNode* insert(int key, int distance) {
    FibonacciNode* newNode = new FibonacciNode(key, distance);
    if (!minNode) {
      minNode = newNode;
    } else {
      mergeIntoRootList(minNode, newNode);
      if (newNode->distance < minNode->distance) {
	minNode = newNode;
      }
    }
    ++nodeCount;
    return newNode;
  }
  
  FibonacciNode* extractMin() {
    FibonacciNode* extracted = minNode;
    if (extracted) {
      if (extracted->child) {
	FibonacciNode* child = extracted->child;
	do {
	  child->parent = nullptr;
	  child = child->right;
	} while (child != extracted->child);
	mergeIntoRootList(minNode, extracted->child);
      }
      
      if (extracted->right == extracted) {
	minNode = nullptr;
      } else {
	minNode = extracted->right;
	removeNodeFromList(extracted);
	consolidate();
      }
      --nodeCount;
    }
    return extracted;
  }
  
  void decreaseKey(FibonacciNode* node, int newDistance) {
    if (newDistance >= node->distance) return;
    node->distance = newDistance;
    FibonacciNode* parent = node->parent;
    
    if (parent && node->distance < parent->distance) {
      cut(node, parent);
      cascadingCut(parent);
    }
    
    if (node->distance < minNode->distance) {
      minNode = node;
    }
  }
  
  bool isEmpty() const {
    return minNode == nullptr;
  }
};

// Función para Dijkstra usando Fibonacci Heap
std::vector<int> dijkstra(const std::vector<std::vector<std::pair<int, int>>>& graph, int start) {
  int n = graph.size();
  std::vector<int> distances(n, std::numeric_limits<int>::max()); // Vector de distancias
  std::vector<int> parents(n, -1);
  FibonacciHeap heap;
  std::unordered_map<int, FibonacciNode*> nodeMap;
  
  distances[start] = 0;
  nodeMap[start] = heap.insert(start, 0);
  
  while (!heap.isEmpty()) {
    FibonacciNode* minNode = heap.extractMin();
    int u = minNode->key;
    
    for (const auto& neighbor : graph[u]) {
      int v = neighbor.first;
      int weight = neighbor.second;
      
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
  
  //cout << "Distancias desde el nodo " << start << ":\n";
  //for (int i = 0; i < n; ++i) {
  //    cout << "Nodo " << i << ": " << (distances[i] == INT_MAX ? -1 : distances[i]) << '\n';
  //}
  return distances;
}

// Programa principal
int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<std::pair<int, int>>> graph(n);
  
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    graph[u].push_back({v, w});
  }
  
  int start;
  std::cin >> start;
  
  
  std::vector<int> distances = dijkstra(graph, start);
  
  // Imprimir las distancias minimas
  std::cout << "Distancias desde el nodo " << start << ":\n";
  for (int i = 0; i < n; ++i) {
    if (distances[i] == std::numeric_limits<int>::max()) {
      std::cout << "Nodo " << i << ": Inalcanzable\n";
    } else {
      std::cout << "Nodo " << i << ": " << distances[i] << "\n";
    }
  }
  
  return 0;
}
