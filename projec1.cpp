#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Nodo {
    string espanol;
    string ingles;
    string italiano;
    string frances;
    string aleman;
    Nodo* siguiente;
};

class Diccionario {
private:
    Nodo* cabeza;
    string archivoRuta;

public:
    Diccionario(const string& ruta) {
        cabeza = nullptr;
        archivoRuta = ruta;
    }

    // Agrega un nodo al final de la lista (para mantener el orden original del archivo)
    void agregarAlFinal(const string& espanol, const string& ingles, const string& italiano, const string& frances, const string& aleman) {
        Nodo* nuevoNodo = new Nodo{espanol, ingles, italiano, frances, aleman, nullptr};

        if (cabeza == nullptr) {
            cabeza = nuevoNodo;
            return;
        }

        Nodo* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }

    // Agrega una palabra ingresada por el usuario y guarda en archivo
    void agregarNodo(const string& espanol, const string& ingles, const string& italiano, const string& frances, const string& aleman) {
        agregarAlFinal(espanol, ingles, italiano, frances, aleman);
        guardarEnArchivo();  // Guardamos después de agregar
    }

    void mostrarPalabras() {
        Nodo* actual = cabeza;
        int contador = 1;
        while (actual != nullptr) {
            cout << contador++ << ". " << actual->espanol << endl;
            actual = actual->siguiente;
        }
    }

    void traducirPalabra(const string& palabra, int idioma) {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            if (actual->espanol == palabra) {
                switch (idioma) {
                    case 1:
                        cout << "Traducción en Inglés: " << actual->ingles << endl;
                        break;
                    case 2:
                        cout << "Traducción en Italiano: " << actual->italiano << endl;
                        break;
                    case 3:
                        cout << "Traducción en Francés: " << actual->frances << endl;
                        break;
                    case 4:
                        cout << "Traducción en Alemán: " << actual->aleman << endl;
                        break;
                    default:
                        cout << "Idioma no válido." << endl;
                }
                return;
            }
            actual = actual->siguiente;
        }
        cout << "Palabra no encontrada." << endl;
    }

    void eliminarNodo(const string& palabra) {
        Nodo* actual = cabeza;
        Nodo* anterior = nullptr;
        while (actual != nullptr) {
            if (actual->espanol == palabra) {
                if (anterior == nullptr) {
                    cabeza = actual->siguiente;
                } else {
                    anterior->siguiente = actual->siguiente;
                }
                delete actual;
                guardarEnArchivo();  // Guardamos después de eliminar
                cout << "Palabra eliminada correctamente." << endl;
                return;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        cout << "Palabra no encontrada para eliminar." << endl;
    }

    void guardarEnArchivo() {
        ofstream archivo(archivoRuta);
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            archivo << actual->espanol << "," << actual->ingles << "," << actual->italiano << ","
                    << actual->frances << "," << actual->aleman << endl;
            actual = actual->siguiente;
        }
        archivo.close();
    }

    void cargarDesdeArchivo() {
        ifstream archivo(archivoRuta);
        if (!archivo) {
            cout << "Error al abrir el archivo. Verifica la ruta y los permisos." << endl;
            return;
        }

        string linea, espanol, ingles, italiano, frances, aleman;

        while (getline(archivo, linea)) {
            stringstream ss(linea);
            if (getline(ss, espanol, ',') &&
                getline(ss, ingles, ',') &&
                getline(ss, italiano, ',') &&
                getline(ss, frances, ',') &&
                getline(ss, aleman)) {

                // Eliminar espacios extra
                espanol = trim(espanol);
                ingles = trim(ingles);
                italiano = trim(italiano);
                frances = trim(frances);
                aleman = trim(aleman);

                agregarAlFinal(espanol, ingles, italiano, frances, aleman);
            }
        }
        archivo.close();
        cout << "Palabras cargadas correctamente desde el archivo." << endl;
    }

    string trim(const string& str) {
        size_t first = str.find_first_not_of(" \t\n\r");
        size_t last = str.find_last_not_of(" \t\n\r");
        return (first == string::npos) ? "" : str.substr(first, (last - first + 1));
    }
};

int main() {
    string rutaArchivo = "C:/Users/megugu/Desktop/Proyecto/palabrasprojec1.txt";
    Diccionario diccionario(rutaArchivo);
    diccionario.cargarDesdeArchivo();

    while (true) {
        int opcion;
        cout << "\n1. Traducir palabra\n2. Agregar palabra\n3. Eliminar palabra\n4. Mostrar palabras\n5. Salir\n";
        cout << "Selecciona una opción: ";
        cin >> opcion;

        if (opcion == 1) {
            string palabra;
            int idioma;
            cout << "Introduce la palabra a traducir: ";
            cin.ignore();
            getline(cin, palabra);
            cout << "Selecciona el idioma para traducir (1=Inglés, 2=Italiano, 3=Francés, 4=Alemán): ";
            cin >> idioma;
            diccionario.traducirPalabra(palabra, idioma);
        } else if (opcion == 2) {
            string espanol, ingles, italiano, frances, aleman;
            cout << "Introduce la palabra en español: ";
            cin.ignore();
            getline(cin, espanol);
            cout << "Introduce la traducción en inglés: ";
            getline(cin, ingles);
            cout << "Introduce la traducción en italiano: ";
            getline(cin, italiano);
            cout << "Introduce la traducción en francés: ";
            getline(cin, frances);
            cout << "Introduce la traducción en alemán: ";
            getline(cin, aleman);
            diccionario.agregarNodo(espanol, ingles, italiano, frances, aleman);
        } else if (opcion == 3) {
            string palabra;
            cout << "Introduce la palabra a eliminar: ";
            cin.ignore();
            getline(cin, palabra);
            diccionario.eliminarNodo(palabra);
        } else if (opcion == 4) {
            diccionario.mostrarPalabras();
        } else if (opcion == 5) {
            break;
        } else {
            cout << "Opción no válida." << endl;
        }
    }

    return 0;
}
