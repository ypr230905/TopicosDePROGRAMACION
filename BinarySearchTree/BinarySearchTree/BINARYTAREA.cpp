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
#include <cmath> // Necesario para std::log
#include <stack> // Para el recorrido post-order iterativo

using namespace std;

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
            this->data = data;
        }

        T data;  // Valor guardado en el nodo.

        TreeNode<T>* parent;     // Puntero al nodo padre.
        TreeNode<T>* leftChild;  // Puntero al hijo izquierdo.
        TreeNode<T>* rightChild; // Puntero al hijo derecho.
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
        if (root == nullptr)
        {
            root = new TreeNode<T>(value);
            count++;
            return;
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

    void AddRecursive(T value, TreeNode<T>* currentNode)
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
                return AddRecursive(value, currentNode->rightChild);
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
                return AddRecursive(value, currentNode->leftChild);
            }
        }
        else
        {
            // Valor duplicado, no se añade.
            return;
        }
    }

    // Añade un valor de forma iterativa.
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
                // Valor duplicado, no se añade.
                return;
            }
        }
    }

    // Recorrido inorden recursivo.
    void InOrderWithRecursive()
    {
        InOrderRecursive(root);
    }

    // Calcula la altura mínima del árbol.
    int MinimaAltura()
    {
        return MinimaAlturaDeArbol(count, 2);
    }

    // Nodo raíz del árbol.
    TreeNode<T>* root;

    // Conteo de nodos.
    int count;

    // Búsqueda recursiva.
    bool SearchWithRecursive(T value)
    {
        TreeNode<T>* resultNode = SearchRecursive(root, value);
        if (resultNode == nullptr)
            return false;
        return true;
    }

    // Búsqueda iterativa.
    bool Search(T value)
    {
        TreeNode<T>* currentNode = root;

        while (currentNode != nullptr)
        {
            if (currentNode->data == value)
            {
                return true;
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

        return false;
    }

    // Eliminación de nodo.
    void Delete(T value)
    {
        TreeNode<T>* nodeToDelete = SearchRecursive(root, value);

        if (nodeToDelete == nullptr)
        {
            cout << "no existe el valor " << value << " en este árbol." << endl;
            return;
        }

        // Caso 1: sin hijos.
        if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild == nullptr)
        {
            if (nodeToDelete->parent->leftChild == nodeToDelete)
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

        // Caso 2: un solo hijo derecho.
        if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild != nullptr)
        {
            if (nodeToDelete->parent->leftChild == nodeToDelete)
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
        // Caso 2: un solo hijo izquierdo.
        else if (nodeToDelete->leftChild != nullptr && nodeToDelete->rightChild == nullptr)
        {
            if (nodeToDelete->parent->leftChild == nodeToDelete)
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

        // Caso 3: dos hijos.
        TreeNode<T>* successorNode = Successor(nodeToDelete);

        successorNode->leftChild = nodeToDelete->leftChild;
        nodeToDelete->leftChild->parent = successorNode;

        if (successorNode->parent->leftChild == successorNode)
        {
            successorNode->parent->leftChild = successorNode->rightChild;
        }
        else
        {
            successorNode->parent->rightChild = successorNode->rightChild;
        }
        successorNode->rightChild->parent = successorNode->parent;

        successorNode->rightChild = nodeToDelete->rightChild;
        nodeToDelete->rightChild->parent = successorNode;

        successorNode->parent = nodeToDelete->parent;
        if (nodeToDelete->parent->leftChild == nodeToDelete)
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

    // Recorrido post-order ITERATIVO
    void PostOrderIterative()
    {
        if (root == nullptr)
        {
            cout << "Árbol vacío, nada que imprimir" << endl;
            return;
        }

        stack<TreeNode<T>*> nodeStack;
        TreeNode<T>* current = root;
        TreeNode<T>* lastVisited = nullptr;

        while (!nodeStack.empty() || current != nullptr)
        {
            if (current != nullptr)
            {
                nodeStack.push(current);
                current = current->leftChild;
            }
            else
            {
                TreeNode<T>* peekNode = nodeStack.top();
                if (peekNode->rightChild != nullptr && lastVisited != peekNode->rightChild)
                {
                    current = peekNode->rightChild;
                }
                else
                {
                    cout << peekNode->data << endl;
                    lastVisited = peekNode;
                    nodeStack.pop();
                }
            }
        }
    }

private:
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

    void InOrderRecursive(TreeNode<T>* node)
    {
        if (node != nullptr)
        {
            InOrderRecursive(node->leftChild);
            cout << node->data << endl;
            InOrderRecursive(node->rightChild);
        }
    }

    void PreOrderRecursive(TreeNode<T>* node)
    {
        if (node != nullptr)
        {
            cout << node->data << endl;
            PreOrderRecursive(node->leftChild);
            PreOrderRecursive(node->rightChild);
        }
    }

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

