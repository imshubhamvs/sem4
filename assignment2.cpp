#include <iostream>
#include <string>

using namespace std;

// Class for a node in BST
class Node
{
    string keyword;
    string meaning;
    Node *left;
    Node *right;

public:
    Node(string key, string val)
    {
        keyword = key;
        meaning = val;
        left = nullptr;
        right = nullptr;
    }
    friend class Dictionary;
};

// Binary Search Tree class
class Dictionary
{
private:
    Node *root;

    Node *insertUtil(Node *root, string key, string val);
    Node *deleteUtil(Node *root, string key);
    Node *inSuccesor(Node *node);
    int maxComparisonsUtil(Node *root, string key, int comparisons);

public:
    Dictionary()
    {
        root = nullptr;
    }
    ~Dictionary();

    void insert(string key, string val);
    void remove(string key);
    void update(string key, string val);
    void displayInOrder();
    int maxComparisons(string key);
    void displayInOrderUtil(Node *r);
    // Menu-driven functions
    void displayMenu();
    void processChoice(int choice);
};

// Destructor to deallocate memory
Dictionary::~Dictionary()
{
    // Implement post-order traversal to delete nodes
    while (root != nullptr)
    {
        remove(root->keyword);
    }
}

// Insertion operation
Node *Dictionary::insertUtil(Node *root, string key, string val)
{
    if (root == nullptr)
    {
        return new Node(key, val);
    }

    if (key < root->keyword)
    {
        root->left = insertUtil(root->left, key, val);
    }
    else if (key > root->keyword)
    {
        root->right = insertUtil(root->right, key, val);
    }
    else
    { // Update meaning if key already exists
        root->meaning = val;
    }

    return root;
}

void Dictionary::insert(string key, string val)
{
    root = insertUtil(root, key, val);
}

// Deletion operation
Node *Dictionary::deleteUtil(Node *root, string key)
{
    if (root == nullptr)
    {
        return root;
    }

    if (key < root->keyword)
    {
        root->left = deleteUtil(root->left, key);
    }
    else if (key > root->keyword)
    {
        root->right = deleteUtil(root->right, key);
    }
    else
    {
        // Node with only one child or no child
        if (root->left == nullptr)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }

        Node *temp = inSuccesor(root->right);

        // Copy the inorder successor
        root->keyword = temp->keyword;
        root->meaning = temp->meaning;

        // Delete the inorder successor
        root->right = deleteUtil(root->right, temp->keyword);
    }
    return root;
}

Node *Dictionary::inSuccesor(Node *node)
{
    Node *current = node;
    while (current && current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

void Dictionary::remove(string key)
{
    root = deleteUtil(root, key);
}

// Update operation
void Dictionary::update(string key, string val)
{
    remove(key);      // Remove existing entry
    insert(key, val); // Insert updated entry
}

// Display in-order traversal
void Dictionary::displayInOrderUtil(Node *r)
{
    if (r != nullptr)
    {
        displayInOrderUtil(r->left);
        cout << r->keyword << " : " << r->meaning << endl;
        displayInOrderUtil(r->right);
    }
}

void Dictionary::displayInOrder()
{
    displayInOrderUtil(root);
}

// Maximum comparisons required for finding a keyword
int Dictionary::maxComparisonsUtil(Node *root, string key, int comparisons)
{
    if (root == nullptr)
    {
        return comparisons;
    }

    if (key == root->keyword)
    {
        return comparisons + 1;
    }
    else if (key < root->keyword)
    {
        return maxComparisonsUtil(root->left, key, comparisons + 1);
    }
    else
    {
        return maxComparisonsUtil(root->right, key, comparisons + 1);
    }
}

int Dictionary::maxComparisons(string key)
{
    return maxComparisonsUtil(root, key, 0);
}

// Menu-driven functions
void Dictionary::displayMenu()
{
    cout << "Dictionary Menu:\n";
    cout << "1. Add new entry\n";
    cout << "2. Delete an entry\n";
    cout << "3. Update an entry\n";
    cout << "4. Display dictionary\n";
    cout << "5. Find max comparisons for a keyword\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

void Dictionary::processChoice(int choice)
{
    string key, val;
    switch (choice)
    {
    case 1:
        cout << "Enter keyword to add: ";
        cin >> key;
        cout << "Enter meaning: ";
        cin.ignore();
        getline(cin, val);
        insert(key, val);
        cout << "Entry added successfully.\n";
        break;
    case 2:
        cout << "Enter keyword to delete: ";
        cin >> key;
        remove(key);
        cout << "Entry deleted successfully.\n";
        break;
    case 3:
        cout << "Enter keyword to update: ";
        cin >> key;
        cout << "Enter new meaning: ";
        cin.ignore();
        getline(cin, val);
        update(key, val);
        cout << "Entry updated successfully.\n";
        break;
    case 4:
        cout << "Dictionary contents:\n";
        displayInOrder();
        break;
    case 5:
        cout << "Enter keyword to find max comparisons: ";
        cin >> key;
        cout << "Maximum comparisons required for finding '" << key << "': " << maxComparisons(key) << endl;
        break;
    case 6:
        cout << "Exiting...\n";
        exit(0);
    default:
        cout << "Invalid choice. Please enter a valid option.\n";
    }
}

// Main function
int main()
{
    Dictionary dict;

    while (true)
    {
        dict.displayMenu();
        int choice;
        cin >> choice;
        dict.processChoice(choice);
        cout << endl;
    }

    return 0;
}
