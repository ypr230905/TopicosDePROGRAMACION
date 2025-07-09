// YUNUEN PORTES RAMÍREZ

#pragma once
#include <iostream>
#include <forward_list>
#include <cmath>
using namespace std;

// 1) SentinelLinkedList
// Esta clase implementa una lista ligada con nodo centinela (head), que facilita operaciones como inserción y eliminación al frente.
template <typename T>
class SentinelLinkedList
{
private:
    struct Node
    {
        T value;      // dato que guarda el nodo
        Node* next;   // apuntador al siguiente nodo
    };

    Node* head; // nodo centinela (antes del primero real)
    Node* tail; // último nodo real
    int count;  // número de elementos en la lista

public:
    SentinelLinkedList()
    {
        head = new Node(); // se crea nodo centinela vacío
        tail = head;       // al inicio, tail también apunta al centinela
        count = 0;
    }

    void PushBack(T val)
    {
        Node* newNode = new Node{ val, nullptr }; // se crea nuevo nodo al final
        tail->next = newNode; // el último apunta al nuevo
        tail = newNode;       // tail se actualiza
        count++;
    }

    T PopBack()
    {
        if (count == 0)
        {
            cout << "Cuidado, estás haciendo pop back cuando la lista está vacía\n";
            return {};
        }

        Node* prev = head; // empezamos desde el nodo centinela
        while (prev->next != tail) // recorremos hasta llegar al penúltimo
        {
            prev = prev->next;
        }

        T val = tail->value; // guardamos el valor a eliminar
        delete tail;         // liberamos memoria del último nodo
        tail = prev;         // actualizamos tail al penúltimo
        tail->next = nullptr; // aseguramos que tail no apunta a basura
        count--;
        return val; // regresamos el valor que se eliminó
    }

    void PushFront(T val)
    {
        Node* newNode = new Node{ val, head->next }; // se inserta justo después del centinela
        head->next = newNode;
        if (count == 0) tail = newNode; // si es el primer nodo real, actualizamos tail
        count++;
    }

    T PopFront()
    {
        if (count == 0)
        {
            cout << "Advertencia: la lista está vacía, no se puede hacer PopFront\n";
            return {};
        }

        Node* first = head->next; // tomamos el primero real
        T val = first->value;     // guardamos el valor
        head->next = first->next; // el centinela apunta al siguiente
        if (first == tail) tail = head; // si era el único, tail regresa al centinela
        delete first; // liberamos el nodo eliminado
        count--;
        return val; // regresamos el valor
    }

    int GetCount() { return count; } // regresa cuántos elementos hay

    T Front()
    {
        if (count == 0)
        {
            cout << "Advertencia, la lista está vacía, no hay Front\n";
            return {};
        }
        return head->next->value; // regresa el valor del primero real
    }

    ~SentinelLinkedList()
    {
        Node* current = head; // empezamos desde el centinela
        while (current != nullptr)
        {
            Node* temp = current;
            current = current->next;
            delete temp; // se libera cada nodo uno por uno
        }
    }
};

// 2) LQueue
// Implementación de una cola (queue) usando nuestra lista ligada con nodo centinela
// Sigue el principio FIFO (First In First Out)
template <typename T>
class LQueue
{
private:
    SentinelLinkedList<T> data; // se apoya en la lista ligada

public:
    LQueue() {}

    int GetCount() { return data.GetCount(); } // devuelve el número de elementos en la cola

    void Enqueue(T value) // agrega al final (como en una cola normal)
    {
        data.PushBack(value);
    }

    T Dequeue() // saca el primero (como en una cola normal)
    {
        return data.PopFront();
    }

    T Front() // consulta el primer elemento sin eliminarlo
    {
        return data.Front();
    }
};

// 3) LStack
// Implementación de una pila (stack) usando forward_list de STL
// Sigue el principio LIFO (Last In First Out)
template <typename T>
class LStack
{
private:
    forward_list<T> data; // lista ligada hacia adelante (de STL)
    int count;

public:
    LStack() { count = 0; }

    void Push(T val) // agrega al inicio (O(1))
    {
        data.push_front(val);
        count++;
    }

    T Pop() // elimina el primero (tope)
    {
        if (count == 0)
        {
            cout << "Advertencia: el stack está vacío, no se puede hacer Pop\n";
            return {};
        }
        T val = data.front(); // guarda el valor a eliminar
        data.pop_front();     // elimina el primero
        count--;
        return val;           // regresa el valor eliminado
    }

    T Peak() // consulta el valor del tope sin quitarlo
    {
        if (count == 0)
        {
            cout << "Advertencia: el stack está vacío, no hay Peak\n";
            return {};
        }
        return data.front();
    }

    int Count() { return count; } // devuelve el número de elementos en la pila
};

// 4) HERENCIA
// Clases relacionadas con figuras geométricas, usando herencia y polimorfismo puro
class Figura
{
protected:
    string nombre; // nombre de la figura (usado para identificar)

public:
    Figura(string name) : nombre(name) {}
    virtual ~Figura() {}

    virtual float CalcularArea() const = 0;       // método virtual puro (obligatorio en hijos)
    virtual float CalcularPerimetro() const = 0;  // método virtual puro (obligatorio en hijos)

    const string& ObtenerNombreDeFigura() const { return nombre; }
};

// Círculo con fórmula de área y perímetro
class Circulo : public Figura
{
private:
    float radio; // radio del círculo

public:
    Circulo(float r) : Figura("Circulo"), radio(r) {}

    float CalcularArea() const override
    {
        return 3.1416f * radio * radio; // fórmula del área
    }

    float CalcularPerimetro() const override
    {
        return 2 * 3.1416f * radio; // fórmula del perímetro
    }
};

// Cuadrado con lado igual
class Cuadrado : public Figura
{
protected:
    float lado; // longitud de un lado

public:
    Cuadrado(float l) : Figura("Cuadrado"), lado(l) {}

    float CalcularArea() const override
    {
        return lado * lado; // área del cuadrado
    }

    float CalcularPerimetro() const override
    {
        return 4 * lado; // perímetro del cuadrado
    }
};

// Figura regular con n lados iguales
class FiguraNLados : public Figura
{
private:
    int lados;       // número de lados
    float longitud;  // longitud de cada lado

public:
    FiguraNLados(int n, float l) : Figura("FiguraNLados"), lados(n), longitud(l) {}

    float CalcularArea() const override
    {
        return (lados * longitud * longitud) / (4 * tan(3.1416f / lados));
    }

    float CalcularPerimetro() const override
    {
        return lados * longitud;
    }
};

// Cubo que hereda de Cuadrado (todas sus caras son cuadrados)
class Cubo : public Cuadrado
{
public:
    Cubo(float l) : Cuadrado(l) { nombre = "Cubo"; }

    float Surface() const // área superficial (6 caras cuadradas)
    {
        return 6 * lado * lado;
    }

    float Volumen() const // volumen del cubo (lado^3)
    {
        return lado * lado * lado;
    }

    float CalcularArea() const override
    {
        return Surface(); // redefinimos para devolver superficie
    }

    float CalcularPerimetro() const override
    {
        return 12 * lado; // un cubo tiene 12 aristas del mismo largo
    }
};

// Línea formada por varios segmentos (sin área, solo suma de longitudes)
class Linea : public Figura
{
private:
    float* segmentos; // arreglo dinámico con cada segmento de la línea
    int tam;          // número de segmentos

public:
    Linea(float* arr, int n) : Figura("Linea"), tam(n)
    {
        segmentos = new float[n]; // reservamos memoria
        for (int i = 0; i < n; i++)
        {
            segmentos[i] = arr[i]; // copiamos cada segmento
        }
    }

    ~Linea()
    {
        delete[] segmentos; // libera la memoria dinámica
    }

    float CalcularArea() const override
    {
        return 0; // una línea no tiene área
    }

    float CalcularPerimetro() const override
    {
        float suma = 0;
        for (int i = 0; i < tam; i++)
        {
            suma += segmentos[i]; // sumamos todas las longitudes
        }
        return suma; // perímetro es la suma de los segmentos
    }
};
