#pragma once

#include <iostream>
#include <cmath>
#include <stack>

using namespace std;

// Función para calcular logaritmo en cualquier base, porque C++ es así y no lo trae fácil :(
// Literalmente es logaritmo natural de x dividido entre logaritmo natural de la base.
double log_base_n(double x, double base);

// Esta cosa devuelve la altura mínima que podría tener un árbol con X nodos y Y hijos por nodo.
// Básicamente para comparar si tu árbol está balanceado o es un caos.
int MinimaAlturaDeArbol(int numeroDeNodos, int maximoDeHijosPorNodo);

template <typename T>
class BinarySearchTree
{
    // Clase interna para los nodos del árbol.
    // Cada nodo guarda un dato, y tiene punteros a su papá, hijo izquierdo y derecho.
    class TreeNode
    {
    public:
        TreeNode() : data(T()), parent(nullptr), leftChild(nullptr), rightChild(nullptr) {}
        TreeNode(const T& value) : data(value), parent(nullptr), leftChild(nullptr), rightChild(nullptr) {}

        T data;
        TreeNode* parent;
        TreeNode* leftChild;
        TreeNode* rightChild;
    };

public:
    // Constructor bonito: empieza sin raíz y sin nodos.
    BinarySearchTree() : root(nullptr), count(0) {}

    // Destructor dramático: borra TODO el subárbol y deja todo en nullptr.
    ~BinarySearchTree() { DeleteSubtree(root); root = nullptr; count = 0; }

    // Agrega un nodo usando recursividad porque... bueno, a veces la vida se complica.
    void AddWithAddRecursive(const T& value)
    {
        if (root == nullptr)
        {
            // Si el árbol está vacío, este será el nodo raíz y fin de la historia.
            root = new TreeNode(value);
            ++count;
            return;
        }
        AddRecursive(value, root);
    }

    // Crea un nodo nuevo y lo cuelga como hijo izq o der según diga.
    void InsertarNode(TreeNode* currentNode, bool isLeftChild, const T& value)
    {
        TreeNode* newNode = new TreeNode(value);
        newNode->parent = currentNode;
        if (isLeftChild)
            currentNode->leftChild = newNode;
        else
            currentNode->rightChild = newNode;
        ++count;
    }

    // Aquí la magia recursiva: decide si el valor va a la izq o a la der y sigue buscando hueco.
    void AddRecursive(const T& value, TreeNode* currentNode)
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
                AddRecursive(value, currentNode->rightChild);
                return;
            }
        }
        else
        {
            if (currentNode->leftChild == nullptr)
            {
                InsertarNode(currentNode, true, value);
                return;
            }
            else
            {
                AddRecursive(value, currentNode->leftChild);
                return;
            }
        }
    }

    // Versión NO recursiva, porque a veces da miedo (muchi) el stack overflow :’)
    void Add(const T& value)
    {
        if (root == nullptr)
        {
            root = new TreeNode(value);
            ++count;
            return;
        }

        TreeNode* currentNode = root;
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
            else
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
        }
    }

    // Recorre el árbol en orden, que es como ordenar de menor a mayor.
    void InOrderWithRecursive()
    {
        InOrderRecursive(root);
    }

    // Recorre el árbol en postorden, o sea primero hijos, luego el papá.
    void PostOrderWithRecursive()
    {
        PostOrderRecursive(root);
    }

    // Versión iterativa del postorden (porque recursivo es demasiado mainstream).
    void PostOrderIterative()
    {
        if (root == nullptr)
        {
            cout << "Árbol vacío, nada que imprimir" << endl;
            return;
        }

        stack<TreeNode*> nodeStack;
        TreeNode* current = root;
        TreeNode* lastVisited = nullptr;

        while (!nodeStack.empty() || current != nullptr)
        {
            if (current != nullptr)
            {
                nodeStack.push(current);
                current = current->leftChild;
            }
            else
            {
                TreeNode* peekNode = nodeStack.top();
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

    // Devuelve la altura mínima posible del árbol actual (si fuera perfectamente balanceado, cosa que no pasa en la vida real).
    int MinimaAltura()
    {
        return MinimaAlturaDeArbol(count, 2);
    }

    // Busca recursivamente un valor (porque a veces sí quieres recursividad).
    bool SearchWithRecursive(const T& value)
    {
        TreeNode* resultNode = SearchRecursive(root, value);
        return (resultNode != nullptr);
    }

    // Busca de manera iterativa, como escaneando un cuarto a ojo.
    bool Search(const T& value)
    {
        TreeNode* currentNode = root;
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

    // Borra un nodo del árbol con todos los casos posibles. Spoiler: es un drama.
    void Delete(const T& value)
    {
        TreeNode* nodeToDelete = SearchRecursive(root, value);
        if (nodeToDelete == nullptr)
        {
            cout << "no existe el valor " << value << " en este árbol." << endl;
            return;
        }

        // Caso 1: nodo hoja (sin hijos).
        if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild == nullptr)
        {
            if (nodeToDelete->parent == nullptr)
                root = nullptr;
            else if (nodeToDelete->parent->leftChild == nodeToDelete)
                nodeToDelete->parent->leftChild = nullptr;
            else
                nodeToDelete->parent->rightChild = nullptr;

            delete nodeToDelete;
            --count;
            return;
        }

        // Caso 2: solo hijo derecho.
        if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild != nullptr)
        {
            TreeNode* child = nodeToDelete->rightChild;
            if (nodeToDelete->parent == nullptr)
                root = child;
            else if (nodeToDelete->parent->leftChild == nodeToDelete)
                nodeToDelete->parent->leftChild = child;
            else
                nodeToDelete->parent->rightChild = child;

            child->parent = nodeToDelete->parent;
            delete nodeToDelete;
            --count;
            return;
        }

        // Caso 3: solo hijo izquierdo.
        if (nodeToDelete->leftChild != nullptr && nodeToDelete->rightChild == nullptr)
        {
            TreeNode* child = nodeToDelete->leftChild;
            if (nodeToDelete->parent == nullptr)
                root = child;
            else if (nodeToDelete->parent->leftChild == nodeToDelete)
                nodeToDelete->parent->leftChild = child;
            else
                nodeToDelete->parent->rightChild = child;

            child->parent = nodeToDelete->parent;
            delete nodeToDelete;
            --count;
            return;
        }

        // Caso 4: tiene dos hijos (el más tedioso).
        TreeNode* successorNode = Minimum(nodeToDelete->rightChild);
        if (successorNode != nodeToDelete->rightChild)
        {
            if (successorNode->parent->leftChild == successorNode)
                successorNode->parent->leftChild = successorNode->rightChild;
            else
                successorNode->parent->rightChild = successorNode->rightChild;

            if (successorNode->rightChild)
                successorNode->rightChild->parent = successorNode->parent;

            successorNode->rightChild = nodeToDelete->rightChild;
            if (successorNode->rightChild)
                successorNode->rightChild->parent = successorNode;
        }

        successorNode->parent = nodeToDelete->parent;
        if (nodeToDelete->parent == nullptr)
            root = successorNode;
        else if (nodeToDelete->parent->leftChild == nodeToDelete)
            nodeToDelete->parent->leftChild = successorNode;
        else
            nodeToDelete->parent->rightChild = successorNode;

        successorNode->leftChild = nodeToDelete->leftChild;
        if (successorNode->leftChild)
            successorNode->leftChild->parent = successorNode;

        delete nodeToDelete;
        --count;
    }

    TreeNode* root;
    int count;

private:
    // Busca el nodo más a la izquierda (mínimo valor) desde un nodo dado.
    TreeNode* Minimum(TreeNode* node)
    {
        TreeNode* minimum = node;
        while (minimum->leftChild != nullptr)
            minimum = minimum->leftChild;
        return minimum;
    }

    // Busca recursivamente (como Google pero más lento).
    TreeNode* SearchRecursive(TreeNode* currentNode, const T& value)
    {
        if (currentNode == nullptr)
            return nullptr;
        if (currentNode->data == value)
            return currentNode;
        if (value < currentNode->data)
            return SearchRecursive(currentNode->leftChild, value);
        return SearchRecursive(currentNode->rightChild, value);
    }

    // Inorder recursivo: izquierda -> nodo -> derecha.
    void InOrderRecursive(TreeNode* node)
    {
        if (node != nullptr)
        {
            InOrderRecursive(node->leftChild);
            cout << node->data << endl;
            InOrderRecursive(node->rightChild);
        }
    }

    // Postorder recursivo: hijos primero, papá después.
    void PostOrderRecursive(TreeNode* node)
    {
        if (node != nullptr)
        {
            PostOrderRecursive(node->leftChild);
            PostOrderRecursive(node->rightChild);
            cout << node->data << endl;
        }
    }

    // Borra todo el subárbol desde un nodo (modo apocalipsis).
    void DeleteSubtree(TreeNode* node)
    {
        if (node == nullptr) return;
        DeleteSubtree(node->leftChild);
        DeleteSubtree(node->rightChild);
        delete node;
    }
};
