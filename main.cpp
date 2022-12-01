//Autores:
//  Fernando Resendiz Bautista A01769659
//  Jorge Omar Lopez Gemigniani A01769675
//  Carlos Eduardo Jimenez Santiago A01769960
//
//Ultima fecha de modificacion : 1 de diciembre de 2022
//
//Explicaicon: El siguiente codigo da respuesta a la actividad integradora 2, cubriendo los 3 puntos principales con algoritmos adecuados para la misma
//solucion de los diferentes problemas. Cada seccion del codigo que responde un punto tiene sus propios comentarios para un mejor entendimiento.

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <climits>
#include <algorithm>
#include <string>
#include <string.h>  
#include <queue> 
#include <map>

int costoMinimo = INT_MAX;
std::vector<int> Nodos;
std::map<int, std::string> diccNumLet = {{0, "A",},
                                {1, "B",},
                                {2, "C",},
                                {3, "D",},
                                {4, "E",},
                                {5, "F",},
                                {6, "G",},
                                {7, "H",},
                                {8, "I",},
                                {9, "J",},
                                {10, "K",},
                                {11, "L",},
                                {12, "M",},
                                {13, "N",},
                                {14, "O",},
                                {15, "P",},
                                {16, "Q",},
                                {17, "R",},
                                {18, "S",},
                                {19, "T",},
                                {20, "U",},
                                {21, "V",},
                                {22, "W",},
                                {23, "X",},
                                {24, "Y",},
                                {25, "Z"}};

struct coord
{
    int index;
    float x;
    float y;
    float dist;
};

//La funcion encuentra el vertice que tenga el menor costo
//de entre los que aun no se encuentren en el MST
int minMST(int N, std::vector<int> mins, std::vector<bool> flags){
    int MIN=INT_MAX;
    int min_i; //almacena el indice del mínimo
    
    //recorre la cantidad de colonias o nodos que haya
    for(int i=0; i<N; i++){
        //si el nodo no se ha marcado y el minimo es menor que el minimo actual
        //entonces se añade el minimo encontrado a la variable MIN y se da
        //el indice
        if (flags[i]==false && mins[i]<MIN){
            MIN=mins[i];
            min_i=i;
        }
    }
    return min_i; //Retorna el indice del minimo
}

//Buscará el MST usando el algoritmo de Prim, utilizando el vector de la matriz de adyacencias y
//seleccionando los nodos a los que se moverá a la vez que marca cuales ya se han cruzado, con el fin de 
//no repetir y crear ciclos.
void P1(int N, std::vector<std::vector<int>> M){
    std::vector<int> MST(N);            //vector para guardar el mst
    std::vector<int> mins(N, INT_MAX);  //valores minimos de arista
    std::vector<bool> flags(N, false);  //booleanos para marcar los nodos

    mins[0]= 0; //el minimmo de la posicion 0 será 0 para que siempre sea el inicial
    MST[0]= -1;
    
    for(int i=0; i<N-1; i++){
        int r = minMST(N, mins, flags); //escogerá el minimo que aun no esté en el MST
        flags[r] = true; //añade el vertice escogido al MST
        
        //El segundo ciclo añade los vertices que se seleccionen, solo
        //añadiendo aquellos que aún no e hayen en el MST
        for(int j=0; j<N; j++){
            if (M[r][j] && flags[j] == false
				&& M[r][j] < mins[j])
				MST[j] = r, mins[j] = M[r][j];
        }
    }

    //Este ultimo ciclo unicamnte va a imprimir los nodos que se requieren para el MST y así
    //tener conexos todos los nodos.
    std::cout<<"Mejor forma de cableado\n";
    for (int i = 1; i<N; i++){
        std::cout<<"colonia "<<MST[i]<<" ->"<<" colonia "<<i<<"\t distancia : "<<M[i][MST[i]];
        std::cout<<std::endl;
    }
}

//Funcion encargada de buscar el camino con menor costo en un ciclo hamiltoniano
void caminoMinimo(std::vector<std::vector<int>> &M, std::vector<int> &Camino, std::vector<int> &NodosVisitados, int costo, int index, int N,std::vector<int> &Nodos, std::vector<int> &CaminoFinal, int posCamino){
    //Si hemos revisado todos los nodos
    if (index == N){
        //Si el nuevo costo es menor que el anterior entonces cambiamos el camino y el costo minimo
        if(costo + M[Camino[index - 1]][0] < costoMinimo){
            CaminoFinal = Camino;
        }
        costoMinimo = std::min(costoMinimo, costo + M[Camino[index - 1]][0]);
        return;
    }

    //El ciclo for es para ir revisando todos los nodos y llevar registro de que nodos visitamos para asi no crear ciclos
    for(int i = 1; i < N; i++){
        if(M[Camino[index - 1]][i] && NodosVisitados[i] == 0){
            Camino[index] = i;
            NodosVisitados[i] = 1;
            costo += M[Camino[index - 1]][i];            
            caminoMinimo(M, Camino, NodosVisitados, costo, index + 1, N, Nodos, CaminoFinal, posCamino + 1);
            Camino[index] = -1;
            NodosVisitados[i] = 0;
            costo = costo - M[Camino[index - 1]][i];
        }
    }
    return;
}

//Esta funcion se encarga de declarar algunas variables que se usaran
void P2(std::vector<std::vector<int>> &M, std::vector<int> &NodosVisitados, std::vector<int> &Camino, int N,std::vector<int> &Nodos, std::vector<int> &CaminoFinal){
    //Este ciclo for se encarga de generar los valores dentro de las matrices para saber el camino y los nodos visitados
    for(int i = 0; i < N; i++){
        Camino[i] = -1;
        NodosVisitados[i] = 0;
    }

    Camino[0] = 0;
    NodosVisitados[0] = 1;
    int posCamino = 0;

    caminoMinimo(M, Camino, NodosVisitados, 0, 1, N, Nodos, CaminoFinal, posCamino);
    return;
}

//Esta funcion traduce el camino de numeros a letras del abecedario
std::string numbers2Letters(std::vector<int> &CaminoFinal){
    std::string Path;
    
    //El ciclo for se encarga de usar el diccionario (o mapa) para saber que letra representa cada numero
    for(int i = 0; i < CaminoFinal.size(); i++){
        int num2Let = CaminoFinal[i];
        std::string letter = diccNumLet[num2Let];
        Path += letter;        
    }
    return Path;
}

void P3(std::vector<coord> locations){

    std::string s;
    coord client;
    coord closest;
    closest.dist = std::numeric_limits<float>::max();

    std::cout<<"Ingrese la coordenada del nuevo cliente con el formato (x,y):"<<std::endl;
    //Almacena la coordenada en un string formato (x,y)
    std::cin >> s;
    //Extrae el valor de la coordenada x
    client.x = std::stof(s.substr(1 , s.find(",")));
    //Extrae el valor de la coordenada x
    client.y = std::stof(s.substr(s.find(",") + 1, s.length()));

    for(coord & central : locations){
        // Calcula la distancia de cada central al cliente
        central.dist = sqrt(pow(central.x - client.x,2) + pow(central.y - client.y,2));
        // Si la distancia es menor a la menor distancia encontrada hasta el momento se sustituye el valor
        if(central.dist < closest.dist){
            closest = central;
        }
    }

    // Imprime el número de la central más cercana, su distancia y su ubicación
    std::cout<<"La central mas cercana al nuevo cliente es la central #"<<closest.index<<std::endl;
    std::cout<<"La cual se enctuentra a una distancia de "<<closest.dist<<std::endl;
    std::cout<<"En la coordenada: "<<"("<<closest.x<<","<<closest.y<<")"<<std::endl;

}

int main(){
    
    int N = 0;
    //Recibimos los parametros dados por el usuario
    std::cout << "Ingrese el numero de colonias en la ciudad : ";
    std::cin >> N;
    int T = N*N;
    std::vector<std::vector<int>> M(N, std::vector<int> (N));
    std::vector<coord> locations(N);
    std::string s;

    std::cout << "Ingrese los valores de la matriz de distancias entre las colonias" << std::endl;

    //Este ciclo for recibe la matriz de adyacencias
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            std::cin >> M[i][j];
        }
    }

    std::cout << "Ingrese las coordenadas de las centrales con el formato (x,y)" << std::endl;
    //Este ciclo for recibe la entrada de las coordenadas
    for(int i = 0; i < N; i++){
        std::cin >> s;
        locations[i].index = i;
        locations[i].x = std::stof(s.substr(1 , s.find(",")));
        locations[i].y = std::stof(s.substr(s.find(",") + 1, s.length()));
    }
    //Primer algoritmo empleado
    P1(N,M);

    //Declaramos nuestros vectores a utilizar en este codigo
    std::vector<int> NodosVisitados(N);
    std::vector<int> Camino(N);
    std::vector<int> CaminoFinal(N);
    
    //Segundo algoritmo empleado
    P2(M, NodosVisitados, Camino, N, Nodos, CaminoFinal);

    std::cout << "El costo del camino mas corto para recorrer todas las colonias y regresar el origen es de : " << costoMinimo << std::endl;

    CaminoFinal.resize(N + 1);
    CaminoFinal[N] = 0;

    std::string Path = numbers2Letters(CaminoFinal);
    
    std::cout <<"El camino a seguir es el siguiente : " << Path << std::endl;
    
    //Tercer algoritmo empleado
    P3(locations);

    return 0;
}