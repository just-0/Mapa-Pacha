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
            double x = stod(campos[1]);
            double y = stod(campos[2]);

            vector<double> Attr;
            int tmn = campos.size();
            for (int i = 3; i < tmn; i++) {
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
    QuadTree* ptr = q1.Test(26);
    target = ptr;
    //cout<<qs->bottomLeft.x<<", "<<qs->bottomLeft.y<<endl; //qs puede dar nullptr
    // cout<<ptr->bottomLeft.x<<", "<<ptr->bottomLeft.y<<endl; //qs puede dar nullptr
    cout<<"Datos insertados en el arbol -> "<<q1.nPoints<<endl;


    
    BTree* btree= new BTree();
    btree->build(&q1);
    btree->traversal(btree->root);
    btree->test();


    cout<<"TARGET: \n";
    for (int j = 0; j< target->bottomLeft.Atributos.size(); j++) {
            std::cout << target->bottomLeft.Atributos[j] << " ";
        }
    cout<<endl;
    return 0;

    //64 63 38 52 23 71.5 32.5 31.5 58 40 67 51.5 23.5 73.5 64.5 58 65.5 50 37 56.5 29 50 69.5 53 60.5 54.5 95 66.5 38 69.5
    //57.6667 55.6667 63 55.6667 16.3333 60.6667 24.3333 26 43.3333 85.3333 68.6667 49 61.6667 30.6667 28.6667 59.6667 73 56.3333 55.3333 32.6667 47.3333 23.6667 70.6667 52 49.6667 66 84.3333 58.6667 54.3333 72.3333
}
