#include <iostream>
#include <climits>

using namespace std;

struct Edge
{
    int destino;
    int peso;
    Edge *proximo;
};

void Gadd(Edge *grafo[], int origem, int destino, int peso)
{
    Edge *novaAresta = new Edge;
    novaAresta->destino = destino;
    novaAresta->peso = peso;
    novaAresta->proximo = grafo[origem];
    grafo[origem] = novaAresta;
}

void Grem(Edge *grafo[], int origem, int destino)
{
    if (grafo[origem] == nullptr)
    {
        return;
    }

    if (grafo[origem]->destino == destino)
    {
        Edge *temp = grafo[origem];
        grafo[origem] = grafo[origem]->proximo;
        delete temp;
        return;
    }

    Edge *anterior = grafo[origem];
    Edge *atual = grafo[origem]->proximo;

    while (atual != nullptr && atual->destino != destino)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual != nullptr)
    {
        anterior->proximo = atual->proximo;
        delete atual;
    }
}

class MinHeap
{
private:
    int *arr;
    int *pos;
    int tam;

public:
    MinHeap(int cap)
    {
        tam = 0;
        arr = new int[cap];
        pos = new int[cap];
    }

    int parent(int i)
    {
        return (i - 1) / 2;
    }

    void insert(int value, int dist)
    {
        int i = tam - 1;
        arr[tam] = value;
        pos[value] = dist;
        tam++;

        while (i > 0 && pos[arr[parent(i)]] > pos[arr[i]])
        {
            swap(pos[i], pos[parent(i)]);
            i = parent(i);
        }
    }

    void update(int v, int dist)
    {
        pos[v] = dist;
        int i = 0;
        while (i < tam && arr[i] != v)
        {
            i++;
        }
        while (i > 0 && pos[arr[parent(i)]] > pos[arr[i]])
        {
            swap(arr[i], arr[parent(i)]);
            i = parent(i);
        }
    }

    int extractMin()
    {
        int root = arr[0];
        int index = arr[tam - 1];
        tam--;

        arr[0] = index;

        heapify(0);

        return root;
    }

    void heapify(int i)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < tam && pos[arr[left]] < pos[arr[smallest]])
            smallest = left;
        if (right < tam && pos[arr[right]] < pos[arr[smallest]])
            smallest = right;

        if (smallest != i)
        {
            swap(arr[i], arr[smallest]);
            heapify(smallest);
        }
    }
};

void dijkstra(Edge *grafo[], int quadras, int source, int destino)
{
    int dist[quadras];
    int prev[quadras];
    MinHeap minHeap(quadras);

    for (int i = 0; i < quadras; i++)
    {
        dist[i] = INT_MAX;
        prev[i] = -1;
        minHeap.insert(i, dist[i]);
    }

    dist[source] = 0;
    minHeap.update(source, dist[source]);

    for (int i = 0; i < quadras; i++)
    {
        int u = minHeap.extractMin();

        Edge *current = grafo[u];

        while (current != nullptr)
        {
            int v = current->destino;
            int weight = current->peso;

            if (dist[u] != INT_MAX && (dist[u] + weight) < dist[v])
            {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                minHeap.update(v, dist[v]);
            }

            current = current->proximo;
        }
    }

    if (dist[destino] != INT_MAX)
    {
        cout << dist[destino] << endl;
    }
    else
    {
        cout << "-1" << endl;
    }
}

int main()
{
    int quadras, ruas, eventos, origem, destino, peso, acao;
    cin >> quadras >> ruas >> eventos;

    Edge *G[quadras] = {nullptr};

    for (int i = 0; i < ruas; i++)
    {
        cin >> origem >> destino >> peso;
        Gadd(G, origem, destino, peso);
    }

    for (int i = 0; i < eventos; i++)
    {
        cin >> acao;
        if (acao == 1)
        {
            cin >> origem >> destino;
            Grem(G, origem, destino);
        }
        else
        {
            cin >> origem >> destino;
            dijkstra(G, quadras, origem, destino);
        }
    }

    return 0;
}
