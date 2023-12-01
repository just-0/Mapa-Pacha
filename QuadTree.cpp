#include "QuadTree.h"

QuadTree::QuadTree(double x, double y, double a, int level)
        : bottomLeft(x, y) {
    h = a;
    nPoints = 0;
    this->level =  level;
}

QuadTree::~QuadTree() {
    for (int i = 0; i < 4; i++) {
        delete children[i];
    }
}

void QuadTree::insert(const Point p) {
    if (nPoints < maxPoints && children[0] == nullptr)
    {
        points[nPoints++] = new Point(p.x, p.y, p.Atributos);
    } else {
        if (children[0] == nullptr) {
            children[0] = new QuadTree(bottomLeft.x, bottomLeft.y, h / 2,level+1);
            children[1] = new QuadTree(bottomLeft.x + h / 2, bottomLeft.y, h / 2,level+1);
            children[2] = new QuadTree(bottomLeft.x, bottomLeft.y + h / 2, h / 2,level+1);
            children[3] = new QuadTree(bottomLeft.x + h / 2, bottomLeft.y + h / 2, h / 2,level+1);

            for (int j = 0; j < maxPoints; j++) {
                for (int i = 0;  i < 4; i++) {
                    if (children[i]->bottomLeft.x <= points[j]->x && points[j]->x < children[i]->bottomLeft.x + children[i]->h &&
                        children[i]->bottomLeft.y <= points[j]->y && points[j]->y < children[i]->bottomLeft.y + children[i]->h) {

                        children[i]->insert(*points[j]);
                        delete points[j];
                        points[j] = nullptr;
                        break;
                    }
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            if (children[i]->bottomLeft.x <= p.x && p.x < children[i]->bottomLeft.x + children[i]->h && children[i]->bottomLeft.y <= p.y && p.y < children[i]->bottomLeft.y + children[i]->h) {
                children[i]->insert(p);
                nPoints++;
                break;
            }
        }
    }
}

void QuadTree::dfs() {
    if (nPoints <= maxPoints && nPoints != 0) {
        cout << "-----" << endl;
        for (int k = 0; k < maxPoints; k++) {
            if (points[k] != nullptr) {
                cout << "(" << points[k]->x << ", " << points[k]->y << ")"<< endl;
            }
        }

        cout << "-----" << endl;
    }
    for (int i = 0; i < 4; i++)
        if (children[i] != nullptr)
            children[i]->dfs();
}

vector<QuadTree*> QuadTree::bfs2(QuadTree* root){
    vector<QuadTree*> ans;
    queue<QuadTree*> q;
    q.push(root);
    while(!q.empty()){
        QuadTree* nodo= q.front();
        ans.push_back(nodo);
        for(int i= 0; i< 4; i++){
            if(nodo->children[i]!= nullptr){
                q.push(nodo->children[i]);
            }
        }
        q.pop();
    }
    return ans;
}


void QuadTree::bfs() {
    if (nPoints == 0) {
        return; // No hay puntos en el árbol
    }

    queue<QuadTree*> q;
    q.push(this);

    while (!q.empty()) {
        QuadTree* current = q.front();
        q.pop();

        // Aqui realizar algo con el nodo acual que es "current"
        cout << "-----" << endl;
        for (int k = 0; k < maxPoints; k++) {
            if (current->points[k] != nullptr) {
                cout << "(" << current->points[k]->x << ", " << current->points[k]->y << ")"<<endl;
            }
        }
        cout << "-----" << endl;

        // Encola los hijos no nulos, es parte de el bfs
        for (int i = 0; i < 4; i++) {
            if (current->children[i] != nullptr) {
                q.push(current->children[i]);
            }
        }
    }
}



vector<double> QuadTree::representative() {
    if (nPoints != 0 && nPoints <= maxPoints) //Nodo hoja
    {
        vector<double> temp(DIM,0);
        for (int k = 0; k < maxPoints; k++)
        {
            if(points[k] != nullptr)
            {
                for(int i = 0; i < DIM ; i++)
                {
                    temp[i] = temp[i] + this->points[k]->Atributos[i];
                }
            }
        }
        for (int j = 0; j < DIM; j++) {
            this->bottomLeft.Atributos[j] = this->bottomLeft.Atributos[j] + temp[j] / nPoints;
        }
        return temp;
    }
    vector<double> temp1(DIM, 0);
    for (int i = 0; i < 4; i++) // Para cada hijo
    {
        if (children[i] != nullptr && children[i]->nPoints > 0) {
            vector<double> temp2 = (children[i]->representative());
            if (!temp2.empty()) {
                for (int j = 0; j < DIM; j++) {
                    temp1[j] = temp1[j] + temp2[j];
                }
            }
        }

    }
    for (int j = 0; j < DIM; j++) {
        this->bottomLeft.Atributos[j] = this->bottomLeft.Atributos[j] + temp1[j] / nPoints;
    }
    // this->rep= temp1;
    return temp1;
}


QuadTree* QuadTree::find(QuadTree &Q)
{
    double x = Q.bottomLeft.x, y = Q.bottomLeft.y, h = Q.h;

    if(this->bottomLeft.x == x && this->bottomLeft.y == y && this->h == h)
    {
        return this;
    }
    for (int i = 0;  i < 4; i++) {
        if (children[i] != nullptr &&children[i]->bottomLeft.x <= x && x < children[i]->bottomLeft.x + children[i]->h &&
            children[i]->bottomLeft.y <= y && y < children[i]->bottomLeft.y + children[i]->h) {
            return children[i]->find(Q);
        }
    }

    return nullptr;
}

QuadTree* QuadTree::Test(int a) {
    if (nPoints <= maxPoints && nPoints != 0) {
        cout << "-----" << endl;
        for (int k = 0; k < maxPoints; k++) {
            if (points[k] != nullptr) {
                cout << "(" << points[k]->x << ", " << points[k]->y << ")"<< endl;
            }
        }
        cout << "-----" << endl;
    }
    if(a == 0)
    {
        return this;
    }
    for (int i = 0; i < 4; i++)
        if (children[i] != nullptr)
            children[i]->Test(a-1);
}