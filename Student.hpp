#pragma once

#include <iostream>
#include <string>




class Student
{
  friend std::ostream & operator<<( std::ostream & os, const Student & student );
  friend std::istream & operator>>( std::istream & is,       Student & student );

  friend bool operator==( const Student & lhs, const Student & rhs );
  friend bool operator <( const Student & lhs, const Student & rhs );

  public:
    Student();
    Student( std::string name, unsigned nsem = 1U );

    void updateNSemesters();
    void name            ( const std::string & name      );
    void semesters       ( unsigned            semesters );

  private:
    std::string _name;
    unsigned    _numOfSemesters = 0;
};


bool operator!=( const Student & lhs, const Student & rhs );
bool operator<=( const Student & lhs, const Student & rhs );
bool operator> ( const Student & lhs, const Student & rhs );
bool operator>=( const Student & lhs, const Student & rhs );
