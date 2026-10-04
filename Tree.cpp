#include "Tree.h"

using namespace std;

TreeNode::TreeNode(Resource res) {
    data = res;
    left = nullptr;
    right = nullptr;
}

BST::BST() {
    root = nullptr;
}

BST::~BST() {
    destroyTree(root);
}

void BST::destroyTree(TreeNode* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

void BST::insert(Resource res) {
    root = insertRec(root, res);
}

TreeNode* BST::insertRec(TreeNode* node, Resource res) {
    if (node == nullptr) {
        return new TreeNode(res);
    }
    if (res.getResourceID() < node->data.getResourceID()) {
        node->left = insertRec(node->left, res);
    } else if (res.getResourceID() > node->data.getResourceID()) {
        node->right = insertRec(node->right, res);
    }
    return node;
}

Resource* BST::search(string id) const {
    TreeNode* result = searchRec(root, id);
    if (result != nullptr) {
        return &(result->data);
    }
    return nullptr;
}

TreeNode* BST::searchRec(TreeNode* node, string id) const {
    if (node == nullptr || node->data.getResourceID() == id) {
        return node;
    }
    if (node->data.getResourceID() > id) {
        return searchRec(node->left, id);
    }
    return searchRec(node->right, id);
}

void BST::displayInorder() const {
    inorderRec(root);
    cout << endl;
}

void BST::inorderRec(TreeNode* node) const {
    if (node != nullptr) {
        inorderRec(node->left);
        cout << node->data.getResourceID() << " ";
        inorderRec(node->right);
    }
}

void BST::displayPreorder() const {
    preorderRec(root);
    cout << endl;
}

void BST::preorderRec(TreeNode* node) const {
    if (node != nullptr) {
        cout << node->data.getResourceID() << " ";
        preorderRec(node->left);
        preorderRec(node->right);
    }
}

void BST::displayPostorder() const {
    postorderRec(root);
    cout << endl;
}

void BST::postorderRec(TreeNode* node) const {
    if (node != nullptr) {
        postorderRec(node->left);
        postorderRec(node->right);
        cout << node->data.getResourceID() << " ";
    }
}

TreeNode* BST::minValueNode(TreeNode* node) {
    TreeNode* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

void BST::deleteResource(string id) {
    root = deleteRec(root, id);
}

TreeNode* BST::deleteRec(TreeNode* node, string id) {
    if (node == nullptr) return node;

    if (id < node->data.getResourceID()) {
        node->left = deleteRec(node->left, id);
    } else if (id > node->data.getResourceID()) {
        node->right = deleteRec(node->right, id);
    } else {
        if (node->left == nullptr) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }

        TreeNode* temp = minValueNode(node->right);
        node->data = temp->data;
        node->right = deleteRec(node->right, temp->data.getResourceID());
    }
    return node;
}
