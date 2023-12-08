#include<iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "QuadTree.h"
#include "BTree.h"
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
        while (getline(ss, campo, ';'))
        {
            campos.push_back(campo);
        }



        // if(contador == 400)break;//AQUI INDICAR CUANTOS DATOS INGRESAR
        if(!campos[0].empty() && !campos[1].empty())//ESTO ES PARA IGNORAR LAS ENTRADAS QUE NO TIENEN NADA
        {
            double x = stod(campos[0]);
            double y = stod(campos[1]);

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

int main() {
    QuadTree q1(-500, -500, 1000);
    //q1.dfs();

    ReadCSV("meteorite_clean_test.csv", q1);
    q1.representative();
    // q1.dfs();	
    //q1.bfs();
    // QuadTree buscame(0,-500,250);
    // QuadTree *qs = q1.find(buscame);
    // QuadTree* ptr = q1.Test(3);
    //cout<<qs->bottomLeft.x<<", "<<qs->bottomLeft.y<<endl; //qs puede dar nullptr
    // cout<<ptr->bottomLeft.x<<", "<<ptr->bottomLeft.y<<endl; //qs puede dar nullptr
    cout<<"Datos insertados en el arbol -> "<<q1.nPoints<<endl;

    BTree* btree= new BTree();
    target= new QuadTree(-50,-50,20); //QuadTree que eligió Erick, 1era punto del dataset
    target->bottomLeft.Atributos= {54,38,74,71,94,25,4,2,7,71,4,58,37,5,51,68,95,18,9,95,52,51,30,2,29,91,42,36,77,73};
    btree->build(&q1);
    // btree->traversal(btree->root);
    // btree->test();
    return 0;
}
