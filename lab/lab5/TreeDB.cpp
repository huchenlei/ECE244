//
// Created by CharlieHu on 2016-11-12.
//

#include "TreeDB.h"

// initialize static member field
int TreeDB::probesCount = 0;

TreeDB::TreeDB() : root(NULL) {}

TreeDB::TreeDB(TreeNode *root) : root(root) {}

TreeDB::~TreeDB() {
}

bool TreeDB::insert(DBentry *newEntry) {
    // special case when the DB is empty
    if (root == NULL) {
        root = new TreeNode(newEntry);
        return true;
    }

    int compareResult = root->getEntryPtr()->getName().compare(newEntry->getName());
    if (compareResult == 0) {
        cout << "Error: entry already exists" << endl;
        return false;
    } else if (compareResult > 0) {
        // go to left side
        if (root->getLeft() == NULL) {
            TreeNode *newNode = new TreeNode(newEntry);
            root->setLeft(newNode);
            newNode->setParent(root);
            return true;
        }
        TreeDB subTree(root->getLeft());
        return subTree.insert(newEntry);
    } else if (compareResult < 0) {
        // go to right side
        if (root->getRight() == NULL) {
            TreeNode *newNode = new TreeNode(newEntry);
            root->setRight(newNode);
            newNode->setParent(root);
            return true;
        }
        TreeDB subTree(root->getRight());
        return subTree.insert(newEntry);
    }
}

DBentry *TreeDB::find(const string name) {
    TreeNode *treeNode = findNode(name);
    if (treeNode != NULL) {
        return treeNode->getEntryPtr();
    } else {
        cout << "Error: entry does not exist" << endl;
        return NULL;
    }
}

TreeNode *TreeDB::findNode(const string name) {
    if (root == NULL)
        return NULL;
    TreeNode *result = NULL;
    int compareResult = root->getEntryPtr()->getName().compare(name);
    if (compareResult == 0) {
        probesCount++;
        result = root;
    } else if (compareResult > 0) {
        // go to left side(root > name)
        TreeDB subTree(root->getLeft());
        probesCount++;
        result = subTree.findNode(name);
    } else if (compareResult < 0) {
        // go to right side(root < name)
        TreeDB subTree(root->getRight());
        probesCount++;
        result = subTree.findNode(name);
    }
    return result;
}

bool TreeDB::remove(const string name) {
    TreeNode *nodeToRemove = findNode(name);
    if (nodeToRemove == NULL)
        return false;

    TreeNode *parentNode = nodeToRemove->getParent();
    if (nodeToRemove->getLeft() == NULL && nodeToRemove->getRight() == NULL) {
        // the node is leaf and is not root
        if (parentNode != NULL) {
            if (parentNode->getRight() == nodeToRemove) {
                parentNode->setRight(NULL);
            } else {
                parentNode->setLeft(NULL);
            }
        } else {
            root = NULL;
        }
    } else if (nodeToRemove->getLeft() == NULL) {
        // the node has right branch and is not root
        if (parentNode != NULL) {
            if (parentNode->getRight() == nodeToRemove) {
                // node to remove is the right branch of the parent node
                parentNode->setRight(nodeToRemove->getRight());
            } else {
                parentNode->setLeft(nodeToRemove->getRight());
            }
        } else {
            root = nodeToRemove->getRight();
        }
        nodeToRemove->getRight()->setParent(parentNode);


    } else if (nodeToRemove->getRight() == NULL) {
        // the node has left branch and is not root
        if (parentNode != NULL) {
            if (parentNode->getRight() == nodeToRemove) {
                parentNode->setRight(nodeToRemove->getLeft());
            } else {
                parentNode->setLeft(nodeToRemove->getLeft());
            }
        } else {
            root = nodeToRemove->getLeft();
        }
        nodeToRemove->getLeft()->setParent(parentNode);
    } else {
        // when node has both left branch and right branch
        // the left max node that would replace node to delete
        TreeNode *leftMaxNode = findMaxNode(nodeToRemove->getLeft());
        // the branch connect to the leftMaxNode
        TreeNode *leftNodeBranch = leftMaxNode->getLeft();
        if (leftMaxNode != nodeToRemove->getLeft()) {
            // reconnect the left branch of leftMaxNode to leftMaxNode's parent node
            leftMaxNode->getParent()->setRight(leftNodeBranch);
            leftNodeBranch->setParent(leftMaxNode->getParent());

            // reconnect leftMaxNode to the position of node to remove
            leftMaxNode->setLeft(nodeToRemove->getLeft());
            leftMaxNode->setRight(nodeToRemove->getRight());
            leftMaxNode->setParent(parentNode);
            nodeToRemove->getRight()->setParent(leftMaxNode);
            nodeToRemove->getLeft()->setParent(leftMaxNode);
        } else {
            // when the left max node is the left node of node to remove
            // directly connect the left max node branch to the position of node to remove
            leftMaxNode->setRight(nodeToRemove->getRight());
            leftMaxNode->setParent(parentNode);
            nodeToRemove->getRight()->setParent(leftMaxNode);
        }

        if (parentNode != NULL) {
            if (parentNode->getRight() == nodeToRemove) {
                parentNode->setRight(leftMaxNode);
            } else {
                parentNode->setLeft(leftMaxNode);
            }
        } else {
            // when removing the root
            root = leftMaxNode;
        }
    }
    // delete the old node
    delete nodeToRemove;
    return true;
}

TreeNode *TreeDB::findMaxNode(TreeNode *rootNode) {
    TreeNode *currentNode = rootNode;
    while (currentNode->getRight() != NULL)
        currentNode = currentNode->getRight();
    return currentNode;
}

void TreeDB::clear() {
    if(root == NULL)
        return;

    TreeDB subTreeLeft(root->getLeft());
    TreeDB subTreeRight(root->getRight());
    subTreeLeft.clear();
    subTreeRight.clear();
    delete root;
    root = NULL;
}


void TreeDB::printProbes(const string name) {
    probesCount = 0;
    if(find(name))
        cout << probesCount << endl;
}

void TreeDB::countActive() const {
    cout << _countActive() << endl;
}

int TreeDB::_countActive() const {
    if(root == NULL)
        return 0;
    int active = root->getEntryPtr()->getActive() ? 1 : 0;
    TreeDB subTreeLeft(root->getLeft());
    TreeDB subTreeRight(root->getRight());
    return subTreeLeft._countActive() + subTreeRight._countActive() + active;
}

void TreeDB::printall() {
    myVector db;
    populateVector(db);
    db.sort();
    for (int i = 0; i < db.getSize(); ++i) {
        db[i]->printInfo();
//        cout << *(db[i]) << endl;
    }
}

void TreeDB::populateVector(myVector &m) {
    if(root != NULL) {
        m.push_back(root->getEntryPtr());
    }else{
        return;
    }
    TreeDB subTreeRight(root->getRight());
    TreeDB subTreeLeft(root->getLeft());
    subTreeLeft.populateVector(m);
    subTreeRight.populateVector(m);
}

// wheels
myVector::myVector() : currentCursor(0){
    // default capacity 5
    capsule = new DBentry *[DEFAULT_VECTOR_SIZE]();
}

myVector::myVector(int size) : size(size), currentCursor(0){
    capsule = new DBentry *[size]();
}

DBentry *&myVector::operator[](const int index) {
    if (index < 0) {
//        args_exception ae("Error: myVector index can not be negative");
//        throw ae;
    }
    if (index >= size) {
        // expand the array
        DBentry **newCapsule = new DBentry *[index + 1]();
        size = index + 1;
        for (int i = 0; i < size; ++i)
            newCapsule[i] = capsule[i];
        delete[] capsule;
        capsule = newCapsule;
    }
    return capsule[index];
}

int myVector::getSize() const {
    return currentCursor;
}

void myVector::push_back(DBentry *treeNode) {
    (*this)[currentCursor] = treeNode;
    currentCursor++;
}

myVector::~myVector() {
    delete[] capsule;
}

void myVector::sort() {
    // need at least 2 element to be eligible for sorting
    if(currentCursor > 1)
        qsort(capsule, 0, currentCursor - 1);
}

void myVector::qsort(DBentry **arr, int begin, int end) {
    int pivotIndex = selectAndShuffle(arr, begin, end);
    if (pivotIndex - 1 > begin)
        qsort(arr, begin, pivotIndex - 1);
    if (pivotIndex + 1 < end)
        qsort(arr, pivotIndex + 1, end);
    return;
}

int myVector::selectAndShuffle(DBentry **arr, int begin, int end) {
    string pivotValue = arr[begin]->getName();
    int current_index = begin;
    for (int i = begin + 1; i <= end; ++i) {
        if (arr[i]->getName().compare(pivotValue) < 0) {
            current_index++;
            swap(arr[current_index], arr[i]);
        }
    }
    swap(arr[begin], arr[current_index]);
    return current_index;
}
