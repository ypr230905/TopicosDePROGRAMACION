// BINARYSEARCHTREE.CPP
#include "BinarySearchTree.h"

// Función para calcular logaritmo en base n, que nos ayuda con la altura mínima del árbol.
double log_base_n(double x, double base)
{
    return std::log(x) / std::log(base);
}

// Calcula la altura mínima de un árbol con cierto número de nodos y máximo de hijos por nodo.
int MinimaAlturaDeArbol(int numeroDeNodos, int maximoDeHijosPorNodo)
{
    int maximoDeHijosMenos1PorNumeroDeNodosMasUno = ((maximoDeHijosPorNodo - 1) * numeroDeNodos + 1);
    int altura = ceil(log_base_n(maximoDeHijosMenos1PorNumeroDeNodosMasUno, maximoDeHijosPorNodo)) - 1;
    return altura;
}
// BINARYSEARCHTREE.H
#pragma once

#include <iostream>
using namespace std;

#include <cmath> // Necesario para std::log

// Declaración de funciones auxiliares para altura mínima
double log_base_n(double x, double base);
int MinimaAlturaDeArbol(int numeroDeNodos, int maximoDeHijosPorNodo);

template <typename T>
class BinarySearchTree
{
    // Clase interna que representa a cada nodo del árbol.
    template <typename T>
    class TreeNode
    {
    public:
        TreeNode()
        {
            // Inicializamos punteros a null y data vacío.
            parent = leftChild = rightChild = nullptr;
            data = {};
        }

        TreeNode(T data)
        {
            parent = leftChild = rightChild = nullptr;
            // 'this' se refiere al objeto actual, aquí asignamos el dato.
            this->data = data;
        }

        T data;  // Valor guardado en el nodo.

        // Puntero al nodo padre (quien apunta a este nodo).
        TreeNode<T>* parent;

        // Punteros a los hijos izquierdo y derecho (porque es binario).
        TreeNode<T>* leftChild;
        TreeNode<T>* rightChild;
    };

public:
    // Constructor del árbol, inicia vacío.
    BinarySearchTree()
    {
        root = nullptr;
        count = 0;
    }

    // Añadir un valor usando recursión para insertarlo en su lugar correcto.
    void AddWithAddRecursive(T value)
    {
        // Si el árbol está vacío, creamos el nodo raíz con el valor.
        if (root == nullptr)
        {
            root = new TreeNode<T>(value);
            count++;
            return; // Salimos porque ya insertamos el valor.
        }

        TreeNode<T>* currentNode = root;
        AddRecursive(value, currentNode);
    }

    // Función que crea e inserta un nuevo nodo como hijo izquierdo o derecho.
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

    /*
    Aquí corregimos el manejo de valores duplicados, que antes no se contemplaba.
    Si intentamos insertar un valor que ya existe, simplemente no lo añadimos para evitar bucles infinitos o errores.
    Esto mantiene limpio nuestro árbol de pesadillas.
    */
    void AddRecursive(T value, TreeNode<T>* currentNode)
    {
        if (value > currentNode->data)
        {
            // Si el valor es mayor, vamos al hijo derecho (recursivo).
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
            // Si el valor es menor, vamos al hijo izquierdo (recursivo).
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
            // Si llegamos aquí, el valor ya existe en el árbol, no lo insertamos.
            return;
        }
    }

    // Añade un valor de forma iterativa, recorriendo el árbol desde la raíz.
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
                // Valor duplicado, no se añade para evitar ciclos infinitos.
                return;
            }
        }
    }

    // Recorre el árbol en orden (izquierda, nodo, derecha) de forma recursiva.
    void InOrderWithRecursive()
    {
        InOrderRecursive(root);
    }

    // Calcula la altura mínima del árbol basado en el número de nodos y máximo de hijos (2 para binario).
    int MinimaAltura()
    {
        return MinimaAlturaDeArbol(count, 2);
    }

    // Nodo raíz del árbol.
    TreeNode<T>* root;

    // Conteo de cuántos nodos hay en total.
    int count;

    // Busca un valor usando recursión, devuelve true si lo encuentra.
    bool SearchWithRecursive(T value)
    {
        TreeNode<T>* resultNode = SearchRecursive(root, value);
        if (resultNode == nullptr)
            return false;
        return true;
    }

    // Nueva función iterativa para buscar un valor, más fácil y rápida.
    bool Search(T value)
    {
        TreeNode<T>* currentNode = root;

        while (currentNode != nullptr)
        {
            if (currentNode->data == value)
            {
                return true; // ¡Lo encontramos!
            }
            else if (value < currentNode->data)
            {
                currentNode = currentNode->leftChild;
            }
            else
            {
                currentNode = currentNode->rightChild;
            }
        }

        // Si llegamos aquí, no estaba en el árbol.
        return false;
    }

    // Función para borrar un nodo con valor dado, manejando los tres casos posibles.
    void Delete(T value)
    {
        // Buscamos el nodo que tiene el valor que queremos borrar.
        TreeNode<T>* nodeToDelete = SearchRecursive(root, value);

        if (nodeToDelete == nullptr)
        {
            cout << "no existe el valor value en este árbol." << endl;
            return;
        }

        // Caso 1: el nodo no tiene hijos.
        if (nodeToDelete->leftChild == nullptr &&
            nodeToDelete->rightChild == nullptr)
        {
            // Desconectamos el nodo de su padre.
            if (nodeToDelete->parent->leftChild == nodeToDelete) // ¿Soy hijo izquierdo?
            {
                nodeToDelete->parent->leftChild = nullptr;
            }
            else
            {
                nodeToDelete->parent->rightChild = nullptr;
            }

            count--;
            delete nodeToDelete;
            return;
        }
        // Caso 2: tiene un solo hijo derecho.
        if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild != nullptr)
        {
            // El hijo derecho toma el lugar del nodo a borrar.
            if (nodeToDelete->parent->leftChild == nodeToDelete) // ¿Soy hijo izquierdo?
            {
                nodeToDelete->parent->leftChild = nodeToDelete->rightChild;
            }
            else
            {
                nodeToDelete->parent->rightChild = nodeToDelete->rightChild;
            }

            nodeToDelete->rightChild->parent = nodeToDelete->parent;
            delete nodeToDelete;
            count--;
            return;
        }
        // Caso 2: tiene un solo hijo izquierdo.
        else if (nodeToDelete->leftChild != nullptr && nodeToDelete->rightChild == nullptr)
        {
            if (nodeToDelete->parent->leftChild == nodeToDelete) // ¿Soy hijo izquierdo?
            {
                nodeToDelete->parent->leftChild = nodeToDelete->leftChild;
            }
            else
            {
                nodeToDelete->parent->rightChild = nodeToDelete->leftChild;
            }

            nodeToDelete->leftChild->parent = nodeToDelete->parent;
            delete nodeToDelete;
            count--;
            return;
        }

        // Caso 3: el nodo tiene dos hijos.
        TreeNode<T>* successorNode = Successor(nodeToDelete);  // Sucesor no puede ser nulo aquí.

        // Reasignamos los hijos izquierdo y derecho para que el sucesor ocupe el lugar.
        successorNode->leftChild = nodeToDelete->leftChild;
        nodeToDelete->leftChild->parent = successorNode;

        // Reasignamos el hijo derecho del sucesor al padre del sucesor.
        if (successorNode->parent->leftChild == successorNode) // ¿Es hijo izquierdo?
        {
            successorNode->parent->leftChild = successorNode->rightChild;
        }
        else
        {
            successorNode->parent->rightChild = successorNode->rightChild;
        }
        successorNode->rightChild->parent = successorNode->parent;

        // Ahora conectamos el hijo derecho del nodo a borrar con el sucesor.
        successorNode->rightChild = nodeToDelete->rightChild;
        nodeToDelete->rightChild->parent = successorNode;

        // Actualizamos el padre del sucesor y su conexión.
        successorNode->parent = nodeToDelete->parent;
        if (nodeToDelete->parent->leftChild == nodeToDelete) // ¿Nodo a borrar es hijo izquierdo?
        {
            nodeToDelete->parent->leftChild = successorNode;
        }
        else
        {
            nodeToDelete->parent->rightChild = successorNode;
        }

        count--;
        delete nodeToDelete;
    }

private:
    // Funciones privadas para encontrar máximos y mínimos desde un nodo dado.

    TreeNode<T>* TreeMaximum()
    {
        return Maximum(root);
    }

    TreeNode<T>* Maximum(TreeNode<T>* node)
    {
        TreeNode<T>* maximum = node;
        while (maximum->rightChild != nullptr)
            maximum = maximum->rightChild;

        return maximum;
    }

    TreeNode<T>* TreeMinimum()
    {
        return Minimum(root);
    }

    TreeNode<T>* Minimum(TreeNode<T>* node)
    {
        TreeNode<T>* minimum = node;
        while (minimum->leftChild != nullptr)
            minimum = minimum->leftChild;

        return minimum;
    }

    TreeNode<T>* MinimumWithRecursive()
    {
        return MinimumRecursive(root);
    }

    TreeNode<T>* MinimumRecursive(TreeNode<T>* currentNode)
    {
        if (currentNode->leftChild == nullptr)
            return currentNode;
        return MinimumRecursive(currentNode->leftChild);
    }

    // Función que encuentra el sucesor en orden del nodo dado.
    TreeNode<T>* Successor(TreeNode<T>* node)
    {
        if (node->rightChild != nullptr)
            return Minimum(node->rightChild);

        TreeNode<T>* ancestor = node->parent;
        while (ancestor != nullptr && node == ancestor->rightChild)
        {
            node = ancestor;
            ancestor = node->parent;
        }
        return ancestor;
    }

    // Función que encuentra el predecesor en orden del nodo dado.
    TreeNode<T>* Predecessor(TreeNode<T>* node)
    {
        if (node->leftChild != nullptr)
            return Maximum(node->leftChild);

        TreeNode<T>* ancestor = node->parent;
        while (ancestor != nullptr && node == ancestor->leftChild)
        {
            node = ancestor;
            ancestor = node->parent;
        }
        return ancestor;
    }

    // Función recursiva para buscar un nodo con cierto valor.
    TreeNode<T>* SearchRecursive(TreeNode<T>* currentNode, T value)
    {
        if (currentNode == nullptr)
            return nullptr;
        if (currentNode->data == value)
            return currentNode;
        if (value < currentNode->data)
            return SearchRecursive(currentNode->leftChild, value);
        return SearchRecursive(currentNode->rightChild, value);
    }

    // Recorrido inorden recursivo (izquierda, nodo, derecha).
    void InOrderRecursive(TreeNode<T>* node)
    {
        if (node != nullptr)
        {
            InOrderRecursive(node->leftChild);
            cout << node->data << endl;
            InOrderRecursive(node->rightChild);
        }
    }

    // Recorrido preorden recursivo (nodo, izquierda, derecha).
    void PreOrderRecursive(TreeNode<T>* node)
    {
        if (node != nullptr)
        {
            cout << node->data << endl;
            PreOrderRecursive(node->leftChild);
            PreOrderRecursive(node->rightChild);
        }
    }

    // Recorrido postorden recursivo (izquierda, derecha, nodo).
    void PostOrderRecursive(TreeNode<T>* node)
    {
        if (node != nullptr)
        {
            PostOrderRecursive(node->leftChild);
            PostOrderRecursive(node->rightChild);
            cout << node->data << endl;
        }
    }
};

/*
  NOTA: Este código comentado abajo era para probar que la función Successor funcionara.

  T SuccessorValue(T value)
  {
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

