#include<iostream>
#include<random>
using namespace std;

struct Point{
    	float x;
    	float y;

    	Point(float a, float b) : x(a), y(b){}
};



class QuadTree{
	private:
    		static const int maxPoints = 2;

    		QuadTree *children[4] = {nullptr};
    		const Point *points[maxPoints] = {nullptr};

    		// bottomLeft y h definen el espacio(cubo más grande)
    		Point bottomLeft;
    		float h;

	public:
    		int nPoints; // puntos ingresados.
    		QuadTree(float, float, float);
    		~QuadTree();
			void dfs();
			//bool exist( const Point &);
			void insert( const Point  );
			//const Point* find_closest( const Point &, int radius);


};



QuadTree::QuadTree(float x, float y, float a)
	:bottomLeft(x,y)
{
	h = a;
	nPoints = 0;
}

QuadTree::~QuadTree() {
	for (int i = 0; i < 4; i++) {
		delete children[i];
	}
}


void QuadTree::insert(const Point p)
{
	if(nPoints < maxPoints && children[0] == nullptr)//Si no supera el limite simplemente se almacena
	{
		points[nPoints++] = new Point(p.x, p.y);
	}
	else
	{
		if(children[0] == nullptr)//Crear QuadTree's
		{
			children[0] = new QuadTree(bottomLeft.x,	 bottomLeft.y,	h/2);
			children[1] = new QuadTree(bottomLeft.x+h/2, bottomLeft.y,	h/2);
			children[2] = new QuadTree(bottomLeft.x, bottomLeft.y + h/2, h/2);
			children[3] = new QuadTree(bottomLeft.x+h/2, bottomLeft.y + h/2, h/2);

			for(int j= 0; j< maxPoints;j++)// Colocar los puntos del padre en los octantes hijos.
			{
				for(int i = 0; i < 4; i++)
				{
					if(children[i]->bottomLeft.x <= points[j]->x && points[j]->x < children[i]->bottomLeft.x+children[i]->h &&
							children[i]->bottomLeft.y <= points[j]->y && points[j]->y < children[i]->bottomLeft.y+children[i]->h) 
					{
                        nPoints--;
						children[i]->insert(*points[j]);
                        delete points[j];
                        points[j] = nullptr;
						break;
					}
					
				}

			}
		}

		// Buscar el QuadTree adecuado

		for(int i = 0; i < 4; i++)
		{
			if(children[i]->bottomLeft.x <= p.x && p.x < children[i]->bottomLeft.x+children[i]->h && children[i]->bottomLeft.y <= p.y && p.y < children[i]->bottomLeft.y+children[i]->h)
			{
				children[i]->insert(p);
				break;
			}
			
		}
	}

}

void QuadTree::dfs()
{
	if(nPoints !=  0 )
	{
		cout<<"-----"<<endl;
		for(int k = 0; k < maxPoints; k++)
		{
			if(points[k] != nullptr)cout<<"("<<points[k]->x<<", "<<points[k]->y<<")"<<endl;
		}

		cout<<"-----"<<endl;
	}
	for (int i = 0; i < 4; i++) if (children[i] != nullptr) children[i]->dfs(); 
}
void TestGenerar(QuadTree &a)
{
	random_device rd;  // Genera una semilla de números aleatorios
   	mt19937 gen(rd()); // Inicializa el generador con la semilla

    // Crea una distribución uniforme en el rango especificado
    uniform_int_distribution<> dis(1, 100);

    // Genera un número aleatorio
    

	for(int i = 0; i < 5; i++)
	{
		a.insert(Point((dis(gen)), dis(gen)));
	}

}

int main()
{
	QuadTree q1(0,0,200);
	

	TestGenerar(q1);
	q1.dfs();
	cout<<"Hola"<<endl;
	

	return 1;
}
