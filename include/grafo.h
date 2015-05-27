#ifndef GRAFO_H
#define GRAFO_H
#include "LinkedList.h"
#include "ArrayList.h"
#include <winbgim.h>
#include <time.h>

#define largoCeldas 8
#define largoArco 16


class Grafo
{
    private:
        int filas;
        int columnas;
        int cantidadNodos;
        bool *visitados ;
        int tortuga=0;
        int grados=270;
        int items;
        int nivel;
        int ItemsAleatorios[100];
        LinkedList<int> itemsAleatorio;
        LinkedList<int>* ListadeAdyacencia;
        LinkedList<int>*laberinto;
        ArrayList<int> *listaVisitados;


    public:
        Grafo(int pFilas, int pColumnas,int pNivel) {
            initwindow(pColumnas*(largoArco+1),pFilas*(largoArco+4));
            filas = pFilas;
            columnas = pColumnas;
            cantidadNodos = filas*columnas;
            items = 0;
            nivel=pNivel;
            ListadeAdyacencia= new LinkedList<int>[cantidadNodos];
            visitados = new bool [cantidadNodos];
            laberinto = new LinkedList<int>[cantidadNodos];

            dibujaLaberinto();

        }virtual ~Grafo() {}

    void agregarVecinosGrafo(){
        for (int i =0; i < cantidadNodos; i++){
            if ((i % columnas) != 0)
                ListadeAdyacencia[i].append(i - 1);
            if (((i + 1) % columnas) != 0)
                ListadeAdyacencia[i].append(i + 1);
            if ((i - columnas) >= 0)
                ListadeAdyacencia[i].append(i - columnas);
            if ((i + columnas) < cantidadNodos)
                ListadeAdyacencia[i].append(i + columnas);}
    }

    void crearLaberinto(int ini,int infiniteRandom){
        int random;
        visitados[ini] = 1;
        while (ListadeAdyacencia[ini].getSize() > 0){

            for(int i=0;i<infiniteRandom;i++){
            random = rand()%ListadeAdyacencia[ini].getSize();}
            crearLaberintoAux(ini,random,infiniteRandom);
        }
    }

    void crearLaberintoAux(int ini,int random,int infiniteRandom){

        ListadeAdyacencia[ini].goToPos(random);
        int valorNodo = ListadeAdyacencia[ini].getElement();
        ListadeAdyacencia[ini].remove();
        ListadeAdyacencia[ini].goToStart();

        if(visitados[valorNodo] == 0){
            visitados[valorNodo] = 1;
            laberinto[ini].append(valorNodo);
            laberinto[valorNodo].append(ini);
            crearLaberinto(valorNodo,infiniteRandom);
        }
    }

    void dibujaLaberinto(){
        for (int i = 0; i < cantidadNodos ; i++){
            visitados[i] = 0;}
        agregarVecinosGrafo();
        srand (time(NULL));
        int infiniteRandom= rand()%1001+1;
        crearLaberinto(0,1);

        dibujarArco();
        dibujarNodos();
        ponerItems();
    }


    void dibujarNodos(){
        setfillstyle(SOLID_FILL, 15); // 15 = blanco
        for (int f = 0; f < filas ; f++){
            for (int c = 0; c < columnas ; c++){
                int x = largoCeldas + largoCeldas * 2 * c;
                int y = largoCeldas + largoCeldas * 2 * f;
                if (c+1==columnas&&f+1==filas)
                    setfillstyle(USER_FILL,10);
                bar(x, y, x + largoCeldas, y + largoCeldas);}
        }
    }

    void dibujarArco(){
        setfillstyle(SOLID_FILL, 30);
        for(int n=0; n<cantidadNodos; n++){
            for(laberinto[n].goToStart();
                laberinto[n].getPos() < laberinto[n].getSize();
                laberinto[n].next()){

                int x1 = (n % columnas) * largoCeldas * 2 + largoCeldas;
                int y1 = (n / columnas) * largoCeldas * 2 + largoCeldas;
                int x2 = (laberinto[n].getElement() % columnas) * largoCeldas * 2 + largoCeldas*2;
                int y2 = (laberinto[n].getElement() / columnas) * largoCeldas * 2 + largoCeldas*2;

                bar(x1, y1, x2, y2);
            }
        }
    }







    bool validarMovimiento(int numero){
        for(laberinto[tortuga].goToStart();
            laberinto[tortuga].getPos() < laberinto[tortuga].getSize();
            laberinto[tortuga].next()){

            if(laberinto[tortuga].getElement()==numero)
                return true;
        }
        for(laberinto[numero].goToStart();
            laberinto[numero].getPos()<laberinto[numero].getSize();
            laberinto[numero].next()){

            if (laberinto[numero].getElement()==tortuga)
                return true;
        }
        return false;
    }

    void botones(){
        char  boton = getch();
        cout<<boton<<endl;
        if(boton=='w'||boton=='H'){
            if ((tortuga/columnas)!= 0){
                if(validarMovimiento(tortuga - columnas))
                    tortuga=tortuga - columnas;
            }
        }
        if(boton=='s'||boton=='P'){
            if((tortuga/columnas)!=(filas-1)){
                if(validarMovimiento(tortuga + columnas))
                    tortuga=tortuga+columnas;
            }
        }
        if(boton=='a'||boton=='K'){
            if(validarMovimiento(tortuga-1)){
                if(tortuga%columnas!=0)
                    tortuga=tortuga-1;
            }
        }
        if(boton=='d'||boton=='M'){
            if((tortuga+1)%(columnas)!=0){
                 if(validarMovimiento(tortuga+1))
                    tortuga = tortuga+1;
            }
        }
    }
    void Tortuga(int posicionAnte){

        setfillstyle(USER_FILL,15);
        int x1=(posicionAnte % columnas) * largoArco + largoCeldas;
        int y1=(posicionAnte / columnas) * largoArco + largoCeldas;
        int x2=(posicionAnte % columnas) * largoArco + largoCeldas * 2;
        int y2=(posicionAnte / columnas) * largoArco + largoCeldas * 2;
        if (posicionAnte==(filas*columnas-1))
                setfillstyle(USER_FILL,10);
        bar(x1,y1,x2,y2);

        int x =((tortuga % columnas) * largoArco + largoCeldas)+4;
        int y =((tortuga / columnas) * largoArco + largoCeldas)+4;

        setcolor(4);
        setfillstyle(SOLID_FILL, 4);
        fillellipse(x,y,3.5,3.5);
    }
    void ponerItems(){

        for(int i=0;i<nivel;i++){
            int random= rand()%(cantidadNodos-1);
            ItemsAleatorios[i]=random;
            setfillstyle(USER_FILL,9);
            int x1=(ItemsAleatorios[i] % columnas) * largoArco + largoCeldas;
            int y1=(ItemsAleatorios[i] / columnas) * largoArco + largoCeldas;
            int x2=(ItemsAleatorios[i] % columnas) * largoArco + largoCeldas * 2;
            int y2=(ItemsAleatorios[i] / columnas) * largoArco + largoCeldas * 2;
            if (ItemsAleatorios[i]==(filas*columnas-1)){
                setfillstyle(USER_FILL,10);
                bar(x1,y1,x2,y2);}
            setcolor(3);
            setfillstyle(SOLID_FILL, 2);
            fillellipse(x1+4,y1+4,3.5,3.5);

        }
        /*for(int i=0;i<cantidadNodos;i++){
            for(ListadeAdyacencia[i].goToStart();ListadeAdyacencia[i].getPos()<ListadeAdyacencia[i].getSize();ListadeAdyacencia[i].next()){
                cout<<ListadeAdyacencia[i].getElement()<<endl;
            }
        }*/
    }

    int victoria(){
        cout<<"Muy bien!!"<<endl;
        cout<<"Siguiente: nivel "<<nivel+1<<endl;
        cout<<endl;
        ListadeAdyacencia[0].clear();
        closegraph();
        return items;
    }


    int jugar(){
        int posicionAnte=tortuga;
        while(true){
            if ((tortuga==cantidadNodos-1)&&items==nivel)
                return victoria();

            for(int i=0;i<nivel;i++){
                if (tortuga==ItemsAleatorios[i]){
                    items++;
                    ItemsAleatorios[i]=cantidadNodos+5;
                }
            }
            Tortuga(posicionAnte);
            posicionAnte=tortuga;
            botones();
        }
    }


};

#endif // GRAFO_H
