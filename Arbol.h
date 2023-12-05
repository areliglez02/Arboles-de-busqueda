#ifndef Arbol_H_INCLUDED
#define Arbol_H_INCLUDED
#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
struct Nodo {
    T elem;
    Nodo* izq;
    Nodo* der;

    Nodo(const T& elemento) : elem(elemento), izq(nullptr), der(nullptr) {}
};

template <typename T>
class Arbol
{
private:
    Nodo<T>* raiz;

    void insertaRecursivo(Nodo<T>*& nodo, const T& elemento);
    void eliminaRecursivo(Nodo<T>*& nodo, const T& elemento);

    Nodo<T>* hijoIzquierdo(Nodo<T>* nodo);
    Nodo<T>* hijoDerecho(Nodo<T>* nodo);
    Nodo<T>* localizaRecursivo(Nodo<T>* nodo, const T& elemento);

    T elementoMenor(Nodo<T>* nodo);
    T elementoMayor(Nodo<T>* nodo);
    int altura(Nodo<T>* nodo);
    int alturaIzquierda(Nodo<T>* nodo);
    int alturaDerecha(Nodo<T>* nodo);
    int factorEquilibrio(Nodo<T>* nodo);

    void recorrePreorder(Nodo<T>* nodo);
    void recorreInorder(Nodo<T>* nodo);
    void recorrePostorder(Nodo<T>* nodo);
    void anulaRecursivo(Nodo<T>*& nodo);

    void rotacionSimpleDerecha(Nodo<T>*& nodo);
    void rotacionSimpleIzquierda(Nodo<T>*& nodo);
    void rotacionDobleDerecha(Nodo<T>*& nodo);
    void rotacionDobleIzquierda(Nodo<T>*& nodo);

    void balanceo(Nodo<T>*& nodo);

public:
    Arbol() : raiz(nullptr) {}

    void inicializa();
    bool vacio() const;
    void inserta(const T& elemento);
    void elimina(const T& elemento);
    Nodo<T>* localiza(const T& elemento);
    T recupera(Nodo<T>* pos);
    void recorrePreorder();
    void recorreInorder();
    void recorrePostorder();
    void anula();
    T obtenerElementoMenor();
    T obtenerElementoMayor();
    int obtenerAltura();
    int obtenerAlturaIzquierda();
    int obtenerAlturaDerecha();
};

template <typename T>
void Arbol<T>::inicializa() {
    raiz = nullptr;
}

template <typename T>
bool Arbol<T>::vacio() const {
    return raiz == nullptr;
}

template <typename T>
void Arbol<T>::inserta(const T& elemento) {
    insertaRecursivo(raiz, elemento);
    balanceo(raiz);
}

template <typename T>
void Arbol<T>::insertaRecursivo(Nodo<T>*& nodo, const T& elemento) {
    if (nodo == nullptr) {
        nodo = new Nodo<T>(elemento);
    }else {
        if (elemento < nodo->elem) {
            insertaRecursivo(nodo->izq, elemento);
        }else {
            insertaRecursivo(nodo->der, elemento);
        }
    }
}

template <typename T>
void Arbol<T>::elimina(const T& elemento) {
    eliminaRecursivo(raiz, elemento);
    balanceo(raiz);
}

template <typename T>
void Arbol<T>::eliminaRecursivo(Nodo<T>*& nodo, const T& elemento) {
    if (nodo == nullptr) {
        return;
    }if (elemento < nodo->elem) {
        eliminaRecursivo(nodo->izq, elemento);
    }else if (elemento > nodo->elem) {
        eliminaRecursivo(nodo->der, elemento);
    }else {
        if (nodo->izq == nullptr) {
            Nodo<T>* temp = nodo->der;
            delete nodo;
            nodo = temp;
        }else if (nodo->der == nullptr) {
            Nodo<T>* temp = nodo->izq;
            delete nodo;
            nodo = temp;
        }else {
            Nodo<T>* sucesor = nodo->der;
            while (sucesor->izq != nullptr) {
                sucesor = sucesor->izq;
            }
            nodo->elem = sucesor->elem;

            eliminaRecursivo(nodo->der, sucesor->elem);
        }
    }
}

template <typename T>
Nodo<T>* Arbol<T>::hijoIzquierdo(Nodo<T>* nodo) {
    return (nodo != nullptr) ? nodo->izq : nullptr;
}

template <typename T>
Nodo<T>* Arbol<T>::hijoDerecho(Nodo<T>* nodo) {
    return (nodo != nullptr) ? nodo->der : nullptr;
}

template <typename T>
Nodo<T>* Arbol<T>::localiza(const T& elemento) {
    return localizaRecursivo(raiz, elemento);
}

template <typename T>
Nodo<T>* Arbol<T>::localizaRecursivo(Nodo<T>* nodo, const T& elemento) {
    if (nodo == nullptr || nodo->elem == elemento) {
        return nodo;
    }

    if (elemento < nodo->elem) {
        return localizaRecursivo(nodo->izq, elemento);
    }

    return localizaRecursivo(nodo->der, elemento);
}

template <typename T>
T Arbol<T>::recupera(Nodo<T>* pos) {
    if (pos == nullptr) {
        throw std::runtime_error("Posición nula, no se puede recuperar el elemento.");
    }

    return pos->elem;
}

template <typename T>
void Arbol<T>::recorrePreorder() {
    recorrePreorder(raiz);
    std::cout << std::endl;
}

template <typename T>
void Arbol<T>::recorrePreorder(Nodo<T>* nodo) {
    if (nodo != nullptr) {
        std::cout << nodo->elem << " ";
        recorrePreorder(nodo->izq);
        recorrePreorder(nodo->der);
    }
}

template <typename T>
void Arbol<T>::recorreInorder() {
    recorreInorder(raiz);
    std::cout << std::endl;
}

template <typename T>
void Arbol<T>::recorreInorder(Nodo<T>* nodo) {
    if (nodo != nullptr) {
        recorreInorder(nodo->izq);
        std::cout << nodo->elem << " ";
        recorreInorder(nodo->der);
    }
}

template <typename T>
void Arbol<T>::recorrePostorder() {
    recorrePostorder(raiz);
    std::cout << std::endl;
}

template <typename T>
void Arbol<T>::recorrePostorder(Nodo<T>* nodo) {
    if (nodo != nullptr) {
        recorrePostorder(nodo->izq);
        recorrePostorder(nodo->der);
        std::cout << nodo->elem << " ";
    }
}

template <typename T>
void Arbol<T>::anula() {
    anulaRecursivo(raiz);
}

template <typename T>
void Arbol<T>::anulaRecursivo(Nodo<T>*& nodo) {
    if (nodo != nullptr) {
        anulaRecursivo(nodo->izq);
        anulaRecursivo(nodo->der);
        delete nodo;
        nodo = nullptr;
    }
}

template <typename T>
T Arbol<T>::elementoMenor(Nodo<T>* nodo) {
    if (nodo == nullptr) {
        throw std::runtime_error("El árbol está vacío, no se puede obtener el elemento menor.");
    }

    while (nodo->izq != nullptr) {
        nodo = nodo->izq;
    }

    return nodo->elem;
}

template <typename T>
T Arbol<T>::elementoMayor(Nodo<T>* nodo) {
    if (nodo == nullptr) {
        throw std::runtime_error("El árbol está vacío, no se puede obtener el elemento mayor.");
    }

    while (nodo->der != nullptr) {
        nodo = nodo->der;
    }

    return nodo->elem;
}

template <typename T>
int Arbol<T>::altura(Nodo<T>* nodo) {
    if (nodo == nullptr) {
        return 0;
    }

    int alturaIzq = altura(nodo->izq);
    int alturaDer = altura(nodo->der);

    return (alturaIzq > alturaDer) ? alturaIzq + 1 : alturaDer + 1;
}

template <typename T>
int Arbol<T>::alturaIzquierda(Nodo<T>* nodo) {
    if (nodo == nullptr) {
        return 0;
    }

    return altura(nodo->izq);
}

template <typename T>
int Arbol<T>::alturaDerecha(Nodo<T>* nodo) {
    if (nodo == nullptr) {
        return 0;
    }

    return altura(nodo->der);
}

template <typename T>
int Arbol<T>::factorEquilibrio(Nodo<T>* nodo) {
    if (nodo == nullptr) {
        return 0;
    }

    return alturaDerecha(nodo) - alturaIzquierda(nodo);
}

template <typename T>
void Arbol<T>::balanceo(Nodo<T>*& nodo) {
    if (factorEquilibrio(nodo) < -1) {
        if (factorEquilibrio(nodo->izq) == -1) {
            rotacionSimpleDerecha(nodo);
        }
        else {
            rotacionDobleDerecha(nodo);
        }
    }
    else if (factorEquilibrio(nodo) > 1) {
        if (factorEquilibrio(nodo->der) == 1) {
            rotacionSimpleIzquierda(nodo);
        }
        else {
            rotacionDobleIzquierda(nodo);
        }
    }
}

template <typename T>
void Arbol<T>::rotacionSimpleDerecha(Nodo<T>*& nodo) {
    Nodo<T>* aux1 = nodo->izq;
    Nodo<T>* aux2 = aux1->der;
    nodo->izq = aux2;
    aux1->der = nodo;
    nodo = aux1;
}

template <typename T>
void Arbol<T>::rotacionSimpleIzquierda(Nodo<T>*& nodo) {
    Nodo<T>* aux1 = nodo->der;
    Nodo<T>* aux2 = aux1->izq;
    nodo->der = aux2;
    aux1->izq = nodo;
    nodo = aux1;
}

template <typename T>
void Arbol<T>::rotacionDobleDerecha(Nodo<T>*& nodo) {
    rotacionSimpleIzquierda(nodo->izq);
    rotacionSimpleDerecha(nodo);
}

template <typename T>
void Arbol<T>::rotacionDobleIzquierda(Nodo<T>*& nodo) {
    rotacionSimpleDerecha(nodo->der);
    rotacionSimpleIzquierda(nodo);
}

template <typename T>
T Arbol<T>::obtenerElementoMenor() {
    return elementoMenor(raiz);
}

template <typename T>
T Arbol<T>::obtenerElementoMayor() {
    return elementoMayor(raiz);
}

template <typename T>
int Arbol<T>::obtenerAltura() {
    return altura(raiz);
}

template <typename T>
int Arbol<T>::obtenerAlturaIzquierda() {
    return alturaIzquierda(raiz);
}

template <typename T>
int Arbol<T>::obtenerAlturaDerecha() {
    return alturaDerecha(raiz);
}
#endif // Arbol_H_INCLUDED

