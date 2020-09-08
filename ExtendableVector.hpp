#pragma once

#include <algorithm>                                                      // move(), move_backward(), copy()
#include <cstddef>                                                        // size_t
#include <stdexcept>                                                      // range_error




// Template Class Definition
template<typename T>
class ExtendableVector
{
  public:
    // Constructors, destructor, and assignments
    ExtendableVector            ( std::size_t capacity = 64      );       // power of 2, but nothing special about 2^6
    ExtendableVector            ( const ExtendableVector & other );       // Copy constructor
    ExtendableVector & operator=( const ExtendableVector & rhs   );       // Copy assignment
   ~ExtendableVector            ();

    // Queries
    T &          at        ( std::size_t index );                         // Checks bounds, throws std::range_error
    T &          operator[]( std::size_t index );                         // No bonds checking

    std::size_t size();
    bool        empty();


    // Iterators
    T * begin();
    T * end();


    // Mutators
    void push_back( const T & value );                                    // Checks capacity, throws std::range_error

    std::size_t erase( std::size_t index    );                            // Checks bounds, throws std::range_error
    T *         erase( T *         position );                            // Checks bounds, throws std::range_error

    void set( std::size_t index, const T & value );                       // Checks bounds, throws std::range_error

    std::size_t insert( std::size_t beforeIndex,    const T & value );    // Checks capacity, throws std::range_error
    T *         insert( T *         beforePosition, const T & value );    // Checks capacity, throws std::range_error

    void clear();


  private:
    std::size_t _size     = 0;                                            // number of elements in the data structure
    std::size_t _capacity = 0;                                            // length of the array
    T *         _array    = nullptr;                                      // pointer to dynamically allocated array

    void reserve( size_t newCapacity );                                   // helper function to change capacity
};






// Implementation

// Constructor with initial capacity argument
template<typename T>
ExtendableVector<T>::ExtendableVector( std::size_t capacity )
  : _size( 0 ), _capacity( capacity ), _array( new T[capacity]() )
{}



template <typename T>
std::size_t ExtendableVector<T>::size()
{ return _size; }



template <typename T>
bool ExtendableVector<T>::empty()
{ return _size == 0; }



template <typename T>
T * ExtendableVector<T>::begin()
{ return _array; }



template <typename T>
T * ExtendableVector<T>::end()
{ return _array + _size; }                                                // Note the pointer arithmetic used



template <typename T>
void ExtendableVector<T>::clear()
{
  // destroy the elements held allowing resources to be released.  But maintain "this" ExtendableVector's capacity
  while( _size != 0 ) _array[--_size].~T();                               // Direct call to destructor
}



template <typename T>
T & ExtendableVector<T>::at( std::size_t index )
{
  if( index >= _size ) throw std::range_error( "index out of bounds" );

  return _array[ index ];
}



template <typename T>
void ExtendableVector<T>::push_back( const T & value )
{ insert( _size, value ); }                                               // delegate to insert() leveraging error checking



// Overloaded Array-Access Operator
template <typename T>
T & ExtendableVector<T>::operator[]( std::size_t index )
{ return _array[ index ]; }                                               // Note: array bounds intentionally not checked



template <typename T>
void ExtendableVector<T>::set( std::size_t index, const T & value )
{ at( index ) = value; }                                                  // delegate to at() leveraging error checking



// Removes element from position. Elements from higher positions are shifted back to fill gap.
// Vector size decrements
template <typename T>
std::size_t ExtendableVector<T>::erase( std::size_t index )
{
  if( index >= _size ) throw std::range_error( "index out of bounds" );

  // shift elements to the left and decrement the number of elements in the container
  std::move( _array + index + 1, _array + _size, _array + index );        // Note the pointer arithmetic here
  --_size;

  return index;
}



template <typename T>
T * ExtendableVector<T>::erase( T * position )
{
  // delegate to delete by index
  auto index = position - begin();                                        // Note the pointer arithmetic here
  erase( index );
  return position;
}



// Copies x to element at position. Items at that position and higher are shifted over to make room. Vector size increments.
template <typename T>
std::size_t ExtendableVector<T>::insert( std::size_t beforeIndex, const T & value )
{
  if( _size >= _capacity ) reserve( 2 * _capacity );                      // If at max capacity, double the capacity
  if( beforeIndex > _size ) beforeIndex = _size;                          // insert at the back

  // move elements to create space starting from the right and working left
  std::move_backward( _array + beforeIndex, _array + _size, _array + _size + 1 );    // Note the pointer arithmetic here

  _array[ beforeIndex ] = value;                                          // make a copy of the element in the empty slot
  ++_size;

  return beforeIndex;
}



template <typename T>
T* ExtendableVector<T>::insert( T * beforePosition, const T & value )
{
  auto index = beforePosition - begin();                                  // Note the pointer arithmetic here
  insert( index, value );
  return beforePosition;
}



template <typename T>
void ExtendableVector<T>::reserve( std::size_t newCapacity )
{
  if( newCapacity > _capacity )
  {
    T * newArray = new T[newCapacity]();
    // Move values to new array
    std::move( _array, _array + _size, newArray );

    delete[] _array;
    _array    = newArray;
    _capacity = newCapacity;
  }
}



// Copy Constructor
template <typename T>
ExtendableVector<T>::ExtendableVector( const ExtendableVector<T> & other )
: _size( other._size ), _capacity( other._capacity ), _array( new T[other._capacity]() )
{
  // Copy each element from the other vector to this vector
  std::copy_n( other._array, other._size, _array );
}



// Overloaded Assignment Operator
template<typename T>
ExtendableVector<T> & ExtendableVector<T>::operator=( const ExtendableVector<T> & rhs )
{
  if( this != &rhs )
  {
    // Can the stuff in the right hand side (rhs) fit into this vector? If not, expand this vector's capacity
    reserve( rhs._size );

    std::copy( rhs._array, rhs._array + rhs._size, _array );
    _size = rhs._size;
  }

  return *this;
}



// Destructor
template <typename T>
ExtendableVector<T>::~ExtendableVector()
{ delete[] _array; }
