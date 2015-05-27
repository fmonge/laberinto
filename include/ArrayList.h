
#define ARRAYLIST_H
#include <string>
#include <limits>
#include <stdexcept>

using namespace std;
template <typename E>
class ArrayList {

E* elements;
int maxi;
int siz;
int pos;

public:
    ArrayList(int pMax = 1023){
    elements = new E[pMax];
    maxi = pMax;

    siz = 0;
    pos = 0;
    }

    ~ArrayList(){
        delete [] elements;
    }

    void insert(E pElement) throw(runtime_error) {
        if (siz == maxi)
            throw runtime_error("List full");

        for (int i = siz; i > pos; i--)
            elements[i] = elements[i - 1];
        elements[pos] = pElement;
        siz++;
    }
    void append(E pElement) throw(runtime_error) {
        if (siz == maxi)
            throw runtime_error("List is full!!");

        elements[siz] = pElement;
        siz++;
    }
    E remove() throw(runtime_error) {
        if (siz == 0)
            return("Empty list!!");

        if ((pos < 0) || (pos >= siz))
            return("Out of limits");

        E res = elements[pos];
        for (int i = pos; i < siz - 1; i++)
            elements[i] = elements[i + 1];

        siz--;
        if (siz==pos)
            pos--;
        return res;
    }
    void clear() {
        siz = 0;
        pos = 0;
        delete [] elements;
        elements = new E[maxi];
    }
    E getElement() throw(runtime_error) {
        if ((pos < 0) || (pos >= siz))
            return("Out of limits!!");
        return elements[pos];
    }

    void goToStart(){pos = 0;}

    void goToEnd(){pos = siz-1;}

    void goToPos(int nPos) throw(runtime_error) {
        if ((nPos < 0) || (nPos > siz))
            throw runtime_error("############    Out of limits!!    ############");
        pos = nPos;
    }
    void previous() {
        if (pos > 0)
            pos--;
    }

    void next() {
        if (pos < siz-1)
            pos++;
    }
    int getPos() {return pos;}

    int getSize() {return siz;}
};
