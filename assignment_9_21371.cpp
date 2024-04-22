#include <iostream>

using namespace std;

struct Node {
    string key;
    string meaning;
    Node* left;
    Node* right;
    int height;

    Node(string key, string meaning) : key(key), meaning(meaning), left(nullptr), right(nullptr), height(1) {}
};

int height(Node* node) {
    return node ? node->height : 0;
}

int balanceFactor(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

void updateHeight(Node* node) {
    node->height = max(height(node->left), height(node->right)) + 1;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node* insert(Node* root, string key, string meaning, int& comparisons) {
    if (!root) {
        return new Node(key, meaning);
    }

    comparisons++;

    if (key < root->key) {
        root->left = insert(root->left, key, meaning, comparisons);
    } else if (key > root->key) {
        root->right = insert(root->right, key, meaning, comparisons);
    } else {
        root->meaning = meaning;
        return root;
    }

    updateHeight(root);

    int bf = balanceFactor(root);

    // Left Left Case
    if (bf > 1 && key < root->left->key) {
        return rightRotate(root);
    }
    // Right Right Case
    if (bf < -1 && key > root->right->key) {
        return leftRotate(root);
    }
    // Left Right Case
    if (bf > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Right Left Case
    if (bf < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node* minValueNode(Node* node) {
    Node* current = node;

    while (current->left) {
        current = current->left;
    }

    return current;
}

Node* deleteNode(Node* root, string key, int& comparisons) {
    if (!root) {
        return root;
    }

    comparisons++;

    if (key < root->key) {
        root->left = deleteNode(root->left, key, comparisons);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key, comparisons);
    } else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;

            if (!temp) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }

            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->key, comparisons);
        }
    }

    if (!root) {
        return root;
    }

    updateHeight(root);

    int bf = balanceFactor(root);

    // Left Left Case
    if (bf > 1 && balanceFactor(root->left) >= 0) {
        return rightRotate(root);
    }
    // Left Right Case
    if (bf > 1 && balanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Right Right Case
    if (bf < -1 && balanceFactor(root->right) <= 0) {
        return leftRotate(root);
    }
    // Right Left Case
    if (bf < -1 && balanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorder(Node* root) {
    if (!root) {
        return;
    }

    inorder(root->left);
    cout << root->key << " : " << root->meaning << endl;
    inorder(root->right);
}

void reverseInorder(Node* root) {
    if (!root) {
        return;
    }

    reverseInorder(root->right);
    cout << root->key << " : " << root->meaning << endl;
    reverseInorder(root->left);
}

int maxComparisons(Node* root, string key, int comparisons) {
    if (!root) {
        return comparisons;
    }

    comparisons++;

    if (key == root->key) {
        return comparisons;
    } else if (key < root->key) {
        return maxComparisons(root->left, key, comparisons);
    } else {
        return maxComparisons(root->right, key, comparisons);
    }
}

void menu(Node*& root) {
    while (true) {
        cout << "\nDictionary Operations Menu:" << endl;
        cout << "1. Add Keyword" << endl;
        cout << "2. Delete Keyword" << endl;
        cout << "3. Update Meaning" << endl;
        cout << "4. Display Data in Ascending Order" << endl;
        cout << "5. Display Data in Descending Order" << endl;
        cout << "6. Find Maximum Comparisons for Finding a Keyword" << endl;
        cout << "7. Exit" << endl;

        int choice;
        cout << "\nEnter your choice: ";
        cin >> choice;

        string key, meaning;
        int comparisons = 0;

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                cin >> key;
                cout << "Enter meaning: ";
                cin.ignore();
                getline(cin, meaning);
                root = insert(root, key, meaning, comparisons);
                cout << "Keyword added successfully!" << endl;
                break;

            case 2:
                cout << "Enter keyword to delete: ";
                cin >> key;
                root = deleteNode(root, key, comparisons);
                if (root) {
                    cout << "Keyword deleted successfully!" << endl;
                } else {
                    cout << "Keyword not found!" << endl;
                }
                break;

            case 3:
                cout << "Enter keyword to update: ";
                cin >> key;
                cout << "Enter new meaning: ";
                cin.ignore();
                getline(cin, meaning);
                root = deleteNode(root, key, comparisons);
                root = insert(root, key, meaning, comparisons);
                cout << "Meaning updated successfully!" << endl;
                break;

            case 4:
                cout << "\nDictionary in Ascending Order:" << endl;
                inorder(root);
                break;

            case 5:
                cout << "\nDictionary in Descending Order:" << endl;
                reverseInorder(root);
                break;

            case 6:
                cout << "Enter keyword to find: ";
                cin >> key;
                comparisons = maxComparisons(root, key, comparisons);
                cout << "Maximum comparisons required: " << comparisons << endl;
                break;

            case 7:
                return;

            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }
}

int main() {
    Node* root = nullptr;
    menu(root);
    return 0;
}
