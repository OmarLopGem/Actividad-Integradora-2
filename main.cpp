#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <climits>
#include <algorithm>  
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

void P1(){

}

void caminoMinimo(std::vector<std::vector<int>> &M, std::vector<int> &Camino, std::vector<int> &NodosVisitados, int costo, int index, int N,std::vector<int> &Nodos, std::vector<int> &CaminoFinal, int posCamino){
    if (index == N){
        if(costo + M[Camino[index - 1]][0] < costoMinimo){
            CaminoFinal = Camino;
        }
        costoMinimo = std::min(costoMinimo, costo + M[Camino[index - 1]][0]);
        return;
    }

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

void P2(std::vector<std::vector<int>> &M, std::vector<int> &NodosVisitados, std::vector<int> &Camino, int N,std::vector<int> &Nodos, std::vector<int> &CaminoFinal){
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

std::string numbers2Letters(std::vector<int> &CaminoFinal){
    std::string Path;
    

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
    std::cin >> s;
    client.x = std::stof(s.substr(1 , s.find(",")));
    client.y = std::stof(s.substr(s.find(",") + 1, s.length()));

    for(coord & central : locations){
        central.dist = sqrt(pow(central.x - client.x,2) + pow(central.y - client.y,2));
        if(central.dist < closest.dist){
            closest = central;
        }
    }

    std::cout<<"La central mas cercana al nuevo cliente es la central #"<<closest.index<<std::endl;
    std::cout<<"La cual se enctuentra a una distancia de "<<closest.dist<<std::endl;
    std::cout<<"En la coordenada: "<<"("<<closest.x<<","<<closest.y<<")"<<std::endl;

}

int main(){
    
    int N = 0;
    
    std::cout << "Ingrese el numero de colonias en la ciudad : ";
    std::cin >> N;
    int T = N*N;
    std::vector<std::vector<int>> M(N, std::vector<int> (N));
    std::vector<coord> locations(N);
    std::string s;

    std::cout << "Ingrese los valores de la matriz de distancias entre las colonias" << std::endl;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            std::cin >> M[i][j];
        }
    }

    std::cout << "Ingrese las coordenadas de las centrales con el formato (x,y)" << std::endl;

    for(int i = 0; i < N; i++){
        std::cin >> s;
        locations[i].index = i;
        locations[i].x = std::stof(s.substr(1 , s.find(",")));
        locations[i].y = std::stof(s.substr(s.find(",") + 1, s.length()));
    }
    

    std::vector<int> NodosVisitados(N);
    std::vector<int> Camino(N);
    std::vector<int> CaminoFinal(N);
    
    P2(M, NodosVisitados, Camino, N, Nodos, CaminoFinal);

    std::cout << "El costo del camino mas corto para recorrer todas las colonias y regresar el origen es de : " << costoMinimo << std::endl;

    CaminoFinal.resize(N + 1);
    CaminoFinal[N] = 0;

    std::string Path = numbers2Letters(CaminoFinal);
    
    std::cout <<"El camino a seguir es el siguiente : " << Path << std::endl;
    
    P3(locations);

    return 0;
}