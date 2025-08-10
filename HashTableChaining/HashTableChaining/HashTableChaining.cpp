#include <iostream>
#include <forward_list>
#include <string>
#include <stdexcept>
using namespace std;

// Clase base para Hash Table con encadenamiento separado (chaining)
template <typename T>
class HashTableChaining
{
protected:
    forward_list<T>* data;   // Array dinámico de listas enlazadas para manejar colisiones
    unsigned int arraySize;  // Tamaño del array

public:
    // Constructor pide tamaño del array y crea las listas vacías
    HashTableChaining(unsigned int size)
    {
        data = new forward_list<T>[size];
        arraySize = size;
    }

    // Destructor libera la memoria del array de listas
    virtual ~HashTableChaining()
    {
        delete[] data;
    }

    // Función hash básica: módulo del tamaño del array (se puede mejorar)
    virtual int HashFunction(T key)
    {
        return key % arraySize;
    }

    // Método para agregar elementos sin control de repetidos
    virtual void Add(T element)
    {
        int index = HashFunction(element);
        data[index].push_front(element); // Inserta al inicio para eficiencia O(1)
    }

    // Método para eliminar elemento, lanza excepción si no existe
    void Remove(T element) // ← ya no es virtual
    {
        int index = HashFunction(element);
        forward_list<T>& listAtIndex = data[index];

        for (auto i : listAtIndex)
        {
            if (i == element)
            {
                listAtIndex.remove(i);  // Borra el primer elemento igual a 'element'
                return;
            }
        }
        // Si no encontró el elemento, lanza error para avisar que no está
        throw runtime_error("No se encontró el elemento " + to_string(element) + " en la tabla hash.");
    }

    // Método para checar si un elemento está en la tabla hash
    bool Contains(T element) // ← ya no es virtual
    {
        int index = HashFunction(element);
        forward_list<T>& listAtIndex = data[index];

        for (auto i : listAtIndex)
        {
            if (i == element)
                return true;  // Si lo encontró, devuelve true
        }
        return false; // Si recorrió todo y no encontró, devuelve false
    }

    // Método para imprimir el contenido de cada lista en cada índice
    void Print()
    {
        for (int i = 0; i < arraySize; i++)
        {
            cout << "Lista índice " << i << ": ";
            for (auto j : data[i])
                cout << j << ", ";
            cout << endl;
        }
    }
};

// Clase HashSet que hereda de HashTableChaining
// Aquí sí controlamos que NO se puedan agregar elementos repetidos
template <typename T>
class HashSet : public HashTableChaining<T>
{
public:
    // Constructor simplemente llama al padre para inicializar
    HashSet(unsigned int size) : HashTableChaining<T>(size) {}

    // Sobrescribimos Add para evitar duplicados
    void Add(T element) override
    {
        // Solo agrega si el elemento NO está ya en el HashSet
        if (!this->Contains(element))
        {
            int index = this->HashFunction(element);
            this->data[index].push_front(element); // Insertar al inicio de la lista
        }
        else
        {
            // Opcional: podrías mostrar un mensaje o simplemente ignorar
            // cout << "Elemento " << element << " ya existe en el HashSet." << endl;
        }
    }

    // Remove y Contains se heredan tal cual del padre, no hace falta cambiarlos
};

// Función para probar que la clase HashSet funcione correctamente
void HashSetExample()
{
    HashSet<int> myHashSet(10);

    cout << "Agregando 5, 10 y 5 de nuevo (no debe duplicar el 5)" << endl;
    myHashSet.Add(5);
    myHashSet.Add(10);
    myHashSet.Add(5); // Este no debe agregarse porque ya existe

    myHashSet.Print();

    cout << "¿Contiene 5? " << (myHashSet.Contains(5) ? "Sí" : "No") << endl;
    cout << "¿Contiene 7? " << (myHashSet.Contains(7) ? "Sí" : "No") << endl;

    cout << "Quitando el elemento 5..." << endl;
    myHashSet.Remove(5);
    myHashSet.Print();

    cout << "Intentando quitar 5 de nuevo (debe lanzar excepción porque ya no está)" << endl;
    try
    {
        myHashSet.Remove(5);
    }
    catch (const runtime_error& e)
    {
        cout << "Error capturado: " << e.what() << endl;
    }
}

int main()
{
    HashSetExample();  // Ejecutamos la prueba
    return 0;
}
