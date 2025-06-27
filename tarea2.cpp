// YUNUEN PORTES RAMÍREZ

// PRIMERO
#include <iostream>
using namespace std;

void cambiarBool(bool arr[], int tam) 
{
    // esta función recibe un arreglo de bools y su tamaño
    // modifica cada valor: true si el índice es impar, false si es par
    for (int i = 0; i < tam; i++) 
    {
        arr[i] = (i % 2 != 0);
    }
}

void cambiarEnteros(int* arr, int tam) 
{
    // esta función recibe un arreglo de enteros y los modifica con punteros
    int* aux = arr; // puntero auxiliar que apunta al mismo arreglo
    for (int i = 0; i < tam; i++) {
        *(aux + i) = *(aux + i) % 2; // cambia par por 0 e impar por 1
        cout << "dir: " << (aux + i) << ", valor: " << *(aux + i) << endl;
    }
}

// SEGUNDO
struct Rectangulo 
{
    // estructura Rectangulo con sus 4 atributos
    int x, y, alto, ancho;

    Rectangulo() : x(0), y(0), alto(0), ancho(0) {} // constructor por defecto
    Rectangulo(int a, int b, int h, int an) : x(a), y(b), alto(h), ancho(an) {} // con todo
    Rectangulo(int h, int an) : x(0), y(0), alto(h), ancho(an) {} // solo alto y ancho
};

bool imprimirRectangulo(const Rectangulo& r, int& finX, int& finY) 
{
    // esta función imprime el punto inicial y final del rectángulo
    finX = r.x + r.ancho;
    finY = r.y + r.alto;

    cout << "Inicio: (" << r.x << ", " << r.y << "), Fin: (" << finX << ", " << finY << ")";
    return (r.x >= 0 && r.y >= 0 && r.alto >= 0 && r.ancho >= 0); // checa que todo sea válido
}

bool CheckOverlap(Rectangulo a, Rectangulo b) 
{
    // esta función verifica si dos rectángulos se cruzan o no
    // Si uno está totalmente a la izquierda, derecha, arriba o abajo del otro,
    // entonces NO se cruzan. Por eso se usa el "!" para negar esas condiciones.
    return !(a.x + a.ancho <= b.x || b.x + b.ancho <= a.x ||
        a.y + a.alto <= b.y || b.y + b.alto <= a.y);
}

int main() 
{
    bool arregloB[5]; // se crea un arreglo de 5 booleanos
    cambiarBool(arregloB, 5); // se modifica usando la función

    cout << "Booleanos: ";
    for (int i = 0; i < 5; i++) cout << arregloB[i] << " "; // se imprime el arreglo
    cout << endl;

    int arregloE[10]; // arreglo de 10 enteros
    for (int i = 0; i < 10; i++) arregloE[i] = i; // se llena con valores del 0 al 9

    cambiarEnteros(arregloE, 10); // se modifica usando punteros

    Rectangulo r1(0, 0, 5, 5);
    Rectangulo r2(6, 6, 5, 5);
    Rectangulo r3(2, 2, 2, 2);
    Rectangulo r4(1, 1, 7, 2);

    int fx, fy; // para guardar el punto final
    imprimirRectangulo(r1, fx, fy); // imprime r1

    cout << "\nr1 y r2 se cruzan? " << (CheckOverlap(r1, r2) ? "si" : "no") << endl;
    cout << "r1 y r3 se cruzan? " << (CheckOverlap(r1, r3) ? "si" : "no") << endl;
    cout << "r1 y r4 se cruzan? " << (CheckOverlap(r1, r4) ? "si : "no") << endl;
    // en todas estas se va a imprimir "si" si se llegan a crizazr y "no" en caso de que no
    return 0;
}

// TERCERO
int main3() 
{
    float* ptr = nullptr; // puntero a float inicializado como nulo

    ptr = new float(7.77); // se pide memoria dinámica con valor 7.77
    float num = 6.66; // se declara variable normal
    ptr = &num; // ahora ptr apunta a num, se pierde la dirección pedida con new (¡memory leak!)

    cout << "OJO PIOJO, estas usando memory leak!!!!";
    cout << "tiene explicación :D es porque perdiste la dirección pedida con new y no hiciste delete\n";

    ptr = new float(1984); // se vuelve a pedir memoria dinámica
    float* otro = ptr; // otro puntero apunta al mismo lugar

    delete ptr; // se libera la memoria
    ptr = nullptr; // ptr ahora ya no apunta a nada

    if (ptr == nullptr) cout << "ptr == nullptr"; // se verifica que ptr es nulo
    if (ptr == NULL) cout << "ptr == NULL"; // NULL también funciona, aunque es viejo

    if (otro != nullptr && otro != NULL)
        cout << "hay un puntero a la memoria eliminada. OJO"; // otro sigue apuntando a algo que ya se borró

    return 0;
}

/*
Fuentes consultadas:
- https://cplusplus.com/doc/tutorial/pointers/
- https://cplusplus.com/doc/tutorial/structures/
- https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/Conditional_Operator 