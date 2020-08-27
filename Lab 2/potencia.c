#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Cabeceras
typedef struct lista Lista;
typedef struct nodo Nodo;
typedef struct subnodo Subnodo;
typedef struct matriz Matriz;
Matriz* leer();
Lista* crearLista(int largo);
Nodo* crearNodo(int fila);
void agregarNodo(Lista* lista, Nodo* nodo);
Subnodo* crearSubnodo(int columna, double valor);
void agregarSubnodo(Nodo* nodo, Subnodo* subnodo);
Lista* matrizDispersa(Matriz* matriz);
Lista* calcularPotencia(Lista* lista);
double calcularValor(Lista* lista1, Lista* lista2, int largo, int posFila, int posColumna);
Subnodo* buscar(Lista* lista, int i, int j);
//Estructuras
typedef struct lista
{
	Nodo* inicio;
	Nodo* final;
	int largo;
	int potencia;
}Lista;

typedef struct nodo
{
	Nodo* siguiente;
	Nodo* anterior;
	Subnodo* inicio;
	Subnodo* final;
	int fila;
	int largosub;
}Nodo;

typedef struct subnodo
{
	Subnodo* siguiente;
	Subnodo* anterior;
	int columna;
	double valor;
}Subnodo;

typedef struct matriz
{
	int porte;
	int potencia;
	int** matrizz;
}Matriz;
//
//Main
int main(){
	Matriz* matriz = leer();
	Lista* lista = matrizDispersa(matriz);
	printf("La matriz resultante es: \n");
	Lista* listaPotencia = calcularPotencia(lista);
	int result1 = (sizeof(lista));// + ((sizeof(Nodo))*(lista->largo)) + ((sizeof(Subnodo)*(Nodo->largosub)));
	printf("El tamano en memoria de la matriz dispersa es: %i bytes\n", result1);
	int result2 = sizeof(matriz);
	printf("El tamano en memoria de la matriz completa habria sido : %i bytes\n", result2);	
	return 1;
}
//
//Funcion utilizada para leer el archivo.in
Matriz* leer(){
	char* nombre = (char*)malloc(sizeof(char) * 50); 
	FILE* archivo;
	int comprobArch = 0;
	int comprobNom = 0;
	int tamano;
	int potencia;
	do{
		if(comprobArch == 1){
			printf("El nombre del archivo es incorrecto.\n");
		}
		else{
			comprobArch = 1;
		}
		do{
			if(comprobNom == 1){
				printf("Lo ingresado no es valido.\n");
			}
			else{
				comprobNom = 1;
			}
			printf("Ingrese el nombre de archivo:\n");
		}while(scanf("%s", nombre) <= 0);
		archivo = fopen(nombre, "r");
		comprobNom = 0;
	}while(archivo == NULL);
	free(nombre);
	Matriz* nueva = (Matriz*)malloc(sizeof(Matriz));
	fscanf(archivo, "%d %d", &tamano, &potencia);
	int i;
	nueva->porte = tamano;
	nueva->potencia = potencia;
	nueva->matrizz = (int**)malloc(sizeof(int*) * nueva->porte);
	printf("La matriz en el archivo es:\n");
	for(i = 0; i < nueva->porte; i++){
		nueva->matrizz[i] = (int*)malloc(sizeof(int) * nueva->porte);
	}
	int j;
	for(i = 0; i < nueva->porte; i++){
		for(j = 0; j < nueva->porte; j++){
			fscanf(archivo, "%d", &(nueva->matrizz[i][j]));
			printf("%d ", nueva->matrizz[i][j]);
		}
		printf("\n");
	}
	if(fclose(archivo) == 0);
	return nueva;
}
//
//Funcion hecha para crear listas
Lista* crearLista(int largo){
	Lista* lista = (Lista*)malloc(sizeof(Lista));
	lista->inicio = NULL;
	lista->final = NULL;
	lista->largo = 0;
	int i = 0;
	while (i<largo){
		Nodo* nodo = crearNodo(i);
		agregarNodo(lista,nodo);
		i++;
	}
	return lista;
}
//
//Funcion hecha para crear nodos
Nodo* crearNodo(int fila){
	Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
	nodo->siguiente = NULL;
	nodo->anterior = NULL;
	nodo->inicio = NULL;
	nodo->final = NULL;
	nodo->fila = fila;
	nodo->largosub = 0;
	return nodo;
}
//
//Funcion hecha para agregar nodos
void agregarNodo(Lista* lista, Nodo* nodo){
	if (lista->inicio == NULL){
		lista->inicio = nodo;
		lista->final = nodo;
	}
	else{
		Nodo* aux = lista->final;
		aux->siguiente = nodo;
		nodo->anterior = aux;
		lista->final = nodo;
	}
	lista->largo = lista->largo+1;
}
//
//Funcion hecha para crear subnodos
Subnodo* crearSubnodo(int columna, double valor){
	Subnodo* subnodo = (Subnodo*) malloc(sizeof(Subnodo));
	subnodo->siguiente = NULL;
	subnodo->anterior = NULL;
	subnodo->columna = columna;
	subnodo->valor = valor;
	return subnodo;
}
//
//Funcion hecha para agregar subnodos
void agregarSubnodo(Nodo* nodo, Subnodo* subnodo){
	if (nodo->inicio == NULL){
		nodo->inicio = subnodo;
		nodo->final = subnodo;
	}
	else{
		Subnodo* aux = nodo->final;
		aux->siguiente = subnodo;
		subnodo->anterior = aux;
		nodo->final = subnodo;
	}
	nodo->largosub = nodo->largosub + 1;
}
//
//Funcion creada para hacer la matriz dispersa (sin guardar los ceros)
Lista* matrizDispersa(Matriz* matriz){
	int i = 0;
	int j = 0;
	Lista* lista = crearLista(matriz->porte);
    lista->largo = matriz->porte;
    lista->potencia = matriz->potencia;
	while(i < matriz->porte){
		j = 0;
		while(j < matriz->porte){
			if(matriz->matrizz[i][j] == 0){

			}else{
				int x = 0;
				Nodo* aux = lista->inicio;
				while((x != i) && (x < i)){
					aux = aux->siguiente;
					x++;
				}
				Subnodo* sub = crearSubnodo(j, matriz->matrizz[i][j]);
				agregarSubnodo(aux, sub);			
			}
			j++;
		}	
		i++;
	}
	return lista;
}
//
//Funcion para calcular la potencia de matrices
Lista* calcularPotencia(Lista* lista){
	int tamano = lista->largo;
	int potencia = lista->potencia;
	Lista* listaResultante = crearLista(tamano);
	int i = 0;
	int j = 0;
	if(potencia % 2 == 0){
		while(i < tamano){
			j = 0;
			while(j < tamano){
				double valor = calcularValor(lista, lista, tamano, i, j);
				printf("%lf ", valor);
				if(valor == 0){

				}
				else{
					int x = 0;
					Nodo* aux = listaResultante->inicio;
					while((x != i) && (x < i)){
						aux = aux->siguiente;
						x++;
					}
					Subnodo* sub = crearSubnodo(j, valor);
					agregarSubnodo(aux, sub);
				}
			j++;
			}
		printf("\n");	
		i++;
		}
	return lista;
	}
	else if(potencia % 2 != 0){
		while(i < tamano){
			j = 0;
			while(j < tamano){
				double valor = 0; //calcularValor(lista, lista2, tamano, i, j);
				printf("%lf ", valor);
				if(valor == 0){

				}
				else{
					int x = 0;
					Nodo* aux = listaResultante->inicio;
					while((x != i) && (x < i)){
						aux = aux->siguiente;
						x++;
					}
					Subnodo* sub = crearSubnodo(j, valor);
					agregarSubnodo(aux, sub);
				}
			j++;
			}
		printf("\n");	
		i++;
		}
	return lista;
	}		    
}
//
//Funcion para calcular el valor de una pocicion de la matriz
double calcularValor(Lista* lista1, Lista* lista2, int largo, int posFila, int posColumna){
	double valor = 0;
    int i = 0;
    int j = 0;
    while(i < largo){
    	while(j < largo){
    		double filacolumna1 = 0;
                if(buscar(lista1, posFila, j) != NULL){
                    filacolumna1 = (buscar(lista1, posFila, j))->valor;
                }
                else{
                    filacolumna1 = 0;
                }
    		double filacolumna2 = 0;
                if(buscar(lista2, j, posColumna) != NULL){
                    filacolumna2 = (buscar(lista2, j, posColumna))->valor;
                }
                else{
                    filacolumna2 = 0;
                }
    		if(filacolumna1 != 0 && filacolumna2 != 0){
    			valor = valor + (filacolumna1 * filacolumna2);
    		}
    		j++;
    	}
    	i++;
    }
    return valor;
}
//
//Funcion que encuentra el valor que esta en algun nodo de la matriz
Subnodo* buscar(Lista* lista, int i, int j){
    if(i >= lista->largo || j >= lista->largo){
        return NULL;
    }
    Nodo* aux1 = lista->inicio;
    Subnodo* aux2;
    while(aux1->fila < i){
        aux1 = aux1->siguiente;
    }
    aux2 = aux1->inicio;
    if(aux2 == NULL){
        return NULL;
    }
    while(aux2 != NULL){
        if(aux2->columna == j){      	
            return aux2;
        }
        else{
            aux2 = aux2->siguiente;
        }
    }
    return NULL;
}
//