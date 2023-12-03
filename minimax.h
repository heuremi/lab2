#include <bits/stdc++.h>
using namespace std;

const int filas = 6;
const int columnas = 7;

struct Nodo{
	struct Nodo **hijos;
	int *movimientos;
	int n_hijos;
	char tablero[filas][columnas];
	double valor;
	int nivel;
};

void CopiaTablero(char tablero1[filas][columnas], char tablero2[filas][columnas]){
	for(int i = 0;i < filas; i++){
		for(int j = 0; j < columnas; j++){
			tablero2[i][j] = tablero1[i][j];
		}
	}
}

Nodo CreaNodo(char tablero[filas][columnas],int nivel,int dificultad, int posibilidades, bool victoriaCPU, bool victoriaJugador){
	int j=0;
	Nodo p;

	p.nivel = nivel;
	CopiaTablero(tablero,p.tablero);
	p.n_hijos = posibilidades;
	p.valor = 0;
	if (victoriaCPU || victoriaJugador || p.nivel == 2*dificultad+2){
        p.n_hijos = 0;
	}

	if (p.n_hijos != 0){
        p.hijos = (Nodo **) malloc(p.n_hijos*sizeof(Nodo *));
        p.movimientos = (int *) malloc(p.n_hijos*sizeof(int));
        for(int i = 0; i < columnas; i++){
            if(tablero[0][i] == ' '){
                p.movimientos[j] = i;
                j += 1;
            }
        }
	}
	else{
        p.hijos = NULL;
        p.movimientos = NULL;
	}


	return p;
}

void AplicarTirada(char partida[filas][columnas],int columna, char ficha){
	for(int i = 0; i < filas; i++){
		if(partida[filas-1-i][columna] == ' '){
			partida[filas-1-i][columna] = ficha;
			break;
		}
	}
}

void CreaNivel(Nodo *Padre,char ficha,int dificultad, int posibilidades, bool victoriaCPU, bool victoriaJugador){
	int i;
	Nodo *Hijo;

	for(i=0;i<Padre->n_hijos;i++){
		Hijo = (Nodo *) malloc(sizeof(Nodo));
		CopiaTablero(Padre->tablero,Hijo->tablero);
		AplicarTirada(Hijo->tablero,Padre->movimientos[i],ficha);
		*Hijo = CreaNodo(Hijo->tablero,Padre->nivel+1,dificultad, posibilidades, victoriaCPU, victoriaJugador);
		Padre->hijos[i] = Hijo;
	}
}

void CreaDobleNivel(Nodo *raiz,int dificultad, int posibilidades, bool victoriaCPU, bool victoriaJugador){
	int i;
	CreaNivel(raiz,'X',dificultad, posibilidades, victoriaCPU, victoriaJugador);
	for(i=0;i<raiz->n_hijos;i++){
		CreaNivel(raiz->hijos[i],'O',dificultad, posibilidades, victoriaCPU, victoriaJugador);
	}
}

void CreaArbol(Nodo *raiz, int profundidad, int dificultad, int posibilidades, bool victoriaCPU, bool victoriaJugador){
	CreaDobleNivel(raiz,dificultad, posibilidades, victoriaCPU, victoriaJugador);
	if(profundidad == 0) return;
	else{
		int i; int j;
		for(i=0;i<raiz->n_hijos;i++){
			for(j=0;j<raiz->hijos[i]->n_hijos;j++){
				CreaArbol(raiz->hijos[i]->hijos[j],profundidad-1,dificultad, posibilidades, victoriaCPU, victoriaJugador);
			}
		}
	}
	return;
}

void BorraArbol(Nodo *raiz){
	if(raiz->n_hijos == 0){
        free(raiz);
	}
	else{
        int i;
        for (i=0;i<raiz->n_hijos;i++){
            BorraArbol(raiz->hijos[i]);
        }
        free(raiz->hijos);
        free(raiz->movimientos);
	}

	return;
}

void ValorarHojas(Nodo *raiz, double heuristica){
    if (raiz->n_hijos == 0){
        raiz->valor = heuristica;
    }
    else{
        int i;
        for (i=0;i<raiz->n_hijos;i++){
            ValorarHojas(raiz->hijos[i], heuristica);
        }
    }
}

void MiniMaxConPoda(Nodo *Raiz, double alpha, double beta) {
    if (Raiz->n_hijos != 0) {
        for (int i = 0; i < Raiz->n_hijos; i++) {
            if (Raiz->hijos[i]->n_hijos != 0) {
                MiniMaxConPoda(Raiz->hijos[i], alpha, beta);
            }
        }

        if (Raiz->nivel % 2 == 0) { // MAX
            Raiz->valor = Raiz->hijos[0]->valor;
            for (int i = 1; i < Raiz->n_hijos; i++) {
                if (Raiz->hijos[i]->valor > Raiz->valor) {
                    Raiz->valor = Raiz->hijos[i]->valor;
                }
                alpha = std::max(alpha, Raiz->valor);
                if (beta <= alpha) {
                    break;  // Poda alfa-beta
                }
            }
        } else { // MIN
            Raiz->valor = Raiz->hijos[0]->valor;
            for (int i = 1; i < Raiz->n_hijos; i++) {
                if (Raiz->hijos[i]->valor < Raiz->valor) {
                    Raiz->valor = Raiz->hijos[i]->valor;
                }
                beta = std::min(beta, Raiz->valor);
                if (beta <= alpha) {
                    break;  // Poda alfa-beta
                }
            }
        }

        Raiz->valor /= 2;
    }
}

int ElegirTirada(char partida[filas][columnas], int dificultad, int posibilidades, bool victoriaCPU, bool victoriaJugador, int profundidad, double heuristica){
	Nodo Raiz = CreaNodo(partida,0,dificultad, posibilidades, victoriaCPU, victoriaJugador);
	int movimiento;
	CreaArbol(&Raiz, profundidad, dificultad, posibilidades, victoriaCPU, victoriaJugador);
	ValorarHojas(&Raiz, heuristica);
	MiniMaxConPoda(&Raiz, -100000, 100000);

	// Elegimos random entre todas las posibilidades que son igual de buenas
	int num_tiradas_buenas = 0;
	int tiradas_buenas[8];
	int i; int j=0;
	for (i=0;i<Raiz.n_hijos;i++){
		if (Raiz.hijos[i]->valor == 2.0*Raiz.valor){
			num_tiradas_buenas++;
			tiradas_buenas[j] = Raiz.movimientos[i];
			j++;
		}
	}
	int index = rand()%num_tiradas_buenas;
	movimiento = tiradas_buenas[index];
	BorraArbol(&Raiz);

	return movimiento;
}