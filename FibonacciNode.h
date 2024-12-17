#ifndef FIBONACCI_NODE_H
#define FIBONACCI_NODE_H

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

    FibonacciNode(int k, int d);
};

#endif // FIBONACCI_NODE_H
