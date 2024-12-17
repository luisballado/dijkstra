#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include "FibonacciNode.h"
#include <vector>
#include <unordered_map>
#include <cmath>
#include <climits>

class FibonacciHeap {
private:
    FibonacciNode* minNode;
    int nodeCount;

    void mergeIntoRootList(FibonacciNode* a, FibonacciNode* b);
    void removeNodeFromList(FibonacciNode* node);
    void link(FibonacciNode* y, FibonacciNode* x);
    void consolidate();
    void cut(FibonacciNode* node, FibonacciNode* parent);
    void cascadingCut(FibonacciNode* node);

public:
    FibonacciHeap();
    FibonacciNode* insert(int key, int distance);
    FibonacciNode* extractMin();
    void decreaseKey(FibonacciNode* node, int newDistance);
    bool isEmpty() const;
};

#endif // FIBONACCI_HEAP_H
