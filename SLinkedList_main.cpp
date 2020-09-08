#include <iostream>
#include <stdexcept>
#include <string>

#include "SLinkedList.hpp"
#include "Student.hpp"




namespace
{
  // Forward traverse the list by "visiting" the node and then recurse
  void forwardPrint( SLinkedList<Student>::Iterator i )
  {
    if( i == nullptr ) return;

    std::cout << *i;
    forwardPrint( i.next() );
  }




  // Backward traverse the list by recursing and then "visiting" the node
  void backwardPrint( SLinkedList<Student>::Iterator i )
  {
    if( i == nullptr ) return;

    backwardPrint( i.next() );
    std::cout << *i;
  }
}    // namespace








int main()
{
  SLinkedList<Student> students;

  Student s;
  for( int i = 0; i < 5; i++ )
  {
    s.name( "Student_" + std::to_string(i) );
    s.semesters(2);
    students.prepend(s);
  }

  SLinkedList<Student> classRoster( students );
  for( int i = 1; i <= 5; i++ )
  {
    s.name( "Student_" + std::to_string(i * 10) );
    s.semesters(2);
    classRoster.append(s);
  }

  students = classRoster;
  std::cout << "Front and back:\n" << classRoster.front() << classRoster.back() << "\n\n";

  std::cout << "Range-based for loop traversal:\n";
  for( const auto & student : students ) std::cout << student; //requires SLinkedList::begin() and SLinkedList::end() member functions
  std::cout << "\n\n";

  classRoster.insertAfter( classRoster.begin()+2, Student("Bob") );

  std::cout << "Recursive forward traversal:\n";
  // Printing the list does not alter the list
  forwardPrint( students.begin() );
  std::cout << "\n\n";


  std::cout << "Recursive backward traversal:\n";
  // Printing the list does not alter the list
  backwardPrint( students.begin() );
  std::cout << "\n\n";

  // reverse the list 
  // This changes the list
  students.reverse();

  std::cout << "Recursive forward traversal (after reversal):\n";
  // Printing the list does not alter the list
  forwardPrint( students.begin() );
  std::cout << "\n\n";


  std::cout << "Recursive backward traversal (after reversal):\n";
  // Printing the list does not alter the list
  backwardPrint( students.begin() );
  std::cout << "\n\n";



  std::cout << "Pop until empty traversal:\n";
  while( !students.empty() )
  {
    std::cout << students.front();
    students.removeFront();
  }


  SLinkedList<unsigned int> testScores;
  testScores.append( 89 );
  testScores.append( 92 );
  testScores.append( 75 );
  testScores.append( 97 );
  std::cout << "\nTest score average is: " << testScores.add() / testScores.size() << "%\n";
}

// For testing purposes, explicitly instantiate the class template.  Template
// class member functions are only instantiated, and thus semantically checked
// by the compiler, when used.  Explicitly instantiating the class forces all
// the member functions to be instantiated, and thus semantically checked by the
// compiler.  It enables the compiler to find errors in your code.
// template class SLinkedList<Student>;
