// YUNUEN PORTES RAMÍREZ 
// profe, perdon por la tardanza, pero si tuve varios problemas ahi personales y con la tarea en general, no sabia como subirlo, se me olvido todo :b
// de referencia use este: cplusplus.com - forward_list, y también me apoyé del chat para cosas como las figuras y para que me ayudara a entregar, la vdd.

#include <iostream>
#include <forward_list> // para la pila (stack)
#include <cmath>        // para tan() en FiguraNLados
#include "SentinelLinkedList.h" // usamos la versión exacta del repo
using namespace std;

// LQUEUE 
// Implementación de una cola (FIFO) con la SentinelLinkedList de la clase

// Nos apoyamos de la versión exacta con Find, Insert, Remove, etc.
template <typename T>
class LQueue {
private:
    SentinelLinkedList<T> data;

public:
    void Enqueue(T value) { data.PushBack(value); }
    T Dequeue() { return data.PopFront(); }
    T Front() const { return data.Front(); }
    int GetCount() const { return data.GetCount(); }
};

// LSTACK 
// Pila (LIFO) basada en forward_list (de STL) con contador
template <typename T>
class LStack {
private:
    forward_list<T> data;
    int count;

public:
    LStack() : count(0) {}

    void Push(T val) {
        data.push_front(val); // más fácil así, al inicio
        count++;
    }

    T Pop() {
        if (count == 0) {
            cout << "Advertencia: el stack está vacío, no se puede hacer Pop\n";
            return {};
        }
        T val = data.front();
        data.pop_front();
        count--;
        return val;
    }

    T Peak() const {
        if (count == 0) {
            cout << "Advertencia: el stack está vacío, no hay Peak\n";
            return {};
        }
        return data.front();
    }

    int Count() const { return count; }
};

// JERARQUÍA DE FIGURAS
// Clase base Figura, clases derivadas con override y destructores bien puestos
class Figura {
protected:
    string nombre;

public:
    Figura(string name) : nombre(name) {}
    virtual ~Figura() {}

    virtual float CalcularArea() const = 0;
    virtual float CalcularPerimetro() const = 0;
    const string& ObtenerNombreDeFigura() const { return nombre; }
};

class Circulo : public Figura {
private:
    float radio;

public:
    Circulo(float r) : Figura("Circulo"), radio(r) {}
    ~Circulo() override {}

    float CalcularArea() const override { return 3.1416f * radio * radio; }
    float CalcularPerimetro() const override { return 2 * 3.1416f * radio; }
};

class Cuadrado : public Figura {
private: //Antes lado era protected para que el Cubo pudiera usarlo directo porque hereda de Cuadrado, pero vi lo que me pregunto y supuse que fuera private para aplicar bien la encapsulación, asi creo que podemos hacer que todo se haga por medio de funciones (como CalcularArea()), y no andar accediendo variables desde afuera. Ya lo cambié, y ahora el Cubo calcula las cosas sin tocar lado directamente, todo bonito y seguro, esoero ;;
    float lado;

public:
    Cuadrado(float l) : Figura("Cuadrado"), lado(l) {}
    ~Cuadrado() override {}

    float CalcularArea() const override { return lado * lado; }
    float CalcularPerimetro() const override { return 4 * lado; }
};

class FiguraNLados : public Figura {
private:
    int lados;
    float longitud;

public:
    FiguraNLados(int n, float l) : Figura("FiguraNLados"), lados(n), longitud(l) {}
    ~FiguraNLados() override {}

    float CalcularArea() const override {
        return (lados * longitud * longitud) / (4 * tan(3.1416f / lados));
    }

    float CalcularPerimetro() const override {
        return lados * longitud;
    }
};

class Cubo : public Cuadrado {
public:
    Cubo(float l) : Cuadrado(l) { nombre = "Cubo"; }
    ~Cubo() override {}

    float Surface() const { return 6 * CalcularArea(); }

    float Volumen() const {
        float lado = sqrt(CalcularArea());
        return lado * lado * lado;
    }

    float CalcularArea() const override { return Surface(); }
    float CalcularPerimetro() const override {
        return 12 * sqrt(CalcularArea());
    }
};

class Linea : public Figura {
private:
    float* segmentos;
    int tam;

public:
    Linea(float* arr, int n) : Figura("Linea"), tam(n) {
        segmentos = new float[n];
        for (int i = 0; i < n; i++) segmentos[i] = arr[i];
    }

    ~Linea() override {
        delete[] segmentos;
    }

    float CalcularArea() const override { return 0; } // no tiene área

    float CalcularPerimetro() const override {
        float suma = 0;
        for (int i = 0; i < tam; i++) suma += segmentos[i];
        return suma;
    }
};

// MAIN
// Aquí se prueba todo lo anterior con ejemplos :)
int main() {
    // Cola
    LQueue<int> cola;
    cola.Enqueue(10);
    cola.Enqueue(20);
    cola.Enqueue(30);
    cout << "Front de la cola: " << cola.Front() << endl;
    cola.Dequeue();
    cout << "Nuevo Front: " << cola.Front() << ", Count: " << cola.GetCount() << endl;

    // Pila
    LStack<string> pila;
    pila.Push("uno");
    pila.Push("dos");
    cout << "Tope de pila: " << pila.Peak() << endl;
    pila.Pop();
    cout << "Nuevo tope: " << pila.Peak() << ", Count: " << pila.Count() << endl;

    // Figuras
    Figura* f1 = new Circulo(5);
    Figura* f2 = new Cuadrado(4);
    Figura* f3 = new FiguraNLados(6, 3);
    float segs[] = { 1.2, 2.5, 3.1 };
    Figura* f4 = new Linea(segs, 3);
    Figura* f5 = new Cubo(3);

    Figura* figuras[] = { f1, f2, f3, f4, f5 };
    for (auto fig : figuras) {
        cout << fig->ObtenerNombreDeFigura() << ": A=" << fig->CalcularArea()
            << ", P=" << fig->CalcularPerimetro() << endl;
        delete fig; // liberamos memoria bien
    }

    return 0;
}
