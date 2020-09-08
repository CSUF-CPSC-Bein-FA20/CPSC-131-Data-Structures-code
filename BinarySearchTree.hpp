#pragma once
#include <iostream>

/*******************************************************************************
**  Binary Search Tree Abstract Data Type Definition (Duplicate keys allowed)
*******************************************************************************/
template <typename Key, typename Value>
class BinarySearchTree {
  public:
    BinarySearchTree             () = default;
    BinarySearchTree             ( const BinarySearchTree & original );     // performs a deep copy
    BinarySearchTree & operator= (       BinarySearchTree   rhs      );     // performs a deep copy assignment  NOTE: INTENTIONALLY PASSED BY VALUE (delegates to copy constructor)
   ~BinarySearchTree             ();                                        // performs a deep node destruction

    // Queries
    Value search     ( const Key & key )                       const;       // zyBook 6.4, 6.10:  Returns the value associated with the first node found matching given key. Throws invalid_argument if key not found
    void insert      ( const Key & key, const Value & value );              // zyBook 6.5, 6.9, 6.10:  Inserts a new node populated with key and value in a proper location obeying the BST ordering property.
    void remove      ( const Key & key );                                   // zyBook 6.6, 6.9, 6.10:  Removes the first-found matching node, restructuring the tree to preserve the BST ordering property.
    void printInorder()                                        const;       // zyBook 6.7:  Prints the contents of the tree in ascending sorted order
    int  getHeight   ()                                        const;       // zyBook 6.8:  Returns the height of the tree, or -1 if tree is empty

    void clear();                                                           // Returns the tree to an empty state releasing all nodes


  private:
    struct Node;
    Node * root_ = nullptr;

    // Helper functions
    void clear          ( Node * node );
    void insertIterative( Node * node );                                    // zyBook Figure 6.9.1: BSTInsert algorithm for BSTs with nodes containing parent pointers.
    void insertRecursive( Node * parent, Node * nodeToInsert );             // zyBook Figure 6.10.2: Recursive BST insertion and removal.
    void remove         ( Node * node );                                    // zyBook Figure 6.9.3: BSTRemoveKey and BSTRemoveNode algorithms for BSTs with nodes containing parent pointers.  (Figure 6.10.2 identical but passes parent instead of using parent pointer in Node)
    void printInorder   ( Node * node ) const;                              // zyBook Figure 6.7.1: BST inorder traversal algorithm.
    int  getHeight      ( Node * node ) const;                              // zyBook Figure 6.8.3: BSTGetHeight algorithm.


    Node * makeCopy( Node * node );                                         // Copy constructor helper function

    Node * searchIterative(              const Key & key ) const;           // zyBook Figure 6.4.1: BST search algorithm.
    Node * searchRecursive( Node * node, const Key & key ) const;           // zyBook Figure 6.10.1: BST recursive search algorithm.

    bool replaceChild( Node * parent,                                       // zyBook Figure 6.9.2: BSTReplaceChild algorithm.
                       Node * currentChild,
                       Node * newChild );
  };






// Include template function definitions
#include "BinarySearchTree.hxx"
