#include "FibonacciHeap.h"

FibonacciHeap::FibonacciHeap() : minNode(nullptr), nodeCount(0) {}

void FibonacciHeap::mergeIntoRootList(FibonacciNode* a, FibonacciNode* b) {
    if (!a || !b) return;
    FibonacciNode* aRight = a->right;
    a->right = b;
    b->left = a;
    b->right = aRight;
    aRight->left = b;
}

void FibonacciHeap::removeNodeFromList(FibonacciNode* node) {
    if (!node) return;
    node->left->right = node->right;
    node->right->left = node->left;
    node->left = node->right = node;
}

void FibonacciHeap::link(FibonacciNode* y, FibonacciNode* x) {
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

void FibonacciHeap::consolidate() {
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

void FibonacciHeap::cut(FibonacciNode* node, FibonacciNode* parent) {
    removeNodeFromList(node);
    parent->degree--;
    mergeIntoRootList(minNode, node);
    node->parent = nullptr;
    node->marked = false;
}

void FibonacciHeap::cascadingCut(FibonacciNode* node) {
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

FibonacciNode* FibonacciHeap::insert(int key, int distance) {
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

FibonacciNode* FibonacciHeap::extractMin() {
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

void FibonacciHeap::decreaseKey(FibonacciNode* node, int newDistance) {
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

bool FibonacciHeap::isEmpty() const {
    return minNode == nullptr;
}
