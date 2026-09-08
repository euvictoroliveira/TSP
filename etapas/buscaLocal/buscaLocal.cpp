#include "buscaLocal.h"
#include "../../data.h"
#include <stdlib.h>
#include "buscaLocal.h"
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <cmath>

// Implementação do RVND
void RVND(Solution &s){
    std::vector<int> NL = {1,2,3,4,5};
    bool improved = false; // indica se a ultima vizinhaça explorada melhorou a solução

    // Fica no laço while enquanto houver vizinhaças para explorar
    while(!NL.empty()){
        int pos = (rand() % NL.size()); // escolhe uma posição da lista de vizinhaças.

        switch(NL[pos]){
            case 1:
                improved = bestImprovementSwap(s);
                break;
            case 2:
                improved = bestImprovementOrOpt2(s);
                break;
            case 3: 
                improved = bestImprovement2opt(s);
                break;
            case 4:
                improved = bestImprovementOrOpt3(s);
                break;
            case 5: 
                improved = bestImprovementReinsertion(s);
                break;
        }

        // se houver melhorias, as vizinhanças voltam a ficar disponíveis.
        if(improved)
            NL = {1, 2, 3, 4, 5};
        else
            NL.erase(NL.begin() + pos); // caso não haja melhorias, a vizinhaça é retirada da lista.
        

    }

}
// Implementação do movimento de swap
bool bestImprovementSwap(Solution &s){
    Data &data = Data::getInstance();
    auto &route = s.route;
    double bestDelta = 0;
    int bestI, bestJ;

    for(int i = 1; i < data.n - 1; i++){
        for(int j = i + 1; j < data.n; j++){
            double aSubtrair, aSomar, delta;

            if((j == i + 1)){
                aSubtrair = data.matrizAdj[route[i - 1]][route[i]] + data.matrizAdj[route[j]][route[j + 1]];
                aSomar =  data.matrizAdj[route[i - 1]][route[j]]+ data.matrizAdj[route[i]][route[j + 1]];
            }else{
                 aSubtrair = data.matrizAdj[route[i - 1]][route[i]] + data.matrizAdj[route[i]] [route[i + 1]] +  data.matrizAdj[route[j - 1]][route[j]] + data.matrizAdj[route[j]][route[j + 1]];
                 aSomar = data.matrizAdj[route[i - 1]][route[j]] + data.matrizAdj[route[j]] [route[i + 1]] +  data.matrizAdj[route[j - 1]][route[i]] + data.matrizAdj[route[i]][route[j + 1]];
            }

            delta = aSomar - aSubtrair;

            if(delta < bestDelta){
                bestDelta = delta;
                bestI = i;
                bestJ = j;
            }
        }
    }

    if(bestDelta < 0){
        s.swap(bestI, bestJ);
        s.cost += bestDelta;
        return true;
    }

    return false;
}
// Implementação do movimento Or-opt-2
bool bestImprovementOrOpt2(Solution &s){
    Data &data = Data::getInstance();
    double delta, bestDelta = 0;
    bool melhorou = false;
    int bestI, bestJ;

    for(int i = 1; i < data.n - 2; i++){
        // movimentos para frente
        for(int j = i + 2; j < data.n - 1; j++){
            delta = s.evaluateOrOpt2(i, j);

            if(delta < bestDelta){
                bestDelta = delta; 
                bestI = i;
                bestJ = j;
                melhorou = true;
            }
        }
        // Movimentos para trás
        for(int j = i - 2; j >= 1; j--){
            delta = s.evaluateOrOpt2(i, j);

            if(delta < bestDelta){
                bestDelta = delta;
                bestI = i;
                bestJ = j;
                melhorou = true;
            }
        }
    }

    if(melhorou)
        s.OrOpt2(bestI, bestJ);


    return melhorou;

}
// Implementa movimento 2opt
bool bestImprovement2opt(Solution &s){
    Data &data = Data::getInstance();
    double delta, bestDelta = 0;
    bool melhorou = false;
    int bestI, bestJ;

    for(int i = 1; i < data.n - 1; i++){
        // movimentos para frente
        for(int j = i + 1; j < data.n -1; j++){
            delta = s.evaluate2Opt(i, j);

            if(delta < bestDelta){
                bestDelta = delta;
                bestI = i;
                bestJ = j;

                melhorou = true;
            }
        }

        // movimentos para trás
        for(int j = i - 2; j >= 1; j--){
            delta = s.evaluate2Opt(i, j);

            if(delta < bestDelta){
                bestDelta = delta;
                bestI = i;
                bestJ = j;

                melhorou = true;
            }   
        }

    }

    if(melhorou)
        s.Opt2(bestI, bestJ);
    

    return melhorou;
}
// Implementa movimento or-opt-3
bool bestImprovementOrOpt3(Solution &s){
    Data &data = Data::getInstance();
    double delta, bestDelta = 0;
    int bestI, bestJ;
    bool melhorou;

    for(int i = 1; i < data.n - 3; i++){
        // Movimentos para frente
        for(int j = i + 3; j < data.n - 1; j++){
            delta = s.evaluateOrOpt3(i, j);

            if( delta < bestDelta){
                bestDelta = delta;
                bestI = i;
                bestJ = j;

                melhorou = true;
            }
        }

        // Movimentos para trás
        for(int j = i - 3; j >= 1; j--){
            delta = s.evaluateOrOpt3(i, j);

            if(delta < bestDelta){
                bestDelta = delta;
                bestI = i;
                bestJ = j;

                melhorou = true;
            }
        }
    }

    if(melhorou)
        s.OrOpt3(bestI, bestJ);

    
    return melhorou;

}
// Implementa movimento reinsertion
bool bestImprovementReinsertion(Solution &s){
    Data &data = Data::getInstance();
    double delta, bestDelta = 0;
    int bestI, bestJ;
    bool melhorou = false;

    for(int i = 1; i < data.n - 1; i++){
        for(int j = i + 1; j < data.n - 1; j++){
            delta = s.evaluateReinsertion(i, j);
            
            if(delta < bestDelta){
                bestDelta = delta;
                bestI = i;
                bestJ = j;

                melhorou = true;
            }
        }

        for(int j = i - 1; j >= 1; j--){
            delta = s.evaluateReinsertion(i, j);

            if(delta < bestDelta){
                bestDelta = delta;
                bestI = i;
                bestJ = j;

                melhorou = true;
            }
        }
    }

    if(melhorou)
        s.OrOpt3(bestI, bestJ);

    return melhorou;

}

Solution solve(){

}
