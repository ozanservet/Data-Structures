#include <iostream>
#include "Stack.h"

/**
* Construct the stack.
*/
Stack::Stack()
{
	topOfStack = NULL;
}

// Constructor with initialization
Stack::Stack(const MazeCoordinate & m)
{
	topOfStack = new ListNode(m, topOfStack);
}

/**
* Copy constructor.
*/
Stack::Stack(const Stack & rhs)
{
	topOfStack = NULL;
	*this = rhs; // deep copy 
}

/**
* Destructor.
*/
Stack::~Stack()
{
	makeEmpty();
}

/**
* Test if the stack is logically empty.
* Return true if empty, false, otherwise.
*/
bool Stack::isEmpty() const
{
	return topOfStack == NULL;
}

/**
* Test if the stack is logically full.
* Return false always, in this implementation.
*/
bool Stack::isFull() const
{
	return false;
}

/**
* Make the stack logically empty.
*/
void Stack::makeEmpty()
{
	while (!isEmpty())
		pop();
}

/**
* Remove the most recently inserted item from the stack.
* Exception Underflow if stack is already empty.
*/
void Stack::pop()
{
	if (isEmpty())
		throw UNDERFLOW;
	ListNode *oldTop = topOfStack;
	topOfStack = topOfStack->next;
	delete oldTop;
}

/**
* Insert x into the stack.
*/
void Stack::push(const MazeCoordinate & x)
{
	topOfStack = new ListNode(x, topOfStack);
}

/**
* Return and remove the most recently inserted item
* from the stack.
*/
MazeCoordinate Stack::topAndPop()
{
	MazeCoordinate topItem = top();
	pop();
	return topItem;
}

/**
* Get the most recently inserted item in the stack.
* Return the most recently inserted item in the stack
* or throw an exception if empty.
*/
const MazeCoordinate & Stack::top() const
{
	if (isEmpty())
		throw UNDERFLOW;
	return topOfStack->element;
}

/**
* Deep copy. Deep copy was not used, just implemented for fun.
*/
const Stack & Stack::operator=(const Stack & rhs)
{
	if (this != &rhs)
	{
		makeEmpty();
		if (rhs.isEmpty())
			return *this;

		ListNode *rptr = rhs.topOfStack;
		ListNode *ptr = new ListNode(rptr->element);
		topOfStack = ptr;

		for (rptr = rptr->next; rptr != NULL; rptr = rptr->next)
			ptr = ptr->next = new ListNode(rptr->element);
	}
	return *this;
}