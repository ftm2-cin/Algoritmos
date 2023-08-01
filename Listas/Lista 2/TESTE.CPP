#include <iostream>

using namespace std;

class HashTable
{
private:
    struct Node
    {
        int key;
        bool removed;
    };

    int andares;     // Number of floors in the hash table
    int numElements; // Number of elements in the hash table
    Node **table;    // 2D array of nodes
    int maxJazidos;  // Maximum number of "jazidos" allowed in a node

    // Hash function to determine the index in the array for a given key
    int hash(int key)
    {
        return key % andares;
    }

public:
    HashTable(int numAndares, int maxJazidos) : andares(numAndares), maxJazidos(maxJazidos)
    {
        table = new Node *[andares];
        for (int i = 0; i < andares; ++i)
        {
            table[i] = new Node[maxJazidos + 1]; // +1 for the main node
            for (int j = 0; j <= maxJazidos; ++j)
            {
                table[i][j].removed = true;
            }
        }
        numElements = 0;
    }

    ~HashTable()
    {
        for (int i = 0; i < andares; ++i)
        {
            delete[] table[i];
        }
        delete[] table;
    }

    void insert(int key, bool print)
    {

        int index = hash(key);

        if (table[index][0].removed)
        {
            table[index][0].key = key;
            table[index][0].removed = false;
            cout << index << ".0" << endl;
        }
        else if (key < table[index][0].key)
        {
            int temp = table[index][0].key;
            table[index][0].key = key;
            cout << index << ".0" << endl;
            insert(temp, false);
        }
        else
        {
            int collisionIndex = 1;
            while (!table[index][collisionIndex].removed && collisionIndex <= maxJazidos && table[index][collisionIndex].key <= key)
            {
                collisionIndex++;
            }

            for (int i = maxJazidos; i >= collisionIndex; i--)
            {
                table[index][i] = table[index][i - 1];
            }

            table[index][collisionIndex].key = key;
            table[index][collisionIndex].removed = false;
            if(print == true){
                cout << index << "." << collisionIndex << endl;
            }
        }
        numElements++;
    }

    void get(int key)
    {
        int index = hash(key);

        if (!table[index][0].removed && table[index][0].key == key)
        {
            cout << index << ".0" << endl;
            return;
        }
        else
        {
            int left = 1;
            int right = maxJazidos;
            while (left <= right)
            {
                int mid = left + (right - left) / 2;
                if (!table[index][mid].removed && table[index][mid].key == key)
                {
                    cout << index << "." << mid << endl;
                    return;
                }
                else if (!table[index][mid].removed && table[index][mid].key < key)
                {
                    left = mid + 1;
                }
                else
                {
                    right = mid - 1;
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
            hashTable.insert(key, true);
        }
        else if (entrada == "REM")
        {
        }
        else if (entrada == "QRY")
        {
            cin >> key;
            hashTable.get(key);
        }
    }

    return 0;
}
