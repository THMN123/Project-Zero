#ifndef TREE_H
#define TREE_H

#include "Resource.h"
#include <iostream>

using namespace std;

class TreeNode {
public:
    Resource data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Resource res);
};

class BST {
private:
    TreeNode* root;

    TreeNode* insertRec(TreeNode* node, Resource res);
    TreeNode* searchRec(TreeNode* node, string id) const;
    void inorderRec(TreeNode* node) const;
    void preorderRec(TreeNode* node) const;
    void postorderRec(TreeNode* node) const;
    TreeNode* deleteRec(TreeNode* node, string id);
    TreeNode* minValueNode(TreeNode* node);
    void destroyTree(TreeNode* node);

public:
    BST();
    ~BST();

    void insert(Resource res);
    Resource* search(string id) const;
    void deleteResource(string id);
    
    // Traversals
    void displayInorder() const;
    void displayPreorder() const;
    void displayPostorder() const;
};

#endif // TREE_H
