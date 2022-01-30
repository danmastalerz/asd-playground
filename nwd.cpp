#include <iostream>
#include <numeric>

// solv:
// No drzewa zrownowazone, w wierzcholku trzymamy NWD z poddrzewa, wiec z dzieci umiemy sie updatowac
// Odpowiedz w korzeniu.
// P.S. implementacja AVL'i zajebana z: https://www.programiz.com/dsa/avl-tree

using namespace std;

class Node {
public:
    int key;
    Node *left;
    Node *right;
    int height;
    int sub_gcd;
};

int child_gcd(Node* n) {
    if (n == NULL)
        return 0;
    return n->sub_gcd;
}

// Calculate height
int height(Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// New node creation
Node *newNode(int key) {
    Node *node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    node->sub_gcd = key;
    return node;
}

// Rotate right
Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left),
                    height(y->right)) +
                1;
    y->sub_gcd = gcd(y->key, gcd(child_gcd(y->left), child_gcd(y->right)));

    x->height = max(height(x->left),
                    height(x->right)) +
                1;
    x->sub_gcd = gcd(x->key, gcd(child_gcd(x->left), child_gcd(x->right)));
    return x;
}

// Rotate left
Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left),
                    height(x->right)) +
                1;
    x->sub_gcd = gcd(x->key, gcd(child_gcd(x->left), child_gcd(x->right)));

    y->height = max(height(y->left),
                    height(y->right)) +
                1;
    y->sub_gcd = gcd(y->key, gcd(child_gcd(y->left), child_gcd(y->right)));
    return y;
}

// Get the balance factor of each node
int getBalanceFactor(Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) -
           height(N->right);
}

// Insert a node
Node *insertNode(Node *node, int key) {
    // Find the correct postion and insert the node
    if (node == NULL)
        return (newNode(key));
    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left),
                           height(node->right));
    node->sub_gcd = gcd(node->key, gcd(child_gcd(node->left), child_gcd(node->right)));

    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1) {
        if (key < node->left->key) {
            return rightRotate(node);
        } else if (key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    if (balanceFactor < -1) {
        if (key > node->right->key) {
            return leftRotate(node);
        } else if (key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}

Node *nodeWithMimumValue(Node *node) {
    Node *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

Node *deleteNode(Node *root, int key) {
    if (root == NULL)
        return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == NULL) ||
            (root->right == NULL)) {
            Node *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            Node *temp = nodeWithMimumValue(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right,
                                     temp->key);
        }
    }

    if (root == NULL)
        return root;

    // Update the balance factor of each node and
    // balance the tree
    root->height = 1 + max(height(root->left),
                           height(root->right));
    root->sub_gcd = gcd(root->key, gcd(child_gcd(root->left), child_gcd(root->right)));

    int balanceFactor = getBalanceFactor(root);
    if (balanceFactor > 1) {
        if (getBalanceFactor(root->left) >= 0) {
            return rightRotate(root);
        } else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balanceFactor < -1) {
        if (getBalanceFactor(root->right) <= 0) {
            return leftRotate(root);
        } else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

int get_gcd(Node *root) {
    if (root == nullptr)
        return 1;
    return root->sub_gcd;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;

    Node *t = NULL;

    char op;
    int v;
    for (int i = 0; i < n; ++i) {
        cin >> op >> v;
        if (op == '+') {
            t = insertNode(t, v);
        }
        else {
            t = deleteNode(t, v);
        }
        cout << get_gcd(t) << '\n';
    }

    return 0;
}

