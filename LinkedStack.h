/** ADT stack: Link-based implementation.
 @file LinkedStack.h */
#ifndef _LINKED_STACK
#define _LINKED_STACK

#include "StackInterface.h"
#include "Node.h"
#include "PrecondViolatedExcep.h"

template <class ItemType>
class LinkedStack : public StackInterface<ItemType>
{
private:
    Node<ItemType> *topPtr; // Pointer to first node in the chain;
    // this node contains the stack’s top
public:
    // Constructors and destructor:
    LinkedStack();                                    // Default constructor
    LinkedStack(const LinkedStack<ItemType> &aStack); // Copy constructor
    virtual ~LinkedStack();                           // Destructor
                                                      // Stack operations:
    bool isEmpty() const;
    bool push(const ItemType &newItem);
    bool pop();
    ItemType peek() const noexcept(false); // Updated to noexcept
}; // end LinkedStack
#include "LinkedStack.cpp"
#endif
