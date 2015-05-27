#include <iostream>
#include <time.h>
#include <ctime>

#include "include/grafo.h"

using namespace std;

void mensajeFindelJuego(){
    cout<<" _____ _          _     _       __                 "<<endl;
    cout<<"|   __|_|___    _| |___| |   __|  |_ _ ___ ___ ___ "<<endl;
    cout<<"|   __| |   |  | . | -_| |  |  |  | | | -_| . | . |"<<endl;
    cout<<"|__|  |_|_|_|  |___|___|_|  |_____|___|___|_  |___|"<<endl;
    cout<<"                                          |___|    "<<endl;
}

int main()
{
    int filas=3;
    int columnas=3;
    int nivel=0;
    int puntuaje=0;
    int extra=10;
    int tiempo=10;

    if (filas > 45)
        filas = 45;
    if (columnas > 72)
        columnas = 72;
    cout<<"Tiempo: "<<tiempo<<endl;
    while (true){
    while (true){
        nivel++;
        if (nivel>99)
            nivel = 99;

        Grafo Laberinto(filas, columnas,nivel);

        clock_t start = clock();
        puntuaje+=Laberinto.jugar();
        clock_t end = clock();

        double segundos = double(end-start)/CLOCKS_PER_SEC;

        if (tiempo<segundos)
            break;
        if (nivel==8)
            extra+=30;
        if (nivel==11)
            extra+=30;
        if (nivel==17)
            extra+=30;
        if (nivel>=22)
            extra+=15;

        tiempo=(tiempo-segundos)+extra;
        cout<<"Tiempo para el siguiente nivel: "<<tiempo<<" segundos"<<endl;
        filas++;
        columnas++;
    }

    mensajeFindelJuego();
    cout<<endl;
    cout<<"Su puntuaje = "<<puntuaje<<endl;
    char t=getch();
    if (t=='r')
        continue;
    break;
    }
}
