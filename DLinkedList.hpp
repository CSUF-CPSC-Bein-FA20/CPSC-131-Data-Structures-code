#pragma once

/*******************************************************************************
** A doubly linked list
*******************************************************************************/
template <typename Data_t>
class DLinkedList
{
  public:
    class Iterator;                                          // A forward iterator

    DLinkedList();                                           // empty list constructor
    DLinkedList            ( const DLinkedList & original ); // copy constructor
    DLinkedList & operator=( const DLinkedList & rhs      ); // copy assignment
   ~DLinkedList();                                           // destructor


    bool    empty() const;                                   // returns true if list has no items
    void    clear();                                         // remove all elements setting size to zero
    size_t  size() const;                                    // returns the number of elements in the list


    Data_t & front();                                        // return list's front element
    void     prepend( const Data_t & element );              // add element to front of list (aka push_front)
    void     removeFront();                                  // remove element at front of list (aka pop_front)

    Data_t & back();                                         // return list's back element
    void     append( const Data_t & element );               // add element to back of list (aka push_back)
    void     removeBack();                                   // remove element at front of list (aka pop_back)

    Iterator insertBefore( const Iterator & position, const Data_t & element ); // Inserts element into list before the one occupied at position
    Iterator remove      ( const Iterator & position                         ); // Removes from list the element occupied at position

    Iterator begin() const;                                  // Returns an Iterator to the list's front element, nullptr if list is empty
    Iterator end  () const;                                  // Returns an Iterator beyond the list's back element.  Do not dereference this Iterator

    Iterator rbegin() const;                                 // Returns an Iterator to the list's back element, nullptr if list is empty
    Iterator rend  () const;                                 // Returns an Iterator beyond the list's front element.  Do not dereference this Iterator


  private:
    struct Node;

    Node * _head = nullptr;                                   // head of the list
    Node * _tail = nullptr;                                   // tail of the list
    size_t _size = 0;
};




/*******************************************************************************
** A doubly linked list bidirectional iterator
*******************************************************************************/
template<typename Data_t>
class DLinkedList<Data_t>::Iterator
{
  friend class DLinkedList<Data_t>;

  public:
    // Compiler synthesized constructors and destructor are fine, just what we
    // want (shallow copies, no ownership) but needed to explicitly say that
    // because there is also a user defined constructor
    Iterator            (                   )    = default;
    Iterator            ( const Iterator  & )    = default;
    Iterator            (       Iterator && )    = default;
    Iterator & operator=( const Iterator  & )    = default;
    Iterator & operator=(       Iterator && )    = default;
   ~Iterator            (                   )    = default;

    Iterator( Node * position );                              // Implicit conversion constructor

    // Pre and post Increment operators move the position to the next node in the list
    Iterator & operator++();                                  // advance the iterator one node (pre -increment)
    Iterator   operator++( int );                             // advance the iterator one node (post-increment)

    // Pre and post Increment operators move the position to the next node in the list
    Iterator & operator--();                                  // retreat the iterator one node (pre -decrement)
    Iterator   operator--( int );                             // retreat the iterator one node (post-decrement)

    Iterator   next     ( size_t delta = 1 ) const;           // Return an iterator delta nodes after this node (this iterator doesn't change)
    Iterator   operator+( size_t rhs       ) const;           // Return an iterator delta nodes after this node (this iterator doesn't change)

    Iterator   prev     ( size_t delta = 1 ) const;           // Return an iterator delta nodes after this node (this iterator doesn't change)
    Iterator   operator-( size_t rhs       ) const;           // Return an iterator delta nodes after this node (this iterator doesn't change)

    // Dereferencing and member access operators provide access to data. The
    // iterator can be constant or non-constant, but the iterator, by
    // definition, points to a non-constant linked list.
    Data_t & operator* () const;
    Data_t * operator->() const;

    // Equality operators
    bool operator==( const Iterator & rhs ) const;
    bool operator!=( const Iterator & rhs ) const;

  private:
    Node * _node = nullptr;
};


// Including template definitions here allows a consistent approach of separating interface (header file) from implementation (source file)
//
// There are three implementations of this interface provided.  One implements the doubly linked list with direct head and tail pointers, one with
// dummy head and tail nodes, and the other is a circularly doubly linked list. The important thing to take away is the they all share the same
// interface, and that the specific implementation can change without affecting consumers of the class.

#include "DLinkedList.hxx"
//  #include "CircularDummyNodeDLinkedList.hxx"
//  #include "DummyNodeDLinkedList.hxx"
