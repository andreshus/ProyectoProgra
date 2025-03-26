#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void cargarPalabrasDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);

    if (!archivo) {
        cout << "Error: No se pudo abrir el archivo en la ruta: " << nombreArchivo << endl;
        return;
    }

    string linea, esp, ing, fra, ale, ita;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, esp, ',');
        getline(ss, ing, ',');
        getline(ss, fra, ',');
        getline(ss, ale, ',');
        getline(ss, ita, ',');

        cout << "Español: " << esp
             << " | Inglés: " << ing
             << " | Francés: " << fra
             << " | Alemán: " << ale
             << " | Italiano: " << ita << endl;
    }

    archivo.close();
}

int main() {
    string nombreArchivo = "C:/Users/megugu/Downloads/palabras.txt";
    cargarPalabrasDesdeArchivo(nombreArchivo);
    return 0;
}
