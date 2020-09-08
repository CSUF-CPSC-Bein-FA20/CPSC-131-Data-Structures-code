#pragma once

/*******************************************************************************
** A singly linked list
*******************************************************************************/
template <typename Data_t>
class SLinkedList
{
  public:
    class Iterator;                                           // A forward iterator

    SLinkedList();                                            // empty list constructor
    SLinkedList            ( const SLinkedList & original );  // copy constructor
    SLinkedList & operator=( const SLinkedList & rhs );       // copy assignment
   ~SLinkedList();                                            // destructor


    bool    empty() const;                                    // returns true if list has no items
    void    clear();                                          // remove all elements setting size to zero
    size_t  size() const;                                     // returns the number of elements in the list


    Data_t & front();                                         // return list's front element
    void     prepend( const Data_t & element );               // add element to front of list (aka push_front)
    void     removeFront();                                   // remove element at front of list (aka pop_front)

    Data_t & back();                                          // return list's back element
    void     append( const Data_t & element );                // add element to back of list (aka push_back)

    Iterator insertAfter( const Iterator & position, const Data_t & element ); // Inserts element into list after the one occupied at position
    Iterator removeAfter( const Iterator & position                         ); // Removes from list the element after the one occupied at position

    Iterator begin();                                         // Returns an Iterator to the list's front element, nullptr if list is empty
    Iterator end  ();                                         // Returns an Iterator beyond the list's back element.  Do not dereference this Iterator



    /**************************************************************************
    ** Extended interface to demonstrate recursive functions
    **************************************************************************/
    // Add a function, named "reverse", to the Singly Linked List that reverses the list without copying the list or moving data in
    // the list. Implement the function recursively.  The function must be implemented recursively.
    // 
    // Client visible interface (the public function)
    void reverse();


    // Add a function, named "add" that returns the sum of all elements in the list.  The function must be implemented recursively.
    // Assume operator+(lhs, rhs) is defined
    //
    // Client visible interface (the public function)
    Data_t add();
  private:
    struct Node;

    Node * _head  = nullptr;                                  // head of the list
    Node * _tail  = nullptr;                                  // tail of the list
    size_t _size = 0;

    // Add a function, named "reverse" ...
    // The private helper function
    void reverse( Node * currentNode );

    // Add a function, named "add" ...
    // The private helper function
    Data_t add( Node * currentNode );
};




/*******************************************************************************
** A singly linked list forward iterator
*******************************************************************************/
template<typename Data_t>
class SLinkedList<Data_t>::Iterator
{
  friend class SLinkedList<Data_t>;

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

    Iterator   next     ( size_t delta = 1 ) const;           // Return an iterator delta nodes after this node (this iterator doesn't change)
    Iterator   operator+( size_t rhs       ) const;           // Return an iterator delta nodes after this node (this iterator doesn't change)

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
#include "SLinkedList.hxx"
