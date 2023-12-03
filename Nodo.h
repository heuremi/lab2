#pragma once
#include <bits/stdc++.h>
using namespace std;

const int filas = 6;
const int columnas = 7;

class Nodo {
	private:
		vector<Nodo*> hijos;
		int puntaje;
		int tablero[filas][columnas];
		int jugadorActual;
	public:
	Nodo(int jugadorAct){
		puntaje = 0;
		jugadorActual = jugadorAct;
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                tablero[i][j] = 0;
            }
        }
	}
	~Nodo(){};
};
