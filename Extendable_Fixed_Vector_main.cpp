#include <iomanip>    // quoted()
#include <iostream>
#include <string>

#include "ExtendableVector.hpp"
#include "FixedVector.hpp"
#include "Student.hpp"




namespace    // anonymous
{
  template<typename T>
  void test( T & vector )
  {
    std::cout << "\n\nTesting " << std::quoted( __func__ ) << '\n';

    Student s( "Adam", 2 );
    vector.push_back( s );
    vector.push_back( Student( "Bob", 1 ) );
    vector.push_back( Student( "Dolores", 3 ) );
    for( const auto & student : vector ) std::cout << student;


    // add student Carla between Bob and Dolores
 // vector.insert( 2,                  Student( "Carla" ) );          // index form
    vector.insert( vector.begin() + 2, Student( "Carla" ) );          // iterator form
    for( const auto & student : vector ) std::cout << student;


    // update Carla's record
    vector[2].updateNSemesters();
    std::cout << vector[2];


    // remove student Adam (element at index 0)
 // vector.erase( 0              );                                   // index form
    vector.erase( vector.begin() );                                   // iterator form
    for( const auto & student : vector ) std::cout << student;


    // Copy and assignment
    auto aCopy = vector;                                              // copy
    for( const auto & student : aCopy ) std::cout << student;

    vector.clear();
    for( const auto & student : aCopy ) std::cout << student;

    vector = aCopy;    // assignment;
    for( const auto & student : aCopy ) std::cout << student;
  }
}    // anonymous namespace



int main()
{
  FixedVector<Student>      fixedStudentVector( 10 );
  ExtendableVector<Student> extendableStudentVector;                  // in contrast to FixedVector, capacity is not specified

  test( fixedStudentVector      );
  test( extendableStudentVector );

  return 0;
}
