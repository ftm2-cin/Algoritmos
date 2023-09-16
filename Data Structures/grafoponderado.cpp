#include <iostream>

using namespace std;

// Estrutura para representar uma aresta ponderada
struct Edge
{
    int destino;
    int peso;
    Edge *proximo;
};

// Função para adicionar uma aresta ponderada ao grafo de forma ordenada
void adicionarArestaOrdenada(Edge *grafo[], int origem, int destino, int peso)
{
    Edge *novaAresta = new Edge;
    novaAresta->destino = destino;
    novaAresta->peso = peso;
    novaAresta->proximo = nullptr;

    // Caso especial: Se a lista ligada estiver vazia ou o destino for menor que o primeiro destino na lista
    if (grafo[origem] == nullptr || grafo[origem]->destino > destino)
    {
        novaAresta->proximo = grafo[origem];
        grafo[origem] = novaAresta;
    }
    else
    {
        Edge *atual = grafo[origem];
        while (atual->proximo != nullptr && atual->proximo->destino < destino)
        {
            atual = atual->proximo;
        }
        novaAresta->proximo = atual->proximo;
        atual->proximo = novaAresta;
    }
}

// Função para imprimir o grafo com pesos
void imprimirGrafo(Edge *grafo[], int numVertices)
{
    for (int i = 0; i < numVertices; ++i)
    {
        cout << "Vértice " << i << " conectado a:";

        Edge *atual = grafo[i];
        while (atual != nullptr)
        {
            cout << " (Vértice " << atual->destino << ", Peso " << atual->peso << ")";
            atual = atual->proximo;
        }

        cout << endl;
    }
}

int main()
{
    int numVertices = 5;
    Edge *grafo[numVertices] = {nullptr};

    // Adicione arestas ponderadas ao grafo de forma ordenada
    adicionarArestaOrdenada(grafo, 0, 1, 2);
    adicionarArestaOrdenada(grafo, 0, 3, 1);
    adicionarArestaOrdenada(grafo, 1, 2, 3);
    adicionarArestaOrdenada(grafo, 2, 3, 2);
    adicionarArestaOrdenada(grafo, 3, 4, 4);

    // Imprima o grafo com pesos
    imprimirGrafo(grafo, numVertices);

    // Libere a memória alocada para as arestas
    for (int i = 0; i < numVertices; ++i)
    {
        Edge *atual = grafo[i];
        while (atual != nullptr)
        {
            Edge *proximo = atual->proximo;
            delete atual;
            atual = proximo;
        }
    }

    return 0;
}
