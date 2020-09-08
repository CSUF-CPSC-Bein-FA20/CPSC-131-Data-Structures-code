#include <array>
#include <exception>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <typeinfo>
#include <vector>

#include "DLinkedList.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
#include "Student.hpp"



// Queue calls the first element "front", stack calls it "top".  Create a function to delegate to the right thing
template<class Container>
auto top( Container & c )
{ return c.top(); }

template<typename T, typename C>
auto top( std::queue<T, C> & c )
{ return c.front(); }



// A simple test driver to exercise the container.  Sense stacks and queues have (nearly) the same interface, the same test driver
// is used for both.  The container tested is intentionally passed by value (makes a local copy).
template<class Container_Type>
void test( Container_Type myContainer )
{
  std::cout << "Using:     " << typeid( myContainer ).name() << '\n'    // come compilers generate more readable results with
            << "Function:  " << __func__ << '\n';                       // type_info::name(), others with __func__, so let's do them
                                                                        // both just so we cover our bases

  // A stack is an Abstract Data Type, usually implemented as a limited interlace over some other data structure
  // Things you can do to a stack:
  myContainer.push( {"Tom"   } );
  myContainer.push( {"Aaron" } );
  myContainer.push( {"Brenda"} );
  myContainer.pop();
  myContainer.push( {"Katelyn"} );


  // Display the contents.  Stacks and queues do not allow traversal (you can't see anything but the top (stack and queue) and both
  // (queue only), so to display the contents we have to inspect each element at the top and then remove it until the container is
  // empty.
  while( !myContainer.empty() )
  {
    std::cout << top( myContainer );
    myContainer.pop();
  }
  std::cout << '\n';
}







int main()
{
  try
  {
    /////////////////// Stacks //////////////////////
    // zyBook Stack Usage
    Stack<Student> myStack_1;                               // empty stack where stack is implemented over a singly linked list (the default)
    test( myStack_1 );

    Stack<Student, DLinkedList<Student>> myStack_2;         // empty stack where stack is implemented over a double linked list
    test( myStack_2 );

    // array based Stack, not in zyBook
    Stack<Student, std::array<Student, 10>> myStack_3;      // empty stack where stack is implemented over a fixed sized standard array
    test( myStack_3 );

    // Standard Stack usage with standard containers
    std::stack<Student> myStack_4;                          // default standard stack (uses std::deque as underlying container)
    test( myStack_4 );

    std::stack<Student, std::list<Student>> myStack_5;      // standard stack with standard doubly linked list as underlying container
    test( myStack_5 );

    std::stack<Student, std::vector<Student>> myStack_6;    // standard stack with standard vector as underlying container
    test( myStack_6 );




    /////////////////// Queues //////////////////////
    // zyBook Queue Usage
    Queue<Student> myQueue_1;                               // empty queue where queue is implemented over a doubly linked list (the default)
    test( myQueue_1 );

    // array based Queue, not in zyBook
    Queue<Student, std::array<Student, 3>> myQueue_3;      // empty queue where queue is implemented over a fixed sized standard array
    test( myQueue_3 );

    // Standard Queue usage with standard containers
    std::queue<Student> myQueue_4;                          // default standard queue (uses std::deque as underlying container)
    test( myQueue_4 );

    std::queue<Student, std::list<Student>> myQueue_5;      // standard queue with standard doubly linked list as underlying container
    test( myQueue_5 );
  }

  catch (const std::exception & ex)
  {
    std::cerr << ex.what() << '\n';
  }
}
