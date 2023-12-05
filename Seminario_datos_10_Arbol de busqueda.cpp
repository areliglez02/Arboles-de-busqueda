#include <iostream>
#include "Arbol.h"

using namespace std;

int main() {

    Arbol<int> miArbol;
    int elemento;
    int num;
    int elementoAEliminar;
    int repite=1;

    std::cout << "\n Digite la cantidad de elementos a insertar en el arbol: ";
    std::cin >> num;

    for (int i = 0; i < num; ++i) {
        std::cout << "\n Ingrese el elemento " << (i + 1) << ": ";
        std::cin >> elemento;
        miArbol.inserta(elemento);
    }
do{
    std::cout << "\n\n\t\t\t--- ARBOL ---" << std::endl;

    std::cout << "\n Elemento Menor: " << miArbol.obtenerElementoMenor();
    std::cout << std::endl << std::endl;

    std::cout << "\n Elemento Mayor: " << miArbol.obtenerElementoMayor();
    std::cout << std::endl << std::endl;

    std::cout << "\n Altura del arbol: " << miArbol.obtenerAltura();
    std::cout << std::endl << std::endl;

    std::cout << "\n Altura del Subarbol Izquierdo: " << miArbol.obtenerAlturaIzquierda();
    std::cout << std::endl << std::endl;

    std::cout << "\n Altura del Subarbol Derecho: " << miArbol.obtenerAlturaDerecha();
    std::cout << std::endl << std::endl;

    std::cout << "\n Recorrido Preorder: ";
    miArbol.recorrePreorder();
    std::cout << std::endl << std::endl;

    std::cout << "\n Recorrido Inorder: ";
    miArbol.recorreInorder();
    std::cout << std::endl << std::endl;

    std::cout << "\n Recorrido Postorder: ";
    miArbol.recorrePostorder();
    std::cout << std::endl << std::endl;

    std::cout << "\n Ingrese el elemento que desea eliminar: ";
    std::cin >> elementoAEliminar;
    miArbol.elimina(elementoAEliminar);


    std::cout << "\n Arbol despues de eliminar " << elementoAEliminar << ":" << std::endl;
    std::cout << "\n Recorrido Inorder: ";
    miArbol.recorreInorder();
    std::cout << "**********" << std::endl;
} while (repite);
    return 0;
}