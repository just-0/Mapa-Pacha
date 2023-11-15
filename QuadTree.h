#ifndef QUADTREE_H
#define QUADTREE_H

#include<iostream>
#include<random>
#include <queue>

const int DIM = 30; //Cantidad de Dimensiones por cada dato

using namespace std;
struct Point {
    float x;
    float y;
    vector<float> Atributos;
    Point(float a, float b, vector<float> c = vector<float>(DIM,0)) : x(a), y(b), Atributos(c) {}
};

class QuadTree {

private:
    static const int maxPoints = 2;
    QuadTree* children[4] = {nullptr};
    const Point* points[maxPoints] = {nullptr};



    // bottomLeft y h definen el área(cuadrado más grande)

    Point bottomLeft;
    float h;

public:
    int nPoints; // puntos ingresados.
    QuadTree(float, float, float);
    ~QuadTree();
    void dfs();
    void bfs();
    void insert(const Point);
    
    vector<float> representative();// Hallar el vector representativo para cada cuadrante
};

#endif // QUADTREE_H
