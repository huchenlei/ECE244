//
// Created by CharlieHu on 2016-11-12.
//

#include "TreeNode.h"

TreeNode::TreeNode(DBentry *_entryPtr) : entryPtr(_entryPtr),
                                         left(NULL), right(NULL), parent(NULL) {}

TreeNode::~TreeNode() {
    delete entryPtr;
}

DBentry *TreeNode::getEntryPtr() const {
    return entryPtr;
}

TreeNode *TreeNode::getLeft() const {
    return left;
}

void TreeNode::setLeft(TreeNode *left) {
    TreeNode::left = left;
}

TreeNode *TreeNode::getRight() const {
    return right;
}

void TreeNode::setRight(TreeNode *right) {
    TreeNode::right = right;
}

TreeNode *TreeNode::getParent() const {
    return parent;
}

void TreeNode::setParent(TreeNode *parent) {
    TreeNode::parent = parent;
}
