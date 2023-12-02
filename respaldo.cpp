#include <iostream>
#include "QuadTree.cpp"
#include <unistd.h>
#include <fstream>
#include <sstream>

using namespace std;

#define MAX 6
#define MIN 3

struct btreeNode {
    QuadTree* val[MAX + 1];
    int count;
    btreeNode* link[MAX + 1];
};

btreeNode* root;
QuadTree* target; //El quadtree que eligio erick

// Función de similitud
bool operator<(const QuadTree& qt1, const QuadTree& qt2) {
    double dist1 = 0.0, dist2 = 0.0;
    if (target->bottomLeft.Atributos.size() != qt1.bottomLeft.Atributos.size()) {
        std::cout << "aea 1" << std::endl;
    }
    if (target->bottomLeft.Atributos.size() != qt2.bottomLeft.Atributos.size()) {
        std::cout << "aea 2" << std::endl;
    }
    if (qt1.bottomLeft.Atributos.size() != qt2.bottomLeft.Atributos.size()) {
        std::cout << "aea 3" << std::endl;
    }
    for (int i = 0; i < qt1.bottomLeft.Atributos.size(); i++) {
        dist1 += std::pow((qt1.bottomLeft.Atributos[i] - target->bottomLeft.Atributos[i]), 2);
        dist2 += std::pow((qt2.bottomLeft.Atributos[i] - target->bottomLeft.Atributos[i]), 2);
    }
    return std::sqrt(dist1) < std::sqrt(dist2);
}

bool operator==(const QuadTree& qt1, const QuadTree& qt2) {
    return (qt1.h == qt2.h && qt1.bottomLeft.x == qt2.bottomLeft.x && qt1.bottomLeft.y == qt2.bottomLeft.y);
}

/* Crear nuevo nodo */
btreeNode* createNode(QuadTree* val, btreeNode* child) {
    btreeNode* newNode = new btreeNode;
    newNode->val[1] = val;
    newNode->count = 1;
    newNode->link[0] = root;
    newNode->link[1] = child;
    return newNode;
}

/* Agregar valor al nodo en la posición apropiada */
void addValToNode(QuadTree* val, int pos, btreeNode* node, btreeNode* child) {
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

/* Dividir el nodo */
void splitNode(QuadTree* val, QuadTree** pval, int pos, btreeNode* node, btreeNode* child, btreeNode** newNode) {
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

/* Establecer el valor en el nodo */
int setValueInNode(QuadTree* val, QuadTree** pval, btreeNode* node, btreeNode** child) {

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
            cout << "Duplicados no permitidos\n";
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

/* Insertar val en el árbol B */
void insertion(QuadTree* val) {
    int flag;
    QuadTree* pval;
    btreeNode* child;

    flag = setValueInNode(val, &pval, root, &child);
    if (flag)
        root = createNode(pval, child);
}

/* Buscar val en el árbol B */
void searching(QuadTree* val, int* pos, btreeNode* myNode) {
    if (!myNode) {
        return;
    }

    if (*val < *(myNode->val[1])) {
        *pos = 0;
    } else {
        for (*pos = myNode->count; (*val < *(myNode->val[*pos]) && *pos > 1); (*pos)--);
        if (*val == *(myNode->val[*pos])) {
            cout << "El dato dado se encuentra\n";
            return;
        }
    }
    searching(val, pos, myNode->link[*pos]);
    return;
}

/* Tranversal del árbol B */
void traversal(btreeNode* myNode) {
    int i;
    if (myNode) {
        for (i = 0; i < myNode->count; i++) {
            traversal(myNode->link[i]);
            QuadTree* qt= myNode->val[i+1];
            for(int j= 0; j< qt->bottomLeft.Atributos.size(); j++){
                cout<<qt->bottomLeft.Atributos[j]<<" ";
            }cout<<endl;
            // cout << myNode->val[i + 1]->rep[0] << ' ';
        }
        traversal(myNode->link[i]);
    }
}
//----------------------------------------------------------------------------------------------------------------------
string CWD;
void ReadCSV(const string& filename, QuadTree &o) {
    ifstream archivo(filename);

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    vector<string> campos;
    int contador = 0;

    getline(archivo, linea);

    while (getline(archivo, linea))
    {
        istringstream ss(linea);
        string campo;
        while (getline(ss, campo, ','))
        {
            campos.push_back(campo);
        }



        // if(contador == 1287)break;//AQUI INDICAR CUANTOS DATOS INGRESAR
        if(!campos[0].empty() && !campos[1].empty())//ESTO ES PARA IGNORAR LAS ENTRADAS QUE NO TIENEN NADA
        {
            double x = stof(campos[0]);
            double y = stof(campos[1]);

            vector<double> Attr;
            int tmn = campos.size();
            for (int i = 2; i < tmn; i++) {
                Attr.push_back(stoi(campos[i]));
            }
            o.insert(Point(x, y, Attr));
        }
        //cout << "x: " << x << ", y: " << y <<endl;
        contador ++;


        campos.clear();
    }
    cout<<endl<<endl<<endl<<"Se leyeron "<<contador<<" datos "<<endl;
    archivo.close();
}

string getCWD(){
    char cwd[1024]; // Buffer para almacenar la ruta actual
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        return string(cwd);
    } 
    else {
        perror("getcwd");
        return "";
    }
}

int main() {
    CWD= getCWD();
    QuadTree q1(-500, -500, 1000);
    target= new QuadTree(-50,-50,20);//primer elemento del dataset
    target->bottomLeft.Atributos= {6,96,54,70,61,71,39,23,85,77,95,15,76,57,85,5,33,48,17,94,39,42,9,13,15,59,5,93,19,63};
    target->level= 4;
    ReadCSV(CWD+"/meteorite_clean_test.csv", q1);
    q1.representative();
    // q1.dfs();
    // vector<QuadTree*> allNodes= q1.bfs2(&q1);	
    vector<QuadTree*> allNodes= q1.bfs2(&q1);
    cout<<"tam: "<<allNodes.size()<<endl;
    int cnt= 0;
    for(auto node:allNodes){
        if(node->bottomLeft.Atributos.size()== 0) continue;
        cnt++;
        insertion(node);
    }
    traversal(root);
    cout<<"cnt: "<<cnt<<endl;
    // q1.bfs();
    cout<<"Datos insertados en el arbol -> "<<q1.nPoints<<endl;
    // target = new QuadTree();

    return 0;
}

