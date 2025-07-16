// YUNUEN PORTES RAMÍREZ - ESTRUCTURAS DE DATOS Y HERENCIA EN C++

// profe, perdon por la tardanza, pero si tuve varios problemas ahi personales y con la tarea en general, no sabia como subirlo, se me olvido todo :b
// de referencia use este; cplusplus.com - forward_list, chat para que me ayudara en cosas como lo de las figuras y para que me ayudara a entregarlo la vdd
//1
#pragma once
#include <iostream>
#include <forward_list> // para la pila (stack)
#include <cmath>        // para tan() en FiguraNLados
using namespace std;

// Esta clase es una lista ligada con un nodo especial al inicio (nodo centinela),
// lo que nos ayuda a simplificar las operaciones en los extremos (inicio/final).
template <typename T>
class SentinelLinkedList
{
private:
    struct Node
    {
        T value;      // valor del nodo
        Node* next;   // puntero al siguiente
    };

    Node* head; // nodo centinela
    Node* tail; // último nodo real (el que contiene datos)
    int count;  // cuántos nodos reales hay

public:
    // Constructor: al inicio solo hay un nodo centinela
    SentinelLinkedList()
    {
        head = new Node();
        tail = head;
        count = 0;
    }

    // Agrega al final
    void PushBack(T val)
    {
        Node* newNode = new Node{ val, nullptr };
        tail->next = newNode;
        tail = newNode;
        count++;
    }

    // Elimina el último nodo (el real, no el centinela)
    T PopBack()
    {
        if (count == 0)
        {
            cout << "Cuidado, estás haciendo pop back cuando la lista está vacía\n";
            return {};
        }

        Node* prev = head;
        while (prev->next != tail) prev = prev->next;

        T val = tail->value;
        delete tail;
        tail = prev;
        tail->next = nullptr;
        count--;
        return val;
    }

    // Inserta al frente (después del centinela)
    void PushFront(T val)
    {
        Node* newNode = new Node{ val, head->next };
        head->next = newNode;
        if (count == 0) tail = newNode;
        count++;
    }

    // Elimina el primero real (después del centinela)
    T PopFront()
    {
        if (count == 0)
        {
            cout << "Advertencia: la lista está vacía, no se puede hacer PopFront\n";
            return {};
        }

        Node* first = head->next;
        T val = first->value;
        head->next = first->next;
        if (first == tail) tail = head;
        delete first;
        count--;
        return val;
    }

    // Regresa el primer valor (sin eliminar)
    T Front()
    {
        if (count == 0)
        {
            cout << "Advertencia, la lista está vacía, no hay Front\n";
            return {};
        }
        return head->next->value;
    }

    // Regresa cuántos elementos hay
    int GetCount() { return count; }

    // Libera toda la memoria (incluyendo centinela)
    ~SentinelLinkedList()
    {
        Node* current = head;
        while (current != nullptr)
        {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};
//2
template <typename T>
class LQueue
{
private:
    SentinelLinkedList<T> data; // usamos la lista como base

public:
    LQueue() {}

    int GetCount();      // cuántos elementos hay
    void Enqueue(T val); // insertar al final
    T Dequeue();         // quitar del frente
    T Front();           // ver el frente sin quitar
};

// Ahora implementamos lo anterior fuera de la clase (como si fuera un archivo .tpp)

template <typename T>
int LQueue<T>::GetCount() { return data.GetCount(); }

template <typename T>
void LQueue<T>::Enqueue(T val) { data.PushBack(val); }

template <typename T>
T LQueue<T>::Dequeue() { return data.PopFront(); }

template <typename T>
T LQueue<T>::Front() { return data.Front(); }
//3
template <typename T>
class LStack
{
private:
    forward_list<T> data; // usamos la lista de STL
    int count;

public:
    LStack() { count = 0; }

    void Push(T val)
    {
        data.push_front(val); // se agrega al inicio (O(1))
        count++;
    }

    T Pop()
    {
        if (count == 0)
        {
            cout << "Advertencia: el stack está vacío, no se puede hacer Pop\n";
            return {};
        }
        T val = data.front();
        data.pop_front();
        count--;
        return val;
    }

    T Peak()
    {
        if (count == 0)
        {
            cout << "Advertencia: el stack está vacío, no hay Peak\n";
            return {};
        }
        return data.front();
    }

    int Count() { return count; }
};
//4
// Esta clase es abstracta. Solo sirve como base.
class Figura
{
protected:
    string nombre;

public:
    Figura(string name) : nombre(name) {}
    virtual ~Figura() {}

    virtual float CalcularArea() const = 0;
    virtual float CalcularPerimetro() const = 0;

    const string& ObtenerNombreDeFigura() const { return nombre; }
};

// Círculo clásico: área y perímetro con pi
class Circulo : public Figura
{
private:
    float radio;

public:
    Circulo(float r) : Figura("Circulo"), radio(r) {}

    float CalcularArea() const override { return 3.1416f * radio * radio; }
    float CalcularPerimetro() const override { return 2 * 3.1416f * radio; }
};

// Cuadrado con lado igual
class Cuadrado : public Figura
{
protected:
    float lado;

public:
    Cuadrado(float l) : Figura("Cuadrado"), lado(l) {}

    float CalcularArea() const override { return lado * lado; }
    float CalcularPerimetro() const override { return 4 * lado; }
};

// Figura de n lados iguales (polígono regular)
class FiguraNLados : public Figura
{
private:
    int lados;
    float longitud;

public:
    FiguraNLados(int n, float l) : Figura("FiguraNLados")
    {
        if (n < 3)
        {
            cout << "Una figura debe tener al menos 3 lados. Se asigna 3 por defecto.\n";
            lados = 3;
        }
        else lados = n;

        longitud = l;
    }

    float CalcularArea() const override
    {
        return (lados * longitud * longitud) / (4 * tan(3.1416f / lados));
    }

    float CalcularPerimetro() const override { return lados * longitud; }
};

// Cubo: hereda de cuadrado (cada cara es un cuadrado)
class Cubo : public Cuadrado
{
public:
    Cubo(float l) : Cuadrado(l) { nombre = "Cubo"; }

    float Surface() const { return 6 * lado * lado; }
    float Volumen() const { return lado * lado * lado; }

    float CalcularArea() const override { return Surface(); }
    float CalcularPerimetro() const override { return 12 * lado; }
};

// Línea hecha de segmentos (no tiene área)
class Linea : public Figura
{
private:
    float* segmentos;
    int tam;

public:
    Linea(float* arr, int n) : Figura("Linea"), tam(n)
    {
        segmentos = new float[n];
        for (int i = 0; i < n; i++) segmentos[i] = arr[i];
    }

    Linea(const Linea& otra) : Figura("Linea"), tam(otra.tam)
    {
        segmentos = new float[tam];
        for (int i = 0; i < tam; i++) segmentos[i] = otra.segmentos[i];
    }

    void SetSegmento(int i, float val)
    {
        if (i >= 0 && i < tam) segmentos[i] = val;
        else cout << "Índice fuera de rango al modificar segmento.\n";
    }

    ~Linea() { delete[] segmentos; }

    float CalcularArea() const override { return 0; }

    float CalcularPerimetro() const override
    {
        float suma = 0;
        for (int i = 0; i < tam; i++) suma += segmentos[i];
        return suma;
    }
};
//5
int main()
{
    // --- COLA ---
    cout << "--- LQueue (Cola) ---\n";
    LQueue<int> cola;
    cola.Enqueue(10);
    cola.Enqueue(20);
    cout << "Front: " << cola.Front() << "\n";
    cout << "Dequeue: " << cola.Dequeue() << "\n";

    // --- PILA ---
    cout << "\n--- LStack (Pila) ---\n";
    LStack<string> pila;
    pila.Push("Hola");
    pila.Push("Mundo");
    cout << "Peak: " << pila.Peak() << "\n";
    cout << "Pop: " << pila.Pop() << "\n";

    // --- FIGURAS ---
    cout << "\n--- Figuras ---\n";
    Circulo c(3);
    Cuadrado q(4);
    FiguraNLados pent(5, 2);
    Cubo cubo(2);
    float segs[] = { 1.2, 2.5, 3.1 };
    Linea linea(segs, 3);

    Figura* figuras[] = { &c, &q, &pent, &cubo, &linea };

    for (Figura* f : figuras)
    {
        cout << f->ObtenerNombreDeFigura() << " - Área: " << f->CalcularArea()
            << ", Perímetro: " << f->CalcularPerimetro() << "\n";
    }

    return 0;
}
