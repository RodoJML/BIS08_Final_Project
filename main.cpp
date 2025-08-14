#include <iostream>
#include <stack>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

void mover(stack<int> &desde, stack<int> &hasta, char nomDesde, char nomHasta);
void hanoi(int n, stack<int> &origen, stack<int> &auxiliar, stack<int> &destino,char nomOrigen, char nomAux, char nomDestino);
void printTowers(const stack<int> &origen, const stack<int> &auxiliar, const stack<int> &destino);
stack<int> crearListaNumeros();

int main()
{
    // --------------------- Variables -------------------------
    bool exit = false;      // Controla si el menu principal sigue activo
    int opcionMenu;         // Guarda la opción seleccionada por el usuario en el menú principal
    
    stack<int> origen;      // Torre de origen
    stack<int> auxiliar;    // Torre auxiliar
    stack<int> destino;     // Torre de destino


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
        printf("1. Ingresar la cantidad de discos.              \n");
        printf("2. Aplicar Torres de Hanoi                      \n");
        printf("3. Mostrar Torres de Hanoi                      \n");
        printf("4. Salir                                        \n");
        printf("\nSeleccione una opcion: ");
        scanf("%i", &opcionMenu);

        // Torres de Hanoi: 
        // El juego consiste en mover una pila de discos de una torre a otra.
        // 1. Solo se puede mover un disco a la vez.
        // 2. Un disco más grande no puede estar encima de uno más pequeño.
        // 3. Solo se puede mover el disco superior de una torre.

        // Dependiendo de la opción seleccionada, se ejecuta una acción
        switch(opcionMenu){
            case 1: 
                // Aqui se crea la lista (osea los discos con sus tamaños)
                origen = crearListaNumeros();
                break;

            case 2:
                if(origen.empty()){
                    // Esto evita que se intente aplicar Torres de Hanoi sin discos
                    // Vuelve al menú principal, dando oportunidad de ingresar una lista.
                    printf("No se han ingresado elementos a la lista, usar opción 1 para ingresar discos.\n");
                    continue; 
                }

                // Si existe una lista de discos, se procede a aplicar Torres de Hanoi
			    hanoi(origen.size(), origen, auxiliar, destino, 'A', 'B', 'C');
                break;
            case 3:
                // Mostrar el estado de las torres
                printTowers(origen, auxiliar, destino);
                break;
            case 4:
                // Opción para salir del programa
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

stack<int> crearListaNumeros() {
    stack<int> lista;
    int tamañoLista, valor;

    cout << "\n-- Creando Discos -----------------------------\n";
    cout << "¿Cuantos Discos desea Agregar?: ";
    cin >> tamañoLista;

    // Solicitar al usuario cada valor (del más grande al más pequeño)
    cout << "Ingrese los tamaños de los discos del MÁS GRANDE al MÁS PEQUEÑO:\n";
    for (int i = 0; i < tamañoLista; i++) {
        cout << "Disco [" << i + 1 << "] (más grande primero): ";
        cin >> valor;
        lista.push(valor);  // Agregar valor a la lista
    }

    cout << "\nLista creada exitosamente.\n";
    cout << "IMPORTANTE: El disco más pequeño está arriba, el más grande abajo.\n";

    return lista;
}

void mover(stack<int> &desde, stack<int> &hasta, char nomDesde, char nomHasta) {
    int disco = desde.top();    // tomar el último disco
    desde.pop();                // quitarlo de la torre origen
    hasta.push(disco);          // colocarlo en la torre destino
    cout << "Mover disco " << disco << " de " << nomDesde << " a " << nomHasta << endl;
}


void hanoi(int n, stack<int> &origen, stack<int> &auxiliar, stack<int> &destino,
           char nomOrigen, char nomAux, char nomDestino) {

    // Esta function toma los siguientes parámetros:
    //  * int n: Esta es la cantidad de discos a mover
    //  * stack<int> &origen:   Esta es la torre de origen (Puede ser cualquier torre, no necesariamente la torre A)
    //  * stack<int> &auxiliar: Esta es la torre auxiliar  (Puede ser cualquier torre, no necesariamente la torre B)
    //  * stack<int> &destino:  Esta es la torre destino   (Puede ser cualquier torre, no necesariamente la torre C)

    // Ejemplo de Torres de Hanoi con 3 discos:
    //  
    //  1    
    //  2     
    //  3       
    // ___  ___   ___
    //  A    B     C        

    if (n == 1) {
        // Caso base: Si solo hay que mover un disco, se mueve directamente a la torre destino
        mover(origen, destino, nomOrigen, nomDestino);
    } else {

        // Caso recursivo: 
        // Mover todos los discos menos el ultimo a la torre auxiliar
        //
        //              A       C        B         
        //    Discos  Desde   Helper   Hasta        "A"       "C"       "B"
        hanoi(n - 1, origen, destino, auxiliar, nomOrigen, nomDestino, nomAux);
        //  1             //                 //                 // 
        //  2             //   2             //                 //        1    
        //  3             //   3         1   //   3    2    1   //   3    2    
        // ___  ___  ___  //  ___  ___  ___  //  ___  ___  ___  //  ___  ___  ___
        //  A    B    C   //   A    B    C   //   A    B    C   //   A    B    C

        // Mover el disco más grande a la torre destino
        //      A        C  
        //    Desde    Hasta      "A"         "C"
        mover(origen, destino, nomOrigen, nomDestino);
        //                //                  
        //       1        //        1         
        //  3    2        //        2    3   
        // ___  ___  ___  //  ___  ___  ___  
        //  A    B    C   //   A    B    C   

        // Mover los discos que quedaron en la torre auxiliar a la torre destino
        //              B        A         C         
        //    Discos  Desde    Helper    Hasta     "B"       "A"       "C"
        hanoi(n - 1, auxiliar, origen, destino, nomAux, nomOrigen, nomDestino);
        //                //                  //                //             1
        //       1        //                  //            2   //             2
        //       2    3   //   1    2    3    //  1         3   //             3
        // ___  ___  ___  //  ___  ___  ___   // ___  ___  ___  //  ___  ___  ___
        //  A    B    C   //   A    B    C    //  A    B    C   //   A    B    C
    }
}                    

// Esta función imprime el estado de las torres A, B y C, mostrando los discos en cada torre
void printTowers(const stack<int> &origen, const stack<int> &auxiliar, const stack<int> &destino) {
    // Esta función imprime el estado actual de las torres
    // Se imprimen los discos de cada torre, desde el disco más pequeño (en la cima) hasta el más grande (en la base)

    printf("\nTower A: ");
    if (origen.empty()) {
        printf("[vacía]\n");
    } else {
        stack<int> temp = origen;
        printf("(arriba) ");
        while (!temp.empty()) {
            printf("%d ", temp.top());
            temp.pop();
        }
        printf("(abajo)\n");
    }

    printf("Tower B: ");
    if (auxiliar.empty()) {
        printf("[vacía]\n");
    } else {
        stack<int> temp = auxiliar;
        printf("(arriba) ");
        while (!temp.empty()) {
            printf("%d ", temp.top());
            temp.pop();
        }
        printf("(abajo)\n");
    }

    printf("Tower C: ");
    if (destino.empty()) {
        printf("[vacía]\n");
    } else {
        stack<int> temp = destino;
        printf("(arriba) ");
        while (!temp.empty()) {
            printf("%d ", temp.top());
            temp.pop();
        }
        printf("(abajo)\n");
    }
}
