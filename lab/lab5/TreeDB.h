//
// Created by CharlieHu on 2016-11-12.
//

#ifndef LAB5_TREEDB_H
#define LAB5_TREEDB_H

#define DEFAULT_VECTOR_SIZE 5

#include "TreeNode.h"
#include "DBentry.h"

// reinventing Vector since the use of Vector from std lib is not allowed in lab5
// this myVector is used to hold pointers to DBentry
// vector elements would be sorted by their name
class myVector {
private:
    int size;
    int currentCursor;
    DBentry **capsule;

    int selectAndShuffle(DBentry **arr, int begin, int end);

    void qsort(DBentry **arr, int begin, int end);

public:
    virtual ~myVector();

    myVector();

    int getSize() const;

    myVector(int size);

    DBentry *&operator[](const int index);

    void push_back(DBentry *treeNode);

    void sort();
};


class TreeDB {

private:
    TreeNode *root;
    static int probesCount;

    TreeNode *findNode(const string name);

    TreeNode *findMaxNode(TreeNode *rootNode);

    void populateVector(myVector &m);

    int _countActive() const;

public:
    // the default constructor, creates an empty database.
    TreeDB();

    TreeDB(TreeNode *root);

    // the destructor, deletes all the entries in the database.
    ~TreeDB();

    // inserts the entry pointed to by newEntry into the database.
    // If an entry with the same key as newEntry's exists
    // in the database, it returns false. Otherwise, it returns true.
    bool insert(DBentry *newEntry);

    // searches the database for an entry with a key equal to name.
    // If the entry is found, a pointer to it is returned.
    // If the entry is not found, the NULL pointer is returned.
    // Also sets probesCount
    DBentry *find(const string name);

    // deletes the entry with the specified name (key)  from the database.
    // If the entry was indeed in the database, it returns true.
    // Returns false otherwise.
    // See section 6 of the lab handout for the *required* removal method.
    // If you do not use that removal method (replace deleted node by
    // maximum node in the left subtree when the deleted node has two children)
    // you will not match exercise's output.
    bool remove(const string name);

    // deletes all the entries in the database.
    void clear();

    // prints the number of probes stored in probesCount
    void printProbes(const string name);

    // computes and prints out the total number of active entries
    // in the database (i.e. entries with active==true).
    void countActive() const;

    void printall();
};

#endif //LAB5_TREEDB_H
