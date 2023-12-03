#pragma once
#include <bits/stdc++.h>
#include "Nodo.h"
using namespace std;

const int filas = 6;
const int columnas = 7;

class Arbol{
    public:
        Nodo* raiz; // Puedes agregar un atributo para representar el nodo raíz

        Arbol() {
            raiz = new Nodo();
        }

        ~Arbol() {
            delete raiz;
        }
        void construirArbol(Nodo* nodo, int profundidad) {
        if (profundidad == 0) {
            // No se construyen más nodos si se alcanza la profundidad máxima
            return;
        }

        for (int columna = 0; columna < columnas; ++columna) {
            if (nodo->tablero[0][columna] == ' ') {
                // Realiza un movimiento simulado en el tablero
                for (int i = filas - 1; i >= 0; i--) {
                    if (nodo->tablero[i][columna] == ' ') {
                        nodo->tablero[i][columna] = (profundidad % 2 == 0) ? 'X' : 'O';
                        break;
                    }
                }

                // Crea un nuevo nodo hijo
                Nodo* hijo = new Nodo();
                // Copia el tablero del nodo actual al nuevo nodo
                for (int i = 0; i < filas; ++i) {
                    for (int j = 0; j < columnas; ++j) {
                        hijo->tablero[i][j] = nodo->tablero[i][j];
                    }
                }

                // Agrega el nuevo nodo como hijo y realiza la llamada recursiva
                nodo->hijos.push_back(hijo);
                construirArbol(hijo, profundidad - 1);

                // Deshace el movimiento simulado en el tablero para probar otros movimientos
                for (int fila = 0; fila < filas; ++fila) {
                    if (nodo->tablero[fila][columna] != ' ') {
                        nodo->tablero[fila][columna] = ' ';
                        break;
                    }
                }
            }
        }
}
