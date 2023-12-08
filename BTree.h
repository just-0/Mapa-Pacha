#pragma once

#include "QuadTree.h"
#define MAX 6
#define MIN 3

extern QuadTree* target;
struct btreeNode {
    QuadTree* val[MAX + 1];
    int count;
    btreeNode* link[MAX + 1];
};

class BTree {
public:
    btreeNode* root;
    btreeNode* createNode(QuadTree* val, btreeNode* child);
    void addValToNode(QuadTree* val, int pos, btreeNode* node, btreeNode* child);
    void splitNode(QuadTree* val, QuadTree** pval, int pos, btreeNode* node, btreeNode* child, btreeNode** newNode);
    int setValueInNode(QuadTree* val, QuadTree** pval, btreeNode* node, btreeNode** child);

    BTree();
    ~BTree();
    void build(QuadTree* qt);
    void insertion(QuadTree* val);
    void searching(QuadTree* val, int* pos, btreeNode* myNode);
    void traversal(btreeNode* node);
    void test();
};
