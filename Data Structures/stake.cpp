#include <iostream>
using namespace std;

// Stack node structure
struct Node {
    int data;
    Node* next;
};

// Global variable for the top of the stack
Node* top = NULL;

// Function to check if the stack is empty
bool isEmpty() {
    return (top == NULL);
}

// Function to push an element onto the stack
void push(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = top;
    top = newNode;
    cout << "Pushed " << value << " onto the stack." << endl;
}

// Function to pop an element from the stack
void pop() {
    if (isEmpty()) {
        cout << "Stack is empty. Cannot pop." << endl;
        return;
    }

    Node* temp = top;
    top = top->next;
    int poppedValue = temp->data;
    delete temp;
    cout << "Popped " << poppedValue << " from the stack." << endl;
}

// Function to peek at the top element of the stack
int peek() {
    if (isEmpty()) {
        cout << "Stack is empty. Cannot peek." << endl;
        return -1;
    }

    return top->data;
}

// Function to display the elements of the stack
void display() {
    if (isEmpty()) {
        cout << "Stack is empty." << endl;
        return;
    }

    cout << "Stack elements: ";
    Node* temp = top;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Main function for testing the stack implementation
int main() {
    push(5);
    push(10);
    push(15);
    display();

    cout << "Top element: " << peek() << endl;
    pop();
    cout << "Top element: " << peek() << endl;
    display();

    return 0;
}
