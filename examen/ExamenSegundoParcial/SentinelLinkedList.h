#pragma once


#pragma once

#include <iostream>
using namespace std;


template <typename T>
class SentinelLinkedList
{
private:
	template <typename T>
	class Node
	{
	public:
		Node()
		{
			// Se podr�a lograr implementar sin tenerlo aqu�, y (en teor�a) podr�as ganar 
			// una cantidad peque�a peque��sima de performance, pero como esto es did�ctico, 
			// les va a ayudar a evitar unos cuantos problemillas.
			prev = nullptr;
			next = nullptr;
		}

		Node(T value)
		{
			data = value;
			// Se podr�a lograr implementar sin tenerlo aqu�, y (en teor�a) podr�as ganar 
			// una cantidad peque�a peque��sima de performance, pero como esto es did�ctico, 
			// les va a ayudar a evitar unos cuantos problemillas.
			prev = nullptr;
			next = nullptr;
		}

		T data;
		Node<T>* next;
		Node<T>* prev;
	};


private:
	Node<T>* NIL; // un puntero al primer y �ltimo nodo de nuestra lista ligada.
	int count; // n�mero de elementos en esta lista ligada.

public:
	SentinelLinkedList()
	{
		count = 0;
		NIL = new SentinelLinkedList::Node<T>(); // S� lo tenemos que inicializar al construir la lista.
		NIL->next = NIL;
		NIL->prev = NIL;
	}

	int GetCount() { return count; };

	SentinelLinkedList::Node<T>& Find(T value);

	SentinelLinkedList::Node<T>& FindV2(T value);

	SentinelLinkedList::Node<T>& Successor(SentinelLinkedList::Node<T>* node)
	{
		return node->next;
	}

	SentinelLinkedList::Node<T>& Predecessor(SentinelLinkedList::Node<T>* node)
	{
		return node->prev;
	}


	// A�ade un nuevo nodo al final de la lista.
	void PushBack(T value);

	// Quita el nodo del final de la lista y devuelve su valor.
	T PopBack();

	// Un nodo con el valor valueToInsert se insertar� como el Next de previousNode.
	void Insert(T valueToInsert, Node<T>* previousNode);

	void Remove(T valueToRemove);

	// void Remove(Node<T>* nodeToRemove);

	// Regresa una copia de la data del nodo del frente, pero sin sacarlo de la lista.
	T Front();

	int operationCounter;
};

template<typename T>
void SentinelLinkedList<T>::Remove(T valueToRemove)
{
	// empieza en el primer de la lista
	Node<T>* currentNode = NIL->next; // usamos una variable auxiliar para no tocar la referencia al first.

	// hacemos un ciclo para checar todos los nodos, hasta que ya no haya nodo siguiente.
	while (currentNode != NIL)
	{
		// checa si la data del nodo actual es igual al valor a encontrarse (valueToRemove)
		if (currentNode->data == valueToRemove)
		{
			// El nodo anterior de currentNode su next debe apuntar a donde apunta currentNode-next
			// es decir, el nodo anterior de currentNode es currentNode->prev
			// es decir, el next de currentNode->prev ser�a currentNode->prev->next
			currentNode->prev->next = currentNode->next;
			// ahora hacemos lo mismo pero en la otra direcci�n
			// el prev de currentNode->next ser�a currentNode->next->prev debe apuntar a donde apunta currentNode-prev
			currentNode->next->prev = currentNode->prev;

			delete currentNode;
			count--;
			return;
		}
		else
		{
			// si no lo tiene, continuamos al nodo que le sigue a currentNode.
			currentNode = currentNode->next;
		}
	}

}

template<typename T>
SentinelLinkedList<T>::Node<T>& SentinelLinkedList<T>::Find(T value)
{
	// empieza en el primer de la lista, que ser�a el next de NIL
	Node<T>* currentNode = NIL->next; // usamos una variable auxiliar para no tocar la referencia al first.

	// hacemos un ciclo para checar todos los nodos, desde el primer elemento (NIL->next) hasta NIL
	while (currentNode != NIL)
	{
		// checa si la data del nodo actual es igual al valor a encontrarse (value)
		if (currentNode->data == value)
		{
			// NOTA: Estas dos l�neas son equivalentes, pero la flecha -> es m�s c�moda y pr�ctica y est�ndar.
			// currentNode->data
			// (*currentNode).data

			// si s� lo tiene, regresamos dicho nodo y nos salimos de la funci�n.
			return currentNode;
		}
		else
		{
			// si no lo tiene, continuamos al nodo que le sigue a currentNode.
			currentNode = currentNode->next;
		}
	}

	// si llegamos a esta parte del c�digo, es porque no encontramos ning�n nodo con el valor value.
	// entonces regresamos nullptr porque no existe dicho nodo.
	return nullptr;
}


template<typename T>
SentinelLinkedList<T>::Node<T>& SentinelLinkedList<T>::FindV2(T value)
{
	// empieza en el primer de la lista
	Node<T>* currentNode = NIL->next; // usamos una variable auxiliar para no tocar la referencia al first.

	// hacemos un ciclo para checar todos los nodos, hasta que ya no haya nodo siguiente.
	while (currentNode != NIL)
	{
		// checa si la data del nodo actual es igual al valor a encontrarse (value)
		if (currentNode->data == value)
			return currentNode;

		// si no lo tiene, continuamos al nodo que le sigue a currentNode.
		currentNode = currentNode->next;
	}

	// si llegamos a esta parte del c�digo, es porque no encontramos ning�n nodo con el valor value.
	// entonces regresamos nullptr porque no existe dicho nodo.
	return nullptr;
}

template<typename T>
void SentinelLinkedList<T>::Insert(T valueToInsert, SentinelLinkedList<T>::Node<T>* previousNode)
{
	// Un nodo con el valor valueToInsert se insertar� como el Next de previousNode.

	// Nuevo nodo que ser� el nuevo Next de previousNode 
	Node<T>* newNode = new Node<T>(valueToInsert); // usamos una variable auxiliar para no tocar la referencia al first.

	// NOTA, es importante primero hacer la que va de newNode a previousNode->next y despu�s la de previousNode->next a newNode, 
	// porque si no newNode termina teni�ndose como su propio next, lo cual es un grave error.

	// Hacemos la conexi�n desde newNode hacia el next de previousNode
	newNode->next = previousNode->next;

	// Hacemos la conexi�n desde previousNode hacia newNode como su next
	previousNode->next = newNode;

	// aumentar el tama�o de la lista.
	count++;
}

// A�ade un nuevo nodo al final de la lista.
template<typename T>
void SentinelLinkedList<T>::PushBack(T value)
{
	// Creamos un nuevo nodo con el valor value como su data.
	Node<T>* newNode = new Node<T>(value);
	// su siguiente ya no va a ser nullptr, va a ser el nodo NIL
	newNode->next = NIL;

	// el que era el prev de nil (nil->prev) ahora su next apunta a newNode
	NIL->prev->next = newNode;

	// el prev de newNode apunte al prev de NIL
	newNode->prev = NIL->prev;
	// y ahora que el prev de NIL apunte al nodo nuevo
	NIL->prev = newNode;

	count++; // como metimos un nuevo elemento, aumentamos el contador de elementos.
}

template<typename T>
T SentinelLinkedList<T>::PopBack()
{
	// si no hay ning�n elemento.
	if (count == 0)
	{
		cout << "Cuidado, est�s haciendo pop back cuando ya no hay elementos en esta lista ligada";
		return {}; // {} es un elemento de tipo T con su valor por defecto, sin importar de qu� tipo sea T.
	}

	// ya sabemos que el �ltimo nodo es NIL
	// y sabemos que el pen�ltimo nodo va a ser el NIL->prev
	Node<T>* penultimateNode = NIL->prev;

	// tenemos que poner que del penultimate node ahora NIL apunta hacia su previo y viceversa
	NIL->prev = penultimateNode->prev;
	penultimateNode->prev->next = NIL; 

	// guardamos la data del �ltimo nodo
	T data = penultimateNode->data;

	// ya que tenemos la data borramos al �ltimo nodo
	delete penultimateNode;
	penultimateNode = nullptr;
	count--;

	return data;
}

template <typename T>
T SentinelLinkedList<T>::Front()
{
	if (count == 0)
	{
		cout << "Advertencia, se est� tratando de acceder al primer elemento de una SentinelLinkedList, pero est� vac�a" << endl;
		return {};
	}
	return NIL->next->data;
}


//
/*
for(i = 0; i = N; i++)
{
	suma
	resta
	multiplicaci�n
	print

}
N*4

*/