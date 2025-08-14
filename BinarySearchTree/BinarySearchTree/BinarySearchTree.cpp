#include <cmath>

double log_base_n(double x, double base) {
    return std::log(x) / std::log(base);
}

int MinimaAlturaDeArbol(int numeroDeNodos, int maximoDeHijosPorNodo) {
    if (numeroDeNodos <= 0) return 0;
    int calc = ((maximoDeHijosPorNodo - 1) * numeroDeNodos + 1);
    return static_cast<int>(std::ceil(log_base_n(calc, maximoDeHijosPorNodo))) - 1;
}
