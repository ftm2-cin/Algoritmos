#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

Node *top = NULL;

void pop()
{
    Node *temp = top;
    top = top->next;
    delete temp;
}
void push(int value)
{
    if (top == nullptr || top->data != value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }else
    {
        pop();
    }
    
}


int peek()
{
    if (top == nullptr)
        return -1;

    return top->data;
}

int size()
{
    int count = 0;
    Node *temp = top;

    while (temp != nullptr)
    {
        count++;
        temp = temp->next;
    }

    return count;
}

int main()
{
    int qtdpilhas;
    bool validInput = true;
    string num;
    cin >> qtdpilhas;

    for (int i = 0; i < qtdpilhas; i++)
    {
        top = NULL;
        while (true)
        {
            validInput = true;
            cin >> num;

            if (num == "END")
            {
                break;
            }
            
            for (char c : num)
            {
                if (!isdigit(c))
                {
                    validInput = false;
                }
            }

            if (validInput)
            {
                int parsedNum = stoi(num); 
                push(parsedNum);
            }
        }
        cout << "caso " << i << ": " << size() << " " << peek() << endl;
    }
    return 0;
}