#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* head = NULL;

void insertBefore(int newData) {
    Node* newNode = new Node;
    newNode->data = newData;
    newNode->next = head;
    head = newNode;
}

void insertAfter(int newData) {
    Node* newNode = new Node;
    newNode->data = newData;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

void printList() {
    Node* current = head;
    while (current != NULL) {
        cout << current->data << " ";
        current = current->next;
    }
}

int main() {
    insertAfter(1);
    insertBefore(8);
    insertAfter(2);
    insertAfter(3);

    cout << "Linked List: ";
    printList();
    return 0;
}
