//BINARYSEARCHTREE.CPP
#include "BinarySearchTree.h"

double log_base_n(double x, double base)
{
	return std::log(x) / std::log(base);
}

int MinimaAlturaDeArbol(int numeroDeNodos, int maximoDeHijosPorNodo)
{
	int maximoDeHijosMenos1PorNumeroDeNodosMasUno = ((maximoDeHijosPorNodo - 1) * numeroDeNodos + 1);
	int altura = ceil(log_base_n(maximoDeHijosMenos1PorNumeroDeNodosMasUno, maximoDeHijosPorNodo)) - 1;
	return altura;
}
// BINARYSEARCHTREE.H
#include <iostream>
using namespace std;

#include <cmath> // Required for std::log

double log_base_n(double x, double base);


int MinimaAlturaDeArbol(int numeroDeNodos, int maximoDeHijosPorNodo);

template <typename T>
class BinarySearchTree
{
	template <typename T>
	class TreeNode
	{
	public:
		TreeNode()
		{
			parent = leftChild = rightChild = nullptr;
			data = {};
		}

		TreeNode(T data)
		{
			parent = leftChild = rightChild = nullptr;
			// this se refiere a exactamente el objeto que está mandando a llamar la función. 
			this->data = data;
		}

		T data;
		// el padre de este nodo dentro del árbol. 
		// En otras palabras, this == parent.leftChild || this == parent.rightChild
		TreeNode<T>* parent;

		// vector<TreeNode*> children; // si quisiéramos que tuviera la posibilidad de tener más de dos hijos cada nodo.
		TreeNode<T>* leftChild;
		TreeNode<T>* rightChild;
	};

public:
	BinarySearchTree()
	{
		root = nullptr;
		count = 0;
	}

	void AddWithAddRecursive(T value)
	{
		// primero checamos si root es nullptr. 
		if (root == nullptr)
		{
			// si sí es nullptr, quiere decir que value es el primer valor en entrar, y por tanto se va a 
			// convertir en el nodo root.
			root = new TreeNode<T>(value);
			count++;
			return; // nos salimos de la función.
		}

		TreeNode<T>* currentNode = root;

		AddRecursive(value, currentNode);
	}

	void InsertarNode(TreeNode<T>* currentNode, bool isLeftChild, T value)
	{
		TreeNode<T>* newNode = new TreeNode<T>(value);
		newNode->parent = currentNode;
		if (isLeftChild)
			currentNode->leftChild = newNode;
		else
			currentNode->rightChild = newNode;
		count++;

	}
// Corregimos el manejo de valores duplicados porque el codigo original no contemplaba el caso
// en que value==currentNode->data, lo que podia generar bucles infinitos o errores, ahora simplemente evitamos insertar valores que se repitan, manteniendo la integridad del arbolito de las pesadillas

	void AddRecursive(T value, TreeNode<T>* currentNode)
	{
		if (value > currentNode->data)
		{
			// si "value" es mayor, vamos al hijo derecho (recursivo)
			if (currentNode->rightChild == nullptr)
			{
				InsertarNode(currentNode, false, value);
				return;
			}
			else
			{
				return AddRecursive(value, currentNode->rightChild);
			}
		}
		else if (value < currentNode->data)
		{
			// si "value" es menor, vamos al hijo izquierdo (recursivo)
			if (currentNode->leftChild == nullptr)
			{
				InsertarNode(currentNode, true, value);
				return;
			}
			else
			{
				return AddRecursive(value, currentNode->leftChild);
			}
		}
		else
		{
			// Si llegamos aquí, es porque el valor ya existe en el arbol
			// No insertamos valores duplicados para mantener el arbol limpio
			// Por eso solo salimos sin hacer nada
			return;
		}
	}

	void Add(T value)
	{
		if (root == nullptr)
		{
			root = new TreeNode<T>(value);
			count++;
			return;
		}

		TreeNode<T>* currentNode = root;

		while (currentNode != nullptr)
		{
			if (value > currentNode->data)
			{
				if (currentNode->rightChild == nullptr)
				{
					InsertarNode(currentNode, false, value);
					return;
				}
				else
				{
					currentNode = currentNode->rightChild;
				}
			}
			else if (value < currentNode->data)
			{
				if (currentNode->leftChild == nullptr)
				{
					InsertarNode(currentNode, true, value);
					return;
				}
				else
				{
					currentNode = currentNode->leftChild;
				}
			}
			else
			{
				// Este valor ya existe, no se permiten duplicados.
				// Solo salimos de la función para evitar ciclos infinitos.
				return;
			}
		}
	}

	void InOrderWithRecursive()
	{
		InOrderRecursive(root);
	}


	int MinimaAltura()
	{
		// le dice que tiene N nodos, y que es un árbol de base 2 (porque es binario en este caso).
		return MinimaAlturaDeArbol(count, 2);
	}



	// Es el nodo raíz desde el cual el árbol es capaz de llegar a cualquier otro nodo en el árbol.
	TreeNode<T>* root;

	// cuántos nodos en total tiene el árbol.
	int count;

	// cuántos niveles de profundidad tiene el árbol.
	// int depth;

	bool SearchWithRecursive(T value)
	{
		TreeNode<T>* resultNode = SearchRecursive(root, value);
		if (resultNode == nullptr)
			return false;
		return true;
	}

	void Delete(T value)
	{
		// Corroboramos que existe un nodo con el value dado.
		TreeNode<T>* nodeToDelete = SearchRecursive(root, value);

		if (nodeToDelete == nullptr)
		{
			cout << "no existe el valor value en este árbol." << endl;
			return;
		}

		// si sí existe, entonces checamos cuál de los 3 casos es.
		// caso 1: el nodo no tiene hijos.
		if (nodeToDelete->leftChild == nullptr &&
			nodeToDelete->rightChild == nullptr)
		{
			// entonces no tiene hijos.

			// haces que el puntero a hijo de su padre que apunta a este nodo sea null
			// checamos si nodeToDelete es hijo izquierdo o derecho de su papá.
			if (nodeToDelete->parent->leftChild == nodeToDelete) // soy tu hijo izquierdo?
			{
				nodeToDelete->parent->leftChild = nullptr;
			}
			else
			{
				// si no, entonces somos el hijo derecho
				nodeToDelete->parent->rightChild = nullptr;
			}

			// y luego borras este nodo
			count--;
			delete nodeToDelete;
			return;
		}
		// caso 2: tiene un solo hijo.
		if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild != nullptr)
		{
			// tiene hijo derecho pero no izquierdo
			// haces que dicho hijo tome el lugar de X en el árbol 

			// en pocas palabras: Nieto se conecta al abuelo, y el abuelo al nieto, y luego se borra el papá.
			// nodeToDelete le dice a su papá que ahora que ahora él debe apuntar a su nieto.
			// necesitamos saber si somos hijo izquierdo o derecho del abuelo, para poder reasignar el puntero.
			if (nodeToDelete->parent->leftChild == nodeToDelete) // soy tu hijo izquierdo?
			{
				nodeToDelete->parent->leftChild = nodeToDelete->rightChild;
			}
			else
			{
				// si no, entonces somos el hijo derecho
				nodeToDelete->parent->rightChild = nodeToDelete->rightChild;
			}

			// y el nieto, ahora su parent va a ser su abuelo.
			nodeToDelete->rightChild->parent = nodeToDelete->parent;
			delete nodeToDelete;
			count--;
			return;
		}
		else if (nodeToDelete->leftChild != nullptr && nodeToDelete->rightChild == nullptr)
		{
			// tiene hijo izquierdo pero no derecho.
			// haces que dicho hijo tome el lugar de X en el árbol 

			// en pocas palabras: Nieto se conecta al abuelo, y el abuelo al nieto, y luego se borra el papá.
			// nodeToDelete le dice a su papá que ahora que ahora él debe apuntar a su nieto.
			// necesitamos saber si somos hijo izquierdo o derecho del abuelo, para poder reasignar el puntero.
			if (nodeToDelete->parent->leftChild == nodeToDelete) // soy tu hijo izquierdo?
			{
				nodeToDelete->parent->leftChild = nodeToDelete->leftChild;
			}
			else
			{
				// si no, entonces somos el hijo derecho
				nodeToDelete->parent->rightChild = nodeToDelete->leftChild;
			}

			// y el nieto, ahora su parent va a ser su abuelo.
			nodeToDelete->leftChild->parent = nodeToDelete->parent;
			// y luego borras a X
			delete nodeToDelete;
			count--;
			return;
		}

		// aquí ya sabemos que tiene los dos hijos porque si no no habría llegado a esta línea de código.
		// entonces es el caso 3:

		// encontramos al sucesor de nodeToDelete
		TreeNode<T>* successorNode = Successor(nodeToDelete);  // NOTA, nunca podría ser nulo, porque nodeToDelete tiene sus dos hijos
		// a donde nodeToDelete apuntaba con la izquierda, ahora el sucesor apunta con su izquierda y viceversa.
		successorNode->leftChild = nodeToDelete->leftChild;
		nodeToDelete->leftChild->parent = successorNode;

		// el hijo derecho del sucesor ahora es hijo del papá del sucesor y viceversa.
		// pero necesitamos saber si successorNode es hijo izquierdo o derecho del abuelo.
		if (successorNode->parent->leftChild == successorNode) // soy tu hijo izquierdo?
		{
			successorNode->parent->leftChild = successorNode->rightChild;
		}
		else
		{
			// si no, entonces somos el hijo derecho
			successorNode->parent->rightChild = successorNode->rightChild;
		}
		// conectamos el hijo derecho del sucesor con su abuelo.
		successorNode->rightChild->parent = successorNode->parent;

		// a donde apuntaba nodeToDelete con la derecha, ahora el sucesor va a apuntar con su derecha y viceversa.
		successorNode->rightChild = nodeToDelete->rightChild;
		nodeToDelete->rightChild->parent = successorNode;

		// nos falta que el sucesor sepa quién es su papá, y viceversa
		successorNode->parent = nodeToDelete->parent;
		// aquí SÍ necesitamos saber si nodeToDelete es su hijo derecho o izquierdo
		if (nodeToDelete->parent->leftChild == nodeToDelete) // soy tu hijo izquierdo?
		{
			nodeToDelete->parent->leftChild = successorNode;
		}
		else
		{
			// si no, entonces somos el hijo derecho
			nodeToDelete->parent->rightChild = successorNode;
		}

		count--;
		// y borramos el nodo.
		delete nodeToDelete;
	}



private:
	TreeNode<T>* TreeMaximum()
	{
		// empezamos en la raíz y le pedimos el máximo desde ahí.
		return Maximum(root);
	}

	// Nos da el máximo a partir de node como raíz.
	TreeNode<T>* Maximum(TreeNode<T>* node)
	{
		// empezamos en node y 
		TreeNode<T>* maximum = node;
		// nos vamos todo a la derecha hasta que el hijo derecha sea nullptr.
		while (maximum->rightChild != nullptr)
			maximum = maximum->rightChild;

		return maximum;
	}


	// el mínimo valor T en todo el árbol.
	TreeNode<T>* TreeMinimum()
	{
		// empezamos en la raíz y le pedimos el mínimo desde ahí
		return Minimum(root);
	}

	// Nos da el mínimo a partir de node como raíz.
	TreeNode<T>* Minimum(TreeNode<T>* node)
	{
		// empezamos en node y 
		TreeNode<T>* minimum = node;
		// nos vamos todo a la izquierda hasta que el hijo izquierdo sea nullptr.
		while (minimum->leftChild != nullptr)
			minimum = minimum->leftChild;

		return minimum;
	}

	TreeNode<T>* MinimumWithRecursive()
	{
		// empezamos en la raíz y hacemos recursión.
		return MinimumRecursive(root);
	}

	TreeNode<T>* MinimumRecursive(TreeNode<T>* currentNode)
	{
		if (currentNode->leftChild == nullptr)
			return currentNode;
		// else
		return MinimumRecursive(currentNode->leftChild);
	}

	TreeNode<T>* Successor(TreeNode<T>* node)
	{
		if (node->rightChild != nullptr)
			return Minimum(node->rightChild); // Minimum se debe mandar a llamar desde la derecha del node que se recibió como parámetro.

		// si no, entonces 
		// tomamos el padre de node, y lo guardamos en una variable
		TreeNode<T>* ancestor = node->parent;
		// Mientras que no llegue a null y siga siendo hijo derecho de alguien, entonces se seguirá
		// subiendo en los parents.
		while (ancestor != nullptr && node == ancestor->rightChild)
		{
			// node se vuelve su papá
			node = ancestor;
			// y el papá se vuelve su papá
			ancestor = node->parent;
		}
		return ancestor;
	}

	// lo mismo que Successor, pero invertimos Right por Left, y Minimum por maximum.
	TreeNode<T>* Predecessor(TreeNode<T>* node)
	{
		if (node->leftChild != nullptr)
			return Maximum(node->leftChild); // Maximum se debe mandar a llamar desde la izquierda del node que se recibió como parámetro.

		// si no, entonces 
		// tomamos el padre de node, y lo guardamos en una variable
		TreeNode<T>* ancestor = node->parent;
		// Mientras que no llegue a null y siga siendo hijo izquierdo de alguien, entonces se seguirá
		// subiendo en los parents.
		while (ancestor != nullptr && node == ancestor->leftChild)
		{
			// node se vuelve su papá
			node = ancestor;
			// y el papá se vuelve su papá
			ancestor = node->parent;
		}
		return ancestor;
	}


	TreeNode<T>* SearchRecursive(TreeNode<T>* currentNode, T value)
	{
		if (currentNode == nullptr)
			return nullptr;
		if (currentNode->data == value)
			return currentNode;
		// si el valor que estás buscando (value) es menor que el de este nodo, vete al hijo izquierdo
		if (value < currentNode->data)
		{
			return SearchRecursive(currentNode->leftChild, value);
		}

		// else
		return SearchRecursive(currentNode->rightChild, value);
	}

	void InOrderRecursive(TreeNode<T>* node)
	{
		if (node != nullptr)
		{
			// Mandamos recursivamente a izquierda
			InOrderRecursive(node->leftChild);
			// Luego se visita (en este caso, se imprime su valor)
			cout << node->data << endl;
			// Mandamos recursivamente a derecha
			InOrderRecursive(node->rightChild);
		}
	}

	void PreOrderRecursive(TreeNode<T>* node)
	{
		if (node != nullptr)
		{
			// Luego se visita (en este caso, se imprime su valor)
			cout << node->data << endl;
			// Mandamos recursivamente a izquierda
			PreOrderRecursive(node->leftChild);
			// Mandamos recursivamente a derecha
			PreOrderRecursive(node->rightChild);
		}
	}

	void PostOrderRecursive(TreeNode<T>* node)
	{
		if (node != nullptr)
		{
			// Mandamos recursivamente a izquierda
			PostOrderRecursive(node->leftChild);
			// Mandamos recursivamente a derecha
			PostOrderRecursive(node->rightChild);
			// Luego se visita (en este caso, se imprime su valor)
			cout << node->data << endl;
		}
	}


};

/*
 SOLO ERA PARA MOTIVOS DE PROBAR QUE SUCCESSOR FUNCIONARA, SÍ PARECE FUNCIONAR.
	T SuccessorValue(T value)
	{
		// primero buscamos el nodo que tiene ese valor.
		TreeNode<T>* node = SearchRecursive(root, value);

		if (node == nullptr)
		{
			throw runtime_error("no se encontró value en este árbol para hacer Sucessor");
			return {};
		}

		TreeNode<T>* result = Successor(node);
		if (result == nullptr)
		{
			throw runtime_error("no se encontró un successor para value en este árbol");
			return {};
		}
		return result->data;
	}

*/
