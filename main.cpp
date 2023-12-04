#include <bits/stdc++.h>
#include <fstream>
#include "Minimax.h"
using namespace std;

//imprime el tablero
void mostrarTablero(char partida[filas][columnas]){
	for(int i = 0; i < filas; i++){
		cout << "|";
		for(int j = 0; j < columnas; j++){
			cout<<partida[i][j];
			cout << "|";
		}
		cout<<endl;
	}
	cout<<endl;
}

//revisa todas las posibilidades en donde se pueden poner fichas
int Posibilidades(char partida[filas][columnas]){
	int cont = 0;

	for(int j = 0; j < columnas; j++){
		if(partida[0][j] == ' '){
			cont += 1;
		}
	}

	return cont;
}

//revisa si la IA gano
int VictoriaCPU(char partida[filas][columnas]){
    char ficha = 'X';
	// Chequeo horizontal
	for(int i = 0; i < filas; i++){
		for(int j = 0; j < columnas-3; j++){
			if(partida[i][j] == ficha){
				if(partida[i][j+1] == ficha){
					if(partida[i][j+2] == ficha){
						if(partida[i][j+3] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}

	// Chequeo vertical
	for(int j = 0; j < columnas; j++){
		for(int i = 0; i < filas - 3; i++){
			if(partida[i][j] == ficha){
				if(partida[i+1][j] == ficha){
					if(partida[i+2][j] == ficha){
						if(partida[i+3][j] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}

	// Chequeo diagonal principal
	for(int i = 0; i < filas - 3; i++){
		for(int j = 0; j < columnas-3; j++){
			if(partida[i][j] == ficha){
				if(partida[i+1][j+1] == ficha){
					if(partida[i+2][j+2] == ficha){
						if(partida[i+3][j+3] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}

	// Chequeo diagonal contraria
	for(int i = 0; i < 5; i++){
		for(int j = columnas-1; j > 2; j--){
			if(partida[i][j] == ficha){
				if(partida[i+1][j-1] == ficha){
					if(partida[i+2][j-2] == ficha){
						if(partida[i+3][j-3] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}

	return 0;
}

//revisa si el jugador ya gano
int VictoriaJugador(char partida[filas][columnas]){
    char ficha = 'O';
	// Chequeo horizontal
	for(int i = 0; i < filas; i++){
		for(int j = 0; j < columnas-3; j++){
			if(partida[i][j] == ficha){
				if(partida[i][j+1] == ficha){
					if(partida[i][j+2] == ficha){
						if(partida[i][j+3] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}

	// Chequeo vertical
	for(int j = 0; j < columnas; j++){
		for(int i = 0; i < filas-3; i++){
			if(partida[i][j] == ficha){
				if(partida[i+1][j] == ficha){
					if(partida[i+2][j] == ficha){
						if(partida[i+3][j] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}

	// Chequeo diagonal principal
	for(int i = 0; i < filas-3; i++){
		for(int j = 0; j< columnas-3; j++){
			if(partida[i][j] == ficha){
				if(partida[i+1][j+1] == ficha){
					if(partida[i+2][j+2] == ficha){
						if(partida[i+3][j+3] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}

	// Chequeo diagonal contraria
	for(int i = 0; i < 5; i++){
		for(int j = columnas-1; j > 2; j--){
			if(partida[i][j] == ficha){
				if(partida[i+1][j-1] == ficha){
					if(partida[i+2][j-2] == ficha){
						if(partida[i+3][j-3] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}

	return 0;
}

//asigna puntaje a la victoria del jugador o IA
double Heuristica(char partida[filas][columnas]){
	if (VictoriaCPU(partida)) return 1024;
	if (VictoriaJugador(partida)) return -1024;
	else return 0;
}

//Crea una nueva partida vacia
void NuevaPartida(char partida[filas][columnas]){
	for(int i = 0; i < filas; i++){
		for(int j = 0; j < columnas; j++){
			partida[i][j] = ' ';
		}
	}
}

//Turno jugador
int JuegaJugador(char partida[filas][columnas],char ficha){
	int columna;
	mostrarTablero(partida);
	cout << "Turno jugador: " << endl;
	cin >> columna;
	if(columna < 0 || columna > 7){
		mostrarTablero(partida);
		cout << "No existe esa columna." << endl;
		return JuegaJugador(partida,ficha);
	}
	if(partida[0][columna-1] != ' '){
		mostrarTablero(partida);
		cout << "La columna esta llena! Selecciona otra." << endl;
		return JuegaJugador(partida,ficha);
	}
	AplicarTirada(partida,columna-1,ficha);
	return 0;
}

//Turno IA
int JuegaCPU(char partida[filas][columnas], int dificultad,char ficha){
	mostrarTablero(partida);
	cout << "La IA esta jugando... \n";
	int columna = ElegirTirada(partida,dificultad, Posibilidades(partida), VictoriaCPU(partida), VictoriaJugador(partida), Heuristica(partida), dificultad);
	AplicarTirada(partida,columna,ficha);
	return 0;
}

//Seleccion de dificultad
void PantallaSeleccionDificultad(int *dificultad){
	cout << "Elija dificultad del juego:\n1) Facil.\n2) Medio.\n3) Dificil." << endl;

	char respuesta; cin >> respuesta;
	*dificultad = respuesta - '0'-1;
	if (*dificultad < 0 || *dificultad > 2){
		cout << "Dificultad invalida." << endl;
		PantallaSeleccionDificultad(dificultad);
	}
}

//Seleccion de quien comienza el juego (IA o Jugador)
int SeleccionInicio(){
	cout << "Elija quien comienza el juego:\n1) IA.\n2) Jugador." << endl;
	int eleccion; cin >> eleccion;
	if(eleccion == 1){
		return 1;
	} else if (eleccion == 2){
		return 0;
	} else {
		cout << "Opcion invalida.\n";
		SeleccionInicio();
	}
	return 0;
}

//Guarda la partida en el csv
void guardarPartida(string nombreArchivo, char partida[filas][columnas]){
	ofstream archivo(nombreArchivo);

	if(!archivo.is_open()){
		cout<<"Error al abrir el archivo CSV para guardar la partida"<<endl;
		return;
	}

	for(int i = 0; i < filas; i++){
		archivo<<"|";
		for(int j = 0; j < columnas; j++){
			archivo << partida[i][j];
			archivo<<"|";
		}
		archivo<<endl;
	}
	archivo.close();
}

//Desarrolla la partida
void Partida1jug(char partida[filas][columnas], bool inicial, int dificultad){
	int contador_jugadas = 1;
	while(1){
		inicial = (inicial == 0) ? 1 : 0;
		if(inicial){
			// Turno Jugador
			int EXIT = JuegaJugador(partida,'O');
			if(EXIT == 1){
				return;
			}
			if(VictoriaJugador(partida)){
			mostrarTablero(partida);
			cout << "Gana el jugador!!" << endl;
			return;
			}
		} else {
			// Turno IA
			JuegaCPU(partida,dificultad,'X');
			if(VictoriaCPU(partida)){
				mostrarTablero(partida);
				cout << "Gana la IA!!" << endl;
				return;
			}
		}

		// Si se llena el tablero
		if(Posibilidades(partida)==0){
			mostrarTablero(partida);
			cout << "Empate!!" << endl;
			return;
		}
		guardarPartida("ultimaPartida.csv", partida);

		contador_jugadas++;
	}
}

//Ajustes de la partida (dificultad - Inicio)
void ConfiguracionPartida(){
	char partida[filas][columnas]; 
	int dificultad;
	NuevaPartida(partida);
	PantallaSeleccionDificultad(&dificultad);
	bool inicial = SeleccionInicio();
	Partida1jug(partida, inicial, dificultad);
}

//Carga partida en caso de que exista una
void cargarPartida(string nombreArchivo) {
	char partida[filas][columnas]; 
	NuevaPartida(partida);
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo CSV para cargar la partida" << endl;
        return;
    }

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            char valor;
            archivo >> valor;
            if (valor == '|') {
                archivo.ignore();
            } else {
                partida[i][j] = valor;
            }
        }
    }

    archivo.close();
	Partida1jug(partida, 0, 1);
}

int main(){
	//cargarPartida("ultimaPartida.csv");
	
	while(1){
		cout << "---------- MENU ----------" << endl;
		cout << "1) Jugar nueva partida." << endl;
		cout << "2) Salir." << endl;
		string opcion; cin >> opcion;
		if(opcion == "1"){
			ConfiguracionPartida();
		} 
		else if(opcion == "2"){
			cout << "Nos vemos pronto!" << endl;
			break;
		} 
		else {
			cout << "Opcion invalida" << endl;
		}
	}
	return 0;
}