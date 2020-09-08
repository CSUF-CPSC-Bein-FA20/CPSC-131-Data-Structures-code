#pragma once
#include <type_traits>              // move() ?
#include <cstddef>                  // size_t
#include <stdexcept>                // out_of_range
#include <string>                   // to_string()

#include "Queue.hpp"






/*******************************************************************************
** Primary implementation
*******************************************************************************/
template<typename T, class UnderlyingContainer>
void Queue<T, UnderlyingContainer>::push( const T & element )
{
  collection.prepend( element );      // insert at the front
}



template<typename T, class UnderlyingContainer>
T Queue<T, UnderlyingContainer>::pop()
{
  // Note: zyBook returns the value popped, the C++ standard template library does not.
  //       popping an element from an empty queue error handling is handled by the underlying container
  auto element = collection.back();
  collection.removeBack();
  return element;
}



template<typename T, class UnderlyingContainer>
T & Queue<T, UnderlyingContainer>::top()
{
  // Note: viewing an element from an empty queue error handling is handled by the underlying container
  return collection.back();
}



template<typename T, class UnderlyingContainer>
bool Queue<T, UnderlyingContainer>::empty()
{
  return collection.empty();
}



template<typename T, class UnderlyingContainer>
std::size_t Queue<T, UnderlyingContainer>::size()
{
  return collection.size();
}






/*******************************************************************************
** Partial Specialization for a fixed sized Queue over a fixed sized standard array
*******************************************************************************/
template<typename T, std::size_t CAPACITY>
void Queue<T, std::array<T, CAPACITY>>::push( const T & element )
{
  if( _size >= CAPACITY ) throw std::out_of_range( "ERROR:  Attempt to add to an already full queue of " + std::to_string( CAPACITY ) + " elements." );

  collection[_rear] = element;

  _rear = ( _rear + 1 ) % CAPACITY;
  ++_size;
}



template<typename T, std::size_t CAPACITY>
T Queue<T, std::array<T, CAPACITY>>::pop()
{
  if( empty() ) throw std::out_of_range( "ERROR:  Attempt to remove an element from an empty queue" );

  auto temp = std::move( collection[_front] );

  _front = ( _front + 1 ) % CAPACITY;
  --_size;

  // Note, zyBook returns the value popped, the C++ standard template library does not.
  return temp;
}



template<typename T, std::size_t CAPACITY>
T & Queue<T, std::array<T, CAPACITY>>::top()
{
  if( empty() ) throw std::out_of_range( "ERROR:  Attempt to view an element from an empty queue" );

  return collection[_front];
}



template<typename T, std::size_t CAPACITY>
bool Queue<T, std::array<T, CAPACITY>>::empty()
{
  return _size == 0;
}



template<typename T, std::size_t CAPACITY>
std::size_t Queue<T, std::array<T, CAPACITY>>::size()
{
  return _size;
}
