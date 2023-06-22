#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* top = NULL;

void push(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = top;
    top = newNode;
}

void pop() {
    if (top == NULL) {
        cout << "Stack is empty. Cannot pop." << endl;
        return;
    }

    Node* temp = top;
    top = top->next;
    delete temp;
}

int peek() {
    if (top == NULL) {
        cout << "Stack is empty. Cannot peek." << endl;
        return -1;
    }

    return top->data;
}

int cont() {
    int count = 0;
    Node* temp = top;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    return count;
}

void remove() {
    Node* current = top;
    Node* nextNode = NULL;
    bool removed = true;

    while (removed) {
        current = top;
        nextNode = current->next;
        removed = false;

        while (current != NULL && nextNode != NULL) {
            if (current->data == nextNode->data) {
                pop();
                pop();
                removed = true;
                break;
            } else {
                current = current->next;
                nextNode = nextNode->next;
            }
        }
    }
}

int main() {
    int qtdpilhas;
    char num;
    cin >> qtdpilhas;
    cin.ignore(); // Ignore the newline character after reading qtdpilhas

    for (int i = 0; i < qtdpilhas; i++) {
        num = '\0'; // Reset num to null character
        while (num != 'E') {
            cin >> num;
            if (isdigit(num)) {
                push(num - '0');
            }
        }
        remove();
        remove();
        cout << "caso " << i << ": " << cont() << " " << peek() << endl;

        while (top != NULL) {
            pop();
        }
    }
    return 0;
}
