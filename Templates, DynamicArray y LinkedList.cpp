// YUNUEN PORTES RAMÍREZ
#include <iostream> 
using namespace std;

// FUNCIONES TEMPLATE

// esta función imprime cualquier tipo de arreglo (int, string, float, etc.)
template <typename T>
void PrintArray(T arr[], int size)
{
    for (int i = 0; i < size; i++) // recorre todo el arreglo
    {
        cout << arr[i] << " "; // imprime cada elemento seguido de un espacio
    }
    cout << endl; // salto de línea al final
}

// DIRECTIVA DE PREPROCESADOR
#define COUNT_DYNAMIC_ARRAY_COPIES 1 // activa el contador de copias

// CLASE DYNAMICARRAY
template <typename T>
class DynamicArray
{
private:
    T* data;      // puntero al arreglo dinámico
    int count;    // cuántos elementos tenemos actualmente
    int capacity; // cuánto espacio total tenemos reservado

#if COUNT_DYNAMIC_ARRAY_COPIES
    int copyCounter; // contador de copias (solo si está activado arriba)
#endif

    void resize(int newCapacity)
    {
        // esta función se llama cuando ya no cabe más, o cuando shrink_to_fit lo pide
        T* newData = new T[newCapacity]; // se crea un nuevo arreglo con más (o menos) espacio

#if COUNT_DYNAMIC_ARRAY_COPIES
        for (int i = 0; i < count; i++)
        {
            newData[i] = data[i]; // se copian los datos al nuevo arreglo
            copyCounter++;        // se cuenta cada copia que se hace
        }
#else
        for (int i = 0; i < count; i++)
        {
            newData[i] = data[i]; // mismo proceso pero sin contar
        }
#endif

        delete[] data;     // se libera el arreglo viejo
        data = newData;    // ahora "data" apunta al nuevo arreglo
        capacity = newCapacity; // se actualiza el nuevo tamaño máximo
    }

public:
    // constructor que arranca con capacidad de 2 elementos
    DynamicArray()
    {
        capacity = 2;              // empezamos con 2 espacios
        data = new T[capacity];    // reservamos memoria para esos 2
        count = 0;                 // al inicio no hay elementos

#if COUNT_DYNAMIC_ARRAY_COPIES
        copyCounter = 0;           // el contador inicia en 0
#endif
    }

    void Append(T value)
    {
        // agrega un valor al final del arreglo
        if (count == capacity) // si ya está lleno...
        {
            resize(capacity * 2); // duplicamos el espacio
        }

        data[count] = value; // guardamos el valor al final
        count++;             // aumentamos el número de elementos
    }

    void push_back(T value)
    {
        // igual que append, solo por costumbre de vector
        Append(value);
    }

    void pop_back()
    {
        // elimina el último valor (solo lo descuenta)
        if (count > 0)
        {
            count--; // "olvida" el último elemento
        }
    }

    void shrink_to_fit()
    {
        // reduce el espacio al mínimo necesario
        if (capacity != count)
        {
            resize(count); // se ajusta exactamente a los elementos actuales
        }
    }

    T& operator[](int index)
    {
        // para poder usar corchetes como en los arreglos normales
        return data[index]; // regresa una referencia al elemento
    }

    int size()
    {
        return count; // cuántos elementos hay en total
    }

    void print()
    {
        // imprime todos los elementos que hay
        for (int i = 0; i < count; i++)
        {
            cout << data[i] << " "; // imprime uno por uno
        }
        cout << endl;
    }

#if COUNT_DYNAMIC_ARRAY_COPIES
    int getCopyCounter()
    {
        // regresa el total de copias que se hicieron
        return copyCounter;
    }
#endif

    ~DynamicArray()
    {
        delete[] data; // borra el arreglo cuando ya no se usa
    }
};

// CLASE LINKEDLIST
template <typename T>
class LinkedList
{
private:
    struct Node
    {
        T value;     // valor que guarda el nodo
        Node* next;  // apunta al siguiente nodo
    };

    Node* head; // inicio de la lista

public:
    LinkedList()
    {
        head = nullptr; // lista vacía al inicio
    }

    void push_front(T value)
    {
        // agrega al inicio de la lista
        Node* newNode = new Node; // se crea un nuevo nodo
        newNode->value = value;   // se le asigna el valor
        newNode->next = head;     // apunta al anterior primer nodo
        head = newNode;           // ahora el nuevo nodo es el primero
    }

    void pop_front()
    {
        // elimina el primer nodo (si hay alguno)
        if (head != nullptr)
        {
            Node* temp = head;    // se guarda el nodo actual
            head = head->next;    // se avanza al siguiente
            delete temp;          // se borra el anterior
        }
    }

    void 打印()
    {
        // imprime los valores de la lista (sí, está en chino)
        Node* current = head;
        while (current != nullptr)
        {
            cout << current->value << " "; // imprime cada nodo
            current = current->next;       // avanza al siguiente
        }
        cout << endl;
    }

    void liberarMemoria()
    {
        // borra todos los nodos de la lista
        while (head != nullptr)
        {
            pop_front(); // borra uno por uno desde el inicio
        }
    }
};

// MAIN
int main()
{
    // arreglo normal
    int numeros[] = { 10, 20, 30, 40 }; // arreglo de enteros
    PrintArray(numeros, 4);           // se imprime usando template

    // probando DynamicArray
    DynamicArray<int> miArreglo;      // se crea arreglo dinámico de int
    miArreglo.Append(100);            // agrega 100
    miArreglo.push_back(200);         // agrega 200
    miArreglo.push_back(300);         // agrega 300
    miArreglo.print();                // imprime todos: 100 200 300

    cout << "Primer elemento: " << miArreglo[0] << endl; // accede con []

    miArreglo.pop_back(); // quita el último (300)
    miArreglo.print();    // imprime otra vez: 100 200

    miArreglo.shrink_to_fit(); // recorta memoria para solo esos 2

#if COUNT_DYNAMIC_ARRAY_COPIES
    cout << "Copias realizadas en resize: " << miArreglo.getCopyCounter() << endl; // muestra cuántas veces se copió
#endif

    // probando LinkedList
    LinkedList<string> lista; // lista enlazada de strings
    lista.push_front("mundo"); // inserta "mundo" al inicio
    lista.push_front("hola");  // ahora "hola" queda antes de "mundo"
    lista.打印();              // imprime: hola mundo

    lista.pop_front(); // quita "hola"
    lista.打印();      // ahora solo: mundo

    lista.liberarMemoria(); // borra lo que quede por si acaso

    return 0;
}
