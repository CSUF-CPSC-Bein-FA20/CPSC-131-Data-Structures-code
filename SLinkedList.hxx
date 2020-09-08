#pragma once

#include <stdexcept>    // length_error, invalid_argument

#include "SLinkedList.hpp"






/*******************************************************************************
** A singly linked list's node
*******************************************************************************/
template<typename Data_t>
struct SLinkedList<Data_t>::Node
{
  Node( const Data_t & element ) : _data( element ) {}

  Data_t _data;                                               // linked list element value
  Node * _next = nullptr;                                     // next item in the list
};




/*******************************************************************************
** SLinkedList Function definitions
*******************************************************************************/

/*******************************************************************************
** Extended interface to demonstrate recursive functions
*******************************************************************************/

// Add a function, named "reverse", to the Singly Linked List that reverses the list without copying the list or moving data in
// the list. Implement the function recursively.  The function must be implemented recursively.
//
// Client visible interface (the public function)
template<typename Data_t>
void SLinkedList<Data_t>::reverse()
{
  // Kick off the recursion starting at the head
  reverse( _head );

  // Now swap the head and tail pointers
  auto tmp = _head;
  _head    = _tail;
  _tail    = tmp;
}


// Add a function, named "reverse" ...
// The private helper function
template<typename Data_t>
void SLinkedList<Data_t>::reverse( Node * currentNode )
{
  // There is nothing more to do if we're reversing and empty list or we're at the last node in a non-empty list (base case)
  if( currentNode == nullptr  ||  currentNode->_next == nullptr ) return;    

  // Move down the list to the next node (recurse)
  reverse( currentNode->_next );                                           

  // While unwinding (moving from tail towards head), make the next node point to this node
  currentNode->_next->_next = currentNode;                     
  currentNode       ->_next = nullptr;                            
}




// Add a function, named "add" that returns the sum of all elements in the list.  The function must be implemented recursively.
// Assume operator+(lhs, rhs) is defined
//
// Client visible interface (the public function)
template<typename Data_t>
Data_t SLinkedList<Data_t>::add()
{
  return add( _head );
}


// Add a function, named "add" ...
// The private helper function
template<typename Data_t>
Data_t SLinkedList<Data_t>::add( Node * currentNode )
{
  // Base case - reached the end of the list.  Can't return zero, Data_t may not be an integer type. Return the value initialized
  // default value instead
  if( currentNode == nullptr ) return Data_t();

  // Use a postorder traversal where the left hand side is progressively easier and easier and eventually trivial to solve
  return currentNode->_data + add( currentNode->_next );
}














// empty list constructor
template<typename Data_t>
SLinkedList<Data_t>::SLinkedList() = default;



// copy constructor
template <typename Data_t>
SLinkedList<Data_t>::SLinkedList( const SLinkedList & original )
{
  // Walk the original list adding copies of the elements to this (initially empty) list maintaining order
  for( Node * current = original._head; current != nullptr; current = current->_next )
  { append( current->_data ); }
}



// copy assignment
template <typename Data_t>
SLinkedList<Data_t> & SLinkedList<Data_t>::operator=( const SLinkedList & rhs )
{
  if( this != &rhs )                                          // avoid self assignment
  {
    // Release the contents of this list first
    clear();                                                 // An optimization might be possible by reusing already allocated nodes

    // Walk the right hand side list adding copies of the elements to this list maintaining order
    for( Node * position = rhs._head; position != nullptr; position = position->_next )
    { append( position->_data ); }
  }
  return *this;
}



// destructor
template <typename Data_t>
SLinkedList<Data_t>::~SLinkedList()
{ clear(); }



template <typename Data_t>
bool SLinkedList<Data_t>::empty() const
{ return _head == nullptr; }                                  // can also use return (_size == 0);



template <typename Data_t>
void SLinkedList<Data_t>::clear()
{ while( !empty() ) removeFront(); }



template <typename Data_t>
size_t  SLinkedList<Data_t>::size() const
{ return _size; }



template <typename Data_t>
Data_t& SLinkedList<Data_t>::front()
{
  if( empty() ) throw std::length_error( "empty list" );
  return _head->_data;
}



template <typename Data_t>
void SLinkedList<Data_t>::prepend( const Data_t& element )
{ insertAfter( nullptr, element ); }



template <typename Data_t>
void SLinkedList<Data_t>::removeFront()
{ removeAfter( nullptr ); }



template <typename Data_t>
Data_t& SLinkedList<Data_t>::back()
{
  if( empty() ) throw std::length_error( "attempt to access data from an empty list" );
  return _tail->_data;
}



template <typename Data_t>
void SLinkedList<Data_t>::append( const Data_t & element )
{ insertAfter( _tail, element ); }



template <typename Data_t>
typename SLinkedList<Data_t>::Iterator SLinkedList<Data_t>::insertAfter( const Iterator & position, const Data_t & element )
{
  Node * newNode = new Node( element );                       // create new node

  if ( empty() ) _head = _tail = newNode;

  else if( position == nullptr )                              // Insert at front of list
  {
    // Relink the head
    newNode->_next = _head;                                   // head now follows newNode
    _head          = newNode;                                 // newNode is now the head
  }

  else if( position == _tail )                                // Insert at back of list
  {
    // Relink the tail
    _tail->_next = newNode;                                   // tail now precedes newNode
    _tail        = newNode;                                   // newNode is now the tail
  }

  else                                                        // Insert in the middle of the list
  {
    // Relink the node at current
    newNode->_next        = position._node->_next;
    position._node->_next = newNode;
  }

  ++_size;
  return newNode;
}



template <typename Data_t>
typename SLinkedList<Data_t>::Iterator SLinkedList<Data_t>::removeAfter( const Iterator & position )
{
  if( empty()           ) throw std::length_error( "attempt to remove from an empty list" );
  if( position == _tail ) return nullptr;                     // removing after the tail intentionally does nothing


  Node * oldNode = nullptr;                                   // the node to be removed
  if( position == nullptr )                                   // remove the node at the head of the list
  {
    oldNode = _head;
    _head   = _head->_next;
  }

  else
  {
    oldNode               = position._node->_next;            // remove from middle of list
    position._node->_next = position._node->_next->_next;     // unlink the old node
  }

  --_size;

  if( oldNode == _tail ) _tail = nullptr;                     // remove the tail of the list

  Iterator returnNode( oldNode->_next );                      // return the node after the one removed
  delete oldNode;                                             // delete what used to be the old node
  return returnNode;
}



template <typename Data_t>
typename SLinkedList<Data_t>::Iterator SLinkedList<Data_t>::begin()
{ return Iterator(_head); }



template <typename Data_t>
typename SLinkedList<Data_t>::Iterator SLinkedList<Data_t>::end()
{ return Iterator(); }











/*******************************************************************************
** SLinkedList::Iterator Function definitions
*******************************************************************************/
template <typename Data_t>
SLinkedList<Data_t>::Iterator::Iterator( Node * p )
: _node(p)
{}



template <typename Data_t>
typename SLinkedList<Data_t>::Iterator & SLinkedList<Data_t>::Iterator::operator++()      // pre-increment
{
  if( _node == nullptr ) throw std::invalid_argument( "Attempt to increment null Iterator" );
  _node = _node->_next;
  return *this;
}



template <typename Data_t>
typename SLinkedList<Data_t>::Iterator SLinkedList<Data_t>::Iterator::operator++( int )   // post-increment
{
  Iterator temp( *this );
  operator++();                                               // Delegate to pre-increment leveraging error checking
  return temp;
}



template <typename Data_t>
typename SLinkedList<Data_t>::Iterator SLinkedList<Data_t>::Iterator::next( size_t delta ) const
{
  // advance a copy of this iterator delta times
  Iterator p( *this );
  for(; delta > 0  &&  p != nullptr; --delta, ++p ) /* intentionally empty body */;
  return p;
}



template <typename Data_t>
typename SLinkedList<Data_t>::Iterator SLinkedList<Data_t>::Iterator::operator+( size_t rhs ) const
{ return next(rhs); }



template <typename Data_t>
Data_t & SLinkedList<Data_t>::Iterator::operator* () const
{
  if( _node == nullptr ) throw std::invalid_argument( "Attempt to dereference null Iterator" );
  return _node->_data;
}



template <typename Data_t>
Data_t * SLinkedList<Data_t>::Iterator::operator->() const
{
  if( _node == nullptr ) throw std::invalid_argument( "Attempt to dereference null Iterator" );
  return &(_node->_data);
}



template <typename Data_t>
bool SLinkedList<Data_t>::Iterator::operator==( const Iterator & rhs ) const
{ return _node == rhs._node; }



template <typename Data_t>
bool SLinkedList<Data_t>::Iterator::operator!=( const Iterator & rhs ) const
{ return !(*this == rhs);  }
