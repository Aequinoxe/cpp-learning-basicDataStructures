#pragma once
#include "ArrayList.hpp"

template<typename T>
class ArrayStack
{
public:
	ArrayStack();
	
	~ArrayStack();

	void push(const T& value);

	T pop();

	const T& top() const;

	bool isEmpty() const;

	void printFromBottom() const;

	int size() const;

private:
	ArrayList<T> array;
};

/////////////////////////////////////////////////////IMPLEMENTATION/////////////////////////////////////

template<typename T>
ArrayStack<T>::ArrayStack()
{

}

template<typename T>
ArrayStack<T>::~ArrayStack()
{

}

template<typename T>
void ArrayStack<T>::push(const T& value)
{
	array.append(value);
}

template<typename T>
T ArrayStack<T>::pop()
{

	if (isEmpty())
	{
		throw std::runtime_error("Stack is empty");
	}

	return array.popBack();
}

template<typename T>
const T& ArrayStack<T>::top() const
{
	int size = array.size();
	
	if (isEmpty())
	{
		throw std::runtime_error("Stack is empty");
	}
	
	return array[size - 1];
}

template<typename T>
bool ArrayStack<T>::isEmpty() const
{
	return array.isEmpty();
}

template<typename T>
void ArrayStack<T>::printFromBottom() const
{
	array.print();
	std::cout << " <-- TOP";
}

template<typename T>
int ArrayStack<T>::size() const
{
	return array.size();
}
