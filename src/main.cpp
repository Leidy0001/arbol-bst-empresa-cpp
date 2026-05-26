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
        izquierdo = nullptr;
        derecho = nullptr;
    }
};

class ArbolBST {
private:
    Nodo* raiz;

    Nodo* insertar(Nodo* nodo, Empleado emp) {
        if (nodo == nullptr) {
            return new Nodo(emp);
        }

        if (emp.codigo < nodo->dato.codigo) {
            nodo->izquierdo = insertar(nodo->izquierdo, emp);
        }
        else if (emp.codigo > nodo->dato.codigo) {
            nodo->derecho = insertar(nodo->derecho, emp);
        }
        else {
            cout << "\n⚠ El codigo ya existe.\n";
        }

        return nodo;
    }

    Nodo* buscar(Nodo* nodo, int codigo) {
        if (nodo == nullptr || nodo->dato.codigo == codigo) {
            return nodo;
        }

        if (codigo < nodo->dato.codigo) {
            return buscar(nodo->izquierdo, codigo);
        }

        return buscar(nodo->derecho, codigo);
    }

    void inorden(Nodo* nodo) {
        if (nodo != nullptr) {
            inorden(nodo->izquierdo);
            mostrarEmpleado(nodo);
            inorden(nodo->derecho);
        }
    }

    void preorden(Nodo* nodo) {
        if (nodo != nullptr) {
            mostrarEmpleado(nodo);
            preorden(nodo->izquierdo);
            preorden(nodo->derecho);
        }
    }

    void postorden(Nodo* nodo) {
        if (nodo != nullptr) {
            postorden(nodo->izquierdo);
            postorden(nodo->derecho);
            mostrarEmpleado(nodo);
        }
    }

    int altura(Nodo* nodo) {
        if (nodo == nullptr) {
            return 0;
        }

        int izquierda = altura(nodo->izquierdo);
        int derecha = altura(nodo->derecho);

        return 1 + max(izquierda, derecha);
    }

    void mostrarHojas(Nodo* nodo) {
        if (nodo != nullptr) {

            if (nodo->izquierdo == nullptr &&
                nodo->derecho == nullptr) {

                mostrarEmpleado(nodo);
            }

            mostrarHojas(nodo->izquierdo);
            mostrarHojas(nodo->derecho);
        }
    }

    void mostrarEmpleado(Nodo* nodo) {
        cout << "Codigo: " << nodo->dato.codigo
             << " | Nombre: " << nodo->dato.nombre
             << " | Cargo: " << nodo->dato.cargo << endl;
    }

public:
    ArbolBST() {
        raiz = nullptr;
    }

    void insertarEmpleado(Empleado emp) {
        raiz = insertar(raiz, emp);
    }

    void buscarEmpleado(int codigo) {
        Nodo* resultado = buscar(raiz, codigo);

        if (resultado != nullptr) {
            cout << "\n✓ Empleado encontrado:\n";
            mostrarEmpleado(resultado);
        }
        else {
            cout << "\n✗ Empleado no encontrado.\n";
        }
    }

    void mostrarRaiz() {
        if (raiz != nullptr) {
            cout << "\n===== RAIZ DEL ARBOL =====\n";
            mostrarEmpleado(raiz);
        }
        else {
            cout << "\nEl arbol esta vacio.\n";
        }
    }

    void mostrarInorden() {
        cout << "\n===== RECORRIDO INORDEN =====\n";
        inorden(raiz);
    }

    void mostrarPreorden() {
        cout << "\n===== RECORRIDO PREORDEN =====\n";
        preorden(raiz);
    }

    void mostrarPostorden() {
        cout << "\n===== RECORRIDO POSTORDEN =====\n";
        postorden(raiz);
    }

    void mostrarAltura() {
        cout << "\nAltura del arbol: "
             << altura(raiz) << endl;
    }

    void mostrarNodosHoja() {
        cout << "\n===== NODOS HOJA =====\n";
        mostrarHojas(raiz);
    }
};

int main() {

    ArbolBST arbol;

    // Datos de prueba
    arbol.insertarEmpleado({50, "Empresa UTA", "Raiz"});
    arbol.insertarEmpleado({30, "Gerente Ventas", "Nodo interno"});
    arbol.insertarEmpleado({70, "Gerente Finanzas", "Nodo interno"});
    arbol.insertarEmpleado({20, "Empleado 1", "Hoja"});
    arbol.insertarEmpleado({40, "Empleado 2", "Hoja"});
    arbol.insertarEmpleado({60, "Empleado 3", "Hoja"});
    arbol.insertarEmpleado({80, "Empleado 4", "Hoja"});

    int opcion;

    do {
        cout << "\n=====================================\n";
        cout << "   MENU ARBOL BST EMPRESARIAL\n";
        cout << "=====================================\n";
        cout << "1. Insertar empleado\n";
        cout << "2. Buscar empleado\n";
        cout << "3. Mostrar raiz\n";
        cout << "4. Recorrido inorden\n";
        cout << "5. Recorrido preorden\n";
        cout << "6. Recorrido postorden\n";
        cout << "7. Mostrar altura\n";
        cout << "8. Mostrar hojas\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {

            case 1: {
                Empleado emp;

                cout << "\nCodigo: ";
                cin >> emp.codigo;

                cin.ignore();

                cout << "Nombre: ";
                getline(cin, emp.nombre);

                cout << "Cargo: ";
                getline(cin, emp.cargo);

                arbol.insertarEmpleado(emp);

                cout << "\n✓ Empleado insertado correctamente.\n";
                break;
            }

            case 2: {
                int codigo;

                cout << "\nIngrese codigo a buscar: ";
                cin >> codigo;

                arbol.buscarEmpleado(codigo);
                break;
            }

            case 3:
                arbol.mostrarRaiz();
                break;

            case 4:
                arbol.mostrarInorden();
                break;

            case 5:
                arbol.mostrarPreorden();
                break;

            case 6:
                arbol.mostrarPostorden();
                break;

            case 7:
                arbol.mostrarAltura();
                break;

            case 8:
                arbol.mostrarNodosHoja();
                break;

            case 0:
                cout << "\nPrograma finalizado.\n";
                break;

            default:
                cout << "\nOpcion invalida.\n";
        }

    } while(opcion != 0);

    return 0;
}