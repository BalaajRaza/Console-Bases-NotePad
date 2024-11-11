// Implementation of an AVL Tree to store dictionary for Notepad
#ifndef DICT_H
#define DICT_H

#include<iostream>
using namespace std;

class Node{
    public:
    string word;
    int h;
    Node *left;
    Node *right;

    Node(string w):word(w) , h(0) , left(NULL) , right(NULL){}
};

class Dict{
    Node* rotateLeft(Node* k1){
        Node* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->h = max(height(k1->left) , height(k1->right)) + 1;
        k2->h = max(height(k2->left) , height(k2->right)) + 1;
        return k2;
    }

    Node* rotateRight(Node* k1){
        Node* k2 = k1->left;
        k1->left = k2->right;
        k2->right = k1;
        k1->h = max(height(k1->left) , height(k1->right)) + 1;
        k2->h = max(height(k2->left) , height(k2->right)) + 1;
        return k2;
    }

    Node* rotateLeftRight(Node* k){
        k->left = rotateLeft(k->left);
        return rotateRight(k);
    }

    Node* rotateRightLeft(Node* k){
        k->right = rotateRight(k->right);
        return rotateLeft(k);
    }




    public:
    Node *root;

    Dict(){
        root = NULL;
    }

    int height(Node* node){
        if(node == NULL){
            return -1;
        }
        return node->h;
    }

    void insert(const string& w){
        root = insertR(root , w);
    }

    //insert helper
    Node* insertR(Node* node, const string& w){
        if(node == NULL){
            return new Node(w);
        }
        else{
            if(w < node->word){
                node->left = insertR(node->left , w);
                if(height(node->left) - height(node->right) == 2){
                    if(w < node->left->word){
                        node = rotateRight(node);
                    }
                    else{
                        node = rotateLeftRight(node);
                    }
                }
            }
            else if(w > node->word){
                node->right =insertR(node->right , w);
                if(height(node->left) - height(node->right) == -2){
                    if(w > node->right->word){
                        node = rotateLeft(node);
                    }
                    else{
                        node = rotateRightLeft(node);
                    }
                }
                
            }
            else{
                cout << "Value already exists in the tree" << endl;
            }
        }
        node->h = max(height(node->left), height(node->right))+1;
        return node;
    }

    void deleteNode(const string& w){
        root = deleteNodeH(root , w);
    }

    Node* findSuccessor(Node* node){
        while(node && node->left != NULL){
            node = node->left;
        }
        return node;
    }

    Node* deleteNodeH(Node* node , const string& w){
        if(node == NULL){
            return NULL;
        }

        if(w < node->word){
            node->left = deleteNodeH(node->left ,w);
        }
        else if(w > node->word){
            node->right = deleteNodeH(node->right ,w);
        }
        else{
            if(node->left == NULL){
                Node* backup = node->right;
                delete node;
                return backup;
            }

            else if(node->right == NULL){
                Node* backup = node->left;
                delete node;
                return backup;
            }
            
            Node* temp = findSuccessor(node->right);
            node->word = temp->word;
            node->right = deleteNodeH(node->right , temp->word);

        }
        return node;
    }

    void display(Node* node){
        if(node == NULL){
            return ;
        }
        else{
            display(node->left);
            cout<<node->word<<" ";
            display(node->right);
        }
    }

    bool find(Node* node , const string& w){
        if(node == NULL){
        return false;
        }
        if(node->word == w){
            return true;
        }
        else if(w < node->word){
            return find(node->left , w);
        }
        else if(w > node->word){
            return find(node->right , w);
        }
        return false;
    }

    int findHeight(Node* node) {
    if (node == NULL) {
        return -1; // Conventionally, height of an empty tree is -1
    }
    int leftHeight = findHeight(node->left);
    int rightHeight = findHeight(node->right);
    return max(leftHeight, rightHeight) + 1;
}

    bool isBalanced(Node* node) {
    if (node == NULL) {
        return true; // An empty tree is balanced
    }

    int leftHeight = findHeight(node->left);
    int rightHeight = findHeight(node->right);

    if (abs(leftHeight - rightHeight) > 1) {
        return false; // Not balanced
    }

    // Check recursively for every node
    return isBalanced(node->left) && isBalanced(node->right);
}
};

#endif