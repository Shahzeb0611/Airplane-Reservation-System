#pragma once
#include <iostream>
using namespace std;

template <typename T>
class NodeL
{
public:
	T data;
	NodeL* next;
	NodeL()
	{
		next = NULL;
	}
	NodeL(T data)
	{
		this->data = data;
		next = NULL;
	}
	NodeL<T> operator =(NodeL<T>*& rhs) {
		this->data = rhs->data;
		this->next = rhs->next;
		return *this;
	}
};

template <typename T>
class List
{
public:
	NodeL < T >* head;
	NodeL < T >* tail;
	NodeL < T >* current;
	int size;

	List()
	{
		head = NULL;
		tail = NULL;
		current = NULL;
		size = 0;
	}
	List(NodeL<T>* n)
	{
		head = n;
		tail = n;
		head->next = NULL;
		tail->next = NULL;
		current = head;
		size = 1;
	}
	T& getDataAt(int index)
	{
		NodeL<T>* current = head;
		if (!isEmpty())
		{
			for (int i = 0; i < index; i++)
			{
				if (current->next != NULL)
				{
					current = current->next;
				}

			}
			return current->data;
		}
	}
	//OLD VERSION//
	/*
	T& getDataAt(int index)
	{
		NodeL<T>* current = head;
		if (!isEmpty())
		{
			for (int i = 0; i < index; i++)
			{
				current = current->next;
			}
			return current->data;
		}
	}
	*/
	NodeL<T>*& getNodeAt(int index)
	{
		NodeL<T>* current = head;
		if (!isEmpty())
		{
			for (int i = 0; i < index; i++)
			{
				current = current->next;
			}
			return current;
		}
	}
	NodeL<T>*& getNode(T data)
	{
		NodeL<T>* current = head;
		if (!isEmpty())
		{
			for (int i = 0; i < size; i++)
			{
				if (current->data == data)
					return current;
				current = current->next;
			}
			return current;
		}
	}
	~List()
	{
		clear();
	}
	void insert(const T& newDataItem)
	{
		NodeL<T>* temp = new NodeL<T>;
		temp->data = newDataItem;
		if (head == NULL)
		{
			head = temp;
			head->data = newDataItem;
			head->next = NULL;
			tail = head;
			current = head;
			size = 1;
		}
		else
		{
			tail->next = temp;
			tail = tail->next;
			size += 1;
		}
		current = temp;

		//if (duplicate())
		//	remove();
	}
	void insertAt(const T& newDataItem, int index)
	{
		if (index >= 0 && index <= size + 1)
		{
			NodeL<T>* temp = new NodeL<T>;
			temp->data = newDataItem;
			if (index == 0)
			{
				temp->next = head;
				head = temp;

			}
			else if (index == size)
			{
				tail->next = temp;
				tail = temp;
				temp->next = NULL;
			}
			else if (index < size)
			{

				current = head;
				for (int i = 0; i < index - 1; i++)
				{
					current = current->next;
				}

				temp->next = current->next;
				current->next = temp;

			}
			current = temp;
			size += 1;
		}
		else
		{
			cout << "Out of Range" << endl;
		}
	}
	void remove()
	{
		if (!isEmpty())
		{
			NodeL<T>* temp = head;
			while (temp->next != current && temp->next != NULL)
			{
				temp = temp->next;
			}
			NodeL<T>* toDelete = temp->next;


			//IF ONLY 1 ELEMENT LEFT
			if (current == tail && current == head)
			{
				delete current;
				tail = NULL;
				head = tail;
				size = 0;
				return;
			}
			//IF CURRENT IS AT TAIL
			else if (current == tail)
			{
				toDelete = temp->next;
				tail = temp;
				tail->next = NULL;
				current = head;
			}
			//IF CURRENT IS AT HEAD
			else if (current == head)
			{
				toDelete = head;
				current = toDelete->next;
				head = current;
			}
			//IF CURRENT IS IN THE MIDDLE
			else
			{
				toDelete = temp->next;
				temp->next = toDelete->next;
				current = toDelete->next;
			}
			delete toDelete;
			size -= 1;
		}
		else
			cout << "Empty" << endl;

	}
	void removeAt(int index)
	{
		if (index >= 0 && index < size)
		{
			current = head;
			for (int i = 0; i < index; i++)
			{
				current = current->next;
			}
			remove();
			return;
		}
		cout << "Out of Range" << endl;

	}
	void clear()
	{
		while (head != NULL)
		{
			remove();
		}
	}
	bool isEmpty()
	{
		if (head == NULL)
		{
			return true;
		}
		return false;
	}
	void display()
	{

		if (size != 0)
		{
			NodeL<T>* current = head;

			while (current != NULL)
			{
				cout << "| " << current->data << " |" << endl;
				current = current->next;
			}
		}
		else
			cout << "Empty";

	}
	void sort()
	{
		if (!isEmpty())
		{
			T* ptr = new T[size];
			NodeL<T>* current = head;
			for (int n = 0; n < size; n++)
			{
				ptr[n] = current->data;
				current = current->next;
			}
			T tmp;
			int i, j;
			for (i = 1; i < size; i++)
			{
				tmp = ptr[i];
				for (j = i; j > 0 && tmp < ptr[j - 1]; j--)
				{
					ptr[j] = ptr[j - 1];
				}
				ptr[j] = tmp;
			}
			for (int n = 0; n < size; n++)
			{
				cout << ptr[n] << " ";
			}
			delete ptr;
			return;
		}
		cout << "Empty" << endl;
	}
	bool duplicate()
	{
		NodeL<T>* temp = head;
		NodeL<T>* current = head;
		for (int i = 0; temp != NULL; i++)
		{
			current = head;
			for (int j = 0; current != NULL; j++)
			{
				if (temp != current && temp->data == current->data)
				{
					return true;
				}
				current = current->next;
			}
			temp = temp->next;
		}
		return false;

	}
};