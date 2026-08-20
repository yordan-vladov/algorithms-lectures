#include <iostream>
using namespace std;

struct Node {
    int value;
    int height;
    Node* left;
    Node* right;

    Node(int v) : value(v), height(1), left(nullptr), right(nullptr) {}
};

int height(Node* n) { return n ? n->height : 0; }

int balanceFactor(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* insert(Node* node, int value) {
    if (!node) return new Node(value);

    if (value < node->value)
        node->left = insert(node->left, value);
    else if (value > node->value)
        node->right = insert(node->right, value);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int bf = balanceFactor(node);

    if (bf > 1 && value < node->left->value)
        return rotateRight(node);

    if (bf < -1 && value > node->right->value)
        return rotateLeft(node);

    if (bf > 1 && value > node->left->value) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (bf < -1 && value < node->right->value) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void inorder(Node* node) {
    if (!node) return;
    inorder(node->left);
    cout << node->value << " ";
    inorder(node->right);
}

int main() {
    Node* root = nullptr;

    // Вмъкваме подредени числа - без AVL това би образувало свързан списък
    int values[] = {10, 20, 30, 40, 50, 25};
    for (int v : values)
        root = insert(root, v);

    cout << "Inorder (сортиран ред): ";
    inorder(root);
    cout << endl;

    cout << "Височина на дървото: " << height(root) << endl;
    // Изход: 3 (балансирано), не 6 (изродено)

    return 0;
}
