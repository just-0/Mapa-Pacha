#include "BTree.h"
#include <iostream>
#include <cmath>

QuadTree* target;
BTree::BTree() {
    root = nullptr;
}

BTree::~BTree() {
    // Implement any necessary cleanup here
}

// ERROR SOLUCIONADO: Se debian comparar objetos, no punteros
bool operator<(const QuadTree& qt1, const QuadTree& qt2) {
    double dist1 = 0.0, dist2 = 0.0;
    for (int i = 0; i < qt1.bottomLeft.Atributos.size(); i++) {
        dist1 += std::pow((qt1.bottomLeft.Atributos[i] - target->bottomLeft.Atributos[i]), 2);
        dist2 += std::pow((qt2.bottomLeft.Atributos[i] - target->bottomLeft.Atributos[i]), 2);
    }
    return std::sqrt(dist1) < std::sqrt(dist2);
}

bool operator==(const QuadTree& qt1, const QuadTree& qt2) {
    return (qt1.h == qt2.h && qt1.bottomLeft.x == qt2.bottomLeft.x && qt1.bottomLeft.y == qt2.bottomLeft.y);
}

btreeNode* BTree::createNode(QuadTree* val, btreeNode* child) {
    btreeNode* newNode = new btreeNode;
    newNode->val[1] = val;
    newNode->count = 1;
    newNode->link[0] = root;
    newNode->link[1] = child;
    return newNode;
}

void BTree::addValToNode(QuadTree* val, int pos, btreeNode* node, btreeNode* child) {
    int j = node->count;
    while (j > pos) {
        node->val[j + 1] = node->val[j];
        node->link[j + 1] = node->link[j];
        j--;
    }
    node->val[j + 1] = val;
    node->link[j + 1] = child;
    node->count++;
}

void BTree::splitNode(QuadTree* val, QuadTree** pval, int pos, btreeNode* node, btreeNode* child, btreeNode** newNode) {
    int median, j;

    if (pos > MIN)
        median = MIN + 1;
    else
        median = MIN;

    *newNode = new btreeNode;
    j = median + 1;
    while (j <= MAX) {
        (*newNode)->val[j - median] = node->val[j];
        (*newNode)->link[j - median] = node->link[j];
        j++;
    }
    node->count = median;
    (*newNode)->count = MAX - median;

    if (pos <= MIN) {
        addValToNode(val, pos, node, child);
    } else {
        addValToNode(val, pos - median, *newNode, child);
    }
    *pval = node->val[node->count];
    (*newNode)->link[0] = node->link[node->count];
    node->count--;
}

int BTree::setValueInNode(QuadTree* val, QuadTree** pval, btreeNode* node, btreeNode** child) {
    int pos;
    if (!node) {
        *pval = val;
        *child = nullptr;
        return 1;
    }
    if (*val < *(node->val[1])) {
        pos = 0;
    } else {
        for (pos = node->count; (*val < *(node->val[pos]) && pos > 1); pos--);
        if (*val == *(node->val[pos])) {
            std::cout << "Duplicados no permitidos\n";
            return 0;
        }
    }
    if (setValueInNode(val, pval, node->link[pos], child)) {
        if (node->count < MAX) {
            addValToNode(*pval, pos, node, *child);
        } else {
            splitNode(*pval, pval, pos, node, *child, child);
            return 1;
        }
    }
    return 0;
}

void BTree::insertion(QuadTree* val) {
    int flag;
    QuadTree* pval;
    btreeNode* child;

    flag = setValueInNode(val, &pval, root, &child);
    if (flag)
        root = createNode(pval, child);
}

void BTree::searching(QuadTree* val, int* pos, btreeNode* myNode) {
    if (!myNode) {
        return;
    }

    if (*val < *(myNode->val[1])) {
        *pos = 0;
    } else {
        for (*pos = myNode->count; (*val < *(myNode->val[*pos]) && *pos > 1); (*pos)--);
        if (*val == *(myNode->val[*pos])) {
            std::cout << "El dato dado se encuentra\n";
            return;
        }
    }
    searching(val, pos, myNode->link[*pos]);
    return;
}

double distanciaEcludiana(QuadTree* qt1, QuadTree* qt2){
    double dist= 0;
    for (int i = 0; i < qt1->bottomLeft.Atributos.size(); i++) {
        dist += std::pow((qt1->bottomLeft.Atributos[i] - qt2->bottomLeft.Atributos[i]), 2);
    }
    return std::sqrt(dist);
}
double mnDist= 1e9;
void BTree::traversal(btreeNode* node) {
    int i;
    if (node) {
        for (i = 0; i < node->count; i++) {
            traversal(node->link[i]);
            QuadTree* qt = node->val[i + 1];
            mnDist= min(mnDist,distanciaEcludiana(qt,target));
            std::cout<<"--------------------------------------------------------------------"<<std::endl;
            for (int j = 0; j< qt->bottomLeft.Atributos.size(); j++) {
                std::cout << qt->bottomLeft.Atributos[j] << " ";
            }
            std::cout << std::endl;
        }
        traversal(node->link[i]);
    }
    cout<<"mnDist: "<<mnDist<<endl;
}

int mxlevel= 0;
void BTree::build(QuadTree* qt){
    //Insertar solo nodos hoja
    if (qt->nPoints <= qt->maxPoints && qt->nPoints != 0) {
        mxlevel= max(mxlevel,qt->level);
        this->insertion(qt);
    }
    for (int i = 0; i < 4; i++){
        if (qt->children[i] != nullptr && qt->children[i]->bottomLeft.Atributos.size()!= 0){
            build(qt->children[i]);
        }
    }
    cout<<"mxlevel: "<<mxlevel<<endl;
}