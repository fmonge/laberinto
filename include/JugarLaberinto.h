#ifndef JUGARLABERINTO_H
#define JUGARLABERINTO_H
#include <winbgim.h>
#define PI 3.14159265358979
#include "LinkedList.h"
#include "ArrayList.h"
#include <cmath>
#define CELDAS 8
#define ARCOS 16

class JugarLaberinto
{
    private:
        int filas;
        int columnas;
        int cantidadNodos;
        LinkedList<int> *laberinto;
        bool *visitados ;
        int tortuga=0;
        int grados=270;

    public:
        JugarLaberinto(int pFilas, int pColumnas,LinkedList pLaberinto) {
        filas = pFilas;
        columnas = pColumnas;
        cantidadNodos = filas*columnas;
        laberinto = pLaberinto;




        }
        virtual ~JugarLaberinto() {}

    bool validar(int numero){

        for(laberinto[tortuga].goToStart();
            laberinto[tortuga].getPos() < laberinto[tortuga].getSize();
            laberinto[tortuga].next()){

                if(laberinto[tortuga].getElement()==numero){
                    return true;
                }
            }
            for(laberinto[numero].goToStart();
                laberinto[numero].getPos()<laberinto[numero].getSize();
                laberinto[numero].next()){
                    if (laberinto[numero].getElement()==tortuga){
                        return true;
                    }
                }
            return false;

    }

    void botones(){
       char  boton = getch();

        if(boton=='w'||boton=='H'){
            if ((tortuga/columnas)!= 0){
                if(validar(tortuga - columnas))
                tortuga=tortuga - columnas;
            }
        }
        if(boton=='s'||boton=='P'){
            if((tortuga/columnas)!=(filas-1)){
                if(validar(tortuga + columnas))
                tortuga=tortuga+columnas;
            }
        }
        if(boton=='a'||boton=='K'){
            if(validar(tortuga-1)){
                if(tortuga%columnas!=0)
                tortuga=tortuga-1;
            }
        }
        if(boton=='d'||boton=='M'){
            if((tortuga+1)%(columnas)!=0){
                 if(validar(tortuga+1))
                    tortuga = tortuga+1;
            }
        }
    }

    void Tortuga(){

        setfillstyle(USER_FILL,10);

        bar((((cantidadNodos-1) % columnas) * ARCOS + CELDAS), (((cantidadNodos-1) / columnas) * ARCOS + CELDAS),
             (((cantidadNodos-1) % columnas) * ARCOS + CELDAS * 2), (((cantidadNodos-1) / columnas) * ARCOS + CELDAS * 2));


        int x =((tortuga % columnas) * ARCOS + CELDAS)+4;
        int y =((tortuga / columnas) * ARCOS + CELDAS)+4;
        //Esta parte dibuja el cuerpo primero y cambia el color del lapiz para dibujar la tortuga
        //en un diferente color
        setlinestyle(0,0,1);
        setcolor(4);
        setfillstyle(SOLID_FILL, 4);
        int grad = grados;
        fillellipse(x,y,3.5,3.5);

        //Aqui dibuja la cabeza
        int nuevaDistanciaX = 3.5 * cos(grad*PI/180);
        int nuevaDistanciaY = 3.5 * sin(grad*PI/180);
        int xtemp = nuevaDistanciaX+x;
        int ytemp = nuevaDistanciaY+y;
        setfillstyle(SOLID_FILL, 4);
        fillellipse(xtemp,ytemp,1.5,1.5);

        //Esta parte dibuja las patas de la tortuga
        int patas = 4;
        grad-=45;
        while (patas >0){
            int nuevaDistanciaX = 4.2 * cos(grad*PI/180);
            int nuevaDistanciaY = 4.2 * sin(grad*PI/180);
            int xtemp = nuevaDistanciaX+x;
            int ytemp = nuevaDistanciaY+y;
            fillellipse(xtemp,ytemp,1,1);
            grad-=90;
            patas--;
        }


    }

    void victoria(){
        cout<<" _______                                         _ _ "<<endl;
        cout<<"(  _____)                         _             | | |"<<endl;
        cout<<"| |  ___ _____ ____  _____  ___ _| |_ _____  ___| | |"<<endl;
        cout<<"| | (_  (____ |  _ \(____ |/___|_   _) ___ |/___)_|_|"<<endl;
        cout<<"| |___) / ___ | | | / ___ |___ | | |_| ____|___ |_ _ "<<endl;
        cout<<" |_____/|_____|_| |_|_____(___/  |___)_____|___/|_|_|"<<endl;

    }


    void jugar(){
        while(true){
            if (tortuga==cantidadNodos-1){
                victoria();
                closegraph();}


            Tortuga();
            botones();
    }
};

#endif // JUGARLABERINTO_H
