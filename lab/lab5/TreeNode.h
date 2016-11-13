//
// Created by CharlieHu on 2016-11-12.
//

#ifndef LAB5_TREENODE_H
#define LAB5_TREENODE_H

#include "DBentry.h"

class TreeNode {
private:
    DBentry *entryPtr;
    TreeNode *parent;
    TreeNode *left;
    TreeNode *right;

public:
    // A useful constructor
    TreeNode(DBentry *_entryPtr);

    // the destructor
    ~TreeNode();

    // getter and setters
    DBentry *getEntryPtr() const;

    TreeNode *getLeft() const;

    void setLeft(TreeNode *left);

    TreeNode *getRight() const;

    void setRight(TreeNode *right);

    TreeNode *getParent() const;

    void setParent(TreeNode *parent);

};


#endif //LAB5_TREENODE_H
