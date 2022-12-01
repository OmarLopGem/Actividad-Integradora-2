#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>

struct coord
{
    int index;
    float x;
    float y;
    float dist;
};


void P1(){

}

void P2(){

}

void P3(std::vector<coord> locations){

    // struct cmp{
    //     bool operator()(coord a, coord b){
    //         return a.dist > b.dist;
    //     }
    // };

    // std::priority_queue<coord, std::vector<coord>, cmp> centrals;

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
    
    P3(locations);

    // for(int i = 0; i < N; i++){
    //     for(int j = 0; j < N; j++){
    //         std::cout << M[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // for(int i = 0; i < N; i++){
    //     std::cout << "[" << locations[i].x << "|" << locations[i].y << "]" <<std::endl;
    // }

    return 0;
}