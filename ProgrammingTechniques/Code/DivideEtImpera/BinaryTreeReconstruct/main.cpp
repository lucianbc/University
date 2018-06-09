#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct node {
    int data;
    node* left, * right;

    node(int data) : data(data), left(nullptr), right(nullptr) {}
};


node* readTree() {
    auto* ll = new node(4);
    auto* lr = new node(5);
    auto* l = new node(2);
    auto* root = new node(1);
    auto* r = new node(3);
    auto* rl = new node(6);
    auto* rr = new node(7);

    l->left = ll;
    l->right = lr;
    r->left = rl;
    r->right = rr;
    root->left = l;
    root->right = r;
    return root;
}

struct input {
    vector<int> inorder;
    vector<int> postorder;
};

input read() {
    return {{1, 4, 3, 2}, {4, 1, 2, 3}};
}

node* build_tree(const vector<int> & inorder, const vector<int> & postorder, int & rootIndex, int inorderLeft, int inorderRight, const unordered_map<int, int> & inorderPos) {
    if (inorderLeft > inorderRight)
        return nullptr;
    int data = postorder[rootIndex];
    int dataIndex = inorderPos.at(data);

    rootIndex -= 1;
    auto * right = build_tree(inorder, postorder, rootIndex, dataIndex + 1, inorderRight, inorderPos);
    if (right == nullptr) rootIndex += 1;
    rootIndex -= 1;
    auto * left = build_tree(inorder, postorder, rootIndex, inorderLeft, dataIndex - 1, inorderPos);
    if (left == nullptr) rootIndex += 1;
    auto * tree = new node(data);
    tree->left = left;
    tree->right = right;
    return tree;
}

void print_inorder(node * n) {
    if (n != nullptr) {
        print_inorder(n->left);
        cout<<n->data<<" ";
        print_inorder(n->right);
    }
}

void print_postorder(node * n) {
    if (n != nullptr) {
        print_postorder(n->left);
        print_postorder(n->right);
        cout<<n->data<<" ";
    }
}

void print_preorder(node * n) {
    if (n != nullptr) {
        cout<<n->data<<" ";
        print_preorder(n->left);
        print_preorder(n->right);
    }
}

int main() {

    input in = read();

    unordered_map<int, int> inorder_index;
    for (int i = 0; i < in.inorder.size(); i++) {
        inorder_index[in.inorder[i]] = i;
    }

    int root_poz = in.postorder.size() - 1;

    node* t = build_tree(in.inorder, in.postorder, root_poz, 0, in.inorder.size() - 1, inorder_index);

    print_preorder(t);
    cout<<endl;
    print_postorder(t);
    cout<<endl;
    print_inorder(t);
    cout<<endl;

    return 0;
}