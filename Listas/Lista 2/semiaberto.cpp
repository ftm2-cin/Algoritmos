#include <iostream>

using namespace std;

class HashTable
{
private:
    struct Node
    {
        int key;
        Node **jazidos;
        int numJazidos;
        int maxJazidos;

        Node(int maxJazidos) : maxJazidos(maxJazidos)
        {
            jazidos = new Node *[maxJazidos];
            numJazidos = 0;
        }

        ~Node()
        {
            delete[] jazidos;
        }
    };

    int andares;     // Number of floors in the hash table
    int numElements; // Number of elements in the hash table
    Node **table;    // Array of nodes
    int maxJazidos;  // Maximum number of "jazidos" allowed in a node

    // Hash function to determine the index in the array for a given key
    int hash(int key)
    {
        return key % andares;
    }

    void rehash()
    {
        int newAndares = andares * 2 + 1;         // New size of the hash table
        Node **newTable = new Node *[newAndares]; // Create new table with doubled size
        for (int i = 0; i < newAndares; ++i)
        {
            newTable[i] = nullptr;
        }

        // Reinsert all elements into the new table
        for (int i = 0; i < andares; ++i)
        {
            if (table[i] != nullptr)
            {
                // Reinsert main node
                int newIndex = table[i]->key % newAndares;
                newTable[newIndex] = table[i];

                // Reinsert collision nodes
                for (int j = 0; j < table[i]->numJazidos; ++j)
                {
                    if (table[i]->jazidos[j] != nullptr)
                    {
                        int newCollisionIndex = table[i]->jazidos[j]->key % newAndares;
                        newTable[newCollisionIndex] = table[i]->jazidos[j];
                    }
                }
            }
        }

        // Delete the old table
        for (int i = 0; i < andares; ++i)
        {
            if (table[i] != nullptr)
            {
                delete table[i];
            }
        }
        delete[] table;

        // Update the hash table properties
        andares = newAndares;
        table = newTable;
    }

public:
    HashTable(int numAndares, int maxJazidos) : andares(numAndares), maxJazidos(maxJazidos)
    {
        table = new Node *[andares];
        for (int i = 0; i < andares; ++i)
        {
            table[i] = nullptr;
        }
    }

    ~HashTable()
    {
        for (int i = 0; i < andares; ++i)
        {
            if (table[i] != nullptr)
            {
                delete table[i];
            }
        }
        delete[] table;
    }

    void insert(int key)
    {
        int index = hash(key);

        if (table[index] == nullptr)
        {
            table[index] = new Node(maxJazidos);
            table[index]->key = key;
        }
    }

    // Retrieve the position of the key in the hash table and the position within the collision array
    void get(int key)
    {
        int index = hash(key);

        if (table[index] != nullptr)
        {
            if (table[index]->key == key)
            {
                // Found the node directly
                cout << index << ".0" << endl;
                return;
            }
            else
            {
                // Search for the node in the collision array
                for (int i = 0; i < table[index]->numJazidos; ++i)
                {
                    if (table[index]->jazidos[i] != nullptr && table[index]->jazidos[i]->key == key)
                    {
                        cout << index << "." << i + 1 << endl;
                        return;
                    }
                }
            }
        }

        cout << "?.?" << endl; // Key not found
    }
};

int main()
{
    int key;
    int numAndares;
    int maxJazidosPerNode;
    string entrada;

    cin >> numAndares;
    cin >> maxJazidosPerNode;

    HashTable hashTable(numAndares, maxJazidosPerNode);

    while (cin >> entrada)
    {
        if (entrada == "END")
        {
            break;
        }
        else if (entrada == "ADD")
        {
            cin >> key;
            hashTable.insert(key);
        }
        else if (entrada == "REM")
        {
            // TODO: Implement the removal logic
        }
        else if (entrada == "QRY")
        {
            cin >> key;
            hashTable.get(key);
        }
    }

    return 0;
}

// ADICIONAR REMOÇÃO
// MUDAR PARA VERIFICAR SE TDS JAZIDOS ESTÃO OCUPADOS E NÃO SO DA ARRAY
// ADICIONAR DOUBLE HASH
// ADICIONAR ADD EM FORMA CRESCENTE
// ADICIONAR BINARY SEARCH
