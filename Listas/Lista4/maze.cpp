#include <iostream>

using namespace std;

class UnionFind
{
public:
    int *parent;

    UnionFind(int size)
    {
        parent = new int[size];
        for (int i = 0; i < size; ++i)
        {
            parent[i] = i; // cada nó é pai de si mesmo
        }
    }

    int find(int x)
    {
        if (x != parent[x])
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
        {
            parent[rootX] = rootY;
        }
    }

    ~UnionFind()
    {
        delete[] parent;
    }
};

int main()
{
    int numTests;
    cin >> numTests;

    for (int test = 0; test < numTests; test++)
    {
        int matrixSize, numParedes, numCaminhos;
        cin >> matrixSize >> numParedes >> numCaminhos;

        UnionFind uf(matrixSize * matrixSize);

        for (int p = 0; p < numParedes; p++)
        {
            int wallLocation;
            cin >> wallLocation;
            // aresta direita
            if (wallLocation % (2 * matrixSize - 1) < matrixSize - 1)
            {
                int celula = matrixSize * (wallLocation / (2 * matrixSize - 1)) + (wallLocation % (2 * matrixSize - 1));
                uf.unite(celula, celula + 1);
            }
            else
            {
                // aresta baixo
                int celula2 = matrixSize * (wallLocation / (2 * matrixSize - 1)) + (wallLocation % (2 * matrixSize - 1) - (matrixSize - 1));
                uf.unite(celula2, celula2 + matrixSize);
            }
        }

        for (int i = 0; i < numCaminhos; i++)
        {
            int start, end;
            cin >> start >> end;

            if (uf.find(start) == uf.find(end))
            {
                cout << test << "." << i << " 1" << endl;
            }
            else
            {
                cout << test << "." << i << " 0" << endl;
            }
        }
        cout << endl;
    }

    return 0;
}
