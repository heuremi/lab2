#pragma once
#include <bits/stdc++.h>
using namespace std;

const int filas = 6;
const int columnas = 7;

class Partida
{
    private:
        int profundidad; 
        int tableroActual[6][7];
    public:
        Partida(int prof){
            profundidad = prof;
            for(int i = 0; i < filas; i++){
                for(int j = 0; j < columnas; j++){
                    tableroActual[i][j] = 0;
                }
            }
        }
        char getPieza(int fila, int columna){
            switch(tableroActual[fila][columna]){
                case 0:
                    return ' ';
                case 1: 
                    return 'X';
                case 2:
                    return 'O'; 
            }
            return 'a';
        }
        void mostrarTablero(){
            for(int i = 0; i < filas; i++){
                cout << "|";
                for(int j = 0; j < columnas; j++){
                    switch(tableroActual[i][j]){
                        case 0:
                            cout<<" ";
                        case 1: 
                            cout<<"X";
                        case 2:
                            cout<<"O"; 
                    }
                    cout << "|";
                }
                cout<<endl;
            }
            cout<<endl;
        }
        bool columnaLlena(int col) {
            for(int i=0; i< filas;i++){
                if(tableroActual[i][col] == 0){
                    return false;
                }
            }
            return true;
        }
        bool hacerMovimiento(int columnaActual, char jugador){
            if(columnaActual < 0 || columnaActual >= columnas || columnaLlena(columnaActual)){
                return false;
            }

            for(int i = filas - 1; i >= 0; i--){
                if (tableroActual[i][columnaActual] == 0) {
                    tableroActual[i][columnaActual] = jugador;
                    return true;
                }
            }
            return false;
        }

        bool ganador(int jugador) {
            //horizontal
            for (int i = 0; i < filas; i++) {
                for (int j = 0; j <= columnas - 4; j++) {
                    bool win = true;
                    for (int k = 0; k < 4; k++) {
                        if (tableroActual[i][j + k] != jugador) {
                            win = false;
                            break;
                        }
                    }
                    if (win) {
                        return true;
                    }
                }
            }

            // Vertical
            for (int j = 0; j < columnas; j++) {
                for (int i = 0; i <= filas - 4; i++) {
                    bool win = true;
                    for (int k = 0; k < 4; k++) {
                        if (tableroActual[i + k][j] != jugador) {
                            win = false;
                            break;
                        }
                    }
                    if (win) {
                        return true;
                    }
                }
            }

            // Diagonal ascendente
            for (int i = filas - 1; i >= filas - 3; i--) {
                for (int j = 0; j <= columnas - 4; j++) {
                    bool win = true;
                    for (int k = 0; k < 4; k++) {
                        if (tableroActual[i - k][j + k] != jugador) {
                            win = false;
                            break;
                        }
                    }
                    if (win) {
                        return true;
                    }
                }
            }

        // 4 en diagonal ARREGLAR
        for (int row = 0; row <= filas - 4; ++row) {
            for (int col = 0; col <= columnas - 4; ++col) {
                bool win = true;
                for (int i = 0; i < 4; ++i) {
                    if (tableroActual[row + i][col + i] != jugador) {
                        win = false;
                        break;
                    }
                }
                if (win) {
                    return true;
                }
            }
        }
        return false;
    }
};