
#include <iostream>

using namespace std;

struct Node
{
    int id;
    int bytes;
    int height;
    int sum;
    int size;
    Node *left;
    Node *right;

    Node(int val, int bytes) : id(val), bytes(bytes), height(1), sum(bytes), left(nullptr), right(nullptr) {}
};

class AVLTree
{
private:
    Node *root;

    int height(Node *node)
    {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int balanceFactor(Node *node)
    {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    void updateHeight(Node *node)
    {
        if (node == nullptr)
            return;
        node->height = max(height(node->left), height(node->right)) + 1;
    }

    void updateSum(Node *node)
    {
        if (node == nullptr)
            return;
        node->sum = node->bytes + (node->left ? node->left->sum : 0) + (node->right ? node->right->sum : 0);
    }

    Node *rotateRight(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        updateSum(y);
        updateSum(x);

        return x;
    }

    Node *rotateLeft(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        updateSum(x);
        updateSum(y);

        return y;
    }

    Node *insertNode(Node *node, int key, int bytes)
    {
        if (node == nullptr)
            return new Node(key, bytes);

        if (key < node->id)
            node->left = insertNode(node->left, key, bytes);
        else if (key > node->id)
            node->right = insertNode(node->right, key, bytes);
        else
        {
            node->bytes += bytes;
            updateSum(node);
            return node;
        }

        updateHeight(node);
        updateSum(node);

        int balance = balanceFactor(node);

        if (balance > 1 && key < node->left->id)
            return rotateRight(node);

        if (balance < -1 && key > node->right->id)
            return rotateLeft(node);

        if (balance > 1 && key > node->left->id)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && key < node->right->id)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node *searchNode(Node *node, int key, int *cont)
    {
        if (node == nullptr)
            return nullptr;

        if (key == node->id)
            return node;
        else if (key < node->id)
        {
            *cont += 1;
            return searchNode(node->left, key, cont);
        }
        else
        {
            *cont += 1;
            return searchNode(node->right, key, cont);
        }
    }

    int rank(Node* node, int key, int& sum_so_far) {
        if (node == nullptr)
            return 0;

        if (key < node->id){
            return rank(node->left, key, sum_so_far);
        }
        else if (key > node->id) {
            sum_so_far += node->bytes + (node->left ? node->left->sum : 0);
            return 1 + getSize(node->left) + rank(node->right, key, sum_so_far);
        } 
        else{
            sum_so_far += (node->left ? node->left->sum : 0);
            return getSize(node->left);
        }
    }

    int getSize(Node* node) {
        if (node == nullptr)
            return 0;
        return node->size;
    }

public:
    AVLTree() : root(nullptr) {}

    void add(int id, int bytes)
    {
        root = insertNode(root, id, bytes);
    }

    void wei(int id)
    {
        int cont = 0;
        Node *node = searchNode(root, id, &cont);
        if (node != nullptr)
        {
            cout << node->bytes << ' ' << cont << endl;
        }
        else
        {
            cout << "0 -1" << endl;
        }
    }

    int rnk(int key) {
        int sumbytes = 0;
        rank(root, key, sumbytes);
        return sumbytes;
    }
};

int main()
{
    AVLTree avl;

    int id, bytes, somador = 0;
    string entrada;

    while (cin >> entrada)
    {
        if (entrada == "END")
        {
            break;
        }
        else if (entrada == "ADD")
        {
            cin >> id >> bytes;
            avl.add(id, bytes);
            somador += bytes;
            cout << somador << endl;
        }
        else if (entrada == "WEI")
        {
            cin >> id;
            avl.wei(id);
        }
        else if (entrada == "RNK")
        {
            cin >> id;
            cout << avl.rnk(id) << endl;
        }
    }
    return 0;
}