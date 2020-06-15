#pragma once

struct MazeCoordinate
{
	int x;
	int y;
	MazeCoordinate::MazeCoordinate() {}
	MazeCoordinate::MazeCoordinate(int col, int row) : x(col), y(row) {}
};

// Stack with Linked Lists
class Stack
{
private:
	struct ListNode
	{
		MazeCoordinate   element;
		ListNode *next;

		ListNode(const MazeCoordinate & theElement, ListNode * n = NULL) : element(theElement), next(n) { }
	};
	ListNode *topOfStack;  // list itself is the stack

public:
	Stack();
	Stack(const MazeCoordinate & m);
	Stack(const Stack & rhs);
	~Stack();

	bool isEmpty() const;
	bool isFull() const;
	void makeEmpty();

	void pop();
	void push(const MazeCoordinate & x);
	MazeCoordinate topAndPop();
	const MazeCoordinate & top() const;

	const Stack & operator=(const Stack & rhs);
};