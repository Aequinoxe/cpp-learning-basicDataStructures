#pragma once
#include "sLinkedList.hpp"

template<typename T>
class ListStack
{
public:
	ListStack();

	~ListStack();

	void push(T value);

	T pop();

	const T& peek() const;

	bool isEmpty() const;

	void printFromTop() const;

	int size() const;

private:
	sLinkedList<T> list;
};

/////////////////////////IMPLEMENTATION//////////////////////////

template<typename T>
ListStack<T>::ListStack()
{

}

template<typename T>
ListStack<T>::~ListStack()
{

}

template<typename T>
void ListStack<T>::push(T value)
{
	list.prepend(value);
}

template<typename T>
T ListStack<T>::pop()
{
	if (isEmpty())
	{
		throw std::runtime_error("Stack is empty");
	}
	
	return list.popFront();
}

template<typename T>
const T& ListStack<T>::peek() const
{
	
	if (this->isEmpty())
	{
		throw std::runtime_error("Stack is empty");
	}

	return list.front();
}

template<typename T>
bool ListStack<T>::isEmpty() const
{
	return list.isEmpty();
}

template<typename T>
void ListStack<T>::printFromTop() const
{
	list.print();
}

template<typename T>
int ListStack<T>::size() const
{
	return list.size();
}
