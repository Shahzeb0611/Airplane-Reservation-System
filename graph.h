#pragma once

#include <iostream>
#include <fstream>
#include "DateTime.h"
#include "List.h"
using namespace std;

//NODE CLASS
template <class T, class U>
class Node
{
public:
	T data;					//WILL STORE CITY
	List<U> weight;			//WILL STORE A LIST OF WEIGHTS SINCE THERE ARE MULTIPLE DIRECT EDGES B/W TWO VERTICES
	Node<T, U>* next;
	Node()
	{
		next = NULL;
	}
	Node(int data)
	{
		this->data = data;
		next = NULL;
	}
	Node<T, U>& operator =(Node<T, U>*& rhs) {
		this->data = rhs->data;
		this->next = rhs->next;
		this->weight = rhs->weight;
		return *this;
	}
	bool operator !=(Node<T, U>*& rhs) {
		if (*this->data != rhs->data && *this->next != rhs->next && *this->weight != rhs->weight) {
			return true;
		}
		return false;
	}
};

//QUEUE CLASS
template <class T, class U>
class Queue
{
	Node<T, U>* front;
	Node<T, U>* rear;
	Node<T, U>* current;
	int size;
public:
	Queue()
	{
		front = NULL;
		rear = front;
		current = front;
		size = 0;
	}
	~Queue()
	{
		clear();
	}
	void enqueue(T newDataItem)
	{
		if (isEmpty())
		{
			front = new Node<T, U>();
			front->data = newDataItem;
			rear = front;
			current = front;
			rear->next = NULL;
		}
		else
		{
			Node<T, U>* newNode = new Node<T, U>();
			newNode->data = newDataItem;
			rear->next = newNode;
			rear = newNode;
			rear->next = NULL;
		}
		size++;
	}
	void enqueue(T newDataItem, U weight)
	{
		if (isEmpty())
		{
			front = new Node<T, U>();
			front->data = newDataItem;
			rear = front;
			current = front;
			rear->next = NULL;
		}
		else
		{
			Node<T, U>* newNode = new Node<T, U>();
			newNode->data = newDataItem;
			rear->next = newNode;
			rear = newNode;
			rear->next = NULL;
		}
		rear->weight.insert(weight);
		size++;
	}
	T dequeue()
	{
		if (!isEmpty())
		{
			T temp = front->data;
			current = front;
			front = front->next;
			delete current;
			size--;
			return temp;
		}
		cout << "Empty" << endl;
		//return -1;
	}
	void clear()
	{
		while (!isEmpty())
		{
			dequeue();
		}
	}
	bool isEmpty() const
	{
		if (front == NULL)
		{
			return true;
		}
		return false;
	}
	void display()
	{
		current = front;
		while (current != NULL)
		{
			cout << current->data << " ";
			current->weight.display();
			current = current->next;
		}
		cout << endl;
	}
	int getLength()
	{
		return size;
	}
	bool search(T data)
	{
		current = front;
		while (current != NULL)
		{
			if (current->data == data)
				return true;
			current = current->next;
		}
		return false;
	}
	Node <T, U>* returnPriority()
	{
		if (!isEmpty())
		{
			current = front;
			Node<T, U>* temp1 = NULL;
			temp1 = current;

			Node<T, U>* toReturn = NULL;

			U min = temp1->weight.getDataAt(0);
			T data = temp1->data;

			int index = -1;
			for (int i = 0; i < size; i++)
			{
				if (temp1->weight.getDataAt(0) <= min)
				{
					min = temp1->weight.getDataAt(0);
					data = temp1->data;
					index = i;
				}
				temp1 = temp1->next;
			}
			toReturn = new Node<T, U>;
			toReturn->data = data;
			toReturn->weight.insert(min);
			removeAt(index);
			return toReturn;
		}

	}
	void remove()
	{
		if (!isEmpty())
		{
			Node<T, U>* temp = front;
			while (temp->next != current && temp->next != NULL)
			{
				temp = temp->next;
			}
			Node<T, U>* toDelete = temp->next;


			//IF ONLY 1 ELEMENT LEFT
			if (current == rear && current == front)
			{
				delete current;
				rear = NULL;
				front = rear;
				size = 0;
				return;
			}
			//IF CURRENT IS AT TAIL
			else if (current == rear)
			{
				toDelete = temp->next;
				rear = temp;
				rear->next = NULL;
				current = front;
			}
			//IF CURRENT IS AT HEAD
			else if (current == front)
			{
				toDelete = front;
				current = toDelete->next;
				front = current;
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
			current = front;
			for (int i = 0; i < index; i++)
			{
				current = current->next;
			}
			remove();
			return;
		}
		cout << "Out of Range" << endl;

	}


};

//STACK CLASS
template <typename T, class U>
class Stack
{
	Node<T, U>* top;
	Node<T, U>* bottom;
	Node<T, U>* current;
	int size;
public:
	Stack()
	{
		top = NULL;
		bottom = top;
		current = top;
		size = 0;
	}
	~Stack()
	{
		clear();
	}
	void push(T newDataItem)
	{
		if (isEmpty())
		{
			top = new Node<T, U>();
			top->data = newDataItem;
			bottom = top;
			current = top;
			bottom->next = NULL;
		}
		else
		{
			Node<T, U>* newNode = new Node<T, U>();
			newNode->data = newDataItem;
			newNode->next = top;
			top = newNode;
		}
		size++;
	}
	T pop()
	{
		if (!isEmpty())
		{
			T temp = top->data;
			current = top;
			top = top->next;
			delete current;
			size--;
			return temp;
		}
		cout << "Empty" << endl;
		//return -1;
	}
	T getPop()
	{
		if (top != NULL)
			return top->data;
	}
	void clear()
	{
		while (!isEmpty())
		{
			pop();
		}
	}
	bool isEmpty() const
	{
		if (top == NULL)
		{
			return true;
		}
		return false;
	}
	void display()
	{
		current = top;
		while (current != NULL)
		{
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}
	int getLength()
	{
		return size;
	}
	bool search(T data)
	{
		current = top;
		while (current != NULL)
		{
			if (current->data == data)
				return true;
			current = current->next;
		}
		return false;
	}
};

//ADJACENCY LIST
template <class T, class U>
class AdjList
{
public:
	//********************************************DATA MEMBERS********************************************//
	Node <T, U>* head;		//HEAD OF THE LIST WILL ALWAYS BE A VERTEX WHILE OTHER ELEMENTS OF LIST WILL BE ITS NEIGHBOURS
	Node <T, U>* tail;		//WILL OPTIMEZE INSERTIONS
	Node <T, U>* current;	//WILL BE USED FOR TRAAVERSALS
	AdjList<T, U>* next;	//POINTER TO NEXT LIST, WHERE THE NEXT LIST WILL BE POINTING TOWARDS ANOTHER VERTEX AND ITS NEIGHBOURS
	int size;				//SIZE OF THE LIST INCLUDING VERTEX AND ITS NEIGHBOURS
	int transitCost = 0;
	//****************************************************************************************************//

	//CONSTRUCTOR AND DESTRUCTOR
	AdjList()
	{
		head = NULL;
		tail = NULL;
		current = NULL;
		size = 0;
		next = NULL;
	}
	AdjList(Node<T, U>* n)
	{
		head = n;
		tail = n;
		head->next = NULL;
		tail->next = NULL;
		current = head;
		size = 1;
		next = NULL;
	}
	~AdjList()
	{
		clear();
	}

	//***********HELPER FUNCTIONS**********//
	void insert(const T newDataItem, U weight)
	{
		Node<T, U>* temp = new Node<T, U>;
		temp->data = newDataItem;
		temp->weight.insert(weight);	//FOR MULTIPLE WEIGHTS WITH DIRECT EDGE

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
	}
	void remove()
	{
		current = head->next;
		delete head;
		head = current;
		size--;
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
	void removeDataItem(const T newDataItem)
	{
		current = head;
		for (int i = 0; i < size; i++)
		{
			if (current->data == newDataItem)
			{
				remove();
				return;
			}
			current = current->next;
		}
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
	int getSize()
	{
		return size;
	}
	bool search(T data)
	{
		current = head;
		while (current != NULL)
		{
			if (current->data == data)
				return true;
			current = current->next;
		}
		return false;
	}
	//*************************************//

	//**************GETTERS****************//
	//RETURNS DATA AT INDEX
	T getDataAt(int index)
	{
		Node<T, U>* current = head;
		if (!isEmpty())
		{
			for (int i = 0; i < index; i++)
			{
				current = current->next;
			}
			return current->data;
		}
	}

	//RETURNS NODE AT INDEX
	Node<T, U>*& getNodeAt(int index)
	{
		Node<T, U>* current = head;
		if (!isEmpty())
		{
			for (int i = 0; i < index; i++)
			{
				current = current->next;
			}
			return current;
		}
	}

	//RETURNS NODE WITH DATA
	Node<T, U>*& getNode(T data)
	{
		Node<T, U>* current = head;
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
	//*************************************//

	//****************OUTPUT***************//
	//DISPLAYS LIST
	void display()
	{
		if (size != 0)
		{
			Node<T, U>* current = head;

			while (current != NULL)
			{
				cout << T(current->data) << " -> ";
				current = current->next;
			}
			cout << "NULL" << endl;
		}
		else
			cout << "Empty" << endl;

	}

	//DISPLAYS LIST WITH WEIGHTS
	void displayWeighted()
	{
		if (size != 0)
		{
			Node<T, U>* current = head;

			while (current != NULL)
			{
				cout << "" << T(current->data) << endl << "Weight: " << endl;
				current->weight.display();
				cout << "		|" << endl;
				cout << "		V" << endl;

				current = current->next;
			}
			cout << "	       NULL" << endl;
		}
		else
			cout << "Empty" << endl;

	}
	//*************************************//

};

//WEIGHT CLASS
class Weight
{
public:
	//********************************************DATA MEMBERS********************************************//
	string airline;		//DESTINATION
	Date date;			//DATE OF FLIGHT
	Time time1;			//TIME OF TAKE OFF
	Time time2;			//TIME OF ARRIVAL
	int cost;			//COST OF FLIGHT

	int time_diff = time2.getHours() - time1.getHours();
	//****************************************************************************************************//

	//CONSTRUCTOR//
	Weight()
	{
		airline = "";
		date.setDate("0/0/0");
		time1.setTime("0:0");
		time2.setTime("0:0");
		cost = 0;
		time_diff = 0;
	}
	//***********//

	void setTimeDiff(int t)
	{
		time_diff = t;
	}
	int getTimeDiff()
	{
		return time_diff;
	}

	//**********OPERATORS OVERLOADED**********//
	bool operator== (const Weight& w)
	{
		return ((airline == w.airline) && (date == w.date) && (time1 == w.time1) && (time2 == w.time2) && (cost == w.cost) && (time_diff == w.time_diff));
	}
	bool operator!= (const Weight& w)
	{
		return (!((*this) == w));
	}
	Weight& operator= (const Weight& w)
	{
		if ((*this) != w)
		{
			airline = w.airline;
			date = w.date;
			time1 = w.time1;
			time2 = w.time2;
			cost = w.cost;
			time_diff = w.time_diff;
		}

		return *this;
	}
	bool operator< (const Weight& w)
	{
		return (cost < w.cost);
	}
	bool operator> (const Weight& w)
	{
		return (cost > w.cost);
	}
	bool operator<= (const Weight& w)
	{
		return (cost <= w.cost);
	}
	bool operator>= (const Weight& w)
	{
		return (cost >= w.cost);
	}
	//****************************************//

	//*****************OUTPUT*****************//
	void display()
	{
		cout << airline << " "
			<< cost << " "
			<< date.getDate() << " "
			<< time1.getTime() << " "
			<< time2.getTime() << " " << endl;
	}
	//****************************************//
};
ostream& operator << (ostream& out, Weight& w)
{
	out << w.airline << " "
		<< w.cost << " "
		<< w.date.getDate() << " "
		<< w.time1.getTime() << " "
		<< w.time2.getTime() << " ";
	return out;
}

//********************SORTING WEIGHTS********************// 
void sort_wrt_cost(List<Weight>& w)
{
	Weight temp;
	for (int i = 0; i < w.size; i++)
	{
		for (int j = 0; j < w.size - 1; j++)
		{
			if (w.getDataAt(j).cost >= w.getDataAt(j + 1).cost)
			{
				swap(w.getDataAt(j), w.getDataAt(j + 1));
			}
		}
	}
}
void sort_wrt_days(List<Weight>& w)
{
	Weight temp;
	for (int i = 0; i < w.size; i++)
	{
		for (int j = 0; j < w.size - 1; j++)
		{
			if (w.getDataAt(j).date.getDay() > w.getDataAt(j + 1).date.getDay())
			{
				swap(w.getDataAt(j), w.getDataAt(j + 1));
			}
		}
	}
}
void sort_wrt_time(List<Weight>& w)
{
	Weight temp;
	for (int i = 0; i < w.size; i++)
	{
		int h1;
		int h2;
		for (int j = 0; j < w.size - 1; j++)
		{
			h1 = (w.getDataAt(j).time2.getHours() - w.getDataAt(j).time1.getHours());
			if (h1 < 0)
				h1 += 24;
			h2 = (w.getDataAt(j + 1).time2.getHours() - w.getDataAt(j + 1).time1.getHours());
			if (h2 < 0)
				h2 += 24;
			if (h1 > h2)
			{
				swap(w.getDataAt(j), w.getDataAt(j + 1));
			}
		}
	}
}
//*******************************************************//

//MAIN GRAPH CLASS
template <class T, class U>
class Graph
{
	//********************************************DATA MEMBERS********************************************//
	//WILL MAINTAIN AN ADJACENCY LIST
	//EVERY ELEMENT IN THIS LIST WILL BE A VERTEX
	AdjList<T, U>* head;
	AdjList<T, U>* cursor;
	AdjList<T, U>* tail;
	
	int size;	//THE SIZE OF LIST WILL BE THE NUM OF VERTICES
	//****************************************************************************************************//
public:

	//**********CONSTRUCTOR AND DESTRUCTOR**********//
	Graph()
	{
		head = NULL;
		cursor = NULL;
		tail = NULL;
		size = 0;
	}
	Graph(string filename, string fileHotel)
	{
		head = NULL;
		cursor = NULL;
		tail = NULL;
		size = 0;



		//VARIABLES WE WILL USE TO READ FILE
		string line;
		string Vertex1;
		string Vertex2;
		string date;
		string time1;
		string time2;
		string airline;
		string cost;

		//VARIABLE TO INITIALIZE WEIGHTS
		Date actualDate;
		Time actualTime1;
		Time actualTime2;
		Weight w;

		//COUNTER WILL BE USED FOR READING INDIVIDUAL WORD IN STRING
		int counter = 0;
		//int line1 = 0;
		fstream file(filename, ios::in);
		if (file.is_open())
		{
			while (!file.eof())
			{
				//cout << line1 << endl;
				//line1++;
				getline(file, line);
				line += ' ';
				for (int i = 0; i < line.length(); i++)
				{
					//WILL READ CITY1
					if (counter == 0)
					{
						if (line[i] != ' ')
							Vertex1 += line[i];
						else
							counter++;
					}

					//WILL READ CITY2
					else if (counter == 1)
					{
						if (line[i] != ' ')
							Vertex2 += line[i];
						else
							counter++;
					}

					//WILL READ DATE
					else if (counter == 2)
					{
						if (line[i] != ' ')
							date += line[i];
						else
						{
							counter++;
							actualDate.setDate(date);
						}

					}

					//WILL READ TIME1
					else if (counter == 3)
					{
						if (line[i] != ' ')
							time1 += line[i];
						else
						{
							counter++;
							actualTime1.setTime(time1);
						}
					}

					//WILL READ TIME2
					else if (counter == 4)
					{
						if (line[i] != ' ')
							time2 += line[i];
						else
						{
							counter++;
							actualTime2.setTime(time2);
						}
					}

					//WILL READ COST
					else if (counter == 5)
					{
						if (line[i] != ' ')
							cost += line[i];
						else
							counter++;
					}

					//WILL READ AIRLINE
					else if (counter == 6)
					{
						if (line[i] != ' ')
							airline += line[i];
						else //GRAPH WILL BE GENERATED HERE
						{


							//FOR MAIN GRAPH
							w.airline = airline;
							w.date = actualDate;
							w.time1 = actualTime1;
							w.time2 = actualTime2;
							w.cost = stoi(cost);

							insertVertex(Vertex1);
							insertVertex(Vertex2);
							insertEdge(Vertex1, Vertex2, w);
						}
					}
				}
				//RESETTING VARIABLES
				counter = 0;
				Vertex1 = "";
				Vertex2 = "";
				date = "";
				time1 = "";
				time2 = "";
				cost = "";
				airline = "";
			}
		}
		file.close();



		string place;
		file.open(fileHotel, ios::in);
		counter = 0;
		if (file.is_open())
		{
			while (!file.eof())
			{
				//cout << line1 << endl;
				//line1++;
				place = "";
				cost = "";
				counter = 0;
				getline(file, line);
				line += ' ';

				for (int i = 0; i < line.length(); i++)
				{
					//WILL READ CITY1
					if (counter == 0)
					{
						if (line[i] != ' ')
							place += line[i];
						else
							counter++;
					}
					//WILL READ AIRLINE
					else if (counter == 1)
					{
						if (line[i] != ' ')
							cost += line[i];
						else //GRAPH WILL BE GENERATED HERE
						{
							getList(place)->transitCost = stoi(cost);
						}
					}
				}

			}
		}
		file.close();

		//TO CHECK TRANSIT COSTS
		/*for (int i = 0; i < size; i++)
		{
			cout << getListAt(i)->getDataAt(0)<<" ";
			cout << getListAt(i)->transitCost << endl;;
		}*/
	}
	~Graph()
	{
		clear();
	}
	//**********************************************//

	//*********HELPERS*********//
	void clear()
	{
		while (!isEmpty())
		{
			remove();
		}
	}
	void remove()
	{
		if (!isEmpty())
		{
			cursor = head->next;
			delete head;
			head = cursor;
		}
	}
	bool isEmpty()
	{
		if (head == NULL)
			return true;
		return false;
	}
	//SEARCHES VERTICES IN LIST
	bool searchVertices(T data)
	{
		for (int i = 0; i < size; i++)
		{
			if (getListAt(i)->search(data))
				return true;
		}
		return false;
	}
	//************************//

	//**********************************INSERT**********************************//
	//INSERTS NEW VERTEX
	void insertVertex(T ver)
	{
		if (!searchVertices(ver))	//
		{
			if (head == NULL)
			{
				head = new AdjList<T, U>;
				cursor = head;
				tail = head;
			}
			else
			{
				tail->next = new AdjList<T, U>;
				tail = tail->next;
			}
			Weight w;	//DEFAULT WEIGHT IS ZERO, MEANING THERE IS ZERO WEIGHT BETWEEN A NODE AND ITSELF
			tail->insert(ver, w);
			size++;
		}
		else
		{
			//	cout << "vertex already included" << endl;
		}
	}

	//INSERTS A DIRECTIONAL EDGE B/W TWO VERTICES
	void insertEdge(T src, T dest, U weight)
	{
		if (!getList(src)->search(dest))
		{
			//INSERTS NEIGHBOUR VERTICE WITH GIVEN WEIGHT
			getList(src)->insert(dest, weight);
		}
		else
		{
			//IF THAT NEIGHBOUR ALREADY EXISTS, WE INSERT ANOTHER WEIGHT TO THE DIRECT EDGE
			getList(src)->getNode(dest)->weight.insert(weight);
		}

	}

	//INSERTS AN UNDIRECTIONAL EDGE B/W TWO VERTICES
	void insertEdgeUnDirectional(T src, T dest, U weight)
	{
		//FOR UNDIRECTIONAL EDGE, EDGES WILL BE DOUBLY CONNECTED
		insertEdge(src, dest, weight);
		insertEdge(dest, src, weight);
	}
	//**************************************************************************//

	//****************************************GETTERS****************************************//
	//RETURNS LIST AT INDEX, MEANING IT WILL GIVE NEIGHBOURS OF VERTEX AT INDEX
	AdjList<T, U>*& getListAt(int index)
	{
		cursor = head;
		for (int i = 0; i < index; i++)
		{
			cursor = cursor->next;
		}
		return cursor;
	}

	//RETURNS LIST OF NEIGHBOURS OF DATA
	AdjList<T, U>*& getList(T data)
	{
		cursor = head;
		for (int i = 0; i < size; i++)
		{
			if (cursor->getDataAt(0) == data)
				return cursor;
			cursor = cursor->next;
		}
		return cursor;
	}

	//RETURNS INDEX OF WHERE THE VERTEX IS LYING
	int getIndex(T data)
	{
		cursor = head;
		for (int i = 0; i < size; i++)
		{
			if (cursor->getDataAt(0) == data)
				return i;
			cursor = cursor->next;
		}
		return -1;
	}
	//***************************************************************************************//

	//*************************FLOYD WALA KAAAM BELOW WRT COST*************************//
	bool floydWarshall(string s, string d)//Passing SOurce and destination of type string
	{
		bool flag = true;
		//------CREAING AN 11x11 2D MATRIX OF OF NODES----------// 
		Node<T, U>** Edge;
		Edge = new Node<T, U>* [size];
		for (int i = 0; i < size; i++) {
			Edge[i] = new Node<T, U>[size];
		}
		//-----------------------------------------------------//

		//------Weight temp is initialized with cost 99999 (Max Value)----------// 
		Weight temp;
		temp.cost = 0;
		//....................................................//

		//.................Intializing all Edges of type Node with Empty data and cost 99999................//
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				Edge[i][j].data = " ";
				Edge[i][j].weight.insert(temp);
			}
		}
		//....................................................//

		//------------A 2D Path Matrix of type int-----------//
		int** Path;
		Path = new int* [size];
		for (int i = 0; i < size; i++) {
			Path[i] = new int[size];
		}
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				Path[i][j] = -1;//Initializing data with -1
			}
		}
		//--------------------------------------------------//

		//------Mapping Graph to Matrix--------------------//
		//variabes used for mapping//
		AdjList<T, U>* listTemp = new AdjList<T, U>;
		Node<T, U>* Temp;
		Node<T, U>* Temp2;

		for (int i = 0; i < size; i++) {
			Temp = this->getListAt(i)->getNodeAt(0);
			Temp2 = Temp;
			while (Temp) {
				Edge[getIndex(Temp2->data)][getIndex(Temp->data)] = Temp;
				Temp = Temp->next;
			}
		}
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (Edge[i][j].weight.getNodeAt(0)->data.cost == 0 && i != j) {
					Edge[i][j].weight.getNodeAt(0)->data.cost = 999999;
				}
			}
		}
		//UNCOMMENT TO CHECK IF GRAPH HAS BEEN CORRECTLY MAPPED-OTHER WISE DONT UNCOMMENT----//
		/*
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (Edge[i][j].data!=" ") {

					cout << Edge[i][j].weight.getNodeAt(0)->data.cost;

					cout << endl;

				}
				else {
					//cout << Edge[i][j].weight.getNodeAt(0)->data.cost;
					//Edge[i][j].weight.getNodeAt(0)->data.cost = 0;
					cout << "NO" << endl;
				}
				//cout << Edge[i][j].weight.getNodeAt(0)->data.cost;
			}
			cout << endl;
		}
		*/

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (Edge[i][j].data != " ") {

					sort_wrt_cost(Edge[i][j].weight);//vimp
					//cout << Edge[i][j].weight.getNodeAt(0)->data.cost << " " << setw(8);
				}
				//else
					//cout << "NO" << " " << setw(8);

			}
			//cout << endl;
		}

		//--------------------APPLYING FLOYD-----------------//
		for (int k = 0; k < size; k++)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					//donot alter this condition

					if (Edge[i][j].weight.getNodeAt(0)->data.cost > Edge[i][k].weight.getNodeAt(0)->data.cost + Edge[k][j].weight.getNodeAt(0)->data.cost) {
						Edge[i][j].weight.getNodeAt(0)->data.cost = Edge[i][k].weight.getNodeAt(0)->data.cost + Edge[k][j].weight.getNodeAt(0)->data.cost;
						Path[i][j] = k;//maininting path matrix
					}
				}
			}
		}

		system("CLS");
		//---------------------------//
		cout << " SOURCE : " << s << endl;
		cout << " Destination : " << d << endl;
		int transit = -1;//initializing transit with -1
		PathPrint(Path, getIndex(s), getIndex(d), transit); //this function will update the transit
		//cout << transit;
		if (Edge[getIndex(s)][getIndex(d)].weight.getNodeAt(0)->data.cost != 999999) {
			if (transit != -1) {
				if (Edge[transit][getIndex(d)].weight.getNodeAt(0)->data.cost != 999999 && Edge[getIndex(s)][transit].weight.getNodeAt(0)->data.cost != 999999)
				{
					cout << "THE PATH WITH MINIMUM COST IS :" << endl;
					cout << s << "---->" << getListAt(transit)->getNodeAt(0)->data << "---->" << d << endl;
					cout << endl;

					cout << "Flight 1 : " << s << "---->" << getListAt(transit)->getNodeAt(0)->data << endl << Edge[getIndex(s)][transit].weight.getNodeAt(0)->data << endl;
					cout << endl;

					cout << "Flight 2 : " << getListAt(transit)->getNodeAt(0)->data << "---->" << d << endl << Edge[transit][getIndex(d)].weight.getNodeAt(0)->data << endl;
					cout << endl;

					cout << "TOTAL FARE ESTIMATED = " << Edge[getIndex(s)][transit].weight.getNodeAt(0)->data.cost + Edge[transit][getIndex(d)].weight.getNodeAt(0)->data.cost << endl;
				}
				else {
					cout << "NO FLIGHTS POSSIBLE" << endl;
				}
			}
			else {
				cout << "THE PATH WITH MINIMUM COST IS :" << endl;
				cout << s << "---->" << d << endl;
				cout << Edge[getIndex(s)][getIndex(d)].weight.getNodeAt(0)->data << endl;
				cout << "TOTAL FARE ESTIMATED = " << Edge[getIndex(s)][getIndex(d)].weight.getNodeAt(0)->data.cost << endl;
			}
		}
		else
		{
			flag = false;
			cout << "NO FLIGHTS POSSIBLE" << endl;
		}
		return flag;
	}
	//Function that recursively prints all paths
	void PathPrint(int**& p, int s, int d, int& dummy) {

		int k = p[s][d];
		if (k != -1) {
			if (k == 0) {
				dummy = 0;
				return;
			}
			PathPrint(p, s, k, dummy);
			dummy = printJaga(k);
			//cout << dummy;
			PathPrint(p, k, d, dummy);
		}
	}
	//This function returns and Prints the Transit between two Nodes
	int printJaga(int index) {
		cout << "FLIGHTS INCLUDE :";
		cout << getListAt(index)->getNodeAt(0)->data << endl;
		return index;
	}
	//*********************************************************************************//

	//*************************FLOYD2 WALA KAAAM BELOW WRT TRAVEL TIME************************//
	bool floydWarshall2(string s, string d)//Passing SOurce and destination of type string
	{

		//------CREAING AN 11x11 2D MATRIX OF OF NODES----------// 
		Node<T, U>** Edge;
		Edge = new Node<T, U>* [size];
		for (int i = 0; i < size; i++) {
			Edge[i] = new Node<T, U>[size];
		}
		//-----------------------------------------------------//

		//------Weight temp is initialized with cost 99999 (Max Value)----------// 
		Weight temp;
		temp.time_diff = 0;
		//....................................................//

		//.................Intializing all Edges of type Node with Empty data and cost 99999................//
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				Edge[i][j].data = " ";
				Edge[i][j].weight.insert(temp);
			}
		}
		//....................................................//

		//------------A 2D Path Matrix of type int-----------//
		int** Path;
		Path = new int* [size];
		for (int i = 0; i < size; i++) {
			Path[i] = new int[size];
		}
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				Path[i][j] = -1;//Initializing data with -1
			}
		}
		//--------------------------------------------------//

		//------Mapping Graph to Matrix--------------------//
		//variabes used for mapping//

		AdjList<T, U>* listTemp = new AdjList<T, U>;
		Node<T, U>* Temp;
		Node<T, U>* Temp2;

		for (int i = 0; i < size; i++) {
			Temp = this->getListAt(i)->getNodeAt(0);
			Temp2 = Temp;
			while (Temp) {
				Edge[getIndex(Temp2->data)][getIndex(Temp->data)] = Temp;

				Temp = Temp->next;
			}
		}
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (Edge[i][j].weight.getNodeAt(0)->data.time_diff == 0 && i != j) {
					Edge[i][j].weight.getNodeAt(0)->data.time_diff = 999;
				}
			}
		}
		//UNCOMMENT TO CHECK IF GRAPH HAS BEEN CORRECTLY MAPPED-OTHER WISE DONT UNCOMMENT----//
		/*
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (Edge[i][j].data!=" ") {

					cout << Edge[i][j].weight.getNodeAt(0)->data.cost;

					cout << endl;

				}
				else {
					//cout << Edge[i][j].weight.getNodeAt(0)->data.cost;
					//Edge[i][j].weight.getNodeAt(0)->data.cost = 0;
					cout << "NO" << endl;
				}
				//cout << Edge[i][j].weight.getNodeAt(0)->data.cost;
			}
			cout << endl;
		}
		*/
		//-------------------------------------------------------//
		////Here Cost 99999 means no Direct Flight and 0 means the cost of node with itself
		//cout << "DISPLAYING THE Adjecancy MATRIX READ INITIALLY FROM GRAPH------" << endl;
		//for (int i = 0; i < size; i++)
		//{
		//	for (int j = 0; j < size; j++)
		//	{

		//		//cout << setw(8) << Edge[i][j].weight.getNodeAt(0)->data.time_diff << " ";

		//	}
		////	cout << endl;
		//}
		////THIS WILL SORT THE WEIGHTS OF EACH NODE (this loop is important donot comment sort---can comment the cout statements)
		////cout << endl << "SORTED-------" << endl;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (Edge[i][j].data != " ") {

					sort_wrt_time(Edge[i][j].weight);//vimp
					Edge[i][j].weight.getNodeAt(0)->data.time_diff = Edge[i][j].weight.getNodeAt(0)->data.time2.getHours() - Edge[i][j].weight.getNodeAt(0)->data.time1.getHours();
					if (Edge[i][j].weight.getNodeAt(0)->data.time_diff < 0) {
						Edge[i][j].weight.getNodeAt(0)->data.time_diff += 24;
					}

					//cout << setw(8);
					//cout << Edge[i][j].weight.getNodeAt(0)->data.time_diff << " " << setw(8);
				}
				//else
				//	cout << "NO" << " " << setw(8);

			}
			//cout << endl;
		}
		//Edge[0][2].weight.getNodeAt(0)->data.display();
		//cout << "-------------------" << endl;
		//--------------------APPLYING FLOYD-----------------//
		for (int k = 0; k < size; k++)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					//donot alter this condition
					//if (Edge[i][j].weight.getNodeAt(0)->data.time_diff != 999) {
					if (Edge[i][j].weight.getNodeAt(0)->data.time_diff > (Edge[i][k].weight.getNodeAt(0)->data.time_diff + Edge[k][j].weight.getNodeAt(0)->data.time_diff)) {
						Edge[i][j].weight.getNodeAt(0)->data.time_diff = (Edge[i][k].weight.getNodeAt(0)->data.time_diff + Edge[k][j].weight.getNodeAt(0)->data.time_diff);
						Path[i][j] = k;//maininting path matrix
					}
					//}
				}
			}
		}
		//-------------------------------------------//
		//Printing Matrix After Floyd//
		//This matrix now contains minimum possible costs//
		//cost 99999 means no flight//

		//cout << "DISPLAYING FLOYD's MINIMUM COST MATRIX :-" << endl;
		//for (int i = 0; i < size; i++)
		//{
		//	for (int j = 0; j < size; j++)
		//	{
		//		//if (Edge[i][j].data != " ") {
		//		cout << setw(4) << Edge[i][j].weight.getNodeAt(0)->data.time_diff << " ";

		//		//}
		//		//else
		//			//cout << "NO" << " ";
		//	}
		//	cout << endl;
		//}

		//-------------------------//
		//Printing the Path Matrix After Floyd//
		//This matrix contains the transit between two Nodes//

/*
		cout << "DISPLAYING PATH MATIX :-" << endl;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << setw(4) << Path[i][j] << " ";
			}
			cout << endl;
		}*/
		//---------------------------//
		cout << " SOURCE : " << s << endl;
		cout << " Destination : " << d << endl;
		int* transit = new int[2];
		for (int i = 0; i < 2; i++) {
			transit[i] = -1;
		}

		PathPrint2(Path, getIndex(s), getIndex(d), transit); //this function will update the transit
		//cout << transit[0] << transit[1];
		if (transit[0] == transit[1]) {
			int t = transit[0];
			int transit = t;
			if (Edge[getIndex(s)][getIndex(d)].weight.getNodeAt(0)->data.time_diff != 999) {
				if (transit != -1) {
					if (Edge[transit][getIndex(d)].weight.getNodeAt(0)->data.time_diff != 999 && Edge[getIndex(s)][transit].weight.getNodeAt(0)->data.time_diff != 999)
					{
						cout << "THE PATH WITH MINIMUM Time IS :" << endl;
						cout << s << "---->" << getListAt(transit)->getNodeAt(0)->data << "---->" << d << endl;

						cout << "Flight 1 : " << s << "---->" << getListAt(transit)->getNodeAt(0)->data << endl << Edge[getIndex(s)][transit].weight.getNodeAt(0)->data << endl;
						cout << "Flight 2 : " << getListAt(transit)->getNodeAt(0)->data << "---->" << d << endl << Edge[transit][getIndex(d)].weight.getNodeAt(0)->data << endl;
						cout << "TOTAL Time  ESTIMATED = " << Edge[getIndex(s)][transit].weight.getNodeAt(0)->data.time_diff + Edge[transit][getIndex(d)].weight.getNodeAt(0)->data.time_diff << "hrs." << endl;
					}
					else {
						cout << "NO FLIGHTS POSSIBLE" << endl;
						return false;
					}
				}
				else {
					cout << "THE PATH WITH MINIMUM Time IS :" << endl;
					cout << s << "---->" << d << endl;
					cout << Edge[getIndex(s)][getIndex(d)].weight.getNodeAt(0)->data << endl;
					cout << "TOTAL FARE ESTIMATED = " << Edge[getIndex(s)][getIndex(d)].weight.getNodeAt(0)->data.time_diff << "hrs" << endl;
				}
			}
			else
			{
				cout << "NO FLIGHTS POSSIBLE" << endl;
				return false;
			}
		}
		else {
			if (Edge[getIndex(s)][getIndex(d)].weight.getNodeAt(0)->data.time_diff != 999) {
				if (transit[0] != -1 && transit[1] != -1) {
					if (Edge[transit[1]][getIndex(d)].weight.getNodeAt(0)->data.time_diff != 999 && Edge[getIndex(s)][transit[0]].weight.getNodeAt(0)->data.time_diff != 999 && Edge[transit[0]][transit[1]].weight.getNodeAt(0)->data.time_diff != 999)
					{
						cout << "THE PATH WITH MINIMUM Time IS :" << endl;
						cout << s << "---->" << getListAt(transit[0])->getNodeAt(0)->data << "---->" << getListAt(transit[1])->getNodeAt(0)->data << "---->" << d << endl;

						cout << "Flight 1 : " << s << "---->" << getListAt(transit[0])->getNodeAt(0)->data << endl << Edge[getIndex(s)][transit[0]].weight.getNodeAt(0)->data << endl;
						cout << "Flight 2 : " << getListAt(transit[0])->getNodeAt(0)->data << "---->" << getListAt(transit[1])->getNodeAt(0)->data << endl << Edge[transit[0]][transit[1]].weight.getNodeAt(0)->data << endl;
						cout << "Flight 3 : " << getListAt(transit[1])->getNodeAt(0)->data << "---->" << d << endl << Edge[transit[1]][getIndex(d)].weight.getNodeAt(0)->data << endl;
						cout << "TOTAL Time  ESTIMATED = " << Edge[getIndex(s)][transit[0]].weight.getNodeAt(0)->data.time_diff + Edge[transit[0]][transit[1]].weight.getNodeAt(0)->data.time_diff + Edge[transit[1]][getIndex(d)].weight.getNodeAt(0)->data.time_diff << "hrs." << endl;
					}
					else
					{
						cout << "NO FLIGHTS POSSIBLE" << endl;
						return false;
					}
				}
				else {
					cout << "THE PATH WITH MINIMUM Time IS :" << endl;
					cout << s << "---->" << d << endl;
					cout << Edge[getIndex(s)][getIndex(d)].weight.getNodeAt(0)->data << endl;
					cout << "TOTAL FARE ESTIMATED = " << Edge[getIndex(s)][getIndex(d)].weight.getNodeAt(0)->data.time_diff << "hrs." << endl;
				}
			}
			else
			{
				cout << "NO FLIGHTS POSSIBLE" << endl;
				return false;
			}
		}
		return true;
	}
	//Function that recursively prints all paths
	void PathPrint2(int**& p, int s, int d, int* dummy, int count = 0) {
		int k = p[s][d];
		if (k != -1) {
			dummy[count] = printJaga2(k);
			PathPrint2(p, s, k, dummy);
			count++;
			dummy[count] = printJaga2(k);

			PathPrint2(p, k, d, dummy);
		}
	}
	//This function returns and Prints the Transit between two Nodes
	int printJaga2(int index) {
		return index;
	}
	//****************************************************************************************//

	//************************************OUTPUT************************************//
	//DISPLAYS THE ADJACENCY LIST ALONG WITH VERTICES AND THEIR NEIGHBOURS//
	void displayWeighted()
	{
		cursor = head;
		for (int i = 0; i < size; i++)
		{
			cout << "Vertex " << i + 1 << ":" << endl;
			cursor->displayWeighted();
			cursor = cursor->next;
			cout << "******************************************" << endl;

		}
	}
	void display()
	{
		cursor = head;
		for (int i = 0; i < size; i++)
		{
			cout << "Vertex " << i + 1 << ":" << endl;
			cursor->display();
			cursor = cursor->next;
			cout << "******************************************" << endl;

		}
	}

	//BREADTH FIRST TRAVERSAL
	void BFS(T startNode)
	{
		Queue<T, U> tempQ;
		Node <T, U>* temp;
		tempQ.enqueue(startNode);
		bool* visited = new bool[size];
		for (int i = 0; i < size; i++)
		{
			visited[i] = false;
		}
		visited[getIndex(startNode)] = true;

		while (!tempQ.isEmpty())
		{
			cursor = getList(tempQ.dequeue());
			temp = cursor->getNodeAt(0); // 3
			cout << temp->data << endl;
			while (temp != NULL)
			{


				if (!(tempQ.search(temp->data)) && visited[getIndex(temp->data)] == false)
				{
					visited[getIndex(temp->data)] = true;
					tempQ.enqueue(temp->data);
				}
				temp = temp->next;

			}
		}
		delete visited;
	}

	//DEPTH FIRST TRAVERSAL
	void DFS(T startNode)
	{

		Stack<T, U> tempS;
		Node <T, U>* temp;
		tempS.push(startNode);
		bool* visited = new bool[size];
		for (int i = 0; i < size; i++)
		{
			visited[i] = false;
		}
		visited[getIndex(startNode)] = true;

		while (!tempS.isEmpty())
		{
			//tempS.display();
			cursor = getList(tempS.pop());
			temp = cursor->getNodeAt(0); // 3
			cout << temp->data << endl;

			while (temp != NULL)
			{
				//cout << temp->data << endl;
				if (!(tempS.search(temp->data)) && visited[getIndex(temp->data)] == false)
				{

					visited[getIndex(temp->data)] = true;
					tempS.push(temp->data);
				}
				temp = temp->next;
			}
			//cout << endl;
		}
		delete visited;
	}

	//SHOWS PATH B/W TWO VERTICES
	bool showPath(T startNode, T dest, int wrt = 0)
	{
		if (getList(startNode)->search(dest))
		{
			Weight w;
			int hrs;
			cout << "Direct path exists" << endl;
			cout << startNode << " ---> " << dest << endl;
			//ALL FLIGHTS
			getList(startNode)->getNode(dest)->weight.display();
			if (wrt == 0)
			{
				sort_wrt_cost(getList(startNode)->getNode(dest)->weight);
			}
			else if (wrt == 1)
			{
				sort_wrt_days(getList(startNode)->getNode(dest)->weight);
			}
			else if (wrt == 2)
			{
				sort_wrt_time(getList(startNode)->getNode(dest)->weight);
			}



			//YOUR FLIGHT
			cout << "\nYour Flight:" << endl;
			cout << getList(startNode)->getNode(dest)->weight.getDataAt(0) << endl;;
			cout << "Flight Time: ";
			w = getList(startNode)->getNode(dest)->weight.getDataAt(0);
			hrs = w.time2.getHours() - w.time1.getHours();
			if (hrs < 0)
				hrs += 24;
			cout << hrs << endl;
			return true;
		}
		else
		{
			cout << "No Direct Path Exists" << endl;
			return false;
		}

	}

	//DISPLAYS VERTICES
	void displayVertices()
	{
		cursor = head;
		for (int i = 0; i < size; i++)
		{
			cout << "* " << cursor->getDataAt(0) << endl;
			cursor = cursor->next;
		}
	}
	//*****************************************************************************//
};
Graph<string, Weight>* getSubGraph(string data,string flights,string hotelCharges)
{
	Graph <string, Weight>* gr1 = new Graph <string, Weight>;
	//VARIABLES WE WILL USE TO READ FILE
	string line;
	string Vertex1;
	string Vertex2;
	string date;
	string time1;
	string time2;
	string airline;
	string cost;

	//VARIABLE TO INITIALIZE WEIGHTS
	Date actualDate;
	Time actualTime1;
	Time actualTime2;
	Weight w;

	//COUNTER WILL BE USED FOR READING INDIVIDUAL WORD IN STRING
	int counter = 0;
	//int line1 = 0;
	fstream file(flights, ios::in);
	if (file.is_open())
	{

		while (!file.eof())
		{
			//cout << line1 << endl;
			//line1++;
			getline(file, line);
			line += ' ';
			for (int i = 0; i < line.length(); i++)
			{
				//WILL READ CITY1
				if (counter == 0)
				{
					if (line[i] != ' ')
						Vertex1 += line[i];
					else
						counter++;
				}

				//WILL READ CITY2
				else if (counter == 1)
				{
					if (line[i] != ' ')
						Vertex2 += line[i];
					else
						counter++;
				}

				//WILL READ DATE
				else if (counter == 2)
				{
					if (line[i] != ' ')
						date += line[i];
					else
					{
						counter++;
						actualDate.setDate(date);
					}

				}

				//WILL READ TIME1
				else if (counter == 3)
				{
					if (line[i] != ' ')
						time1 += line[i];
					else
					{
						counter++;
						actualTime1.setTime(time1);
					}
				}

				//WILL READ TIME2
				else if (counter == 4)
				{
					if (line[i] != ' ')
						time2 += line[i];
					else
					{
						counter++;
						actualTime2.setTime(time2);
					}
				}

				//WILL READ COST
				else if (counter == 5)
				{
					if (line[i] != ' ')
						cost += line[i];
					else
						counter++;
				}

				//WILL READ AIRLINE
				else if (counter == 6)
				{
					if (line[i] != ' ')
						airline += line[i];
					else //GRAPH WILL BE GENERATED HERE
					{
						//FOR SUBGRAPH OF EMIRATES FLIGHTS
						if (airline == data)
						{
							w.airline = airline;
							w.date = actualDate;
							w.time1 = actualTime1;
							w.time2 = actualTime2;
							w.cost = stoi(cost);

							gr1->insertVertex(Vertex1);
							gr1->insertVertex(Vertex2);
							gr1->insertEdge(Vertex1, Vertex2, w);
						}

					}
				}
			}
			//RESETTING VARIABLES
			counter = 0;
			Vertex1 = "";
			Vertex2 = "";
			date = "";
			time1 = "";
			time2 = "";
			cost = "";
			airline = "";
		}
	}
	file.close();

	string place;
	file.open(hotelCharges, ios::in);
	counter = 0;
	if (file.is_open())
	{
		while (!file.eof())
		{
			//cout << line1 << endl;
			//line1++;
			place = "";
			cost = "";
			counter = 0;
			getline(file, line);
			line += ' ';

			for (int i = 0; i < line.length(); i++)
			{
				//WILL READ CITY1
				if (counter == 0)
				{
					if (line[i] != ' ')
						place += line[i];
					else
						counter++;
				}
				//WILL READ AIRLINE
				else if (counter == 1)
				{
					if (line[i] != ' ')
						cost += line[i];
					else //GRAPH WILL BE GENERATED HERE
					{
						if (gr1->getList(place) != NULL)
							gr1->getList(place)->transitCost = stoi(cost);
					}
				}
			}

		}
	}
	file.close();

	return gr1;
}

void UI(string flights, string hotelCharges)
{
	int choice = 0;
	int airline = 0;
	bool airlineAll = false;
	string location;
	string destination;
	string transitLocation;
	string d;
	Date date;
	int typeOfFlight;
	int wrt;
	string ready = "yes";
	int counter;
	bool isFlight = true;
	bool Tflag = false;

	Graph<string, Weight>* graph = new Graph<string, Weight>(flights, hotelCharges);

	while (choice != 5)
	{
		counter = 0;
		cout << "\n\n*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*" << endl;
		cout << "Welcome to Jaani International Airlines!" << endl;
		cout << endl;

		/*cout << "__  _" << endl;
		cout << "\ `/ |" << endl;
		cout << " \__`!" << endl;
		cout << " / ,' `-.__________________" << endl;
		cout << "'-'\\_____   J I A         \\_`-." << endl;
		cout << "   <____()-=O=O=O=O=O=[]====-- )" << endl;
		cout << "     `.___ ,-----,_______...- '" << endl;
		cout << "          /    .'" << endl;
		cout << "         /   .'" << endl;
		cout << "        /  .'         " << endl;
		cout << "        `-'" << endl;*/

		cout << "                             |" << endl;
		cout << "                _______     ^^^" << endl;
		cout << "               |**FIA**|  _^^^^^_" << endl;
		cout << "               |[]+++[]| | [][]  |" << endl;
		cout << "            ______+++++| |[][][] |" << endl;
		cout << "           |++++++|++[]| | [][][]|     " << endl;;
		cout << "           || || ||++++| |[][][] |" << "                                    __  _" << endl;
		cout << "           |++++++|_________ [][]|" << "                                    \ `/ |" << endl;
		cout << "           || || ||=|=|=|=|=| [] |" << "                                     \__`!" << endl;
		cout << "           |++++++|=|=|=|=|=|[][]|" << "                                     / ,' `-.__________________" << endl;
		cout << "___________|++HH++|  _HHHH__|   _________   _________  _________" << "      '-'\\_____   J I A         \\_`-." << endl;
		cout << "         _______________   ______________      ______________" << "            <____()-=O=O=O=O=O=[]====-- )" << endl;
		cout << "__________________  ___________    __________________    ____________" << "___   `.___ ,-----,_______...- '" << endl;
		cout << "         _______________                 _______________                        /    .'" << endl;
		cout << "__________________  ___________    __________________    _________________     /   .'" << endl;
		cout << "                                                                              /  .'         " << endl;
		cout << "                                                                              `-'" << endl;

		cout << endl;
		cout << "How may we help you?" << endl;
		cout << "1. Display All Flights" << endl;
		cout << "2. Display All Flights with their Information" << endl;
		cout << "3. Choose a specific airline" << endl;
		cout << "4. Book a Flight" << endl;
		cout << "5. Exit" << endl;
		cout << "*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*" << endl;
		cin >> choice;

		//EXIT
		if (choice == 5)
		{
			cout << "Goodbye!" << endl;
			break;
		}

		system("CLS");

		//DISPLAY FLIGHTS
		if (choice == 1)
		{
			cout << "Here are all the flights:" << endl;
			graph->display();
		}

		//DISPLAY FLIGHTS WITH WEIGHTS
		else if (choice == 2)
		{
			cout << "Here are all the flights and their Information:" << endl;
			graph->displayWeighted();
		}

		//CHOOSE AN AIRLINE
		else if (choice == 3)
		{
			cout << "what airline would you want to travel with?" << endl;
			cout << "1. Emirates \n2. Qatar \n3. ANA \n4. All Airlines\n";
			cin >> airline;
			if (airline == 1)
			{
				delete graph;
				graph = NULL;
				graph = getSubGraph("Emirates",flights,hotelCharges);
				airlineAll = true;
			}
			else if (airline == 2)
			{
				delete graph;
				graph = NULL;
				graph = getSubGraph("Qatar", flights, hotelCharges);
				airlineAll = true;
			}
			else if (airline == 3)
			{
				delete graph;
				graph = NULL;
				graph = getSubGraph("ANA", flights, hotelCharges);
				airlineAll = true;
			}
			else if (airline == 4 && airlineAll == true)
			{
				delete graph;
				graph = NULL;
				graph = new Graph<string, Weight>(flights, hotelCharges);
			}
		}

		//BOOK A FLIGHT
		else if (choice == 4)
		{
			cout << "What is your location ?" << endl;
			graph->displayVertices();

			cin >> location;
			system("CLS");
			isFlight = true;
			ready = "yes";
			while (ready == "yes" && isFlight)
			{


				if (Tflag == false)
				{
					cout << "What is your Destination ?" << endl;
					graph->displayVertices();

					cin >> destination;

					system("CLS");
					cout << "Please enter desired day of flight." << endl;
					cin >> d;
					d += "/12/2019";
					date.setDate(d);

				}
				else
				{
					destination = transitLocation;
					Tflag = false;
				}

				system("CLS");
				cout << "Your Location: " << location << endl;
				cout << "Your Destination: " << destination << endl;
				cout << "Date of Travel: " << date.getDate() << endl;


				cout << "Any Transit Location?" << endl;
				cout << "* no" << endl;
				graph->displayVertices();
				cin >> transitLocation;

				if (transitLocation != "no")
				{
					swap(destination, transitLocation);
					Tflag = true;
				}

				cout << "\nWhat Type of Flight do you want?" << endl;
				cout << "1. Direct Flight." << endl;
				cout << "2. Connected Flight" << endl;
				cin >> typeOfFlight;
				system("CLS");

				if (typeOfFlight == 1)
				{
					if (graph->getList(location)->search(destination))
					{
						cout << "Flight with highest priority of ?" << endl;
						cout << "1. Minimal Cost" << endl;
						cout << "2. Minimal Time" << endl;
						cout << "3. As Soon As Possible" << endl;
						cin >> wrt;
						system("CLS");
						graph->showPath(location, destination, (wrt - 1));
						isFlight = true;
					}
					else
					{
						cout << "No Direct Path Exists for your Flight" << endl;
						isFlight = false;
						break;
					}
				}
				else if (typeOfFlight == 2)
				{
					cout << "Flight with highest priority of ?" << endl;
					cout << "1. Minimal Cost" << endl;
					cout << "2. Minimal Time" << endl;
					cin >> wrt;
					system("CLS");
					if (wrt == 1)
						isFlight = graph->floydWarshall(location, destination);
					else if (wrt == 2)
						isFlight = graph->floydWarshall2(location, destination);
				}

				if (isFlight)
				{
					cout << "\nTransit Cost: "<<graph->getList(destination)->transitCost << endl;

					cout << "Are You Ready for the Flight?" << endl;
					cout << "* yes" << endl;
					cout << "* no" << endl;
					cin >> ready;
					if (ready == "yes")
					{
						for (int i = 0; i < 85; i++)
						{
							system("CLS");

							if (i < 20)
							{
								cout << "\n\n\n\n";
							}
							else if (i >= 20 && i < 30)
							{
								cout << "\n\n\n";
							}
							else if (i >= 30 && i < 40)
							{
								cout << "\n\n";
							}
							else if (i >= 40)
							{
								cout << "\n";
							}

							for (int j = 0; j < i; j++)
								cout << " ";
							cout << "__  _" << endl;
							for (int j = 0; j < i; j++)
								cout << " ";
							cout << "\ `/ |" << endl;
							for (int j = 0; j < i; j++)
								cout << " ";
							cout << " \__`!" << endl;
							for (int j = 0; j < i; j++)
								cout << " ";
							cout << " / ,' `-.__________________" << endl;
							for (int j = 0; j < i; j++)
								cout << " ";
							cout << "'-'\\_____   J I A         \\_`-." << endl;
							for (int j = 0; j < i; j++)
								cout << " ";
							cout << "   <____()-=O=O=O=O=O=[]====-- )" << endl;
							for (int j = 0; j < i; j++)
								cout << " ";
							cout << "     `.___ ,-----,_______...- '" << endl;
							for (int j = 0; j < i; j++)
								cout << " ";
							cout << "          /    .'" << endl;
							for (int j = 0; j < i; j++)
								cout << " ";
							cout << "         /   .'" << endl;
							for (int j = 0; j < i; j++)
								cout << " ";
							cout << "        /  .'         " << endl;
							for (int j = 0; j < i; j++)
								cout << " ";
							cout << "        `-'" << endl;

							if (i < 20)
							{
								cout << "\n";
							}
							else if (i >= 20 && i < 30)
							{
								cout << "\n\n";
							}
							else if (i >= 30 && i < 40)
							{
								cout << "\n\n\n";
							}
							else if (i >= 40)
							{
								cout << "\n\n\n\n";
							}

							cout << "                             |" << endl;
							cout << "                _______     ^^^" << endl;
							cout << "               |**JIA**|  _^^^^^_" << endl;
							cout << "               |[]+++[]| | [][]  |" << endl;
							cout << "            ______+++++| |[][][] |" << endl;
							cout << "           |++++++|++[]| | [][][]|     " << endl;;
							cout << "           || || ||++++| |[][][] |" << endl;
							cout << "           |++++++|_________ [][]|" << endl;
							cout << "           || || ||=|=|=|=|=| [] |" << endl;
							cout << "           |++++++|=|=|=|=|=|[][]|" << endl;
							cout << "___________|++HH++|  _HHHH__|   _________   _________  _________" << endl;
							cout << "         _______________   ______________      ______________" << endl;
							cout << "__________________  ___________    __________________    ____________";
						}
					}
					system("CLS");
					location = destination;
					cout << "You Have Arrived At: " << destination << endl;
					cout << "Now where would you like to go?" << endl;
				}

			}
		}

	}
}