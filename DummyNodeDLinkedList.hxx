#pragma once

#include <stdexcept>    // length_error, invalid_argument

#include "DLinkedList.hpp"




/*******************************************************************************
** A doubly linked list's node
*******************************************************************************/
template<typename Data_t>
struct DLinkedList<Data_t>::Node
{
  Node( const Data_t & element ) : _data( element ) {}

  Data_t _data;                                               // linked list element value
  Node * _next = nullptr;                                     // next item in the list
  Node * _prev = nullptr;                                     // previous item in the list
};






/*******************************************************************************
** DLinkedList with two dummy nodes function definitions
*******************************************************************************/
// empty list constructor
template<typename Data_t>
DLinkedList<Data_t>::DLinkedList()
  : _head( new Node( Data_t() ) ), _tail( new Node( Data_t() ) )
{
  // have them point to each other
  _head->_next = _tail;
  _tail->_prev = _head;
}



// copy constructor
template<typename Data_t>
DLinkedList<Data_t>::DLinkedList( const DLinkedList & original )
  : DLinkedList()
{
  // Walk the original list adding copies of the elements to this (initially empty) list maintaining order
  for( const auto & element : original ) append( element );
}



// copy assignment
template<typename Data_t>
DLinkedList<Data_t> & DLinkedList<Data_t>::operator=( const DLinkedList & rhs )
{
  if( this != &rhs )    // avoid self assignment
  {
    // Release the contents of this list first
    clear();    // An optimization might be possible by reusing already allocated nodes

    // Walk the right hand side list adding copies of the elements to this list maintaining order
    for( const auto & element : rhs ) append( element );
  }
  return *this;
}



// destructor
template<typename Data_t>
DLinkedList<Data_t>::~DLinkedList()
{
  clear();
  delete _head;
  delete _tail;
}



template<typename Data_t>
bool DLinkedList<Data_t>::empty() const
{
  return _head->_next == _tail;
  // can also use return (_size == 0);
}



template<typename Data_t>
void DLinkedList<Data_t>::clear()
{
  while( !empty() ) removeFront();
}



template<typename Data_t>
size_t DLinkedList<Data_t>::size() const
{
  return _size;
}



template<typename Data_t>
Data_t & DLinkedList<Data_t>::front()
{
  if( empty() ) throw std::length_error( "attempt to access data from an empty list" );
  return _head->_next->_data;
}



template<typename Data_t>
void DLinkedList<Data_t>::prepend( const Data_t & element )
{
  insertBefore( _head->_next, element );
}



template<typename Data_t>
void DLinkedList<Data_t>::removeFront()
{
  remove( _head->_next );
}



template<typename Data_t>
Data_t & DLinkedList<Data_t>::back()
{
  if( empty() ) throw std::length_error( "attempt to access data from an empty list" );
  return _tail->_prev->_data;
}



template<typename Data_t>
void DLinkedList<Data_t>::append( const Data_t & element )
{
  insertBefore( _tail, element );
}



template<typename Data_t>
void DLinkedList<Data_t>::removeBack()
{
  remove( _tail->_prev );
}



template<typename Data_t>
typename DLinkedList<Data_t>::Iterator DLinkedList<Data_t>::insertBefore( const Iterator & current, const Data_t & element )
{
  if( current == _head )  throw std::invalid_argument( "Attempt to insert before an invalid location" );

  Node * newNode = new Node( element );    // create new node

  newNode->_next = current._node;
  newNode->_prev = current._node->_prev;

  current._node->_prev->_next = newNode;
  current._node->_prev        = newNode;

  ++_size;
  return newNode;
}



template<typename Data_t>
typename DLinkedList<Data_t>::Iterator DLinkedList<Data_t>::remove( const Iterator & current )
{
  if( empty() )                               throw std::length_error    ( "attempt to remove from an empty list" );
  if( current == _head || current == _tail )  throw std::invalid_argument( "Attempt to remove at an invalid location" );

  current._node->_next->_prev = current._node->_prev;
  current._node->_prev->_next = current._node->_next;

  --_size;

  Iterator returnNode( current._node->_next );    // return the node after the one removed
  delete current._node;                           // delete what used to be the old node
  return returnNode;
}



template<typename Data_t>
typename DLinkedList<Data_t>::Iterator DLinkedList<Data_t>::begin() const
{
  return Iterator( _head->_next );
}



template<typename Data_t>
typename DLinkedList<Data_t>::Iterator DLinkedList<Data_t>::end() const
{
  return Iterator(_tail);
}



template<typename Data_t>
typename DLinkedList<Data_t>::Iterator DLinkedList<Data_t>::rbegin() const
{
  return Iterator( _tail->_prev );
}



template<typename Data_t>
typename DLinkedList<Data_t>::Iterator DLinkedList<Data_t>::rend() const
{
  return Iterator(_head);
}











/*******************************************************************************
** DLinkedList::Iterator Function definitions
*******************************************************************************/
template<typename Data_t>
DLinkedList<Data_t>::Iterator::Iterator( Node * p )
  : _node( p )
{}



template<typename Data_t>
typename DLinkedList<Data_t>::Iterator & DLinkedList<Data_t>::Iterator::operator++()    // pre-increment
{
  if( _node == nullptr ) throw std::invalid_argument( "Attempt to increment null Iterator" );
  _node = _node->_next;
  return *this;
}



template<typename Data_t>
typename DLinkedList<Data_t>::Iterator DLinkedList<Data_t>::Iterator::operator++( int )    // post-increment
{
  Iterator temp( *this );
  operator++();    // Delegate to pre-increment leveraging error checking
  return temp;
}



template<typename Data_t>
typename DLinkedList<Data_t>::Iterator & DLinkedList<Data_t>::Iterator::operator--()    // pre -decrement
{
  if( _node == nullptr ) throw std::invalid_argument( "Attempt to decrement null Iterator" );
  _node = _node->_prev;
  return *this;
}



template<typename Data_t>
typename DLinkedList<Data_t>::Iterator DLinkedList<Data_t>::Iterator::operator--( int )    // post-decrement
{
  Iterator temp( *this );
  operator--();    // Delegate to pre-decrement leveraging error checking
  return temp;
}



template<typename Data_t>
typename DLinkedList<Data_t>::Iterator DLinkedList<Data_t>::Iterator::next( size_t delta ) const
{
  // advance a copy of this iterator delta times
  Iterator p( *this );
  for( ; delta > 0 && p != nullptr; --delta, ++p );   /* intentionally empty body */

  return p;
}



template<typename Data_t>
typename DLinkedList<Data_t>::Iterator DLinkedList<Data_t>::Iterator::operator+( size_t rhs ) const
{
  return next( rhs );
}



template<typename Data_t>
typename DLinkedList<Data_t>::Iterator DLinkedList<Data_t>::Iterator::prev( size_t delta ) const
{
  // retreat a copy of this iterator delta times
  Iterator p( *this );
  for( ; delta > 0 && p != nullptr; --delta, --p );   /* intentionally empty body */

  return p;
}


template<typename Data_t>
typename DLinkedList<Data_t>::Iterator DLinkedList<Data_t>::Iterator::operator-( size_t rhs ) const
{
  return prev( rhs );
}



template<typename Data_t>
Data_t & DLinkedList<Data_t>::Iterator::operator*() const
{
  if( _node == nullptr ) throw std::invalid_argument( "Attempt to dereference null Iterator" );
  return _node->_data;
}



template<typename Data_t>
Data_t * DLinkedList<Data_t>::Iterator::operator->() const
{
  if( _node == nullptr ) throw std::invalid_argument( "Attempt to dereference null Iterator" );
  return &( _node->_data );
}



template<typename Data_t>
bool DLinkedList<Data_t>::Iterator::operator==( const Iterator & rhs ) const
{
  return _node == rhs._node;
}



template<typename Data_t>
bool DLinkedList<Data_t>::Iterator::operator!=( const Iterator & rhs ) const
{
  return !( *this == rhs );
}
