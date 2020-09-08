#pragma once
#include <array>
#include <cstddef>   // size_t

#include "DLinkedList.hpp"

// Queue is an adapter that provides a consistent FIFO interface over an underlying container.  Here, that underlying container is
// defaulted to a singly linked list.  Other choices include a double linked list, vector, and so on.
//    Underlying container must support the following functions:
//    o) void    push( const T & element)
//    o) T       pop()
//    o) T &     top()
//    o) bool    empty()
//    o) size_t  size()
//
//
// Note:  C++20 "Concepts" will enable better enforcement of these constraints, but for now ...
template<typename T, class UnderlyingContainer = DLinkedList<T>>
class Queue
{
public:
  void        push( const T & element );
  T           pop();
  T &         top();                                // peek() in zyBook
  bool        empty();                              // isEmpty() in zyBook
  std::size_t size();                               // getLength() in zyBook

private:
  UnderlyingContainer collection;
};





// Partial Specialization for a fixed sized Queue over a fixed sized standard array 
template<typename T, std::size_t CAPACITY>
class Queue<T, std::array<T, CAPACITY>>
{
public:
  void        push( const T & element );
  T           pop();
  T &         top();                                // peek() in zyBook
  bool        empty();                              // isEmpty() in zyBook
  std::size_t size();                               // getLength() in zyBook

private:
  std::array<T, CAPACITY> collection;
  std::size_t             _front = 0;               // index of the front element
  std::size_t             _rear  = 0;               // index of an empty location where the next element will enter 
  std::size_t             _size  = 0;               // number of elements in the queue, 0 indicates an empty queue
};




#include "Queue.hxx"
