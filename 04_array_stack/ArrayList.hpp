#pragma once
#include <iostream>
#include <stdexcept>

template<typename T>
class ArrayList
{
public:
	ArrayList();
	ArrayList(const ArrayList<T>& other);
	~ArrayList();


	void append(T value);
	void prepend(T value);
	T popFront();
	T popBack();
	void insertAt(int id, T value);
	void removeAt(int id);
	T get(int id) const;

	int size() const;
	bool isEmpty() const;
	void print() const;

	T& operator[](int id);
	const T& operator[](int id) const;
	ArrayList& operator=(const ArrayList<T>& other);

private:
	int capacity;
	int m_size;
	int growFactor;
	T* pData;

	void copy(T* const newTemp) const;
	void resize();
	bool arrayIsFull() const;
	void checkIndex(int id) const;
};

///////////////////////////////////////////////////////IMPLEMENTATION///////////////////////////////////////////////////////

template<typename T>
ArrayList<T>::ArrayList()
{
	this->capacity = 4;
	this->m_size = 0;
	this->growFactor = 2;
	this->pData = new T[capacity];
}

template<typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& other)
{
	this->capacity = other.capacity;
	this->m_size = other.m_size;
	this->growFactor = other.growFactor;
	this->pData = new T[capacity];

	for (int i = 0; i < m_size; i++)
	{
		pData[i] = other.pData[i];
	}
}

template<typename T>
ArrayList<T>::~ArrayList()
{
	delete[] pData;
}

template<typename T>
void ArrayList<T>::append(T value)
{
	if (arrayIsFull())
	{
		resize();
	}

	pData[m_size++] = value;
}

template<typename T>
void ArrayList<T>::prepend(T value)
{
	if (arrayIsFull())
	{
		resize();
	}

	for (int i = m_size; i > 0; i--)
	{
		pData[i] = pData[i - 1];
	}

	pData[0] = value;
	m_size++;
}

template<typename T>
T ArrayList<T>::popFront()
{
	if (isEmpty())
	{
		throw std::out_of_range("ArrayList is empty");
	}

	T temp = pData[0];
	this->removeAt(0);
	return temp;
}

template<typename T>
T ArrayList<T>::popBack()
{
	if (isEmpty())
	{
		throw std::out_of_range("ArrayList is empty");
	}

	return pData[--m_size];
}

template<typename T>
void ArrayList<T>::insertAt(int id, T value)
{
	if (id > m_size || id < 0)
	{
		throw std::out_of_range("List index out of range");
	}

	if (id == m_size)
	{
		this->append(value);
		return;
	}

	if (arrayIsFull())
	{
		resize();
	}

	for (int i = m_size; i > id; i--)
	{
		pData[i] = pData[i - 1];
	}

	pData[id] = value;
	m_size++;
}

template<typename T>
void ArrayList<T>::removeAt(int id)
{
	checkIndex(id);

	for (int i = id; i < m_size - 1; i++)
	{
		pData[i] = pData[i + 1];
	}

	m_size--;
}

template<typename T>
T ArrayList<T>::get(int id) const
{
	checkIndex(id);

	return pData[id];
}

template<typename T>
bool ArrayList<T>::isEmpty() const
{
	return m_size == 0;
}

template<typename T>
void ArrayList<T>::print() const
{
	std::cout << '[';

	for (int i = 0; i < m_size; i++)
	{
		std::cout << pData[i];

		if (i != m_size - 1)
		{
			std::cout << ',';
		}
	}

	std::cout << ']';
}

template<typename T>
int ArrayList<T>::size() const
{
	return m_size;
}

template<typename T>
T& ArrayList<T>::operator[](int id)
{
	checkIndex(id);

	return pData[id];
}

template<typename T>
const T& ArrayList<T>::operator[](int id) const
{
	checkIndex(id);

	return pData[id];
}

template<typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& other)
{

	if (this == &other)
		return *this;

	delete[] this->pData;

	this->capacity = other.capacity;
	this->m_size = other.m_size;
	this->growFactor = other.growFactor;
	this->pData = new T[capacity];

	for (int i = 0; i < m_size; i++)
	{
		pData[i] = other.pData[i];
	}

	return *this;
}

template<typename T>
void ArrayList<T>::copy(T* const pTemp) const
{
	for (int i = 0; i < m_size; i++)
	{
		pTemp[i] = pData[i];
	}
}

template<typename T>
void ArrayList<T>::resize()
{
	capacity *= growFactor;
	T* pTemp = new T[capacity];

	copy(pTemp);

	delete[] pData;
	pData = pTemp;
}

template<typename T>
bool ArrayList<T>::arrayIsFull() const
{
	return m_size == capacity;
}

template<typename T>
void ArrayList<T>::checkIndex(int id) const
{
	if (isEmpty())
	{
		throw std::out_of_range("ArrayList is empty");
	}

	if (id < 0 || id >= m_size)
	{
		throw std::out_of_range("List index out of range");
	}
}
