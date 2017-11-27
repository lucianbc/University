#include <iostream>

using namespace std;

struct Nod
{
    int data;
    Nod* left;
    Nod* right;
    Nod* parent;
};

Nod* newNode(int data)
{
    Nod* myNode = new Nod;
    myNode->data = data;
    myNode->left = NULL;
    myNode->right = NULL;
    myNode->parent = NULL;
    return myNode;
}

int search(Nod* t, int x)
{
    if(t == NULL)
    {
        return 0;
    }
    if(t->data == x)
    {
        return 1;
    }
    else if(t->data < x)
    {
        return search(t->right, x);
    }
    else
    {
        return search(t->left, x);
    }
}

Nod* insert(Nod* t, int x)
{
    if(t == NULL)
        return newNode(x);
    if(x <= t->data)
    {
        Nod* rez = insert(t->left, x);
        t->left = rez;
        rez->parent = t;
    }
    else
    {
        Nod* rez = insert(t->right, x);
        t->right = rez;
        rez->parent = t;
    }
    return t;
}

int findMax(Nod* t)
{
    if(t != NULL)
    {
        while(t->right != NULL)
            t = t->right;
        return t->data;
    }
    return 0x80000001;
}

Nod* findMin(Nod* t)
{
    if(t == NULL)
        return NULL;
    while(t->left != NULL)
        t = t->left;
    return t;
}

Nod* findRef(Nod* t, int x)
{
    if(t == NULL)
    {
        return NULL;
    }
    if(t->data == x)
    {
        return t;
    }
    else if(t->data < x)
    {
        return findRef(t->right, x);
    }
    else
    {
        return findRef(t->left, x);
    }
}

void transplant(Nod* &t, Nod* u, Nod* v)
{
    if(u->parent == NULL)
        t = v;
    else if(u == (u->parent)->left)
        u->parent->left = v;
    else
    {
        u->parent->right = v;
    }
    if(v != NULL)
        v->parent = u->parent;
}

void remove(Nod* &t, int val)
{
    Nod* ref = findRef(t, val);

    if(ref->left == NULL)
    {
        Nod* p = ref->parent;
        transplant(t, ref, ref->right);
    }
    else if(ref->right == NULL)
    {
        transplant(t, ref, ref->left);
    }
    else
    {
        Nod* y = findMin(ref->right);
        if(y->parent != ref)
        {
            transplant(t, y, y->right);
            y->right = ref->right;
            y->right->parent = y;
        }
        transplant(t, ref, y);
        y->left = ref->left;
        y->left->parent = y;
    }
    delete ref;
}

void parcurgeRSD(Nod* arbore)
{
    if(arbore == NULL)
        return;
    cout<<arbore->data<<" ";
    parcurgeRSD(arbore->left);
    parcurgeRSD(arbore->right);
}

void parcurgeSRD(Nod* arbore)
{
    if(arbore == NULL)
        return;
    parcurgeRSD(arbore->left);
    cout<<arbore->data<<" ";
    parcurgeRSD(arbore->right);
}

void parcurgeSDR(Nod* arbore)
{
    if(arbore == NULL)
        return;
    parcurgeRSD(arbore->left);
    parcurgeRSD(arbore->right);
    cout<<arbore->data<<" ";
}

int main()
{
    Nod* root = NULL;
////     4 1 7 3 5 2 6 stergi 4
    root = insert(root, 4);
    root = insert(root, 1);
    root = insert(root, 7);
    root = insert(root, 3);
    root = insert(root, 5);
    root = insert(root, 2);
    root = insert(root, 6);

    parcurgeSRD(root);

    cout<<endl;

    remove(root, 4);

    parcurgeSRD(root);

//    root = insert(root, 4);
//    parcurgeSRD(root);
//    root = insert(root, 1);
//    parcurgeSRD(root);
//    root = insert(root, 7);
//    root = insert(root, 3);
//    root = insert(root, 5);
//    parcurgeSRD(root);



    return 0;
}
