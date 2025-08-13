#include <iostream>
#include <stack>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

void mover(vector<int> &desde, vector<int> &hasta, char nomDesde, char nomHasta);
void hanoi(int n, vector<int> &origen, vector<int> &auxiliar, vector<int> &destino,char nomOrigen, char nomAux, char nomDestino);
vector<int> crearListaNumeros();

int main()
{
    // --------------------- Variables -------------------------
    bool exit = false;                      // Controla si el menu principal sigue activo
    int opcionMenu;                         // Guarda la opción seleccionada por el usuario en el menú principal
    int tamañoLista;                        // Estos son los discos
    vector<int> origen, auxiliar, destino;  // Estas son las 3 torres (La de origen, la auxiliar y la de destino)     


    // --------------- Portada del Proyecto --------------------
    std::string integrantes[5] = {"202011770 Rodolfo Meneses Leal", 
                                  "20220114317 Carlos Jimenez", 
                                  "XXXXXXXXX Victoria ",
                                  "XXXXXXXXX Xander ",
                                  "XXXXXXXXX ABC"};

    printf("\n================= ULatina ====================\n\n");
    printf("Fecha:      14/08/2025                          \n");
    printf("Curso:      BIS08 Estructura de Datos           \n");
    printf("Docente:    Leandro Arturo Castillo Rivera      \n");
    printf("Proyecto:   Torres de Hanoi            \n\n");
    printf("Integrantes:                                    \n");
    
    for(int i = 0; i < (sizeof(integrantes)) / sizeof(integrantes[0]); i++){
        printf("·%s \n", integrantes[i].c_str());
    }
    

    // --------------- Inicio del Programa --------------------
    while(!exit){
        printf("\n----------------- Menu ---------------------- \n\n");
        printf("1. Ingresar la cantidad de discos.               \n");
        printf("2. Aplicar Torres de Hanoi.                      \n");
        printf("3. Salir                                         \n");
        printf("\nSeleccione una opcion: ");
        scanf("%i", &opcionMenu);

        switch(opcionMenu){
            case 1: 
                // Aqui se crea la lista (osea los discos con sus tamaños)
                origen = crearListaNumeros();
                break;

            case 2:
                // Aqui se aplica el algoritmo de Torres de Hanoi
                
                if(origen.empty()){
                    // Esto evita que se intente aplicar Torres de Hanoi sin discos
                    // Vuelve al menú principal, dando oportunidad de ingresar una lista.
                    printf("No se han ingresado elementos a la lista, usar opción 1 para ingresar discos.\n");
                    continue; 
                }

			    tamañoLista = origen.size();
			    hanoi(tamañoLista, origen, auxiliar, destino, 'O', 'A', 'D');
                break;
            case 3:
                printf("Saliendo del programa...\n");
                exit = true;
                break;
            default: 
                printf("Opción no válida. Intente de nuevo.\n");
                continue;
        }

    }

    return 0;

}

void mover(vector<int> &desde, vector<int> &hasta, char nomDesde, char nomHasta) {
    int disco = desde.back();   // tomar el último disco
    desde.pop_back();           // quitarlo de la torre origen
    hasta.push_back(disco);     // colocarlo en la torre destino
    cout << "Mover disco " << disco << " de " << nomDesde << " a " << nomHasta << endl;
}


void hanoi(int n, vector<int> &origen, vector<int> &auxiliar, vector<int> &destino,
           char nomOrigen, char nomAux, char nomDestino) {

    if (n == 1) {
        mover(origen, destino, nomOrigen, nomDestino);
    } else {
        hanoi(n - 1, origen, destino, auxiliar, nomOrigen, nomDestino, nomAux);
        mover(origen, destino, nomOrigen, nomDestino);
        hanoi(n - 1, auxiliar, origen, destino, nomAux, nomOrigen, nomDestino);
    }
}                    

 vector<int> crearListaNumeros() {
    vector<int> lista;
    int tamañoLista, valor;

    cout << "\n-- Creando Lista -----------------------------\n";
    cout << "¿De qué tamaño desea la lista?: ";
    cin >> tamañoLista;

    // Solicitar al usuario cada valor
    for (int i = 0; i < tamañoLista; i++) {
        cout << "Posición [" << i + 1 << "]: ";
        cin >> valor;
        lista.push_back(valor);  // Agregar valor a la lista
    }

    cout << "\nLista creada exitosamente.\n";
    return lista;
}
		
