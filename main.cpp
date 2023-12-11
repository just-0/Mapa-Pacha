#include<iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "QuadTree.h"
#include "BTree.h"
using namespace std;

double min_x= 1e9, min_y= 1e9, max_x= -1e9, max_y= -1e9;
void setMapBoundaries(const string& filename){
    ifstream archivo(filename);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }
    string linea;
    vector<string> campos;
    getline(archivo, linea);
    while (getline(archivo, linea))
    {
        istringstream ss(linea);
        string campo;
        while (getline(ss, campo, ';'))
        {
            campos.push_back(campo);
        }
        if(!campos[0].empty() && !campos[1].empty())
        {
            double x = stod(campos[1]);
            double y = stod(campos[2]);
            min_x= min(x,min_x); min_y= min(y,min_y);
            max_x= max(x,max_x); max_y= max(y,max_y);
        }
        campos.clear();
    }
}

void ReadCSV(const string& filename, QuadTree &o, 
             pair<double,double> bottomLeft, pair<double,double> topRight) {
    target= new QuadTree(bottomLeft.first,bottomLeft.second,
                topRight.first - bottomLeft.first);

    ifstream archivo(filename);

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    vector<string> campos;
    int contador = 0;
    int contador2= 0;

    getline(archivo, linea);
    while (getline(archivo, linea))
    {
        istringstream ss(linea);
        string campo;
        while (getline(ss, campo, ';'))
        {
            campos.push_back(campo);
        }

        // if(contador == 400)break;//AQUI INDICAR CUANTOS DATOS INGRESAR
        if(!campos[0].empty() && !campos[1].empty())//ESTO ES PARA IGNORAR LAS ENTRADAS QUE NO TIENEN NADA
        {
            double x = stod(campos[1]);
            double y = stod(campos[2]);
            min_x= min(x,min_x); min_y= min(y,min_y);
            max_x= max(x,max_x); max_y= max(y,max_y);
            // si esta dentro de la región elegida
            vector<double> Attr;
            int tmn = campos.size();
            for (int i = 3; i < tmn; i++) {
                Attr.push_back(stoi(campos[i]));
            }
            o.insert(Point(x, y, Attr));
            if(bottomLeft.first<= x && x<= topRight.first &&
               bottomLeft.second<= y && y<= topRight.second){
                target->insert(Point(x,y, Attr));
                contador2++;
            }
        }
        //cout << "x: " << x << ", y: " << y <<endl;
        contador ++;
        campos.clear();
    }
    cout<<endl<<endl<<endl<<"Se leyeron "<<contador<<" datos "<<endl;
    cout<<"Se encontraron "<<contador2<<" puntos en la region elegida"<<endl;
    archivo.close();
    o.representative();
    target->representative();
}

void writeTxt(vector<vector<double>> &cuadrantes){
    ofstream archivo("cuadrantes.txt");

    if(!archivo.is_open()){
        cerr<<"Error al crear archivo "<<endl;
        return;
    }
    string linea;
    for(int i= 0; i< cuadrantes.size(); i++){
        for(int j= 0; j< cuadrantes[i].size(); j++){
            archivo << cuadrantes[i][j] << ",\n"[j==cuadrantes[i].size()-1];
        }
    }
    archivo.close();
    cout<<"\nCuadrantes escritos en el archivo cuadrantes.txt"<<endl;
}

double suitableLevel(QuadTree *target, double lim){
    double l= lim/2.0, r= lim;
    while(!(l<= target->h && target->h <= r)){
        r= l;
        l/= 2.0;
    }
    cout<<"Altura anterior de target: "<<target->h<<endl;
    cout<<"Altura adecuada de target: "<<l<<endl;
    return l;
}

int main() {
    pair<double,double> bottomLeft, topRight;
    /*cout<<"Ingrese las coordenadas bottomLeft: ";
    cin>>bottomLeft.first>>bottomLeft.second;
    cout<<"Ingrese las coordenadas topRight: ";
    cin>>topRight.first>>topRight.second;*/
    bottomLeft.first= -1, bottomLeft.second= -1;
    topRight.first= 1, topRight.second= 1;
    // setMapBoundaries("meteorite_clean_test.csv"); // Limites del mapa
    // cout<<"Limites del mapa: "<<min_x<<","<<min_y<<","<<max_x<<","<<max_y<<endl;
    QuadTree q1(-200, -200, 600);
    //q1.dfs();
    ReadCSV("meteorite_clean_test.csv", q1,bottomLeft,topRight);
    target->h= suitableLevel(target,q1.h); // encontrar el nivel adecuado para target
    // q1.dfs();	
    //q1.bfs();
    // QuadTree buscame(0,-500,250);
    // QuadTree *qs = q1.find(buscame);
    // QuadTree* ptr = q1.Test(26);
    //cout<<qs->bottomLeft.x<<", "<<qs->bottomLeft.y<<endl; //qs puede dar nullptr
    // cout<<ptr->bottomLeft.x<<", "<<ptr->bottomLeft.y<<endl; //qs puede dar nullptr
    cout<<"Datos insertados en el arbol -> "<<q1.nPoints<<endl;

    BTree* btree= new BTree(); // target->h después de la creación del  bTree
    btree->build(&q1);
    btree->traversal(btree->root);
    btree->test();
    vector<vector<double>> cuadrantes= {{bottomLeft.first,bottomLeft.second,topRight.first-bottomLeft.first}};
    btree->getCuadrantes(cuadrantes);
    writeTxt(cuadrantes);
    return 0;
}
