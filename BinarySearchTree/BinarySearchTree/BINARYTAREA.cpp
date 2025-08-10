// File: BinarySearchTree.h
#pragma once

#include <iostream>
#include <cmath>
#include <stack>

using namespace std;

// Funciones auxiliares para calcular la altura mínima (definidas en BinarySearchTree.cpp)
double log_base_n(double x, double base);
int MinimaAlturaDeArbol(int numeroDeNodos, int maximoDeHijosPorNodo);

template <typename T>
class BinarySearchTree
{
    // Nodo interno (usa el mismo T del árbol — NO es otra plantilla)
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
    BinarySearchTree() : root(nullptr), count(0) {}

    // Destructor que libera todos los nodos
    ~BinarySearchTree() { DeleteSubtree(root); root = nullptr; count = 0; }

    // Inserción recursiva (si el árbol está vacío crea la raíz)
    void AddWithAddRecursive(const T& value)
    {
        if (root == nullptr)
        {
            root = new TreeNode(value);
            ++count;
            return;
        }
        AddRecursive(value, root);
    }

    // Crea e inserta un nuevo nodo (isLeftChild = true => hijo izquierdo)
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

    // NOTA IMPORTANTE: los duplicados SE ACEPTAN y se envían a la izquierda.
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
            // value <= currentNode->data  => vamos a la izquierda (duplicados a la izquierda)
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

    // Inserción iterativa (doble comportamiento para duplicados: <= va a la izquierda)
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
                // value <= currentNode->data => duplicado o menor: a la izquierda
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

    // Recorrido in-order recursivo
    void InOrderWithRecursive()
    {
        InOrderRecursive(root);
    }

    // Altura mínima (asume árbol binario: max 2 hijos)
    int MinimaAltura()
    {
        return MinimaAlturaDeArbol(count, 2);
    }

    // Miembros públicos (por compatibilidad con tu código previo)
    TreeNode* root;
    int count;

    // Búsqueda recursiva
    bool SearchWithRecursive(const T& value)
    {
        TreeNode* resultNode = SearchRecursive(root, value);
        return (resultNode != nullptr);
    }

    // Búsqueda iterativa
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

    // Eliminación de un valor (maneja correctamente raíz, hijos nulos, y successor)
    void Delete(const T& value)
    {
        TreeNode* nodeToDelete = SearchRecursive(root, value);

        if (nodeToDelete == nullptr)
        {
            cout << "no existe el valor " << value << " en este árbol." << endl;
            return;
        }

        // Caso 1: sin hijos (hoja)
        if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild == nullptr)
        {
            if (nodeToDelete->parent == nullptr)
            {
                // Eliminando la raíz que además es hoja
                root = nullptr;
            }
            else if (nodeToDelete->parent->leftChild == nodeToDelete)
            {
                nodeToDelete->parent->leftChild = nullptr;
            }
            else
            {
                nodeToDelete->parent->rightChild = nullptr;
            }

            delete nodeToDelete;
            --count;
            return;
        }

        // Caso 2: solo hijo derecho
        if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild != nullptr)
        {
            TreeNode* child = nodeToDelete->rightChild;

            if (nodeToDelete->parent == nullptr)
            {
                // nodeToDelete era la raíz
                root = child;
            }
            else if (nodeToDelete->parent->leftChild == nodeToDelete)
            {
                nodeToDelete->parent->leftChild = child;
            }
            else
            {
                nodeToDelete->parent->rightChild = child;
            }

            child->parent = nodeToDelete->parent;
            delete nodeToDelete;
            --count;
            return;
        }

        // Caso 2b: solo hijo izquierdo
        if (nodeToDelete->leftChild != nullptr && nodeToDelete->rightChild == nullptr)
        {
            TreeNode* child = nodeToDelete->leftChild;

            if (nodeToDelete->parent == nullptr)
            {
                root = child;
            }
            else if (nodeToDelete->parent->leftChild == nodeToDelete)
            {
                nodeToDelete->parent->leftChild = child;
            }
            else
            {
                nodeToDelete->parent->rightChild = child;
            }

            child->parent = nodeToDelete->parent;
            delete nodeToDelete;
            --count;
            return;
        }

        // Caso 3: dos hijos -> buscamos successor (mínimo del subárbol derecho)
        TreeNode* successorNode = Minimum(nodeToDelete->rightChild);

        if (successorNode != nodeToDelete->rightChild)
        {
            // Desenganchar al successor de su posición actual y sustituirlo por su hijo derecho (si existe)
            if (successorNode->parent->leftChild == successorNode)
                successorNode->parent->leftChild = successorNode->rightChild;
            else
                successorNode->parent->rightChild = successorNode->rightChild;

            if (successorNode->rightChild)
                successorNode->rightChild->parent = successorNode->parent;

            // Colocar el subárbol derecho del nodeToDelete bajo el successor
            successorNode->rightChild = nodeToDelete->rightChild;
            if (successorNode->rightChild)
                successorNode->rightChild->parent = successorNode;
        }

        // Reemplazar nodeToDelete por successorNode en su padre (o en root)
        successorNode->parent = nodeToDelete->parent;
        if (nodeToDelete->parent == nullptr)
        {
            root = successorNode;
        }
        else if (nodeToDelete->parent->leftChild == nodeToDelete)
        {
            nodeToDelete->parent->leftChild = successorNode;
        }
        else
        {
            nodeToDelete->parent->rightChild = successorNode;
        }

        // Colocar el subárbol izquierdo del nodeToDelete bajo el successor
        successorNode->leftChild = nodeToDelete->leftChild;
        if (successorNode->leftChild)
            successorNode->leftChild->parent = successorNode;

        delete nodeToDelete;
        --count;
    }

    // Recorrido post-order iterativo con comentarios extensos
    void PostOrderIterative()
    {
        if (root == nullptr)
        {
            cout << "Árbol vacío, nada que imprimir" << endl;
            return;
        }

        /* 
Usamos una única pila y el puntero lastVisited.vBajamos por la izquierda siempre que podamos (push).
Cuando no podemos bajar (current == nullptr), inspeccionamos el tope.Si el tope tiene un hijo derecho que no ha sido visitado, nos movemos a ese hijo derecho (current = peek->rightChild) y seguimos.
Si no tiene hijo derecho o ya fue visitado, entonces imprimimos el y lo sacamos de la pila; lo marcamos como lastVisited, y este nos ayuda a saber si el subárbol derecho ya fue al volver al ancestro. */

        stack<TreeNode*> nodeStack;
        TreeNode* current = root;
        TreeNode* lastVisited = nullptr;

        while (!nodeStack.empty() || current != nullptr)
        {
            if (current != nullptr)
            {
                // Empujamos por la izquierda
                nodeStack.push(current);
                current = current->leftChild;
            }
            else
            {
                TreeNode* peekNode = nodeStack.top();

                // Si hay subárbol derecho y no lo hemos visitado aún, explorarlo
                if (peekNode->rightChild != nullptr && lastVisited != peekNode->rightChild)
                {
                    current = peekNode->rightChild; // recorrer el subárbol derecho ahora
                }
                else
                {
                    // No hay subárbol derecho o ya fue visitado -> visitar el nodo
                    cout << peekNode->data << endl;
                    lastVisited = peekNode;
                    nodeStack.pop();
                }
            }
        }
    }

private:
    // Funciones auxiliares para máximo/mínimo
    TreeNode* TreeMaximum() { return Maximum(root); }

    TreeNode* Maximum(TreeNode* node)
    {
        TreeNode* maximum = node;
        while (maximum->rightChild != nullptr)
            maximum = maximum->rightChild;

        return maximum;
    }

    TreeNode* TreeMinimum() { return Minimum(root); }

    TreeNode* Minimum(TreeNode* node)
    {
        TreeNode* minimum = node;
        while (minimum->leftChild != nullptr)
            minimum = minimum->leftChild;

        return minimum;
    }

    TreeNode* MinimumWithRecursive() { return MinimumRecursive(root); }

    TreeNode* MinimumRecursive(TreeNode* currentNode)
    {
        if (currentNode->leftChild == nullptr)
            return currentNode;
        return MinimumRecursive(currentNode->leftChild);
    }

    TreeNode* Successor(TreeNode* node)
    {
        if (node->rightChild != nullptr)
            return Minimum(node->rightChild);

        TreeNode* ancestor = node->parent;
        while (ancestor != nullptr && node == ancestor->rightChild)
        {
            node = ancestor;
            ancestor = node->parent;
        }
        return ancestor;
    }

    TreeNode* Predecessor(TreeNode* node)
    {
        if (node->leftChild != nullptr)
            return Maximum(node->leftChild);

        TreeNode* ancestor = node->parent;
        while (ancestor != nullptr && node == ancestor->leftChild)
        {
            node = ancestor;
            ancestor = node->parent;
        }
        return ancestor;
    }

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

    void InOrderRecursive(TreeNode* node)
    {
        if (node != nullptr)
        {
            InOrderRecursive(node->leftChild);
            cout << node->data << endl;
            InOrderRecursive(node->rightChild);
        }
    }

    void PreOrderRecursive(TreeNode* node)
    {
        if (node != nullptr)
        {
            cout << node->data << endl;
            PreOrderRecursive(node->leftChild);
            PreOrderRecursive(node->rightChild);
        }
    }

    void PostOrderRecursive(TreeNode* node)
    {
        if (node != nullptr)
        {
            PostOrderRecursive(node->leftChild);
            PostOrderRecursive(node->rightChild);
            cout << node->data << endl;
        }
    }

    // Borra recursivamente un subárbol (usado en el destructor)
    void DeleteSubtree(TreeNode* node)
    {
        if (node == nullptr)
            return;
        DeleteSubtree(node->leftChild);
        DeleteSubtree(node->rightChild);
        delete node;
    }
};


// File: BinarySearchTree.cpp
#include <cmath>

// Función para calcular logaritmo en base n, que nos ayuda con la altura mínima del árbol.
double log_base_n(double x, double base)
{
    return std::log(x) / std::log(base);
}

// Calcula la altura mínima de un árbol con cierto número de nodos y máximo de hijos por nodo.
int MinimaAlturaDeArbol(int numeroDeNodos, int maximoDeHijosPorNodo)
{
    if (numeroDeNodos <= 0) return 0;
    int maximoDeHijosMenos1PorNumeroDeNodosMasUno = ((maximoDeHijosPorNodo - 1) * numeroDeNodos + 1);
    int altura = static_cast<int>(std::ceil(log_base_n(maximoDeHijosMenos1PorNumeroDeNodosMasUno, maximoDeHijosPorNodo))) - 1;
    return altura;
}


// File: main.cpp
#include <iostream>

using namespace std;

int main()
{
    BinarySearchTree<int> tree;

    cout << "Insertando: 7, 3, 9, 3, 5, 9, 1, 8, 10 (duplicados deberían ir a la izquierda)" << endl;
    int vals[] = { 7, 3, 9, 3, 5, 9, 1, 8, 10 };
    for (int v : vals) tree.Add(v);

    cout << "\nInOrder (debe imprimirse orden ascendente — duplicados a la izquierda):" << endl;
    tree.InOrderWithRecursive();

    cout << "\nPostOrder iterativo (comentado dentro del método):" << endl;
    tree.PostOrderIterative();

    cout << "\nBuscar 5: " << (tree.Search(5) ? "encontrado" : "no encontrado") << endl;
    cout << "Buscar 11: " << (tree.Search(11) ? "encontrado" : "no encontrado") << endl;

    cout << "\nEliminar hoja (1)" << endl;
    tree.Delete(1);
    cout << "InOrder luego de eliminar 1:" << endl;
    tree.InOrderWithRecursive();

    cout << "\nEliminar nodo con un hijo (9) - eliminará el primer 9 encontrado" << endl;
    tree.Delete(9);
    cout << "InOrder luego de eliminar 9:" << endl;
    tree.InOrderWithRecursive();

    cout << "\nEliminar nodo con dos hijos (7 - la raíz)" << endl;
    tree.Delete(7);
    cout << "InOrder luego de eliminar 7:" << endl;
    tree.InOrderWithRecursive();

    cout << "\nAltura mínima (árbol binario): " << tree.MinimaAltura() << endl;

    cout << "\nIntentar eliminar un valor que no existe (999):" << endl;
    tree.Delete(999);

    cout << "\nFin del main — el destructor del árbol liberará la memoria." << endl;

    return 0;
}
