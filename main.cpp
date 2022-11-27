#include <iostream>
#include <vector>
#include <queue>

void P1(){

}

void P2(){

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

    // for(int i = 0; i < N; i++){
    //     for(int j = 0; j < N; j++){
    //         std::cout << M[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }


    return 0;
}