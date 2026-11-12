#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

struct Nodo {
    int dato;
    Nodo* izq;
    Nodo* der;
};

Nodo* crearNodo(int numero) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = numero;
    nuevo->izq = nullptr;
    nuevo->der = nullptr;
    return nuevo;
}

int obtenerAltura(Nodo* nodo) {
    if (nodo == nullptr) return 0;
    return 1 + max(obtenerAltura(nodo->izq), obtenerAltura(nodo->der));
}

void llenarMatriz(vector<string>& lienzo, Nodo* nodo, int fila, int col, int separacion) {
    if (nodo == nullptr) return;

    // Escribir el número en la posición actual
    string texto = to_string(nodo->dato);
    for (int i = 0; i < (int)texto.size(); i++) {
        if (col + i < (int)lienzo[fila].size()) {
            lienzo[fila][col + i] = texto[i];
        }
    }

    // Dibujar rama izquierda y bajar recursivamente
    if (nodo->izq != nullptr) {
        lienzo[fila + 1][col - separacion / 2] = '/';
        llenarMatriz(lienzo, nodo->izq, fila + 2, col - separacion, max(1, separacion / 2));
    }

    // Dibujar rama derecha y bajar recursivamente
    if (nodo->der != nullptr) {
        lienzo[fila + 1][col + separacion / 2 + (int)texto.size() - 1] = '\\';
        llenarMatriz(lienzo, nodo->der, fila + 2, col + separacion, max(1, separacion / 2));
    }
}

void mostrarArbolVertical(Nodo* raiz) {
    if (raiz == nullptr) return;

    int altura = obtenerAltura(raiz);
    int filas = altura * 2 - 1;
    int columnas = pow(2, altura + 1);

    vector<string> lienzo(filas, string(columnas, ' '));
    int separacionInicial = pow(2, altura - 1);

    llenarMatriz(lienzo, raiz, 0, columnas / 2, separacionInicial);

    for (const string& linea : lienzo) {
        cout << linea << endl;
    }
}

void preorden(Nodo* nodo) {
    if (nodo == nullptr) return;
    cout << nodo->dato << " ";
    preorden(nodo->izq);
    preorden(nodo->der);
}

void inorden(Nodo* nodo) {
    if (nodo == nullptr) return;
    inorden(nodo->izq);
    cout << nodo->dato << " ";
    inorden(nodo->der);
}

void postorden(Nodo* nodo) {
    if (nodo == nullptr) return;
    postorden(nodo->izq);
    postorden(nodo->der);
    cout << nodo->dato << " ";
}

int main() {
    Nodo* raiz = crearNodo(10);
    raiz->izq = crearNodo(5);
    raiz->der = crearNodo(20);
    raiz->izq->izq = crearNodo(3);

    cout << "Arbol binario:" << endl;
    mostrarArbolVertical(raiz);
    cout << endl;

    cout << "Preorden:  ";
    preorden(raiz);
    cout << endl;

    cout << "Inorden:   ";
    inorden(raiz);
    cout << endl;

    cout << "Postorden: ";
    postorden(raiz);
    cout << endl;

    return 0;
}