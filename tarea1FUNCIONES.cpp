// YUNUEN PORTES RAMIREZ
#include <iostream>
#include <string>
#include <ctime>// me ayuda a obtener la fecha y la hora
using namespace std;

// declaro las funciones, para ver si es lunes, masrtes despues de las 12 pm y jueves antes de las 12 pm
void verificarLunes(int dia);
void verificarMartesODespuesMediodia(int dia, int hora);
void verificarJuevesAntesMediodia(int dia, int hora);

int main()
{
    //para pbtener la fehca y hora usare now que es para guardar la hora
    time_t now = time(0);
    //localTime es una estructura que se llenara con la informacion de la fecha y hora
    tm localTime;
    // y localtime_s ayuda a llenar la estructura de forma correcta, lo intente de otra forma y me saltaba una advertencia
    localtime_s(&localTime, &now);

    // aqui es donde saco el dia, hora y minutos usando localTime
    int horaActual = localTime.tm_hour; // este para la hora
    int minutoActual = localTime.tm_min; // y este par ale minuto
    int diaActual = 4;

    // arreglo para imprimir los dias con su NOMBRE en manera de texto
    string nombresDias[] = { "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo" };

    // decir el dia y la hora en la que se compila
    // tmabien uso "(minutoActual<10?"0":"")" para agregar un 0 cuando los minutos son menroes a 10, por ejemplo 12:03 en lugar de 12:3 y que se entienda mejor
    cout << "Hoy es " << nombresDias[diaActual] << " a las " << horaActual << ":" << (minutoActual < 10 ? "0" : "") << minutoActual << endl;
    cout << "----------------------------------------" << endl;


    // aqui hago las funciones que declare al inicio
    // Verifica si es lunes
    verificarLunes(diaActual);
    // Verifica si es jueves antes de las 12 PM
    verificarJuevesAntesMediodia(diaActual, horaActual);
    // Verifica si es martes o si ya es después de las 12
    verificarMartesODespuesMediodia(diaActual, horaActual);

    // ciclo par apoder recorrer la semana de 0 a 6
    // cuando i es iagual a un dia imprime si es ese dia, marcando que los otros no
    for (int i = 0; i < 7; i++)
    {
        if (i == diaActual)
        {
            cout << "Hoy si es " << nombresDias[i] << endl;
        }
        else
        {
            cout << "Hoy no es " << nombresDias[i] << endl;
        }
    }
    //fin del main()
    return 0;
}

// funcion par verificar e impirmir en caso de ser lunes
void verificarLunes(int dia)
{
    if (dia == 0)
    {
        cout << "Es lunes" << endl;
    }
}

// funcion que verifica e imprimir si es jueves antes de las 12
void verificarJuevesAntesMediodia(int dia, int hora)
{
    if (dia == 3 && hora < 12)
    {
        cout << "Es jueves antes del mediodia" << endl;
    }
}

// funcion que verifica e impirmir si es martes o si es después de las 12
void verificarMartesODespuesMediodia(int dia, int hora)
{
    if (dia == 1)
    {
        cout << "Es martes" << endl;
    }
    else if (hora >= 12)
    {
        cout << "No es martes pero es despues de las 12 PM" << endl;
    }
}