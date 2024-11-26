#include <iostream>
#include <queue>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, int data) {
        if (node == nullptr) {
            return new Node(data);
        }
        if (data < node->data) {
            node->left = insert(node->left, data);
        } else {
            node->right = insert(node->right, data);
        }
        return node;
    }

    Node* findMin(Node* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* deleteNode(Node* node, int data) {
        if (node == nullptr) {
            return node;
        }
        if (data < node->data) {
            node->left = deleteNode(node->left, data);
        } else if (data > node->data) {
            node->right = deleteNode(node->right, data);
        } else {
            // Node with one child or no child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }

    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

    bool search(Node* node, int data) {
        if (node == nullptr) {
            return false;
        }
        if (data == node->data) {
            return true;
        } else if (data < node->data) {
            return search(node->left, data);
        } else {
            return search(node->right, data);
        }
    }

    void bfs(Node* node) {
        if (node == nullptr) return;

        queue<Node*> q;
        q.push(node);

        while (!q.empty()) {
            Node* current = q.front();
            cout << current->data << " ";
            q.pop();

            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
        cout << endl;
    }

public:
    BST() {
        root = nullptr;
    }

    void insert(int data) {
        root = insert(root, data);
    }

    void deleteNode(int data) {
        root = deleteNode(root, data);
    }

    void display() {
        inorder(root);
        cout << endl;
    }

    void search(int data) {
        if (search(root, data)) {
            cout << data << " found in the tree." << endl;
        } else {
            cout << data << " not found in the tree." << endl;
        }
    }

    void bfs() {
        bfs(root);
    }
};

int main() {
    BST tree;
    int choice, value;

    do {
        cout << "\nBinary Search Tree Operations Menu:";
        cout << "\n1. Insert";
        cout << "\n2. Delete";
        cout << "\n3. Display (In-order)";
        cout << "\n4. Search";
        cout << "\n5. BFS (Level-wise display)";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insert(value);
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                tree.deleteNode(value);
                break;
            case 3:
                cout << "In-order display: ";
                tree.display();
                break;
            case 4:
                cout << "Enter value to search: ";
                cin >> value;
                tree.search(value);
                break;
            case 5:
                cout << "BFS (Level-wise display): ";
                tree.bfs();
                break;
            case 6:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
