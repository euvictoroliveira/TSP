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

using std::vector;

// Função responsável por calculor o custo de inserção de um vértice. Seus parâmetros são um objeto solução  e um vector de inteiros que representa a lista de candidados.  O retorno é um vector da estrutura InsertionInfo definida acima.
vector<InsertionInfo> calcularCustoInsercao(Solution& s, std::vector<int> CL){
    // Vetor de inserções
    vector<InsertionInfo> custoInsercao = vector<InsertionInfo>((s.route.size() - 1) * CL.size());

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
// Implementa compararCustoInsercao()
bool compararCustoInsercao(InsertionInfo& a, InsertionInfo& b){
    return a.custo < b.custo; // Verifica qual das inserções possui o menor custo. Retorna true se a for menor que b.
}
// Implementa preencherCL()
vector<int> preencherCL(const int& n){
    // Recebe instância da matriz de adjacência
    Data &data = Data::getInstance();
    vector<int> candidatos;

    // For responsável por percorrer todos os candidatos a partir do segundo(o primeiro vértice já está inserido na solução)
    for(int i = 2; i <= data.n; i++){
        // Retorna à iteração caso o vértice atual seja igual ao número passado como parâmetro da função
        if(i == n)
            continue;

        candidatos.push_back(i); // adiciona o vertice a candidate list
    }

    return candidatos; // retorna o vector com os vértices na CL
}
// Implementa ordenar em ordem crescente
void ordenarEmOrdemCrescente(std::vector<InsertionInfo> vector){
    sort(vector.begin(), vector.end(), compararCustoInsercao);
}
// Implementa função para inserir um vértice na solução
void inserir(Solution& s, InsertionInfo& escolhido, std::vector<int>& CL){
    // Inicialmente, é necessário retirar o vértice escolhido da lista de candidatos
    CL.erase(std::remove(CL.begin(), CL.end(), escolhido.noInserido));
    // Inserção do vértice escolhido
    std::vector<int>& route = s.route; // referência para a rota.

    route.insert(route.begin() + escolhido.arestaRemovida + 1, escolhido.noInserido);
    s.cost += escolhido.custo; // adiciona o custo de inserção do vértice ao custo total da solução
    
}