#include "FibonacciNode.h"

FibonacciNode::FibonacciNode(int k, int d)
    : key(k), distance(d), degree(0), marked(false),
      parent(nullptr), child(nullptr), left(this), right(this) {}
