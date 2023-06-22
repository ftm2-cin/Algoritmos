#include <iostream>

using namespace std;

class Stack
{
private:
    struct Node
    {
        int data;
        Node *nextstack;
    };

    Node *top;

public:
    Stack()
    {
        top = nullptr;
    }

    ~Stack()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    void push(int value)
    {
        if (top == nullptr || top->data != value)
        {
            Node *newNode = new Node();
            newNode->data = value;
            newNode->nextstack = top;
            top = newNode;
        }
        else
        {
            pop();
        }
    }

    void pop()
    {
        if (top == nullptr)
        {
            return;
        }

        Node *temp = top;
        top = top->nextstack;
        delete temp;
    }

    int peek()
    {
        if (top == nullptr)
        {
            return -1;
        }

        return top->data;
    }

    bool isEmpty()
    {
        return top == nullptr;
    }
};

struct Node
{
    Stack stack;
    Node *next;
};

Node *head = nullptr;

void insertAfter(int newData)
{
    Node *newNode = new Node;
    newNode->stack.push(newData);

    newNode->next = nullptr;
    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    Node *current = head;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    current->next = newNode;
}

void insertBefore(int newData)
{
    Node *newNode = new Node;
    newNode->stack.push(newData);
    newNode->next = head;
    head = newNode;
}

void insertrock(int position, int newData, int *tamlist)
{
    Node *current = head;
    int currentPosition = 1;

    while (currentPosition < position && current->next != nullptr)
    {
        current = current->next;
        currentPosition++;
    }
    current->stack.push(newData);

    if (current->stack.isEmpty())
    {
        if (current == head)
        {
            head = current->next;
        }
        else
        {
            Node *previous = head;
            while (previous->next != current)
            {
                previous = previous->next;
            }
            previous->next = current->next;
        }
        delete current;
        (*tamlist)--;
    }
}

int main()
{
    int qtdpilhas;
    int tamlist = 0;
    bool validInput;
    int coluna = 0, num = 0;
    string linha;

    cin >> qtdpilhas;

    for (int i = 0; i < qtdpilhas; i++)
    {
        tamlist = 0;
        head = nullptr;
        while (true)
        {
            validInput = true;
            cin >> linha;

            if (linha == "END")
            {
                break;
            }

            if (!isdigit(linha[0]))
            {
                validInput = false;
            }
            else
            {
                coluna = stoi(linha);
                cin >> num;
            }

            if (validInput)
            {
                if (coluna == 0)
                {
                    insertBefore(num);
                    tamlist++;
                }
                else if (coluna == tamlist + 1)
                {
                    insertAfter(num);
                    tamlist++;
                }
                else
                {
                    insertrock(coluna, num, &tamlist);
                }
            }
        }
        cout << "caso " << i << ":";
        Node *current = head;
        while (current != NULL)
        {
            cout << " " << current->stack.peek();
            current = current->next;
        }
        cout << endl;
    }
    return 0;
}