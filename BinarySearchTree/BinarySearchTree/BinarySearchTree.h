#pragma once

#include <iostream>
#include <cmath>
#include <stack>

using namespace std;

double log_base_n(double x, double base);
int MinimaAlturaDeArbol(int numeroDeNodos, int maximoDeHijosPorNodo);

template <typename T>
class BinarySearchTree
{
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
    ~BinarySearchTree() { DeleteSubtree(root); root = nullptr; count = 0; }

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

    void InOrderWithRecursive()
    {
        InOrderRecursive(root);
    }

    // NUEVO: PostOrder recursivo público
    void PostOrderWithRecursive()
    {
        PostOrderRecursive(root);
    }

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

    int MinimaAltura()
    {
        return MinimaAlturaDeArbol(count, 2);
    }

    bool SearchWithRecursive(const T& value)
    {
        TreeNode* resultNode = SearchRecursive(root, value);
        return (resultNode != nullptr);
    }

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

    void Delete(const T& value)
    {
        TreeNode* nodeToDelete = SearchRecursive(root, value);
        if (nodeToDelete == nullptr)
        {
            cout << "no existe el valor " << value << " en este árbol." << endl;
            return;
        }

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
    TreeNode* Minimum(TreeNode* node)
    {
        TreeNode* minimum = node;
        while (minimum->leftChild != nullptr)
            minimum = minimum->leftChild;
        return minimum;
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

    void PostOrderRecursive(TreeNode* node)
    {
        if (node != nullptr)
        {
            PostOrderRecursive(node->leftChild);
            PostOrderRecursive(node->rightChild);
            cout << node->data << endl;
        }
    }

    void DeleteSubtree(TreeNode* node)
    {
        if (node == nullptr) return;
        DeleteSubtree(node->leftChild);
        DeleteSubtree(node->rightChild);
        delete node;
    }
};
