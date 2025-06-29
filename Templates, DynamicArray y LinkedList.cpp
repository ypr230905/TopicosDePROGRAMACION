// YUNUEN PORTES RAMÍREZ

#include <iostream>
#include <string> // para usar strings en la lista
using namespace std;

// FUNCIONES TEMPLATE

// esta función imprime cualquier tipo de arreglo (int, string, float, etc.)
template <typename T>
void PrintArray(T arr[], int size)
{
    for (int i = 0; i < size; i++) // recorre el arreglo
    {
        cout << arr[i] << " "; // imprime cada elemento seguido de un espacio
    }
    cout << endl; // salto de línea al final
}

// DIRECTIVA DE PREPROCESADOR
#define COUNT_DYNAMIC_ARRAY_COPIES 1 // activa el contador de copias (1 = sí, 0 = no)

// CLASE DYNAMICARRAY
template <typename T>
class DynamicArray
{
private:
    T* data;      // puntero al arreglo dinámico
    int count;    // cuántos elementos hay
    int capacity; // cuánto espacio tenemos reservado

#if COUNT_DYNAMIC_ARRAY_COPIES
    int copyCounter; // cuenta cuántas copias se han hecho en los resize
#endif

    void resize(int newCapacity)
    {
        T* newData = new T[newCapacity]; // se pide nuevo arreglo

        for (int i = 0; i < count; i++) // se copian los datos al nuevo
        {
            newData[i] = data[i]; // se copian los valores
#if COUNT_DYNAMIC_ARRAY_COPIES
            copyCounter++; // solo cuenta si está activado el define
#endif
        }

        delete[] data;  // se libera el viejo
        data = newData; // apuntamos al nuevo
        capacity = newCapacity; // actualizamos el tamaño
    }

public:
    // constructor
    DynamicArray()
    {
        capacity = 2; // espacio inicial
        data = new T[capacity]; // reservamos memoria
        count = 0; // sin elementos todavía
#if COUNT_DYNAMIC_ARRAY_COPIES
        copyCounter = 0; // inicia en cero
#endif
    }

    void Append(T value)
    {
        // agrega un valor al final
        if (count == capacity) // si ya no cabe más
        {
            resize(capacity * 2); // duplicamos el espacio
        }
        data[count] = value;
        count++; // aumenta el número de elementos
    }

    void push_back(T value)
    {
        Append(value); // igual que append
    }

    void pop_back()
    {
        if (count > 0)
        {
            count--; // simplemente se "olvida" el último
        }
    }

    void shrink_to_fit()
    {
        // recorta el arreglo al tamaño justo
        if (capacity != count)
        {
            resize(count);
        }
    }

    T& operator[](int index)
    {
        return data[index]; // permite usar corchetes []
    }

    int size()
    {
        return count; // cuántos elementos hay
    }

    void print()
    {
        for (int i = 0; i < count; i++)
        {
            cout << data[i] << " "; // imprime todos
        }
        cout << endl;
    }

#if COUNT_DYNAMIC_ARRAY_COPIES
    int getCopyCounter()
    {
        return copyCounter; // regresa el número de copias
    }
#endif

    ~DynamicArray()
    {
        delete[] data; // libera la memoria al final
    }
};

// CLASE LINKEDLIST
template <typename T>
class LinkedList
{
private:
    struct Node
    {
        T value;     // lo que guarda el nodo
        Node* next;  // a quién apunta
    };

    Node* head; // apunta al inicio de la lista

public:
    LinkedList()
    {
        head = nullptr; // al inicio está vacía
    }

    void push_front(T value)
    {
        // agrega al inicio
        Node* newNode = new Node; // se crea nuevo nodo
        newNode->value = value;   // se le asigna el valor
        newNode->next = head;     // apunta al que estaba antes
        head = newNode;           // ahora es el nuevo primero
    }

    T pop_front()
    {
        // saca y regresa el primer valor
        if (head != nullptr)
        {
            Node* temp = head;       // guardamos el nodo
            T val = temp->value;     // guardamos el valor que tenía
            head = head->next;       // avanzamos al siguiente
            delete temp;             // borramos el anterior
            return val;              // regresamos el valor eliminado
        }

        // si no hay nada, mandamos advertencia y regresamos valor por defecto
        cout << "Advertencia: la lista está vacía, no hay nada que eliminar." << endl;
        return T();
    }

    void imprimir()
    {
        // imprime los valores de la lista
        Node* current = head;
        while (current != nullptr)
        {
            cout << current->value << " ";
            current = current->next;
        }
        cout << endl;
    }

    void liberarMemoria()
    {
        // limpia toda la lista
        while (head != nullptr)
        {
            pop_front(); // borra uno por uno
        }
    }

    // RESPUESTA A 2.2
    // En la clase LinkedList **no falta liberar memoria** porque ya lo hacemos con la función liberarMemoria(),
    // que borra nodo por nodo usando pop_front() hasta que head queda en nullptr.
    // Mientras se llame esa función antes de terminar el programa, no hay fuga de memoria. 👍
};

// MAIN PRINCIPAL
int main()
{
    // PrintArray
    int numeros[] = {10, 20, 30, 40}; // arreglo normal
    PrintArray(numeros, 4);           // se imprime

    // DynamicArray en acción
    DynamicArray<int> miArreglo;
    miArreglo.Append(100);       // agrega 100
    miArreglo.push_back(200);    // agrega 200
    miArreglo.push_back(300);    // agrega 300
    miArreglo.print();           // imprime todo

    cout << "Primer elemento: " << miArreglo[0] << endl; // acceso con []

    miArreglo.pop_back(); // quita el último
    miArreglo.print();    // vuelve a imprimir

    miArreglo.shrink_to_fit(); // ajusta memoria al tamaño justo

#if COUNT_DYNAMIC_ARRAY_COPIES
    cout << "Copias realizadas en resize: " << miArreglo.getCopyCounter() << endl; // muestra cuántas veces se copió
#endif

    // LinkedList en acción
    LinkedList<string> lista;
    lista.push_front("mundo");
    lista.push_front("hola");
    lista.imprimir(); // imprime: hola mundo

    string eliminado = lista.pop_front(); // saca y guarda el que se quitó
    cout << "Se eliminó: " << eliminado << endl;
    lista.pop_front(); // elimina "mundo"
    lista.pop_front(); // intenta eliminar cuando ya está vacía
    lista.imprimir(); // muestra lo que queda (debería estar vacía)
    lista.liberarMemoria(); // limpia la lista

    return 0;
}
