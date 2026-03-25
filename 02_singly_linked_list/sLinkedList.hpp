#pragma once
#include <iostream>
#include <stdexcept>

template<typename T>
class sLinkedList;

template<typename T>
struct Node
{
public:
	Node();
	Node(T value, Node* pNext);
	~Node();

private:
	T value;
	Node* pNext;

	friend class sLinkedList<T>;
};

template<typename T>
class sLinkedList
{
public:
	sLinkedList();
	~sLinkedList();
	sLinkedList(const sLinkedList& other);

	void appendFront(const T& value);
	void appendBack(const T& value);
	void insertAfter(Node<T>* pNode, const T& value);
	void removeAfter(Node<T>* pNode);
	void removeFront();
	void removeBack();
	T popFront();
	T popBack();
	const T& front() const;
	const T& back() const;

	sLinkedList& operator=(const sLinkedList& other);

	int size() const;
	void reverse();
	const Node<T>* find(const T& value) const;
	bool contains(const T& value) const;
	void clear();
	void removeValue(const T& value);
	void merge(sLinkedList& other);

	bool isEmpty() const;
	void print() const;

private:
	int m_size;
	Node<T>* pHead;
	Node<T>* pTail;
};

//////////////////////////////IMPLEMENTATION/////////////////////////////////////////////

template<typename T>
Node<T>::Node() :
	value{}
{
	this->pNext = nullptr;
}

template<typename T>
Node<T>::Node(T value, Node<T>* pNext)
{
	this->value = value;
	this->pNext = pNext;
}

template<typename T>
Node<T>::~Node()
{

}

template<typename T>
sLinkedList<T>::sLinkedList()
{
	pHead = nullptr;
	pTail = nullptr;
	this->m_size = 0;
}

template<typename T>
sLinkedList<T>::~sLinkedList()
{
	clear();
}

template<typename T>
sLinkedList<T>::sLinkedList(const sLinkedList<T>& other)
{
	this->pHead = nullptr;
	this->pTail = nullptr;
	this->m_size = 0;

	Node<T>* pCurrent = other.pHead;

	while (pCurrent != nullptr)
	{
		this->appendBack(pCurrent->value);
		pCurrent = pCurrent->pNext;
	}
}

template<typename T>
void sLinkedList<T>::appendFront(const T& value)
{
	if (pHead == nullptr)
	{
		pHead = new Node<T>(value, nullptr);
		pTail = pHead;
		m_size++;
		return;
	}

	Node<T>* pNewHead = new Node<T>(value, pHead);
	pHead = pNewHead;
	m_size++;
}

template<typename T>
void sLinkedList<T>::appendBack(const T& value)
{
	if (pHead == nullptr)
	{
		pHead = new Node<T>(value, nullptr);
		pTail = pHead;
		m_size++;
		return;
	}

	Node<T>* pNewTail = new Node<T>(value, nullptr);
	pTail->pNext = pNewTail;
	pTail = pNewTail;
	m_size++;
}

template<typename T>
void sLinkedList<T>::insertAfter(Node<T>* pNode, const T& value)
{
	if (pNode == nullptr)
	{
		return;
	}

	Node<T>* pNewNode = new Node<T>(value, pNode->pNext);

	if (pNode->pNext == nullptr)
	{
		pTail = pNewNode;
	}

	pNode->pNext = pNewNode;
	m_size++;
}

template<typename T>
void sLinkedList<T>::removeAfter(Node<T>* pNode)
{
	if (pNode == nullptr || pNode == pTail)
	{
		return;
	}

	Node<T>* pToDelete = pNode->pNext;
	Node<T>* pAfterNext = pToDelete->pNext;
	pNode->pNext = pAfterNext;

	if (pToDelete == pTail)
	{
		pTail = pNode;
	}

	delete pToDelete;
	m_size--;
}

template<typename T>
void sLinkedList<T>::removeFront()
{
	if (pHead == nullptr)
	{
		return;
	}

	if (pHead == pTail)
	{
		delete pHead;
		pHead = nullptr;
		pTail = nullptr;
		m_size--;
		return;
	}

	Node<T>* pNewHead = pHead->pNext;
	delete pHead;
	pHead = pNewHead;
	m_size--;
}

template<typename T>
void sLinkedList<T>::removeBack()
{
	if (this->isEmpty())
	{
		return;
	}

	if (pHead == pTail)
	{
		delete pHead;
		pHead = nullptr;
		pTail = nullptr;
		m_size--;
		return;
	}

	Node<T>* pCurrent = pHead;
	while (pCurrent->pNext->pNext != nullptr)
	{
		pCurrent = pCurrent->pNext;
	}

	delete pCurrent->pNext;
	pCurrent->pNext = nullptr;
	pTail = pCurrent;
	m_size--;
}

template<typename T>
T sLinkedList<T>::popFront()
{
	if (this->isEmpty())
	{
		throw std::runtime_error("List is empty");
	}

	T temp = pHead->value;
	this->removeFront();
	return temp;
}

template<typename T>
T sLinkedList<T>::popBack()
{
	if (this->isEmpty())
	{
		throw std::runtime_error("List is empty");
	}

	T temp = pTail->value;
	this->removeBack();
	return temp;
}

template<typename T>
const T& sLinkedList<T>::front() const
{
	if (this->isEmpty())
	{
		throw std::runtime_error("List is empty");
	}

	return pHead->value;
}

template<typename T>
const T& sLinkedList<T>::back() const
{
	if (this->isEmpty())
	{
		throw std::runtime_error("List is empty");
	}

	return pTail->value;
}

template<typename T>
sLinkedList<T>& sLinkedList<T>::operator=(const sLinkedList& other)
{

	if (this == &other)
	{
		return *this;
	}

	clear();

	if (other.isEmpty())
	{
		return *this;
	}

	this->appendBack(other.pHead->value);
	Node<T>* pCurrent = other.pHead;

	while (pCurrent->pNext != nullptr)
	{
		pCurrent = pCurrent->pNext;

		this->appendBack(pCurrent->value);
	}

	return *this;
}

template<typename T>
int sLinkedList<T>::size() const
{
	return m_size;
}

template<typename T>
void sLinkedList<T>::reverse()
{
	if (isEmpty() || pHead == pTail)
	{
		return;
	}

	Node<T>* pPrevious = nullptr;
	Node<T>* pCurrent = pHead;
	Node<T>* pAfterCurrent = nullptr;

	while (pCurrent != nullptr)
	{
		pAfterCurrent = pCurrent->pNext;
		pCurrent->pNext = pPrevious;
		pPrevious = pCurrent;
		pCurrent = pAfterCurrent;
	}

	pTail = pHead;
	pHead = pPrevious;
}

template<typename T>
const Node<T>* sLinkedList<T>::find(const T& value) const
{
	const Node<T>* pTemp = pHead;

	while (pTemp != nullptr)
	{
		if (pTemp->value == value)
		{
			return pTemp;
		}
		pTemp = pTemp->pNext;
	}

	return nullptr;
}

template<typename T>
bool sLinkedList<T>::contains(const T& value) const
{
	return find(value) != nullptr;
}

template<typename T>
void sLinkedList<T>::clear()
{
	Node<T>* pTemp = pHead;

	while (pTemp != nullptr)
	{
		Node<T>* pDelete = pTemp;
		pTemp = pTemp->pNext;
		delete pDelete;
	}

	pHead = nullptr;
	pTail = nullptr;
	m_size = 0;
}

template<typename T>
void sLinkedList<T>::removeValue(const T& value)
{
	Node<T>* pCurrent = pHead;
	Node<T>* pPrevious = nullptr;

	while (pCurrent != nullptr)
	{

		if (pCurrent->value == value)
		{
			Node<T>* pAfterCurrent = pCurrent->pNext;

			if (pHead == pCurrent)
			{
				removeFront();
			}
			else
			{
				removeAfter(pPrevious);
			}

			pCurrent = pAfterCurrent;
		}
		else
		{
			pPrevious = pCurrent;
			pCurrent = pCurrent->pNext;
		}
	}
}

template<typename T>
void sLinkedList<T>::merge(sLinkedList& other)
{
	if (this == &other || other.isEmpty())
	{
		return;
	}

	if (this->isEmpty())
	{
		this->pHead = other.pHead;
		this->pTail = other.pTail;
		this->m_size = other.m_size;
	}
	else
	{
	pTail->pNext = other.pHead;
	pTail = other.pTail;
	m_size += other.m_size;
	}

	other.pHead = nullptr;
	other.pTail = nullptr;
	other.m_size = 0;
}

template<typename T>
bool sLinkedList<T>::isEmpty() const
{
	return (m_size == 0);
}

template<typename T>
void sLinkedList<T>::print() const
{
	std::cout << "[";

	if (pHead == nullptr)
	{
		std::cout << "]";
		return;
	}

	const Node<T>* pTemp = pHead;

	while (pTemp->pNext != nullptr)
	{
		std::cout << pTemp->value << ",";
		pTemp = pTemp->pNext;
	}

	std::cout << pTail->value << "]";
}
