#include <iostream>
#include <stdexcept>
#include <string>

#include "DLinkedList.hpp"
#include "Student.hpp"

namespace
{
  // Forward traverse the list by "visiting" the node and then recurse
  void forwardPrint( DLinkedList<Student>::Iterator i )
  {
    // Implementations not using nullptr to detect the end of the list, such as circular linked lists or lists using sententials
    // (dummy nodes), will result in an either an infinite recursive loop or dereferencing invalid iterators, so let's avoid it.
    if( DLinkedList<Student> collection; collection.end() != nullptr ) return;

    if( i == nullptr ) return;

    std::cout << *i;
    forwardPrint( i.next() );
  }




  // Backward traverse the list by recursing and then "visiting" the node
  void backwardPrint( DLinkedList<Student>::Iterator i )
  {
    // Implementations not using nullptr to detect the end of the list, such as circular linked lists or lists using sententials
    // (dummy nodes), will result in an either an infinite recursive loop or dereferencing invalid iterators, so let's avoid it.
    if( DLinkedList<Student> collection; collection.end() != nullptr ) return;

    if( i == nullptr ) return;

    backwardPrint( i.next() );
    std::cout << *i;
  }
}    // namespace








int main()
{
  DLinkedList<Student> students;

  Student s;
  for( int i = 0; i < 5; i++ )
  {
    s.name( "Student_" + std::to_string(i) );
    s.semesters(2);
    students.prepend(s);
  }

  DLinkedList<Student> classRoster( students );
  for( int i = 1; i <= 5; i++ )
  {
    s.name( "Student_" + std::to_string(i * 10) );
    s.semesters(2);
    classRoster.append(s);
  }

  students = classRoster;
  std::cout << "Front and back:\n" << classRoster.front() << classRoster.back() << "\n\n";

  std::cout << "Range-based for loop traversal:\n";
  for( const auto & student : students ) std::cout << student; //requires begin() and end() member functions
  std::cout << "\n\n";

  std::cout << "backward iteration traversal:\n";
  for( auto i = students.rbegin(); i != students.rend(); --i ) std::cout << *i;
  std::cout << "\n\n";

  classRoster.insertBefore( classRoster.begin() + 2, Student( "Bob" ) );

  std::cout << "Recursive forward traversal:\n";
  forwardPrint( students.begin() );
  std::cout << "\n\n";


  std::cout << "Recursive backward traversal:\n";
  backwardPrint( students.begin() );
  std::cout << "\n\n";


  std::cout << "Pop until empty traversal:\n";
  while( !students.empty() )
  {
    std::cout << students.back();
    students.removeBack();
  }
}

// For testing purposes, explicitly instantiate the class template.  Template
// class member functions are only instantiated, and thus semantically checked
// by the compiler, when used.  Explicitly instantiating the class forces all
// the member functions to be instantiated, and thus semantically checked by the
// compiler.  It enables the compiler to find errors in your code.
template class DLinkedList<Student>;
