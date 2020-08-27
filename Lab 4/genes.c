#include <stdlib.h>
#include <stdio.h>

//Cabeceras
typedef struct grafo Grafo;
typedef struct nodo Nodo;
Grafo* leerProcesos();
Grafo* leerGenes(Grafo* grafo);
void printearMatrizP(Grafo* grafo);
void printearMatrizG(Grafo* grafo);
//
//Estrcuturas
typedef struct grafo
{
	int porteProcesos;
	char* verticeRaiz;
	int** matrizProcesos;
	int porteGenes;
	int** matrizGenes;
}Grafo;
//Main
int main(){
	Grafo* grafo = leerProcesos();
	printearMatrizP(grafo);
	Grafo* grafito = leerGenes(grafo);
	printearMatrizG(grafito);
}
//
//Funcion que lee el archivo para luego poder crear la matriz de procesos
Grafo* leerProcesos(){
	char* nombre = (char*)malloc(sizeof(char) * 50); 
	FILE* archivo;
	int comprobArch = 0;
	int comprobNom = 0;
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
			printf("Ingrese el nombre de archivo de los Procesos:\n");
		}while(scanf("%s", nombre) <= 0);
		archivo = fopen(nombre, "r");
		comprobNom = 0;
	}while(archivo == NULL);
	printf("Leyendo archivo %s\n", nombre);
	free(nombre);
	Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
	grafo->verticeRaiz = (char*)malloc(sizeof(char) * 2);
	fscanf(archivo, "%d", &(grafo->porteProcesos));
	int i;
	fscanf(archivo, "%s", grafo->verticeRaiz);
	printf("Raiz: %s\n", grafo->verticeRaiz);
	grafo->matrizProcesos = (int**)malloc(sizeof(int*) * grafo->porteProcesos);
	for(i = 0; i < grafo->porteProcesos; i++){
		grafo->matrizProcesos[i] = (int*)malloc(sizeof(int) * grafo->porteProcesos);
	}
	
	for(i = 1; i < grafo->porteProcesos; i++){
		grafo->matrizProcesos[i][1] = 1;
		grafo->matrizProcesos[i][2] = 1;
		grafo->matrizProcesos[1][i] = 1;
		grafo->matrizProcesos[2][i] = 1;
		grafo->matrizProcesos[5][i] = 1;
		grafo->matrizProcesos[4][i] = 1;
	}	
	return grafo;
}
//
//Funcion que lee el archivo para generar la matriz de genes vs procesos
Grafo* leerGenes(Grafo* grafo){
	char* nombre = (char*)malloc(sizeof(char) * 50); 
	FILE* archivo;
	int comprobArch = 0;
	int comprobNom = 0;
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
			printf("Ingrese el nombre de archivo de los Genes:\n");
		}while(scanf("%s", nombre) <= 0);
		archivo = fopen(nombre, "r");
		comprobNom = 0;
	}while(archivo == NULL);
	printf("Leyendo archivo %s\n", nombre);
	free(nombre);
	fscanf(archivo, "%d ", &(grafo->porteGenes));
	int i;	
	grafo->matrizGenes = (int**)malloc(sizeof(int*) * grafo->porteGenes);
	for(i = 0; i < grafo->porteGenes; i++){
		grafo->matrizGenes[i] = (int*)malloc(sizeof(int) * grafo->porteGenes);
	}

	for(i = 1; i < grafo->porteGenes; i++){
		grafo->matrizGenes[i][1] = 1;
		grafo->matrizGenes[1][i] = 1;
		grafo->matrizGenes[3][i] = 1;
	}	
	return grafo;
}
//
//Funcion para printear la matriz de procesos
void printearMatrizP(Grafo* grafo){
	int i,j;
	for(i = 0; i < grafo->porteProcesos; i++){
		for(j = 0; j < grafo->porteProcesos; j++){
			printf("%d ", grafo->matrizProcesos[i][j]);
		}
		printf("\n");
	}
	printf("F \n");
}
//
//Funcion para printear la matriz de genes
void printearMatrizG(Grafo* grafo){
	int i,j;
	for(i = 0; i < grafo->porteGenes; i++){
		for(j = 0; j < grafo->porteGenes; j++){
			printf("%d ", grafo->matrizGenes[i][j]);
		}
		printf("\n");
	}
	printf("F \n");
}
//