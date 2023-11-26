#include<iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "QuadTree.h"
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



        if(contador == 5000)break;//AQUI INDICAR CUANTOS DATOS INGRESAR
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
    //q1.dfs();	
    //q1.bfs();
    cout<<"Datos insertados en el arbol -> "<<q1.nPoints<<endl;
    return 0;
}

