#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Empleado {
    int codigo;
    string nombre;
    string cargo;
};

struct Nodo {
    Empleado dato;
    Nodo* izquierdo;
    Nodo* derecho;

    Nodo(Empleado emp) {
        dato = emp;
        izquierdo = NULL;
        derecho = NULL;
    }
};

class ArbolBST {
private:
    Nodo* raiz;

    Nodo* insertar(Nodo* nodo, Empleado emp) {
        if (nodo == NULL)
            return new Nodo(emp);

        if (emp.codigo < nodo->dato.codigo)
            nodo->izquierdo = insertar(nodo->izquierdo, emp);
        else if (emp.codigo > nodo->dato.codigo)
            nodo->derecho = insertar(nodo->derecho, emp);
        else
            cout << "Codigo repetido.\n";

        return nodo;
    }

    Nodo* buscar(Nodo* nodo, int codigo) {
        if (nodo == NULL || nodo->dato.codigo == codigo)
            return nodo;

        if (codigo < nodo->dato.codigo)
            return buscar(nodo->izquierdo, codigo);

        return buscar(nodo->derecho, codigo);
    }

    void inorden(Nodo* nodo) {
        if (nodo != NULL) {
            inorden(nodo->izquierdo);
            mostrarEmpleado(nodo);
            inorden(nodo->derecho);
        }
    }

    void preorden(Nodo* nodo) {
        if (nodo != NULL) {
            mostrarEmpleado(nodo);
            preorden(nodo->izquierdo);
            preorden(nodo->derecho);
        }
    }

    void postorden(Nodo* nodo) {
        if (nodo != NULL) {
            postorden(nodo->izquierdo);
            postorden(nodo->derecho);
            mostrarEmpleado(nodo);
        }
    }

    int altura(Nodo* nodo) {
        if (nodo == NULL)
            return 0;

        return 1 + max(altura(nodo->izquierdo), altura(nodo->derecho));
    }

    void mostrarHojas(Nodo* nodo) {
        if (nodo != NULL) {
            if (nodo->izquierdo == NULL && nodo->derecho == NULL)
                mostrarEmpleado(nodo);

            mostrarHojas(nodo->izquierdo);
            mostrarHojas(nodo->derecho);
        }
    }

    void mostrarInternos(Nodo* nodo) {
        if (nodo != NULL) {
            if (nodo->izquierdo != NULL || nodo->derecho != NULL)
                mostrarEmpleado(nodo);

            mostrarInternos(nodo->izquierdo);
            mostrarInternos(nodo->derecho);
        }
    }

    int contarNodos(Nodo* nodo) {
        if (nodo == NULL)
            return 0;

        return 1 + contarNodos(nodo->izquierdo) + contarNodos(nodo->derecho);
    }

    void mostrarEmpleado(Nodo* nodo) {
        cout << "Codigo: " << nodo->dato.codigo
             << " | Nombre: " << nodo->dato.nombre
             << " | Cargo: " << nodo->dato.cargo << endl;
    }

public:
    ArbolBST() {
        raiz = NULL;
    }

    void insertarEmpleado(Empleado emp) {
        raiz = insertar(raiz, emp);
    }

    void buscarEmpleado(int codigo) {
        Nodo* res = buscar(raiz, codigo);

        if (res != NULL) {
            cout << "\nEmpleado encontrado:\n";
            mostrarEmpleado(res);
        } else {
            cout << "Empleado no encontrado\n";
        }
    }

    void mostrarRaiz() {
        if (raiz != NULL) {
            cout << "\nRAIZ DEL ARBOL\n";
            mostrarEmpleado(raiz);
        } else {
            cout << "Arbol vacio\n";
        }
    }

    void mostrarInorden() {
        cout << "\nRECORRIDO INORDEN\n";
        inorden(raiz);
    }

    void mostrarPreorden() {
        cout << "\nRECORRIDO PREORDEN\n";
        preorden(raiz);
    }

    void mostrarPostorden() {
        cout << "\nRECORRIDO POSTORDEN\n";
        postorden(raiz);
    }

    void mostrarAltura() {
        cout << "\nAltura del arbol: " << altura(raiz) << endl;
    }

    void mostrarHojasPublic() {
        cout << "\nNODOS HOJA\n";
        mostrarHojas(raiz);
    }

    void mostrarInternosPublic() {
        cout << "\nNODOS INTERNOS\n";
        mostrarInternos(raiz);
    }

    void totalEmpleados() {
        cout << "\nTotal empleados: " << contarNodos(raiz) << endl;
    }
};

int main() {
    ArbolBST arbol;
    int opcion;

    do {
        cout << "\n====== ARBOL BST EMPRESA ======\n";
        cout << "1. Insertar empleado\n";
        cout << "2. Buscar empleado\n";
        cout << "3. Mostrar raiz\n";
        cout << "4. Inorden\n";
        cout << "5. Preorden\n";
        cout << "6. Postorden\n";
        cout << "7. Altura\n";
        cout << "8. Hojas\n";
        cout << "9. Nodos internos\n";
        cout << "10. Total empleados\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            Empleado emp;

            cout << "Codigo: ";
            cin >> emp.codigo;
            cin.ignore();

            cout << "Nombre: ";
            getline(cin, emp.nombre);

            cout << "Cargo: ";
            getline(cin, emp.cargo);

            arbol.insertarEmpleado(emp);
        }

        if (opcion == 2) {
            int cod;
            cout << "Codigo a buscar: ";
            cin >> cod;
            arbol.buscarEmpleado(cod);
        }

        if (opcion == 3) arbol.mostrarRaiz();
        if (opcion == 4) arbol.mostrarInorden();
        if (opcion == 5) arbol.mostrarPreorden();
        if (opcion == 6) arbol.mostrarPostorden();
        if (opcion == 7) arbol.mostrarAltura();
        if (opcion == 8) arbol.mostrarHojasPublic();
        if (opcion == 9) arbol.mostrarInternosPublic();
        if (opcion == 10) arbol.totalEmpleados();

    } while (opcion != 0);

    return 0;
}
