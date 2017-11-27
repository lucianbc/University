#include <iostream>

using namespace std;

struct Node
{
    int key;
    int height;
    Node *left, *right;
};

int max(int a, int b)
{
    return a > b ? a : b;
}

Node* newNode(int val)
{
    Node* n = new Node;
    n->key = val;
    n->left = NULL;
    n->right = NULL;
    n->height = 1;
    return n;
}

int height(Node* n)
{
    if(n == NULL)
        return 0;
    return n->height;
}

Node* rightRotate(Node* y)
{
    Node* x = y->left;
    Node* T2 = x->right;

    // rotire
    x->right = y;
    y->left = T2;

    // recalculeaza inaltimile
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // returneaza noua radacina
    return x;
}

Node* leftRotate(Node* x)
{
    Node* y = x->right;
    Node* T2 = y->left;

    // roteste
    y->left = x;
    x->right = T2;

    // recalculeaza inaltimile
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // returneaza noua radacina
    return y;
}

int getBalance(Node* n)
{
    if(n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

Node* insert(Node* t, int val)
{
    if(t == NULL)
        return newNode(val);

    if(t->key < val)
        t->right = insert(t->right, val);
    else if(t->key > val)
        t->left = insert(t->left, val);
    else
        // valorile egale nu sunt acceptate
        return t;

    t->height = 1 + max(height(t->left), height(t->right));

    int balance = getBalance(t);

    // cazul stanga
    if(balance > 1 && val < t->left->key)
    {
        return rightRotate(t);
    }

    // cazul dreapta
    if(balance < -1 && val > t->right->key)
    {
        return leftRotate(t);
    }

    // cazul stanga dreapta
    if(balance > 1 && val > t->left->key)
    {
        t->left = leftRotate(t->left);
        return rightRotate(t);
    }

    // cazul dreapta stanga
    if(balance < -1 && val < t->right->key)
    {
        t->right = rightRotate(t->right);
        return leftRotate(t);
    }

    // cazul in care arborele este echilibrat
    return t;
}

Node* getMinNode(Node* t)
{
    if(t == NULL)
        return NULL;

    while(t->left != NULL)
        t = t->left;

    return t;
}

Node* deleteNode(Node* root, int key)
{
    if(root == NULL)
        return root;

    if(key < root->key)
        root->right = deleteNode(root->right, key);
    else if(key > root->key)
        root->right = deleteNode(root->right, key);
    else
    {
        // fara fii sau cu un singur fiu
        if(root->left == NULL || root->right == NULL)
        {
            Node* tmp = root->left ? root->left : root->right;

            if(tmp == NULL)
            {
                tmp = root;
                root = NULL;
            }
            else
            {
                *root = *tmp;
            }

            delete tmp;
        }
        else
        {
            // nod cu doi fii
            Node* tmp = getMinNode(root->right);

            root->key = tmp->key;

            root->right = deleteNode(root->right, tmp->key);
        }
    }

    // cazul in care arborele a avut doar un nod
    if(root == NULL)
        return root;

    // actualizeaza inaltimea
    root->height = 1 + max(height(root->left), height(root->right));

    // calculeaza dezechilibrul
    int balance = getBalance(root);

    if(balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if(balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if(balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if(balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void parcurgeRSD(Node* t)
{
    if(t == NULL)
        return;
    cout<<t->key<<" ";
    parcurgeRSD(t->left);
    parcurgeRSD(t->right);
}

int search(Node* t, int key)
{
    if(t == NULL)
        return 0;
    if(t->key == key)
        return 1;
    else if(t->key < key)
        return search(t->right, key);
    else return search(t->left, key);
}

int getMaxValue(Node* t)
{
    if(t == NULL)
        return 0x80000000;
    while(t->right != NULL)
        t = t->right;
    return t->key;
}

void parcurgeSRD(Node* t)
{
    if(t == NULL)
        return;
    parcurgeSRD(t->left);
    cout<<t->key<<" ";
    parcurgeSRD(t->right);
}

int main()
{
    Node* tree = NULL;

    tree = insert(tree, 1);
    tree = insert(tree, 2);
    tree = insert(tree, 3);
    tree = insert(tree, 4);
    tree = insert(tree, 5);
    tree = insert(tree, 6);
    tree = insert(tree, 7);
    tree = insert(tree, 8);

    /*
            9
           /  \
          1    10
        /  \     \
       0    5     11
      /    /  \
     -1   2    6

    */

    parcurgeRSD(tree);

    cout<<endl;

    tree = deleteNode(tree, 5);

    parcurgeRSD(tree);

    /*
            1
           /  \
          0    9
        /     /  \
       -1    5     11
           /  \
          2    6
    */


    cout<<endl;
    parcurgeSRD(tree);

    return 0;
}
