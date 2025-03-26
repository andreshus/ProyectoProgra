#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

struct nodo {
    int nro; // En este caso es un número entero
    char nombrecancion[20];
    char artista[20];
    char duracion[10];
    char genero[20];
    char path[100];  // Ruta del archivo
    struct nodo *sgte;
};
typedef struct nodo *Tlista;

void insertarInicio(Tlista &lista, int valor, char nombre[], char artista[], char duracion[], char genero[], char path[]) {
    Tlista q;
    q = new(struct nodo);
    q->nro = valor;
    strcpy(q->nombrecancion, nombre);
    strcpy(q->artista, artista);
    strcpy(q->duracion, duracion);
    strcpy(q->genero, genero);
    strcpy(q->path, path);
    q->sgte = lista;
    lista = q;
}

void insertarFinal(Tlista &lista, int valor, char nombre[], char artista[], char duracion[], char genero[], char path[]) {
    Tlista t, q = new(struct nodo);
    q->nro = valor;
    strcpy(q->nombrecancion, nombre);
    strcpy(q->artista, artista);
    strcpy(q->duracion, duracion);
    strcpy(q->genero, genero);
    strcpy(q->path, path);
    q->sgte = NULL;
    if (lista == NULL) {
        lista = q;
    } else {
        t = lista;
        while (t->sgte != NULL) {
            t = t->sgte;
        }
        t->sgte = q;
    }
}

void reportarLista(Tlista lista) {
    int i = 0;
    while (lista != NULL) {
        cout << i + 1 << ") " << lista->nro << " -> " << lista->nombrecancion << " | "
             << lista->artista << " | " << lista->duracion << " | " << lista->genero << endl;
        lista = lista->sgte;
        i++;
    }
}

void reproducirCancion(Tlista lista, int pos) {
    Tlista temp = lista;
    int i = 1;
    while (temp != NULL) {
        if (i == pos) {
            cout << "\nReproduciendo canción: " << temp->nombrecancion << endl;
            cout << "Artista: " << temp->artista << endl;
            cout << "Duración: " << temp->duracion << endl;
            cout << "Género: " << temp->genero << endl;
            cout << "Ruta del archivo: " << temp->path << endl;

            // Llamamos a VLC para reproducir el archivo (usando la ruta completa del ejecutable de VLC)
            string command = "D:\\vcl\\VLC\\vlc.exe --play-and-exit " + string(temp->path);
            system(command.c_str()); // Ejecutamos el comando

            return;
        }
        temp = temp->sgte;
        i++;
    }
    cout << "Posición no válida." << endl;
}

void menu1() {
    cout << "\n\t\tLISTA ENLAZADA SIMPLE\n\n";
    cout << "1. INSERTAR CANCION AL INICIO\n";
    cout << "2. INSERTAR CANCION AL FINAL\n";
    cout << "3. MOSTRAR PLAYLIST LISTA\n";
    cout << "4. REPRODUCIR CANCION\n";
    cout << "5. SALIR\n";
    cout << "\nINGRESE OPCION: ";
}

int main() {
    Tlista lista = NULL;
    int op; // Opción del menú
    int _dato; // ID de la canción
    int pos; // Posición a insertar o reproducir
    char cancion[20], artista[20], duracion[10], genero[20], path[100];

    do {
        menu1();
        cin >> op;
        cin.ignore();

        switch (op) {
            case 1:
                cout << "AGREGA EL ID DE TU CANCION: ";
                cin >> _dato;
                cout << "AGREGA EL NOMBRE DE TU CANCION: ";
                cin.ignore();
                cin.getline(cancion, 20);
                cout << "AGREGA EL ARTISTA: ";
                cin.getline(artista, 20);
                cout << "AGREGA LA DURACION DE LA CANCION: ";
                cin.getline(duracion, 10);
                cout << "AGREGA EL GENERO: ";
                cin.getline(genero, 20);
                cout << "AGREGA EL PATH DEL ARCHIVO DE AUDIO: ";
                cin.getline(path, 100);  // Ruta completa del archivo
                insertarInicio(lista, _dato, cancion, artista, duracion, genero, path);
                break;

            case 2:
                cout << "AGREGA EL ID DE TU CANCION: ";
                cin >> _dato;
                cout << "AGREGA EL NOMBRE DE TU CANCION: ";
                cin.ignore();
                cin.getline(cancion, 20);
                cout << "AGREGA EL ARTISTA: ";
                cin.getline(artista, 20);
                cout << "AGREGA LA DURACION DE LA CANCION: ";
                cin.getline(duracion, 10);
                cout << "AGREGA EL GENERO: ";
                cin.getline(genero, 20);
                cout << "AGREGA EL PATH DEL ARCHIVO DE AUDIO: ";
                cin.getline(path, 100);  // Ruta completa del archivo
                insertarFinal(lista, _dato, cancion, artista, duracion, genero, path);
                break;

            case 3:
                cout << "\n\nMOSTRANDO LISTA\n\n";
                reportarLista(lista);
                break;

            case 4:
                cout << "Selecciona la posición de la canción para reproducir: ";
                cin >> pos;
                reproducirCancion(lista, pos);
                break;
        }

        cout << endl;
        system("pause");
        system("cls");

    } while (op != 5);

    system("pause");
    return 0;
}
