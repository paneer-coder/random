#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

class node {
public:
    int data;
    node* left;
    node* right;

    node(int val) {
        this->data = val;
        this->left = nullptr;
        this->right = nullptr;
    }
};

node* buildTree() {
    cout << "Enter the data (-1 to stop): ";
    int data;
    cin >> data;

    if (data == -1) {
        return nullptr;
    }

    node* root = new node(data);

    cout << "Enter data for inserting in left of " << data << endl;
    root->left = buildTree();
    cout << "Enter data for inserting in right of " << data << endl;
    root->right = buildTree();

    return root;
}

void levelOrderTraversal(node* root) {
    if (root == nullptr) {
        return;
    }

    queue<node*> q;
    q.push(root);
    q.push(nullptr);

    while (!q.empty()) {
        node* temp = q.front();
        q.pop();

        if (temp == nullptr) {
            cout << endl;
            if (!q.empty()) {
                q.push(nullptr);
            }
        } else {
            cout << temp->data << " ";
            if (temp->left) {
                q.push(temp->left);
            }
            if (temp->right) {
                q.push(temp->right);
            }
        }
    }
}

void inorder(node* root) {
    if (root == nullptr) {
        return;
    }

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void displayLeaves(node* root) {
    if (root == nullptr) {
        return;
    }

    if (root->left == nullptr && root->right == nullptr) {
        cout << root->data << " ";
    }

    displayLeaves(root->left);
    displayLeaves(root->right);
}

node* copyTree(node* root) {
    if (root == nullptr) {
        return nullptr;
    }

    node* newRoot = new node(root->data);
    newRoot->left = copyTree(root->left);
    newRoot->right = copyTree(root->right);
    return newRoot;
}

int depth(node* root) {
    if (root == nullptr) {
        return 0;
    }

    int leftDepth = depth(root->left);
    int rightDepth = depth(root->right);

    return max(leftDepth, rightDepth) + 1;
}

int main() {
    node* root = nullptr;
    char choice;

    do {
        cout << "\nMenu:\n";
        cout << "a. Insert a new node\n";
        cout << "b. Display level order traversal\n";
        cout << "c. Find depth of the tree\n";
        cout << "d. Display leaf nodes\n";
        cout << "e. Create a copy of the tree\n";
        cout << "f. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 'a': {
                cout << "Creating Binary Tree:\n";
                root = buildTree();
                break;
            }
            case 'b': {
                if (root == nullptr) {
                    cout << "Tree is empty. Please create a tree first.\n";
                } else {
                    cout << "Level Order Traversal:\n";
                    levelOrderTraversal(root);
                }
                break;
            }
            case 'c': {
                if (root == nullptr) {
                    cout << "Tree is empty. Please create a tree first.\n";
                } else {
                    cout << "Depth of the Tree: " << depth(root) << endl;
                }
                break;
            }
            case 'd': {
                if (root == nullptr) {
                    cout << "Tree is empty. Please create a tree first.\n";
                } else {
                    cout << "Leaf Nodes: ";
                    displayLeaves(root);
                    cout << endl;
                }
                break;
            }
            case 'e': {
                if (root == nullptr) {
                    cout << "Tree is empty. Please create a tree first.\n";
                } else {
                    cout << "Copying Tree:\n";
                    node* copiedTree = copyTree(root);
                    cout << "Level Order Traversal of Copied Tree:\n";
                    levelOrderTraversal(copiedTree);
                }
                break;
            }
            case 'f': {
                cout << "Exiting...\n";
                break;
            }
            default: {
                cout << "Invalid choice. Please enter again.\n";
                break;
            }
        }
    } while (choice != 'f');

    return 0;
}

