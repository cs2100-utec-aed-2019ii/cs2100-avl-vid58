#include <iostream>
using namespace std;

class Node{
public:
    int data;
    Node *izq;
    Node *der;
    int fe;

    Node(int n){
        data = n;
        fe = 0;
        izq = NULL;
        der = NULL;
    }

};

class Arbol_AVL{
private:
    Node *raiz = NULL;
public:
    Arbol_AVL(){}
    Node* get_raiz(){
        return raiz;
    }
    // factor equilibrio
    int factor_e(Node *x){

        if (x == NULL){

            return -1;
        }
        else {
            return x->fe;
        }
    }

    //Rotacion izqierda
    Node *R_I(Node *nodo){

        Node *aux = nodo->izq;
        nodo->izq = aux->der;
        aux->der = nodo;

        int max_nodo;
        int max_aux;

        if (factor_e(nodo->izq) > factor_e(nodo->der)){
            max_nodo = factor_e(nodo->izq)+1;

        }
        else {
            max_nodo = factor_e(nodo->der)+1;
        }

        nodo->fe = max_nodo;


        if (factor_e(aux->izq) > factor_e(aux->der)){
            max_aux = factor_e(aux->izq)+1;

        }
        else {
            max_aux = factor_e(aux->der)+1;
        }

        aux->fe = max_aux;

        return aux;

    }

    //Rotacion derecha
    Node *R_D(Node *nodo){

        Node *aux = nodo->der;
        nodo->der = aux->izq;
        aux->izq = nodo;
        int max_nodo;
        int max_aux;

        if (factor_e(nodo->izq) > factor_e(nodo->der)){
            max_nodo = factor_e(nodo->izq);

        }
        else {
            max_nodo = factor_e(nodo->der);
        }

        nodo->fe = max_nodo+1;


        if (factor_e(aux->izq) > factor_e(aux->der)){
            max_aux = factor_e(aux->izq);

        }
        else {
            max_aux = factor_e(aux->der);
        }

        aux->fe = max_aux+1;

        return aux;
    }

    //Rotacion izquierda derecha
    Node *R_ID(Node *c){

        Node *temp;
        c->izq = R_D(c->izq);
        temp = R_I(c);
        return temp;
    }

    //Rotacion derecha izquierda
    Node *R_DI(Node *c){
        Node *temp;
        c->der = R_I(c->der);
        temp = R_D(c);
        return temp;
    }

    void insertar(int d){

        Node *nuevo= new Node(d);
        if (raiz == NULL){
            raiz = nuevo;
        }
        else {
            insertar_AVL(nuevo,raiz);
        }

    }
    Node *insertar_AVL(Node *nuevo, Node *subarbol){

        Node *nuevoPadre = subarbol;

        if (nuevo->data < subarbol->data){
            if (subarbol->izq == NULL){
                subarbol->izq = nuevo;
            }else {
                subarbol->izq = insertar_AVL(nuevo,subarbol->izq);
                if ((factor_e(subarbol->izq) - factor_e(subarbol->der) == 2)){
                    if (nuevo->data < subarbol->izq->data){
                        nuevoPadre = R_I(subarbol);
                    }else {
                        nuevoPadre = R_ID(subarbol);

                    }

                }
            }
        }else if (nuevo->data > subarbol->data){
            if (subarbol->der == NULL){
                subarbol->der = nuevo;
            }
            else {
                subarbol->der = insertar_AVL(nuevo, subarbol->der);
                if ((factor_e(subarbol->der) - factor_e(subarbol->izq) == 2)){

                    if (nuevo->data > subarbol->der->data){
                        nuevoPadre = R_D(subarbol);

                    } else {

                        nuevoPadre = R_DI(subarbol);
                    }
                }
            }
        }
        else {
            cout<<"Nodo Duplicado"<<endl;
        }

        if ((subarbol->izq == NULL) && (subarbol->der != NULL)) {

            subarbol->fe = subarbol->der->fe+1;
        }
        else{

            if ((subarbol->der == NULL) && (subarbol->izq!=NULL)) {

                subarbol->fe = subarbol->izq->fe+1;


            }
            else {
                int maximovalor;

                if (factor_e(subarbol->izq) > factor_e(subarbol->der)){
                    maximovalor = factor_e(subarbol->izq);

                }
                else {
                    maximovalor = factor_e(subarbol->der);
                }
                subarbol->fe = maximovalor+1;

            }

        }

        return nuevoPadre;
    }

    void imprimir(){
        if(raiz == NULL){
            cout<<"\nTa vacio ";
        }
        else{
            int cont = 0;
            i_Orden(raiz,cont);
        }
    }
    void i_Orden(Node *arbol,int cont){
        if(arbol == NULL){
            return;
        }else {
            i_Orden(arbol->der, cont + 1);
            for (int i = 0; i < cont; i++) {
                cout <<"  ";
            }
            cout << arbol->data << endl;
            i_Orden(arbol->izq, cont + 1);
        }
    }
};

int main(){

    Arbol_AVL *arbolito = new Arbol_AVL();

    arbolito->insertar(8);
    arbolito->insertar(3);
    arbolito->insertar(10);
    arbolito->insertar(1);
    arbolito->insertar(6);
    arbolito->insertar(14);
    arbolito->insertar(13);
    arbolito->insertar(4);

    arbolito->imprimir();

}