#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include <stdexcept>
#include "Node.h"

using namespace std;

template <typename E>
class LinkedList
{
private:
    Node<E>* head;
    Node<E>* tail;
    Node<E>* current;
    int size;
    Node<E>* searchPrevious(Node<E>* pNode) {
        if (current == head) {
            return NULL;
        }
        Node<E> *res = head;
        while (res->next != current) {
            res = res->next;
        }
        return res;
    }


public:
    LinkedList() {
        current = tail = head = new Node <E> ();
        size = 0;
    }
    ~LinkedList() {
        clear();
        delete head;

    }
    void previous() {
        if (current != head) {
            current = searchPrevious(current);
        }
    }

    void insert (E pElement){
    current->next = new Node <E> (pElement, current->next);
    if (current == tail){
        tail = current->next;
        }
    size ++;
    }

    void append (E pElement){
        tail -> next = new Node <E> (pElement);
        tail = tail -> next;
        size ++;
    }

    E remove() throw(runtime_error){
    if (current == tail){

        throw runtime_error("No hay elemento");
        }
    E res = current -> next -> element;
    Node <E> *temp = current -> next;
    current->next = current->next->next;
    if (temp == tail){

        tail = current;
    }
    delete temp;
    size --;
    return res;
    }

    void clear(){
    current = head -> next;
    while (head -> next != NULL){
        head -> next = head -> next -> next;
        delete current;
        current = head -> next;
    }
    tail = current = head;
    size = 0;
    }

    E getElement() throw(runtime_error){
    if (current -> next == NULL){
        throw runtime_error("No hay elemento");
        }
    if (current == NULL){

        throw runtime_error("La lista est?vac�a");
        }
    return current -> next -> element;

    }

    void goToStart(){
        current = head;
    }

    void goToEnd(){
        current = tail;
    }

    void goToPos(int nPos)throw(runtime_error){
       if ((nPos < 0) || (nPos > size)) {
            throw runtime_error("Fuera de rango");
        }
        current = head;
        for (int i = 0; i < nPos; i++) {
            current = current->next;
        }

    }

    void next(){
        if (current != tail){
            current = current -> next;
        }
    }

    int getPos(){
        int pos = 0;
        Node<E> * temp = head;
        while (temp != current){

            pos++;
            temp = temp -> next;
        }
        return pos;
    }
    int getSize(){
        return size;
    }

    void impri(){
        cout << "Su lista es: [ ";

        Node<E> *temporal = head->next;
        for(int i = 0; i < size; i++){
                if(current ==temporal ){cout << "*";}

                cout << temporal->element <<  ",";
                temporal = temporal->next;

            }
        cout << "Fin de la lista ]" << endl << endl;
}
    // Invertir la lista
    void invertir()
    {
    Node<E> *prev = NULL;
    Node<E> *next = NULL;
    Node<E> *temp = head->next;

    while (temp) {
        next = temp->next;
        temp->next = prev;
        prev = temp;
        temp = next;
    }
    head->next = prev;
    }

    void concatena()
    {
        int largoF = 0;
        LinkedList<E> *listaEnlazadaL = new LinkedList<E>();
        listaEnlazadaL->goToStart();
        int largoL;
        cout << "Cantidad de valores que desea agregar a L: ";
        cin >> largoL;
        cout << endl;
        largoF += largoL;
        while (largoL != 0) {
            int valorL;
            cout << "Valor para agregar a L: " ;
            cin >>valorL ;

            listaEnlazadaL->append(valorL);
            cout << "Primera Lista " << endl ;
            listaEnlazadaL->impri();
            largoL--;
            }

        LinkedList<E> *listaEnlazadaM = new LinkedList<E>();
        listaEnlazadaM->goToStart();
        int largoM;
        cout << "Cantidad de valores que desea agregar a M: ";
        cin >> largoM;
        cout << endl;
        largoF += largoM;
        while (largoM != 0) {
            int valorM;
            cout << "Valor para agregar a L: " ;
            cin >>valorM;

            listaEnlazadaM->append(valorM);
            cout << "Segunda Lista " << endl;
            listaEnlazadaM->impri();
            largoM--;
            }

        LinkedList<E> *listaEnlazadaF = new LinkedList<E>();
        listaEnlazadaF->goToStart();

        Node<E> *tempL = listaEnlazadaL->head->next;
        Node<E> *tempM = listaEnlazadaM->head->next;

        while (tempL) {
            listaEnlazadaF->append(tempL->element);
            tempL = tempL->next;
            listaEnlazadaF->next();

        }

        while (tempM) {
            listaEnlazadaF->append(tempM->element);
            tempM = tempM->next;
            listaEnlazadaF->next();
        }
        cout << endl;
        cout << "Lista Concatenada " << endl;
        listaEnlazadaF->impri();

    }
    void intercambia(){
        LinkedList<E> *listaEnlazadaI = new LinkedList<E>();
        listaEnlazadaI->goToStart();
        int largoI;
        cout << "Cantidad de valores que desea agregar a I: ";
        cin >> largoI;
        cout << endl;
        while (largoI != 0) {
            int valorI;
            cout << "Valor para agregar a I: " ;
            cin >>valorI;

            listaEnlazadaI->append(valorI);
            cout << "Lista para Intercambio " << endl ;
            listaEnlazadaI->impri();
            largoI--;
            }

        Node<E> *x ;
        Node<E> *y ;
        Node<E> *temp1 = listaEnlazadaI->head->next;
        Node<E> *temp2;
        Node<E> *temp3;

        cout << "Nodos que desea intercambiar" << endl;
        cout << "Posici�n de los dos valores que desea apuntar" << endl;

        cout << "Posicion 1" << endl;
        int valor1;
        cin >> valor1;
        listaEnlazadaI->goToPos(valor1);
        x = listaEnlazadaI->current;


        cout << "Posicion 2" << endl;
        int valor2;
        cin >> valor2;
        listaEnlazadaI->goToPos(valor2);
        y = listaEnlazadaI->current;



        temp3 = x;
        temp2 = y->next;
       temp1 ->next = y;
        y->next = x->next;
        x->next->next= temp3;
        temp3->next = temp2;

        listaEnlazadaI->impri();




    }
};

#endif // LINKEDLIST_H
