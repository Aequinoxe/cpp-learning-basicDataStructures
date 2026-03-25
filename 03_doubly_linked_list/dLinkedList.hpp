#pragma once
#include <iostream>
#include <stdexcept>

template<typename T>
void swap(T& arg1, T& arg2);

template<typename T>
class dLinkedList;

template<typename T>
struct Node
{
public:
	Node();
	Node(T value, Node* pNext, Node* pPrev);
	~Node();

private:
	T value;
	Node* pNext;
	Node* pPrev;

	friend class dLinkedList<T>;
};

template<typename T>
class dLinkedList
{
public:
	dLinkedList();
	~dLinkedList();
	dLinkedList(const dLinkedList& other);

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

	dLinkedList& operator=(const dLinkedList& other);

	int size() const;
	void reverse();
	const Node<T>* find(const T& value) const;
	bool contains(const T& value) const;
	void clear();
	void removeValue(const T& value);
	void merge(dLinkedList& other);

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
	this->pPrev = nullptr;
}

template<typename T>
Node<T>::Node(T value, Node<T>* pNext, Node<T>* pPrev)
{
	this->value = value;
	this->pNext = pNext;
	this->pPrev = pPrev;
}

template<typename T>
Node<T>::~Node()
{

}

template<typename T>
dLinkedList<T>::dLinkedList()
{
	pHead = nullptr;
	pTail = nullptr;
	this->m_size = 0;
}

template<typename T>
dLinkedList<T>::~dLinkedList()
{
	clear();
}

template<typename T>
dLinkedList<T>::dLinkedList(const dLinkedList<T>& other)
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
void dLinkedList<T>::appendFront(const T& value)
{
	if (pHead == nullptr)
	{
		pHead = new Node<T>(value, nullptr, nullptr);
		pTail = pHead;
		m_size++;
		return;
	}

	Node<T>* pNewNode = new Node<T>;

	pHead->pPrev = pNewNode;
	pNewNode->value = value;
	pNewNode->pNext = pHead;
	pHead = pNewNode;

	m_size++;
}

template<typename T>
void dLinkedList<T>::appendBack(const T& value)
{
	if (pHead == nullptr)
	{
		pHead = new Node<T>(value, nullptr, nullptr);
		pTail = pHead;
		m_size++;
		return;
	}

	Node<T>* pNewNode = new Node<T>;

	pTail->pNext = pNewNode;
	pNewNode->value = value;
	pNewNode->pPrev = pTail;
	pTail = pNewNode;

	m_size++;
}

template<typename T>
void dLinkedList<T>::insertAfter(Node<T>* pNode, const T& value)
{
	if (pNode == nullptr)
	{
		return;
	}

	Node<T>* pNewNode = new Node<T>(value, pNode->pNext, pNode);
	m_size++;
	pNode->pNext = pNewNode;

	if (pNewNode->pNext == nullptr)
	{
		pTail = pNewNode;
		return;
	}
	
	pNewNode->pNext->pPrev = pNewNode;
}

template<typename T>
void dLinkedList<T>::removeAfter(Node<T>* pNode)
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
	else
	{
		pAfterNext->pPrev = pNode;
	}

	delete pToDelete;
	m_size--;
}

template<typename T>
void dLinkedList<T>::removeFront()
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
	pNewHead->pPrev = nullptr;
	delete pHead;
	pHead = pNewHead;

	m_size--;
}

template<typename T>
void dLinkedList<T>::removeBack()
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

	Node<T>* pNewTail = pTail->pPrev;
	pNewTail->pNext = nullptr;
	delete pTail;
	pTail = pNewTail;

	m_size--;
}

template<typename T>
T dLinkedList<T>::popFront()
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
T dLinkedList<T>::popBack()
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
const T& dLinkedList<T>::front() const
{
	if (this->isEmpty())
	{
		throw std::runtime_error("List is empty");
	}

	return pHead->value;
}

template<typename T>
const T& dLinkedList<T>::back() const
{
	if (this->isEmpty())
	{
		throw std::runtime_error("List is empty");
	}

	return pTail->value;
}

template<typename T>
dLinkedList<T>& dLinkedList<T>::operator=(const dLinkedList& other)
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
int dLinkedList<T>::size() const
{
	return m_size;
}

template<typename T>
void dLinkedList<T>::reverse()
{
	Node<T>* current = pHead;
	while (current != nullptr)
	{
		swap(current->pPrev, current->pNext);
		current = current->pPrev;
	}
	swap(pHead, pTail);
}

template<typename T>
const Node<T>* dLinkedList<T>::find(const T& value) const
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
bool dLinkedList<T>::contains(const T& value) const
{
	return find(value) != nullptr;
}

template<typename T>
void dLinkedList<T>::clear()
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
void dLinkedList<T>::removeValue(const T& value)
{
	Node<T>* pCurrent = pHead;

	while (pCurrent != nullptr)
	{
		if (pCurrent->value == value)
		{
			if (pCurrent == pHead)
			{
				pCurrent = pHead->pNext;
				removeFront();
				continue;
			}
			else if (pCurrent == pTail)
			{
				removeBack();
				return;
			}
			else
			{
				Node<T>* pDelete = pCurrent;
				Node<T>* pNextTemp = pDelete->pNext;
				Node<T>* pPrevTemp = pDelete->pPrev;
				
				pDelete->pPrev->pNext = pNextTemp;
				pDelete->pNext->pPrev = pPrevTemp;
				
				delete pDelete;
				m_size--;
				pCurrent = pNextTemp;
				continue;
			}
		}
		pCurrent = pCurrent->pNext;
	}
}

template<typename T>
void dLinkedList<T>::merge(dLinkedList& other)
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
		other.pHead->pPrev = pTail;
		pTail = other.pTail;
		m_size += other.m_size;
	}

	other.pHead = nullptr;
	other.pTail = nullptr;
	other.m_size = 0;
}

template<typename T>
bool dLinkedList<T>::isEmpty() const
{
	return (m_size == 0);
}

template<typename T>
void dLinkedList<T>::print() const
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

template<typename T>
void swap(T& arg1, T& arg2)
{
	T temp = arg1;
	arg2 = arg2;
	arg2 = temp;
}
