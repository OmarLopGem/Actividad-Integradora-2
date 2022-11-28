#include <iostream>
#include <vector>
#include <algorithm>  
#include <string>  
#include <queue>

void P1(){

}

int P2(std::vector<std::vector<int>> &M, int origen, std::vector<int> &Nodos, std::vector<int> &Camino){
    int costoCaminoMinimo = INT_MAX;
    do{
        int costoActual = 0;

        int nodoActual = origen;

        Camino.push_back(origen);

        for(int i = 0; i < Nodos.size(); i++){
            costoActual += M[nodoActual][Nodos[i]];
            nodoActual = Nodos[i];
        }
        costoActual += M[nodoActual][origen];

        Camino.push_back(nodoActual);
        
        costoCaminoMinimo = std::min(costoCaminoMinimo, costoActual);
        

    } while (next_permutation(Nodos.begin(), Nodos.end()));

    return costoCaminoMinimo;
}

void P3(){

}

int main(){
    int N = 0;
    std::cout << "Ingrese el numero de colonias en la ciudad : ";
    std::cin >> N;
    std::vector<std::vector<int>> M(N, std::vector<int> (N));

    std::cout << "Ingrese los valores de la matriz de distancias entre las colonias" << std::endl;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            std::cin >> M[i][j];
        }
    }

    int origen = 0;

    std::vector<int> Nodos;
    std::vector<int> Camino;

    for(int i = 0; i < N; i++){
        if(i != origen){
            Nodos.push_back(i);
        }
    }

    // for(int i = 0; i < N; i++){
    //     for(int j = 0; j < N; j++){
    //         std::cout << M[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    int caminoMinimo = P2(M, origen, Nodos, Camino);

    std::cout << "El costo del camino mas corto para recorrer todas las colonias y regresar el origen es de : " << caminoMinimo << std::endl;

    for(int i = 0; i < Camino.size(); i++){
        std::cout << Camino[i];
    }

    return 0;
}