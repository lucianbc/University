#include <iostream>
#include <deque>
#include <vector>

using namespace std;

struct number {
    int nr;
    number(int x) : nr(x) {};

    int operator()() {
        return nr;
    }
};

struct node {
    int data;
    node *left, *right;

    node(int d) : data(d), left(nullptr), right(nullptr) {}
};

node* buildTree(deque<number*> & nodes) {
    if (nodes.empty()) return nullptr;
    number* n = nodes.front();
    nodes.pop_front();
    if (n== nullptr) {
        return nullptr;
    }

    auto * nd = new node(n->nr);
    nd->left = buildTree(nodes);
    nd->right = buildTree(nodes);

    return nd;
}

void traverse(node* n) {
    if (n == nullptr) return;
    traverse(n->left);
    cout<<n->data<<" ";
    traverse(n->right);
}

bool isSearchTree(node* node) {
    if (node == nullptr) return true;

    if (!isSearchTree(node->left))
        return false;

    if(!isSearchTree(node->right))
        return false;

    if (node->left != nullptr && node->left->data > node->data) return false;
    if (node->right != nullptr && node->right->data < node->data) return false;

    return true;
}

int main() {

    vector<number*> in = { new number(4), new number(1), nullptr, new number(3), nullptr, nullptr, new number(7), new number(6), nullptr, nullptr, nullptr };

    deque<number*> d(in.begin(), in.end());

    node* tree = buildTree(d);

    traverse(tree);
    cout<<endl;

    cout<<isSearchTree(tree);
    return 0;
}