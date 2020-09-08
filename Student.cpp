#include <iomanip>    // quoted()
#include <iostream>
#include <string>

#include "Student.hpp"




/******************************************************************************
** Constructors, assignments, and destructor
******************************************************************************/
// Because at least one other constructor has been declared, the compiler won't
// synthesize the default constructor, so define it explicitly
Student::Student() = default;


Student::Student( std::string name, unsigned nsem )
  : _name( name ), _numOfSemesters( nsem )    // Example: constructor initialization list to initialize instance attributes
{}




/******************************************************************************
** Queries
******************************************************************************/




/******************************************************************************
** Mutators
******************************************************************************/

void Student::updateNSemesters()
{ _numOfSemesters++; }

void Student::name( const std::string & name )
{ _name = name; }

void Student::semesters( unsigned semesters )
{ _numOfSemesters = semesters; }



/******************************************************************************
** Logical Operators
**   Notes:
**   1) These are intentionally non-member functions to supports symmetry
**      (design decision)
**   2) short circuit boolean algebra intentionally used to define multiple
**      column (i.e. attribute) sort order
**   3) implement only "equal to" and "less than" functions and define all the
**      others in terms of these two
**   4) C++20 changes this technique with the introduction of the spaceship
**      operator
******************************************************************************/
bool operator<( const Student & lhs, const Student & rhs )
{
  if     ( auto result = lhs._name.compare(rhs._name); result != 0 )  return result < 0;
  else if( lhs._numOfSemesters != rhs._numOfSemesters              )  return lhs._numOfSemesters < rhs._numOfSemesters;
  
  // At this point all attributes are equal, so the lhs cannot be less than the rhs
  return false;
}

bool operator==( const Student & lhs, const Student & rhs )
{
  return lhs._name           == rhs._name
      && lhs._numOfSemesters == rhs._numOfSemesters;
  // alternative:
  //   return !( lhs < rhs )  &&  !( rhs < lhs );
}

bool operator!=( const Student & lhs, const Student & rhs )   { return !( lhs == rhs ); }
bool operator<=( const Student & lhs, const Student & rhs )   { return !( rhs <  lhs ); }
bool operator> ( const Student & lhs, const Student & rhs )   { return  ( rhs <  lhs ); }
bool operator>=( const Student & lhs, const Student & rhs )   { return !( lhs <  rhs ); }




/******************************************************************************
** Insertion and Extraction Operators
**   Notes:
**   1) These must be non-member functions
******************************************************************************/
std::ostream & operator<<( std::ostream & os, const Student & student )
{
  os << "Name: " << std::quoted( student._name );
  os << ", No. of semesters= " << student._numOfSemesters << '\n';

  return os;
}

std::istream & operator>>( std::istream & is, Student & student )
{
  is >> std::quoted( student._name );
  is >> student._numOfSemesters;

  return is;
}
