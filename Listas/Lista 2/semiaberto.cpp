#include <iostream>
using namespace std;

struct Node
{
    int key;
    int removed;
};

int Hash(int key, int andares, int cont)
{
    return (key % andares + cont) % andares;
}

int insert(int key, bool print, int andares, int maxJazidos, int *qtdelementos, Node **table, int cont)
{
    int index = Hash(key, andares, cont);

    if (qtdelementos[index] == maxJazidos)
    {
        cont++;
        if (cont != andares)
        {
            return insert(key, print, andares, maxJazidos, qtdelementos, table, cont);
        }
        else
        {
            return -1;
        }
    }

    int collisionIndex = 0;

    while (table[index][collisionIndex].removed != -1 && table[index][collisionIndex].key <= key)
    {
        collisionIndex++;
    }

    for (int i = maxJazidos - 1; i > collisionIndex; i--)
    {
        table[index][i] = table[index][i - 1];
    }

    table[index][collisionIndex].key = key;
    table[index][collisionIndex].removed = 0;
    qtdelementos[index]++;
    if (print)
    {
        cout << index << "." << collisionIndex << endl;
    }
    return 0;
}

int binarySearch(int key, int floor, int l, Node **table)
{
    int left = 0;
    int right = l - 1;
    int middle = (left + right) / 2;
    int find = 0;
    while (left <= right && find == 0)
    {
        if (table[floor][middle].key == key)
        {
            find = 1;
        }
        else if (table[floor][middle].key > key)
        {
            right = middle - 1;
            middle = (left + right) / 2;
        }
        else
        {
            left = middle + 1;
            middle = (left + right) / 2;
        }
    }
    if (find == 0)
    {
        return -1;
    }
    else
    {
        return middle;
    }
}

int get(int key, int andares, int maxJazidos, Node **table, int cont)
{
    int index = Hash(key, andares, cont);

    if (table[index][0].removed == 0 && table[index][0].key == key)
    {
        cout << index << ".0" << endl;
        return 0;
    }

    int result = binarySearch(key, index, maxJazidos, table);

    if (result != -1)
    {
        if (table[index][result].removed == 1)
        {
            cout << "?.?" << endl;
        }
        else
        {
            cout << index << "." << result << endl;
        }
        return 0;
    }

    if (cont < andares - 1)
    {
        return get(key, andares, maxJazidos, table, cont + 1);
    }
    return -1;
}

int remove(int key, int andares, int maxJazidos, Node **table, int cont)
{
    int index = Hash(key, andares, cont);

    if (table[index][0].removed == 0 && table[index][0].key == key)
    {
        cout << index << ".0" << endl;
        table[index][0].removed = 1;
        return 0;
    }

    int result = binarySearch(key, index, maxJazidos, table);

    if (result != -1)
    {
        if (table[index][result].removed == 1)
        {
            cout << "?.?" << endl;
        }
        else
        {
            cout << index << "." << result << endl;
            table[index][result].removed = 1;
        }
        return 0;
    }

    if (cont < andares - 1)
    {
        return remove(key, andares, maxJazidos, table, cont + 1);
    }
    return -1;
}

int main()
{
    int key;
    int numAndares;
    int maxJazidosPerNode;
    string entrada;

    cin >> numAndares;
    cin >> maxJazidosPerNode;

    Node **table = new Node *[numAndares];
    int *qtdelementos = new int[numAndares];
    for (int i = 0; i < numAndares; ++i)
    {
        table[i] = new Node[maxJazidosPerNode + 1];
        qtdelementos[i] = 0;
        for (int j = 0; j <= maxJazidosPerNode; ++j)
        {
            table[i][j].removed = -1;
            table[i][j].key = 9999999;
        }
    }

    while (cin >> entrada)
    {
        if (entrada == "END")
        {
            break;
        }
        else if (entrada == "ADD")
        {
            cin >> key;
            if (insert(key, true, numAndares, maxJazidosPerNode, qtdelementos, table, 0) == -1)
            {
                int m = numAndares * 2 + 1;
                Node **temp = table;
                Node **cemiterio = new Node *[m];
                int *qtdelementosTemp = new int[m];

                for (int i = 0; i < m; ++i)
                {
                    cemiterio[i] = new Node[maxJazidosPerNode];
                    qtdelementosTemp[i] = 0;
                    for (int j = 0; j < maxJazidosPerNode; ++j)
                    {
                        cemiterio[i][j].removed = -1;
                        cemiterio[i][j].key = 9999999;
                    }
                }

                table = cemiterio;
                qtdelementos = qtdelementosTemp;

                for (int i = 0; i < numAndares; ++i)
                {
                    for (int j = 0; j < maxJazidosPerNode; ++j)
                    {
                        if (temp[i][j].removed == 0)
                        {
                            insert(temp[i][j].key, false, m, maxJazidosPerNode, qtdelementos, table, 0);
                        }
                    }
                }

                for (int i = 0; i < numAndares; ++i)
                {
                    delete[] temp[i];
                }
                delete[] temp;

                numAndares = m;
                insert(key, true, numAndares, maxJazidosPerNode, qtdelementos, table, 0);
            }
        }
        else if (entrada == "QRY")
        {
            cin >> key;
            if (get(key, numAndares, maxJazidosPerNode, table, 0) == -1)
            {
                cout << "?.?" << endl;
            }
        }
        else if (entrada == "REM")
        {
            cin >> key;
            if (remove(key, numAndares, maxJazidosPerNode, table, 0) == -1)
            {
                cout << "?.?" << endl;
            }
        }
    }
    for (int i = 0; i < numAndares; ++i)
    {
        delete[] table[i];
    }
    delete[] table;
    delete[] qtdelementos;

    return 0;
}