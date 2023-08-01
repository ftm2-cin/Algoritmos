#include <iostream>

const int TABLE_SIZE = 10;

struct Node {
    int key;
    int value;
    Node* next;
    bool morto;
    Node(int k, int v) : key(k), value(v), morto(false), next(nullptr) {}
};

class HashTable {
private:
    Node* table[TABLE_SIZE];

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

    void insert(int key, int value) {
        int index = hashFunction(key);
        Node* newNode = new Node(key, value);

        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            Node* temp = table[index];
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    int search(int key) {
        int index = hashFunction(key);

        if (table[index] == nullptr) {
            return -1;
        } else {
            Node* temp = table[index];
            while (temp != nullptr) {
                if (temp->key == key) {
                    return temp->value;
                }
                temp = temp->next;
            }
            return -1;
        }
    }
};

int main() {
    HashTable hashTable;
    hashTable.insert(1, 10);
    hashTable.insert(2, 20);
    hashTable.insert(11, 30);

    std::cout << "Enter a key to search: ";
    int key;
    std::cin >> key;

    int value = hashTable.search(key);

    if (value != -1)
        std::cout << "Value found: " << value << std::endl;
    else
        std::cout << "Value not found." << std::endl;

    return 0;
}
