#include <bits/stdc++.h>
using namespace std;

// traversal using recursion
// traversal using iteration

// 1-> Inorder 
// 2-> preorder
// 3-> postorder (using one stack & using two stack)

// 4-> zigzag   (https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/)
// 5-> vertical (https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/)
// 6-> boundary (https://www.geeksforgeeks.org/problems/boundary-traversal-of-binary-tree/1)

// 7-> morris traversal(Inorder) - (https://leetcode.com/problems/binary-tree-inorder-traversal/)
// 8-> morris traversal(Preorder) 


class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

void inorder(Node* root) {
    if (root == NULL) {
        cout << "Empty tree";
        return;
    }

    stack<Node*> st;
    Node* curr = root;

    while (curr != NULL || !st.empty()) {
        // 1. Reach the leftmost node
        while (curr != NULL) {
            st.push(curr);
            curr = curr->left;
        }

        // 2. Visit the top node
        curr = st.top();
        st.pop();
        cout << curr->data << " ";

        // 3. Go to the right subtree
        curr = curr->right;
    }
}

void preorder(Node* root) {
    if (root == NULL) {
        cout << "NO tree";
        return;
    }

    stack<Node*> st;
    Node* curr = root;

    while (!st.empty() || curr != NULL) {
        while (curr != NULL) {
            cout << curr->data << " ";
            st.push(curr);
            curr = curr->left;
        }

        curr = st.top();
        st.pop();
        curr = curr->right;
    }
}

void postorderUsingTwoStack(Node* root) {
    if (root == NULL) {
        cout << "NO tree";
        return;
    }

    stack<Node*> st1, st2;
    st1.push(root);

    while (!st1.empty()) {
        Node* curr = st1.top();
        st1.pop();
        st2.push(curr);

        if (curr->left) st1.push(curr->left);
        if (curr->right) st1.push(curr->right);
    }

    while (!st2.empty()) {
        cout << st2.top()->data << " ";
        st2.pop();
    }
}

void postorderUsingOneeStack(Node* root){
    if (root == NULL) {
        cout << "NO tree";
        return;
    }

    stack<Node*> st;
    Node* curr = root;
    Node* lastVisited = NULL;

    while (!st.empty() || curr != NULL) {
        if (curr != NULL) {
            st.push(curr);
            curr = curr->left;
        } 
        else {
            Node* peekNode = st.top();
            // If right child exists and traversing node from left child, go right
            if (peekNode->right != NULL && lastVisited != peekNode->right) {
                curr = peekNode->right;
            } 
            else {
                cout << peekNode->data << " ";
                lastVisited = peekNode;
                st.pop();
            }
        }
    }
}


int main() {
    /*
            1
           / \
          2   3
         / \
        4   5
    */
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    cout << "Inorder Traversal: ";
    inorder(root);
    cout << endl;

    
    cout << "Preorder Traversal: ";
    preorder(root);
    cout << endl;
     
    cout << "postorder Traversal: ";
    // postorderUsingTwoStack(root);
    postorderUsingOneeStack(root);
    cout << endl;
    return 0;
}
