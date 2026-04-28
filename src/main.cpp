#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Estructura que representa un empleado dentro de la empresa
// Cada empleado tendrá un código único, nombre y cargo
struct Empleado {
    int codigo;
    string nombre;
    string cargo;
};

// Nodo del Árbol Binario de Búsqueda
// Contiene un empleado y punteros a los hijos izquierdo y derecho
struct Nodo {
    Empleado dato;
    Nodo* izquierdo;
    Nodo* derecho;

    // Constructor que inicializa el nodo con un empleado
    // y establece los hijos como NULL
    Nodo(Empleado emp) {
        dato = emp;
        izquierdo = NULL;
        derecho = NULL;
    }
};

// Clase que implementa el Árbol Binario de Búsqueda (BST)
class ArbolBST {
private:
    Nodo* raiz; // Puntero a la raíz del árbol

    // Función recursiva para insertar un empleado en el árbol
    // Se ordena por el código del empleado
    Nodo* insertar(Nodo* nodo, Empleado emp) {
        // Si el nodo está vacío se crea uno nuevo
        if (nodo == NULL)
            return new Nodo(emp);

        // Si el código es menor se inserta a la izquierda
        if (emp.codigo < nodo->dato.codigo)
            nodo->izquierdo = insertar(nodo->izquierdo, emp);

        // Si el código es mayor se inserta a la derecha
        else if (emp.codigo > nodo->dato.codigo)
            nodo->derecho = insertar(nodo->derecho, emp);

        // Si el código ya existe se muestra mensaje
        else
            cout << "Codigo repetido.\n";

        return nodo;
    }

    // Función recursiva para buscar un empleado por código
    Nodo* buscar(Nodo* nodo, int codigo) {
        // Si se encuentra o el nodo es NULL se retorna
        if (nodo == NULL || nodo->dato.codigo == codigo)
            return nodo;

        // Buscar en el subárbol izquierdo
        if (codigo < nodo->dato.codigo)
            return buscar(nodo->izquierdo, codigo);

        // Buscar en el subárbol derecho
        return buscar(nodo->derecho, codigo);
    }

    // Recorrido INORDEN: izquierda -> raíz -> derecha
    // Muestra los empleados ordenados por código
    void inorden(Nodo* nodo) {
        if (nodo != NULL) {
            inorden(nodo->izquierdo);
            mostrarEmpleado(nodo);
            inorden(nodo->derecho);
        }
    }

    // Recorrido PREORDEN: raíz -> izquierda -> derecha
    // Útil para copiar la estructura del árbol
    void preorden(Nodo* nodo) {
        if (nodo != NULL) {
            mostrarEmpleado(nodo);
            preorden(nodo->izquierdo);
            preorden(nodo->derecho);
        }
    }

    // Recorrido POSTORDEN: izquierda -> derecha -> raíz
    // Se usa para eliminar o liberar memoria del árbol
    void postorden(Nodo* nodo) {
        if (nodo != NULL) {
            postorden(nodo->izquierdo);
            postorden(nodo->derecho);
            mostrarEmpleado(nodo);
        }
    }

    // Calcula la altura del árbol
    // La altura es el número de niveles del árbol
    int altura(Nodo* nodo) {
        if (nodo == NULL)
            return 0;

        return 1 + max(altura(nodo->izquierdo), altura(nodo->derecho));
    }

    // Muestra únicamente los nodos hoja
    // Un nodo hoja no tiene hijos
    void mostrarHojas(Nodo* nodo) {
        if (nodo != NULL) {
            if (nodo->izquierdo == NULL && nodo->derecho == NULL)
                mostrarEmpleado(nodo);

            mostrarHojas(nodo->izquierdo);
            mostrarHojas(nodo->derecho);
        }
    }

    // Muestra los nodos internos del árbol
    // Son los nodos que tienen al menos un hijo
    void mostrarInternos(Nodo* nodo) {
        if (nodo != NULL) {
            if (nodo->izquierdo != NULL || nodo->derecho != NULL)
                mostrarEmpleado(nodo);

            mostrarInternos(nodo->izquierdo);
            mostrarInternos(nodo->derecho);
        }
    }

    // Cuenta el total de nodos del árbol
    // Representa el total de empleados registrados
    int contarNodos(Nodo* nodo) {
        if (nodo == NULL)
            return 0;

        return 1 + contarNodos(nodo->izquierdo) + contarNodos(nodo->derecho);
    }

    // Muestra la información de un empleado
    void mostrarEmpleado(Nodo* nodo) {
        cout << "Codigo: " << nodo->dato.codigo
             << " | Nombre: " << nodo->dato.nombre
             << " | Cargo: " << nodo->dato.cargo << endl;
    }

public:
    // Constructor del árbol
    // Inicializa la raíz como NULL
    ArbolBST() {
        raiz = NULL;
    }

    // Función pública para insertar empleados
    void insertarEmpleado(Empleado emp) {
        raiz = insertar(raiz, emp);
    }

    // Función pública para buscar empleados
    void buscarEmpleado(int codigo) {
        Nodo* res = buscar(raiz, codigo);

        if (res != NULL) {
            cout << "\nEmpleado encontrado:\n";
            mostrarEmpleado(res);
        } else {
            cout << "Empleado no encontrado\n";
        }
    }

    // Muestra la raíz del árbol
    // Representa el jefe principal del organigrama
    void mostrarRaiz() {
        if (raiz != NULL) {
            cout << "\nRAIZ DEL ARBOL\n";
            mostrarEmpleado(raiz);
        } else {
            cout << "Arbol vacio\n";
        }
    }

    // Mostrar recorrido inorden
    void mostrarInorden() {
        cout << "\nRECORRIDO INORDEN\n";
        inorden(raiz);
    }

    // Mostrar recorrido preorden
    void mostrarPreorden() {
        cout << "\nRECORRIDO PREORDEN\n";
        preorden(raiz);
    }

    // Mostrar recorrido postorden
    void mostrarPostorden() {
        cout << "\nRECORRIDO POSTORDEN\n";
        postorden(raiz);
    }

    // Mostrar altura del árbol
    void mostrarAltura() {
        cout << "\nAltura del arbol: " << altura(raiz) << endl;
    }

    // Mostrar nodos hoja
    void mostrarHojasPublic() {
        cout << "\nNODOS HOJA\n";
        mostrarHojas(raiz);
    }

    // Mostrar nodos internos
    void mostrarInternosPublic() {
        cout << "\nNODOS INTERNOS\n";
        mostrarInternos(raiz);
    }

    // Mostrar total de empleados
    void totalEmpleados() {
        cout << "\nTotal empleados: " << contarNodos(raiz) << endl;
    }
};

int main() {
    ArbolBST arbol;
    int opcion;

    // Menú interactivo para manejar el árbol BST
    // Permite insertar, buscar y recorrer el árbol
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

        // Opción para insertar un nuevo empleado
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

        // Opción para buscar empleado por código
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
