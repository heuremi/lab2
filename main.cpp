#include <bits/stdc++.h>
#include "Partida.h";
using namespace std;

const int filas = 6;
const int columnas = 7;

void jugarPartida(){
	cout << "Elija dificultad del juego:\n1) Facil.\n2) Medio.\n3)Dificil." << endl;
	string dificultad; cin >> dificultad;
	int profundidad;
	if(dificultad == "1"){
		profundidad = 2;
	}
	else if(dificultad == "2"){
		profundidad = 4;
	}
	else if(dificultad == "3"){
		profundidad = 6;
	}
	else {
		cout << "Dificultad invalida, volviendo al menu.\n";
		return;
	}
	char jugador;
	cout << "Quien comienza el juego?\n 1) IA.\n2) Jugador." << endl;
	string inicial; cin >> inicial;
	if(inicial == "1"){
		jugador = 'O'; // IA
	} 
	else if(inicial == "2") {
		jugador = 'X'; // jugador
	}
	else {
		cout << "Opcion invalida, volviendo al menu.\n";
		return;
	}
	cout << "Comenzando partida." << endl;
	Partida partida(profundidad);
	while(true){
		partida.mostrarTablero();
		jugador = (jugador == 'O') ? 'O' : 'X';
		if(jugador == 'O'){
			cout << "Turno de la IA." << endl;
			//movimiento IA POR HACER !!!
		}
		else {
			cout << "Turno del jugador." << endl;
			cout << "Ingrese la columna para poner su ficha (1-7): ";
			int pos; cin >> pos; pos -= 1;
			while(pos < 0 || pos > 6 || partida.columnaLlena(pos)){
				cout << "Movimiento invalido. " << endl;
				cin >> pos; pos -= 1;
			} 
			if(!partida.hacerMovimiento(pos, jugador)){
				cout << "El movimiento no pudo realizarse.\n";
			}
		}
		if(partida.ganador(jugador)){
			cout << "Partida terminada! Ganador: ";
			if(jugador == 'X'){
				cout << "jugador." << endl;
			} else {
				cout << "IA." << endl;
			}
			guardarPartida("historial.csv", partida);
			break;
		}
	}
}
void guardarPartida(const string& archivo, Partida partida) {
	ofstream salida(archivo);

	if (!salida) {
		cout << "Error al abrir el archivo para guardar la partida." << endl;
		return;
	}

	// Guardar el estado actual del tablero en el archivo
	for (int i = 0; i < filas; ++i) {
		for (int j = 0; j < columnas; ++j) {
			
			salida << partida.getPieza(i, j) << " ";
		}
		salida << "\n";
	}

	salida.close();
}

void cargarPartida(const string& archivo) {
        ifstream entrada(archivo);

        if (!entrada) {
            cout << "Error al abrir el archivo para cargar la partida. Se creará un tablero nuevo." << endl;
            return;
        }

        // Cargar el estado del tablero desde el archivo
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
               // entrada >> tablero[i][j];
            }
        }

        entrada.close();
}

bool hayJuegoCargado(const string& archivo){
	    ifstream existePartida(archivo);

        if (!existePartida) {
            cout << "Error al abrir el archivo para cargar la partida. Se creará un tablero nuevo." << endl;
            return;
        }

        // Cargar el estado del tablero desde el archivo
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
               // entrada >> tablero[i][j];
            }
        }
		existePartida.close();
}

void verEstadisticas(const string& archivo){
	ifstream entrada(archivo);

    if (!entrada) {
        cout << "Error al abrir el archivo para cargar la partida. Se creará un tablero nuevo." << endl;
        return;
    }

    // Cargar el estado del tablero desde el archivo
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            // entrada >> tablero[i][j];
         }
    }

    entrada.close();
}

int main(){
	if(hayJuegoCargado("historial.csv")){
		cout << "Hola!, deseas retomar el juego guardado?\n1) Si.\n2) No." << endl;
		string op; cin >> op;
		if(op == "1"){
			cargarPartida("historial.csv");
		} else {
			cout << "Volviendo al menu." << endl;
		}
	}
	
	while(true){
		cout << "---------- MENU ----------" << endl;
		cout << "1) Jugar nueva partida." << endl;
		cout << "2) Ver Estadisticas." << endl;
		cout << "3) Salir" << endl;
		string opcion; cin >> opcion;
		if(opcion == "1"){
			jugarPartida();
		} 
		else if(opcion == "2"){
			verEstadisticas("historial.csv");
		} 
		else if(opcion == "3"){
			cout << "Nos vemos pronto!" << endl;
			break;
		} else {
			cout << "Opcion invalida" << endl;
		}
	}
	return 0;
}