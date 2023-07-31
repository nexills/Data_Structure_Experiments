
#include <fstream>
#include <iostream>
#include <string>

// an implementation of a simple binary, AVL tree
// where the run time of add is guaranteed to be O(log n) at worst
// modified from CMPT225, assignment 5

class BST_AVL {

    struct Node {
        int value;
        Node *left;
        Node *right;
        Node* parent;
        // stores the height of the AVL for easy access
        int height;
    };

    Node *root = nullptr;

    // helper recursive functions

    bool is_sorted_recursive(Node* node) const {
        // this function check if the tree is sorted recursively
        if (!node) return true; // base case
        if (!node->left && !node->right) return true; // another base case
        // check if left, right are correct
        if (node->left && node->left->value >= node->value) return false;
        if (node->right && node->right->value <= node->value) return false;
        // recursively check if left and right subtree
        if (node->left && node->right) {
            return is_sorted_recursive(node->left) && is_sorted_recursive(node->right);
        } 
        // check left if only have left child; same for right
        else if (node->left) return is_sorted_recursive(node->left);
        return is_sorted_recursive(node->right);
    }

    void in_order_print(Node* node) const {
        // print the tree in order
        if (!node) return;
        // print left
        in_order_print(node->left);
        // print this node
        std::cout << node->value << " ";
        // print right
        in_order_print(node->right);
        return;
    }

    int in_order_traverse(Node* node) const {
        // traverse the AVL tree in order, return the number of nodes
        if (!node) return 0; // base case
        int number = 0;
        // call left
        number += in_order_traverse(node->left);
            // each node visited is a different word; add 1
        number += 1;
        // call right and return the result
        number += in_order_traverse(node->right);
        return number;
    }

    void post_order_delete(Node* root) {
        // delete the tree post-order, called by destructor
        if (!root) return;
        post_order_delete(root->left);
        post_order_delete(root->right);
        delete root;
        return;
    }

    public:

    void add_node(int val) {
        // Adds val to the AVL. If val is already in the word list, then do nothing.
        // Otherwise add a new Node at the correct location for the word.
        // The AVL is guaranteed to be balanced after calling.
        // setup the new node
        Node* newnode = new Node;
        newnode->value = val;
        newnode->left = nullptr;
        newnode->right = nullptr;
        newnode->height = 1;
        if (!root) {
            // empty tree; set the val as root
            root = newnode;
            newnode->parent = nullptr;
            return;
        } else {
            // non-empty tree
            Node* nodeptr = root;
            Node* parentptr = root; // points to parent of nodeptr
            bool isLeft = 0; // if nodeptr is parentptr's left child
            while (nodeptr) {
                // while current node is not empty
                if (nodeptr->value > val) {
                    // if val is smaller, go left
                    parentptr = nodeptr;
                    nodeptr = nodeptr->left;
                    isLeft = 1;
                } else if (nodeptr->value < val) {
                    // if val is larger, go right
                    parentptr = nodeptr;
                    nodeptr = nodeptr->right;
                    isLeft = 0;
                } else {
                    // node has exact same value
                    return;
                }
            }
            // now nodeptr is null
            if (isLeft) {
                parentptr->left = newnode;
            } else {
                parentptr->right = newnode;
            }
            newnode->parent = parentptr;
        }
        // AVL balance part - this part does the following:
        // 1. if violate AVL, rotate
        // 2. correct the height of all the nodes above
        // from the newnode up until reaching the root
        // setup nodes x, y and z
        Node* z = newnode->parent;
        Node* y = nullptr;
        Node* x = nullptr;
        // left and right keep track of heights for comparison
        // to avoid seg fault comparing with nullptr
        int left = 0;
        int right = 0;
        while (z != nullptr) {
            // 1. check if AVL is violated
            // if z has left/right child, set left & right height
            left = 0;
            right = 0;
            if (z->left) left = z->left->height;
            if (z->right) right = z->right->height;
            // check conditions
            if (left - right > 1) {
                // left higher than right: unbalanced
                // obviously y is left child of z
                y = z->left;
                // if y has left/right child, set left & right height
                left = 0;
                right = 0;
                if (y->left) left = y->left->height;
                if (y->right) right = y->right->height;
                if (left > right) {
                    // single rotation case
                    x = y->left;
                    // adjust parent if z has a parent
                    if (z->parent) {
                        if (z->parent->left == z) {
                            // z is left child
                            z->parent->left = y;
                        } else {
                            // z is right child
                            z->parent->right = y;
                        }
                    }
                    // set the pointers right
                    y->parent = z->parent;
                    z->left = y->right;
                    if (z->left) z->left->parent = z;
                    y->right = z;
                    z->parent = y;
                    if (z == root) root = y;
                } else {
                    // double rotation case
                    x = y->right;
                    // adjust parent if z has a parent
                    if (z->parent) {
                        if (z->parent->left == z) {
                            // z is left child
                            z->parent->left = x;
                        } else {
                            // z is right child
                            z->parent->right = x;
                        }
                    }
                    // set the pointers for x, y, z
                    // also set parent pointers
                    x->parent = z->parent;
                    y->right = x->left;
                    if (y->right) y->right->parent = y;
                    z->left = x->right;
                    if (z->left) z->left->parent = z;
                    x->left = y;
                    x->right = z;
                    y->parent = x;
                    z->parent = x;
                    if (z == root) root = x;
                }
            } else if (right - left > 1) {
                // left lower than right: unbalanced
                // obviously y is right child of z
                y = z->right;
                // if y has left/right child, set left & right height
                left = 0;
                right = 0;
                if (y->left) left = y->left->height;
                if (y->right) right = y->right->height;
                if (left < right) {
                    // single rotation case
                    x = y->right;
                    // adjust parent if z has a parent
                    if (z->parent) {
                        if (z->parent->left == z) {
                            // z is left child
                            z->parent->left = y;
                        } else {
                            // z is right child
                            z->parent->right = y;
                        }
                    }
                    // set pointers
                    y->parent = z->parent;
                    z->right = y->left;
                    if (z->right) z->right->parent = z;
                    y->left = z;
                    z->parent = y;
                    if (z == root) root = y;
                } else {
                    // double rotation case
                    x = y->left;
                    // adjust parent if z has a parent
                    if (z->parent) {
                        if (z->parent->left == z) {
                            // z is left child
                            z->parent->left = x;
                        } else {
                            // z is right child
                            z->parent->right = x;
                        }
                    }
                    // set pointers
                    x->parent = z->parent;
                    y->left = x->right;
                    if (y->left) y->left->parent = y;
                    z->right = x->left;
                    if (z->right) z->right->parent = z;
                    x->right = y;
                    x->left = z;
                    y->parent = x;
                    z->parent = x;
                    if (z == root) root = x;
                }
            }
            // 2. correct height
            if (x) {
                // if AVL rotation has changed the height of x,
                // then height of x needs to be corrected
                if (x->left && x->right) x->height = std::max(x->left->height, x->right->height)+1;
                else if (x->left) x->height = x->left->height+1;
                else if (x->right) x->height = x->right->height+1;
                else x->height = 1;
            }
            if (y) {
                // if AVL rotation has changed the height of y,
                // then height of y needs to be corrected
                if (y->left && y->right) y->height = std::max(y->left->height, y->right->height)+1;
                else if (y->left) y->height = y->left->height+1;
                else if (y->right) y->height = y->right->height+1;
                else y->height = 1;
            }
            if (z) {
                // if AVL rotation has changed the height of z,
                // or that a new node was inserted below z
                // then height of z needs to be corrected
                if (z->left && z->right) z->height = std::max(z->left->height, z->right->height)+1;
                else if (z->left) z->height = z->left->height+1;
                else if (z->right) z->height = z->right->height+1;
                else z->height = 1;
            }
            // reset x, y and set z to its parent
            x = nullptr;
            y = nullptr;
            z = z->parent;
        }
    } // add_word

    // constructor
    BST_AVL() {
        // set root to nullptr
        root = nullptr;
    }
    
    // destructor
    ~BST_AVL() {
        // call delete function
        post_order_delete(root);
    }

    int num_nodes() const {
        // Returns the number of nodes in the word list.
        return in_order_traverse(root);
    }

    bool is_sorted() const {
        // Returns true if the numbers are arranged from small to large, ie. sorted
        if (!root) return true; // empty tree is always sorted
        return is_sorted_recursive(root);
    }

    void print_in_order() const {
        // Prints the numbers of the tree in order
        in_order_print(root);
    }
}; // class BST_AVL

