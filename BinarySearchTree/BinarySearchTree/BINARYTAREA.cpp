// File: main.cpp
#include <iostream>
#include "BinarySearchTree.h"""
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
