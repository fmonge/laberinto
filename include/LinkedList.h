#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include "Node.h"

#include <stdlib.h>
#include <stdexcept>
#include <iostream>



using namespace std;

template <typename E>

class LinkedList{

private:

    Node<E>*head;
    Node<E>*tail;
    Node<E>*current;
    int size;

public:

    LinkedList(){
        current = tail = head = new Node<E>();
        size = 0;
    }

    ~LinkedList(){
        clear();
        delete head;
    }

    void insert(E pElemet){
        current->next = new Node<E>(pElemet, current->next);
        if(current == tail)
            tail = current->next;
        size++;
    }

    void append(E pElement){
        tail->next = new Node<E>(pElement);
        tail = tail->next;
        //tail->next = new Node<E>(pElement,tail=tail->next);
        size++;
    }

    E remove()throw(runtime_error){
        if(current == tail)
            throw runtime_error("No hay elemento para borrar");
        E res = current->next->element;
        Node<E>*tmp = current->next;
        if(current->next == tail)
                tail = current;
        current->next=current->next->next;
        delete tmp;
        size--;
        return res;
    }


    void clear(){        /*
        Clear
        0. puntero tmp = head->next
        1. Repetir hasta que head->next == null
                1.1 head->next = head->next->next
                1.2 borrar el tmp
                1.3 tmp = head->next
        2. tail = current = head
        3. size = 0
        */
        current = head->next;
        while(head->next !=NULL)
        {
                head->next = head->next->next;
                delete current;
                current = head->next;
        }
        tail = current = head;
        size = 0;
    }


    E getElement() throw(runtime_error){
        if(size == 0 || current == NULL)
            return false;
        return current->next->element;
    }

    void goToPos(int pPos)throw(runtime_error){
        if(pPos < 0 || pPos > size)
            throw runtime_error("Posicion no valida");
        current = head;
        for(int i=0; i!=pPos; i++)
            current = current->next;
    }

    void goToEnd(){ current = tail; }

    void goToStart(){current = head; }


    void next(){
        if(current!=tail)
            current = current->next;
    }

    int getPos(){
        if(current == head)
            return 1;
        if(current == tail)
            return size;
        int pos = 0;
        Node<E>* tmp = head;
        for (pos; tmp != current; pos++)
            tmp = tmp->next;
        delete tmp;
        return pos;

    }

    int getSize(){return size;}

    void printList(){
        Node<E>* tmp = head->next;
        for(; tmp!=NULL; tmp=tmp->next)
            cout << " - " << tmp->element << " - ";
        cout << endl;
        //delete tmp;
    }

    void addList(LinkedList<E>* lista){
        // Le agrega otra lista
        Node<E>* tmp = tail->next;
        Node<E>* tmp1 = lista->head;
        tail->next = lista->head->next;
        tail = lista->tail;
        delete tmp;
        delete tmp1;
    }

    void previous(){
        if(current !=head){
            Node<E>* tmp = head;
            while(tmp->next !=current)
                tmp = tmp->next;
            current = tmp;
            delete tmp;
        }
    }
};
#endif // LINKEDLIST_H
