#ifndef CONSTRUCAO_H
#define CONSTRUCAO_H

#include <iostream>
#include "../../solution.h"
/*
    Definição da estrutura usada para guardar informações de inserção de um novo
    vértice em uma aresta.

    As informações armazenadas são: 
        - nó(vértice) inserido
        - aresta anterior que será removida
        - custo da inserção no novo passeio

*/
typedef struct InsertionInfo{
    int noInserido; // vértice k a ser inserido
    int arestaRemovida; // aresta {i,j} removida
    double custo; // custo da inserção, onde custo = c{i,k} + c{k,j} - c{i,j}
} InsertionInfo;


// Funcao de cálculo de custo na inserção de um vértice na solução
std::vector<InsertionInfo> calcularCustoInsercao(Solution s, std::vector<int>& CL);


#endif