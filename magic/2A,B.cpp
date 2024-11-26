#include <iostream>
#include <cctype>
#include <stack>
#include <string>
//((A + B) – C * (D / E)) + F
//AB+CDE/*-F+  
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char val) : data(val), left(nullptr), right(nullptr) {}
};

Node* constructFromPrefix(const string& expr) {
    stack<Node*> st;
    for (int i = expr.length() - 1; i >= 0; --i) {
        if (isalnum(expr[i])) {
            st.push(new Node(expr[i]));
        } else {
            Node* node = new Node(expr[i]);
            node->left = st.top(); st.pop();
            node->right = st.top(); st.pop();
            st.push(node);
        }
    }
    return st.top();
}

Node* constructFromPostfix(const string& expr) {
    stack<Node*> st;
    for (char ch : expr) {
        if (isalnum(ch)) {
            st.push(new Node(ch));
        } else {
            Node* node = new Node(ch);
            node->right = st.top(); st.pop();
            node->left = st.top(); st.pop();
            st.push(node);
        }
    }
    return st.top();
}
void inOrderTraversal(Node* root) {
    stack<Node*> st;
    Node* current = root;
    while (current != nullptr || !st.empty()) {
        while (current != nullptr) {
            st.push(current);
            current = current->left;
        }
        current = st.top(); st.pop();
        cout << current->data << " ";
        current = current->right;
    }
}

void preOrderTraversal(Node* root) {
    if (root == nullptr) return;
    stack<Node*> st;
    st.push(root);
    while (!st.empty()) {
        Node* current = st.top(); st.pop();
        cout << current->data << " ";
        if (current->right) st.push(current->right);
        if (current->left) st.push(current->left);
    }
}

void postOrderTraversal(Node* root) {
    if (root == nullptr) return;
    stack<Node*> st1, st2;
    st1.push(root);
    while (!st1.empty()) {
        Node* current = st1.top(); st1.pop();
        st2.push(current);
        if (current->left) st1.push(current->left);
        if (current->right) st1.push(current->right);
    }
    while (!st2.empty()) {
        cout << st2.top()->data << " ";
        st2.pop();
    }
}

// Helper function to convert infix to postfix expression
int precedence(char ch) {
    if (ch == '+' || ch == '-') return 1;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '^') return 3;
    return 0;
}

string infixToPostfix(const string& expr) {
    stack<char> st;
    string postfix;
    bool expectOperand = true; 

    for (size_t i = 0; i < expr.length(); ++i) {
        char ch = expr[i];

        if (isalnum(ch)) {
            postfix += ch;
            expectOperand = false; 
        } else if (ch == '(') {
            st.push(ch);
            expectOperand = true; 
        } else if (ch == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            st.pop(); 
            expectOperand = false; 
        } else { 
            if (ch == '-' && expectOperand) {
                
                postfix += '0'; 
            }
            while (!st.empty() && precedence(st.top()) >= precedence(ch)) {
                postfix += st.top();
                st.pop();
            }
            st.push(ch);
            expectOperand = true; // After operator, expect an operand
        }
    }

    while (!st.empty()) {
        postfix += st.top();
        st.pop();
    }

    return postfix;
}

int main() {
    string expression;
    char choice;
    int trav;

    cout << "Enter the expression: ";
    cin >> expression;

    cout << "Is the expression prefix (p), infix (i), or postfix (o)? ";
    cin >> choice;

    Node* root = nullptr;

    if (choice == 'p') {
        root = constructFromPrefix(expression);
    } else if (choice == 'o') {
        root = constructFromPostfix(expression);
    } else if (choice == 'i') {
        string postfix = infixToPostfix(expression);
        root = constructFromPostfix(postfix);
    } else {
        cout << "Invalid choice!" << endl;
        return 1;
    }

    while (true) {
        cout << "\nChoose from the following options:\n";
        cout << "1. In-order traversal\n";
        cout << "2. Pre-order traversal\n";
        cout << "3. Post-order traversal\n";
        cout << "4. Exit\n";
        cin >> trav;
        
        switch (trav) {
            case 1:
                cout << "In-order traversal: ";
                inOrderTraversal(root);
                break;
            case 2:
                cout << "Pre-order traversal: ";
                preOrderTraversal(root);
                break;
            case 3:
                cout << "Post-order traversal: ";
                postOrderTraversal(root);
                break;
            case 4:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please select a valid option." << endl;
                break;
        }
    }
    return 0;
}


