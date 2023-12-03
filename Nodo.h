#pragma once
#include <bits/stdc++.h>
using namespace std;

const int filas = 6;
const int columnas = 7;

class Nodo {
	private:
		vector<Nodo*> hijos;
		int puntaje;
	public:
	Nodo(){
		puntaje = 0;
	}
	~Nodo(){};
};
