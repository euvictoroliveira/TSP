#include "solution.h"
#include <iostream>
#include <algorithm>




void Solution::print(){
    std::cout << "Route: ";
    for(int i = 0; i < Data::getInstance().n; i++){
        std::cout << route[i] << " - ";
    }
    std::cout << route[Data::getInstance().n] << std::endl;
    std::cout << "Cost: " << cost << std::endl;
}

void Solution::copy(const Solution &other){
    route = std::vector<int>(other.route);
    cost = other.cost;
}




void Solution::buildTrivial(){
    Data & data = Data::getInstance();
    int i;

    for(i = 1; i <= data.n; i++){
        route[i-1] = i;
    }
    route[data.n] = 1;
    cost = 0;
    for(i = 0; i < data.n - 1; i++){
        cost += data.matrizAdj[route[i]][route[i+1]];
    }
    cost += data.matrizAdj[route[data.n-1]][route[0]];
}


double Solution::evaluateSwap(const int i, const int j){
    Data & data = Data::getInstance();
    
    double  a_subtrair, a_somar, delta;

    if ((j == i + 1)){
        
        a_subtrair = data.matrizAdj[route[i-1]][route[i]] + data.matrizAdj[route[j]][route[j+ 1]]; // arcos que serão "cortados" da solução
        a_somar = data.matrizAdj[route[i -1]][route[j]] + data.matrizAdj[route[i]][route[j + 1]]; // arcos que serão "adicionados" na solução
        
    }
    else{
         a_subtrair = data.matrizAdj[route[i - 1]][route[i]] + data.matrizAdj[route[i]] [route[i + 1]] 
                    + data.matrizAdj[route[j-1]][route[j]] + data.matrizAdj[route[j]][route[j+1]];

        a_somar = data.matrizAdj[route[i - 1]][route[j]] + data.matrizAdj[route[j]] [route[i + 1]] 
                    + data.matrizAdj[route[j - 1]][route[i]] + data.matrizAdj[route[i]][route[j+1]];
        
    }

    delta = a_somar - a_subtrair; // calcula a diferença de custo da solução após sofrer um movimento
    
    //
    
    return delta;
}

void Solution::swap(const int i, const int j){
    Data & data = Data::getInstance();
    cost += evaluateSwap(i, j); // somar a diferença de custo da solução após sofrer um movimento 
                                //implica em atualizar o custo da solução
    int aux = route[i];
    route[i] = route[j];
    route[j] = aux;
    
}

double Solution::evaluateOrOpt2(const int i, const int j){
    Data & data = Data::getInstance();

    double a_subtrair, a_somar, delta;

    if(j == i+2){
        a_subtrair = data.matrizAdj[route[i-1]][route[i]] + data.matrizAdj[route[i+1]][route[j]]
                   + data.matrizAdj[route[j]][route[j+1]];

        a_somar = data.matrizAdj[route[i-1]][route[j]] + data.matrizAdj[route[j]][route[i]]
                + data.matrizAdj[route[i+1]][route[j+1]];

    }else if(i < j){
        a_subtrair = data.matrizAdj[route[i-1]][route[i]] + data.matrizAdj[route[i+1]][route[i+2]]
                   + data.matrizAdj[route[j]][route[j+1]];

        a_somar = data.matrizAdj[route[j]][route[i]] + data.matrizAdj[route[i+1]][route[j+1]]
                + data.matrizAdj[route[i-1]][route[i+2]];
    }else{
        a_subtrair = data.matrizAdj[route[i-1]][route[i]] + data.matrizAdj[route[i+1]][route[i+2]]
                   + data.matrizAdj[route[j-1]][route[j]];

        a_somar = data.matrizAdj[route[i-1]][route[i+2]] + data.matrizAdj[route[i+1]][route[j]]
                + data.matrizAdj[route[j-1]][route[i]];
    }

    delta = a_somar - a_subtrair;

    return delta;
}

void Solution::OrOpt2(const int i, const int j){
    Data & data = Data::getInstance();
    cost += evaluateOrOpt2(i, j);

    if(i <= j){
        std::rotate(route.begin() + i, route.begin() + (i+2), route.begin() + (j+1));
    }else{
        std::rotate(route.begin() + j, route.begin() + i, route.begin() + (i+2));
    }

}

double Solution::evaluate2Opt(const int i, const int j){
    Data & data = Data::getInstance();

    double a_subtrair, a_somar, delta;

    a_subtrair = data.matrizAdj[route[i-1]][route[i]] + data.matrizAdj[route[j]][route[j+1]];

    a_somar = data.matrizAdj[route[i-1]][route[j]] + data.matrizAdj[route[i]][route[j+1]];

    delta = a_somar - a_subtrair;

    return delta;
}

void Solution::Opt2(const int i, const int j){
    Data & data = Data::getInstance();
    cost += evaluate2Opt(i, j);

    std::reverse(route.begin() + i, route.begin() + (j + 1));
}

double Solution::evaluateOrOpt3(const int i, const int j){
    Data & data = Data::getInstance();

    double a_subtrair, a_somar, delta;

    if(j == i+3){
        a_subtrair = data.matrizAdj[route[i-1]][route[i]] + data.matrizAdj[route[i+2]][route[j]] + data.matrizAdj[route[j]][route[j+1]];
        a_somar = data.matrizAdj[route[i-1]][route[j]] + data.matrizAdj[route[j]][route[i]] + data.matrizAdj[route[i+2]][route[j+1]];

    }else if(i < j){
        a_subtrair = data.matrizAdj[route[i-1]][route[i]] + data.matrizAdj[route[i+2]][route[i+3]] + data.matrizAdj[route[j]][route[j+1]];
        a_somar = data.matrizAdj[route[j]][route[i]] + data.matrizAdj[route[i+2]][route[j+1]] + data.matrizAdj[route[i-1]][route[i+3]];
    }else{
        a_subtrair = data.matrizAdj[route[i-1]][route[i]] + data.matrizAdj[route[i+2]][route[i+3]] + data.matrizAdj[route[j-1]][route[j]];
        a_somar = data.matrizAdj[route[i-1]][route[i+3]] + data.matrizAdj[route[i+2]][route[j]] + data.matrizAdj[route[j-1]][route[i]];
    }

    delta = a_somar - a_subtrair;

    return delta;
}

void Solution::OrOpt3(const int i, const int j){
    Data & data = Data::getInstance();
    cost += evaluateOrOpt3(i, j);

    if(i <= j){
        std::rotate(route.begin() + i, route.begin() + (i+3), route.begin() + (j+1));
    }else{
        std::rotate(route.begin() + j, route.begin() + i, route.begin() + (i+3));
    }

}

double Solution::evaluateReinsertion(const int i, const int j){
    Data & data = Data::getInstance();

    double a_subtrair, a_somar, delta;

    if(j == i+1){
        a_subtrair = data.matrizAdj[route[i-1]][route[i]] + data.matrizAdj[route[i]][route[j]] + data.matrizAdj[route[j]][route[j+1]];
        a_somar = data.matrizAdj[route[i-1]][route[j]] + data.matrizAdj[route[j]][route[i]] + data.matrizAdj[route[i]][route[j+1]];
    }else if(i < j){
        a_subtrair = data.matrizAdj[route[i-1]][route[i]] + data.matrizAdj[route[i]][route[i+1]] + data.matrizAdj[route[j]][route[j+1]];
        a_somar = data.matrizAdj[route[i-1]][route[i+1]] + data.matrizAdj[route[j]][route[i]] + data.matrizAdj[route[i]][route[j+1]];
    }else{
        a_subtrair = data.matrizAdj[route[i-1]][route[i]] + data.matrizAdj[route[i]][route[i+1]]+ data.matrizAdj[route[j-1]][route[j]];
        a_somar = data.matrizAdj[route[i-1]][route[i+1]] + data.matrizAdj[route[i]][route[j]] + data.matrizAdj[route[j-1]][route[i]];
    }
    delta = a_somar - a_subtrair;

    return delta;
}