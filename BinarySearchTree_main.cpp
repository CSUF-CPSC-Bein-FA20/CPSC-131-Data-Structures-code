#include <iostream>
#include <string>

#include "BinarySearchTree.hpp"






int main()
{
                                                                      //             Ricardo     //
  BinarySearchTree<std::string, double> studentGrades, gradeBook;     //             /           //
  studentGrades.insert( "Ricardo", 2.5  );                            //         Ellen           //
  studentGrades.insert( "Ellen",   3.5  );                            //          /  \           //
  studentGrades.insert( "Chen",    2.5  );                            //       Chen  Kevin       //
  studentGrades.insert( "Kevin",   3.25 );                            //                \        //
  studentGrades.insert( "Kumar",   3.05 );                            //                Kumar    //


  gradeBook = studentGrades;                                          // test assignment operator, copy constructor, and destructor


  std::string myKey = "Ellen";                                        // find grade of one student
  auto        value = studentGrades.search( myKey );

  std::cout << "Grade of " << myKey << " is " << value << '\n';

  studentGrades.printInorder();                                       // print the entire BST

  if( gradeBook.getHeight() != 3 ) std::cerr << "Tree height does not match expected\n";

  gradeBook.remove( "Ellen" );
  if( gradeBook.getHeight() != 2 ) std::cerr << "Tree height does not match expected\n";
}



// Explicit instantiation - a technique to ensure all functions of the template are created and semantically checked.  By default,
// only functions called get instantiated so you won't know it has compile errors until you actually call it.
template class BinarySearchTree<unsigned, float>;
