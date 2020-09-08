#pragma once
#include <cstddef>                  // size_t
#include <stdexcept>                // out_of_range
#include <string>                   // to_string()

#include "Stack.hpp"






/*******************************************************************************
** Primary implementation
*******************************************************************************/
template<typename T, class UnderlyingContainer>
void Stack<T, UnderlyingContainer>::push( const T & element )
{
  collection.prepend( element );
}



template<typename T, class UnderlyingContainer>
T Stack<T, UnderlyingContainer>::pop()
{
  // Note: zyBook returns the value popped, the C++ standard template library does not.
  //       popping an element from an empty stack error handling is handled by the underlying container
  auto element = collection.front();
  collection.removeFront();
  return element;
}



template<typename T, class UnderlyingContainer>
T & Stack<T, UnderlyingContainer>::top()
{
  // Note: viewing an element from an empty stack error handling is handled by the underlying container
  return collection.front();
}



template<typename T, class UnderlyingContainer>
bool Stack<T, UnderlyingContainer>::empty()
{
  return collection.empty();
}



template<typename T, class UnderlyingContainer>
std::size_t Stack<T, UnderlyingContainer>::size()
{
  return collection.size();
}






/*******************************************************************************
** Partial Specialization for a fixed sized Stack over a fixed sized standard array
*******************************************************************************/
template<typename T, std::size_t CAPACITY>
void Stack<T, std::array<T, CAPACITY>>::push( const T & element )
{
  if( nextAvailableSlot >= collection.size() ) throw std::out_of_range( "ERROR:  Attempt to add to an already full stack of " + std::to_string( collection.size() ) + " elements." );

  collection[nextAvailableSlot++] = element;
}



template<typename T, std::size_t CAPACITY>
T Stack<T, std::array<T, CAPACITY>>::pop()
{
  if( empty() ) throw std::out_of_range( "ERROR:  Attempt to remove an element from an empty stack" );

  // Note, zyBook returns the value popped, the C++ standard template library does not.
  return collection[--nextAvailableSlot];
}



template<typename T, std::size_t CAPACITY>
T & Stack<T, std::array<T, CAPACITY>>::top()
{
  if( empty() ) throw std::out_of_range( "ERROR:  Attempt to view an element from an empty stack" );

  return collection[nextAvailableSlot-1];
}



template<typename T, std::size_t CAPACITY>
bool Stack<T, std::array<T, CAPACITY>>::empty()
{
  return nextAvailableSlot == 0;
}



template<typename T, std::size_t CAPACITY>
std::size_t Stack<T, std::array<T, CAPACITY>>::size()
{
  return nextAvailableSlot;
}
