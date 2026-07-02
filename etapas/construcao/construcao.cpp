/* O método construtivo estima uma solução inicial da seguinte maneira: 
   - Inicia-se com um subtour s', sendo s' linha apensas um subconjunto dos vértices totais do problema.
   - Há também uma lista de candidatos a serem inseridos, denotada por CL = V/V', onde V é grafo total e V' o grafo com os vértices contidos em S'.
   - A cada interação, é calculado o custo dos candidatos a serem inseridos. Esses candidatos são dispostos em uma lista aleatorizada e é escolhido o primeiro dos candidados para inserção em S'
   - O algoritmo para quando CL estiver vazio.
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "construcao.h"

// Função responsável por calculor o custo de inserção de um vértice. Seus parâmetros são um objeto solução  e um vector de inteiros que representa a lista de candidados.  O retorno é um vector da estrutura InsertionInfo definida acima.
std::vector<InsertionInfo> calcularCustoInsercao(Solution& s, std::vector<int> CL){
    // Vetor de inserções
    std::vector<InsertionInfo> custoInsercao = std::vector<InsertionInfo>((s.route.size() - 1) * CL.size());

    // Matriz de adjacência necessária para o cálculo de custo da inserção
    Data & data = Data::getInstance();
    auto & c = data.matrizAdj;


    int l = 0; // contador de cada elemento inserido no vector

    for(int a = 0; a < s.route.size() - 1; a++){
        int i = s.route[a];
        int j = s.route[a + 1];

        for(auto k : CL){
            custoInsercao[l].custo = c[i][k] + c[j][k] - c[i][j];
            custoInsercao[l].noInserido = k;
            custoInsercao[l].arestaRemovida = a;
        
            l++;
        }
    }

    return custoInsercao;
}
