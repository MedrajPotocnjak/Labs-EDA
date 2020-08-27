#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Cabeceras
typedef struct matriz Matriz;
void liberarMatriz(Matriz* matriz);
Matriz* leer();
Matriz* crearMatriz(int porte);
void llenarMatriz(int* valores, Matriz* matLlenar);
Matriz* crearSubMatriz(int i, int j, Matriz* antigua);
long calcularDeterminante(Matriz* matriz);
//
//Estructuras
typedef struct matriz
{
	int porte;
	int** matrizz;
}Matriz;
//
//Main
int main(){
	Matriz* matriz = leer();
	long result = calcularDeterminante(matriz);
	liberarMatriz(matriz);
	printf("Determinante: ");
	printf("%ld", result);
	printf("\n");
	return 1;
}
//
//Funcion que es llamada para liberar espacio asignado a una matriz
void liberarMatriz(Matriz* matriz){
	int i;
	for(i = 0; i < matriz->porte; i++){
		free(matriz->matrizz[i]);
	}
	free(matriz->matrizz);
	free(matriz);
	return;
}
//
//Funcion utilizada para leer el archivo.in y construir la primera matriz
Matriz* leer(){
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
			printf("Ingrese el nombre de archivo:\n");
		}while(scanf("%s", nombre) <= 0);
		archivo = fopen(nombre, "r");
		comprobNom = 0;
	}while(archivo == NULL);
	free(nombre);
	Matriz* nueva = (Matriz*)malloc(sizeof(Matriz));
	fscanf(archivo, "%d", &(nueva->porte));
	int i;
	nueva->matrizz = (int**)malloc(sizeof(int*) * nueva->porte);
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
	return nueva;
}
//
//Funcion hecha para crear matrices 
Matriz* crearMatriz(int porte){
    Matriz* nueva = (Matriz*)malloc(sizeof(Matriz));
    nueva->porte = porte;
    nueva->matrizz = (int**)malloc(sizeof(int*) * (porte + 2));
    int j;
    for(j = 0; j < porte; j++){
        nueva->matrizz[j] = (int*)malloc(sizeof(int) * (porte + 2));
    }
    return nueva;
} 
//
//Funcion hecha para llenar matrices
void llenarMatriz(int* valores, Matriz* matLlenar){
    int i;
    int j;
    int k = 0;
    for(i = 0; i < matLlenar->porte; i++){
        for(j = 0; j < matLlenar->porte; j++){
            matLlenar->matrizz[i][j] = valores[k];
            k++;
        }
    }
    return;
}
//
//Funcion que recibe una matriz de porte n, y crea una de porte n-1 siguiendo la ecuacion de determinante
Matriz* crearSubMatriz(int i, int j, Matriz* antigua){
    int porteNueva = antigua->porte - 1;
    Matriz* submatriz = crearMatriz(porteNueva);
    int k;
    int l;
    int m = 0;
    int* valores = (int*)malloc(sizeof(int) * (porteNueva * porteNueva));
    for(k = 0; k < antigua->porte; k++){
        for(l = 0; l < antigua->porte; l++){
            if(k != i && l != j){
                valores[m] = antigua->matrizz[k][l];
                m++;
            }
        }
    }
    llenarMatriz(valores, submatriz);
    free(valores);
    return submatriz;
}
//
//Funcion utilizada para calcular el determinante de una forma recursiva
long calcularDeterminante(Matriz* matriz){
    if(matriz->porte == 1){
        return matriz->matrizz[0][0];
    }
    else{
        long determinante = 0;
		int j;
        for(j = 0; j < matriz->porte; j++){	
        	Matriz* submatriz;
			submatriz = crearSubMatriz(0, j, matriz);
            determinante = determinante + matriz->matrizz[0][j] * pow(-1, 2+j) * calcularDeterminante(submatriz);
            liberarMatriz(submatriz);
        }
		return determinante;
    }
}
//