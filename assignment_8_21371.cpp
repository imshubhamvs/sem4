#include <iostream>
#include <climits>

using namespace std;

class TreeNode {
public:
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int key) : key(key), left(nullptr), right(nullptr) {}
};

class BST {
private:
    TreeNode* root;
    int n;
    int** dp;
    TreeNode*** roots;

    TreeNode* newTreeNode(int key) {
        return new TreeNode(key);
    }

    TreeNode* constructBSTUtil(int keys[], int i, int j) {
        if (i > j) {
            return nullptr;
        }

        if (dp[i][j] != -1) {
            return roots[i][j] ? roots[i][j] : nullptr;
        }

        int minCost = INT_MAX;
        int minRoot = -1;

        int sumP = 0;
        for (int k = i; k <= j; ++k) {
            sumP += keys[k];
        }

        for (int r = i; r <= j; ++r) {
            TreeNode* leftSubtree = constructBSTUtil(keys, i, r - 1);
            TreeNode* rightSubtree = constructBSTUtil(keys, r + 1, j);

            int cost = (leftSubtree ? dp[i][r - 1] : 0) + (rightSubtree ? dp[r + 1][j] : 0) + sumP;

            if (cost < minCost) {
                minCost = cost;
                minRoot = r;
            }
        }

        dp[i][j] = minCost;
        roots[i][j] = newTreeNode(keys[minRoot]);

        if (i < j) {
            roots[i][j]->left = constructBSTUtil(keys, i, minRoot - 1);
            roots[i][j]->right = constructBSTUtil(keys, minRoot + 1, j);
        }

        return roots[i][j];
    }

    void deleteDP() {
        for (int i = 0; i < n; ++i) {
            delete[] dp[i];
            delete[] roots[i];
        }
        delete[] dp;
        delete[] roots;
    }

public:
    BST(int n) : root(nullptr), n(n) {
        dp = new int*[n];
        roots = new TreeNode**[n];

        for (int i = 0; i < n; ++i) {
            dp[i] = new int[n];
            roots[i] = new TreeNode*[n];

            for (int j = 0; j < n; ++j) {
                dp[i][j] = -1;
                roots[i][j] = nullptr;
            }
        }
    }

    ~BST() {
        deleteDP();
    }

    void constructBST(int keys[]) {
        root = constructBSTUtil(keys, 0, n - 1);
    }

    void printInorder() {
        printInorderUtil(root);
        cout << endl;
    }

    void findMaxComparisons(int key) {
        int maxComparisons = 0;
        findMaxComparisonsUtil(root, key, maxComparisons, 0);
        cout << "Maximum comparisons required: " << maxComparisons << endl;
    }

private:
    void printInorderUtil(TreeNode* root) {
        if (root == nullptr) {
            return;
        }

        printInorderUtil(root->left);
        cout << root->key << " ";
        printInorderUtil(root->right);
    }

    void findMaxComparisonsUtil(TreeNode* root, int key, int& maxComparisons, int comparisons) {
        if (root == nullptr) {
            maxComparisons = max(maxComparisons, comparisons);
            return;
        }

        comparisons++;

        if (key == root->key) {
            maxComparisons = max(maxComparisons, comparisons);
        } else if (key < root->key) {
            findMaxComparisonsUtil(root->left, key, maxComparisons, comparisons);
        } else {
            findMaxComparisonsUtil(root->right, key, maxComparisons, comparisons);
        }
    }
};

int main() {
    int n;
    cout << "Enter the number of keys: ";
    cin >> n;

    int* keys = new int[n];
    cout << "Enter the keys: ";
    for (int i = 0; i < n; ++i) {
        cin >> keys[i];
    }

    BST bst(n);
    bst.constructBST(keys);

    cout << "Inorder traversal of the constructed BST:" << endl;
    bst.printInorder();

    int key;
    cout << "Enter the key to find maximum comparisons: ";
    cin >> key;
    bst.findMaxComparisons(key);

    delete[] keys;

    return 0;
}
