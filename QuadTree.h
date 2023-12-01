#ifndef QUADTREE_H
#define QUADTREE_H

#include<iostream>
#include<random>
#include <queue>
#include<map>

const int DIM = 30; //Cantidad de Dimensiones por cada dato
using namespace std;
struct Point {
    double x;
    double y;
    vector<double> Atributos; // Este vector de atributos es su representative
    Point(double a, double b, vector<double> c = vector<double>(DIM,0)) : x(a), y(b), Atributos(c) {}
};

class QuadTree {
    public:
        static const int maxPoints = 2;
        QuadTree* children[4] = {nullptr};
        const Point* points[maxPoints] = {nullptr};
        vector<QuadTree*> bfs2(QuadTree* root);

        // bottomLeft y h definen el área(cuadrado más grande)

        Point bottomLeft;
        double h;
        int nPoints; // puntos ingresados.
        vector<double> rep;
        QuadTree(double, double, double);
        ~QuadTree();
        void dfs();
        void bfs();
        void insert(const Point);
        
        vector<double> representative();// Hallar el vector representativo para cada cuadrante
        QuadTree* find(QuadTree &Q);

        QuadTree* Test(int); // Función para obtener un cuadrante ya creado aleatorio para testear.
};

#endif // QUADTREE_H

