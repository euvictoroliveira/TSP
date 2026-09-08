#ifndef BUSCALOCAL_H
#define BUSCALOCAL_H

#include <iostream>
#include "../../solution.h"

// Método utilizado para explorar diferentes estruturas de vizinhança
void RVND(Solution &s);
// Método swap: troca a posição de dois vértices dentro da rota
bool bestImprovementSwap(Solution &s);
// Método Or-opt-2: retira bloco de dois vértices consecutivos da rota e reinsere em outra posição.
bool bestImprovementOrOpt2(Solution &s);
// Método 2-opt: remove duas arestas da rota e inverte o segmento intermediário.
bool bestImprovement2opt(Solution &s);
// Método Or-opt-3: semelhante ao or-opt-3, mas utiliza bloco com 3 vértices ao invés de 2.
bool bestImprovementOrOpt3(Solution &s);
// Método insertion: realiza a inserção de um bloco de vértices na rota
bool bestImprovementReinsertion(Solution &s);


Solution solve();

// Em todos os movimentos de perturbação, true indica que houve melhoria e false indica que não.

#endif