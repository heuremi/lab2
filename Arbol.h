#pragma once
#include <bits/stdc++.h>
#include "Nodo.h"
using namespace std;

const int filas = 6;
const int columnas = 7;

class Arbol{
    void construirArbol(Nodo* nodo, int profundidad) {
    if (profundidad == 0) {
        // No se construyen más nodos si se alcanza la profundidad máxima
        return;
    }

    for (int columna = 0; columna < col; ++columna) {
        if (nodo->tablero[0][columna] == ' ') {
            // Realiza un movimiento simulado en el tablero
            for (int fila = FILAS - 1; fila >= 0; --fila) {
                if (nodo->tablero[fila][columna] == ' ') {
                    nodo->tablero[fila][columna] = (profundidad % 2 == 0) ? 'X' : 'O';
                    break;
                }
            }

            // Crea un nuevo nodo hijo
            Nodo* hijo = new Nodo();
            // Copia el tablero del nodo actual al nuevo nodo
            for (int i = 0; i < FILAS; ++i) {
                for (int j = 0; j < COLUMNAS; ++j) {
                    hijo->tablero[i][j] = nodo->tablero[i][j];
                }
            }

            // Agrega el nuevo nodo como hijo y realiza la llamada recursiva
            nodo->hijos.push_back(hijo);
            construirArbol(hijo, profundidad - 1);

            // Deshace el movimiento simulado en el tablero para probar otros movimientos
            for (int fila = 0; fila < FILAS; ++fila) {
                if (nodo->tablero[fila][columna] != ' ') {
                    nodo->tablero[fila][columna] = ' ';
                    break;
                }
            }
        }
    }
}
