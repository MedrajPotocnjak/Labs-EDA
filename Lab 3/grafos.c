#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//Cabeceras
typedef struct grafo Grafo;
Grafo* crearGrafo(char** caracteristicas);
void printearGrafo(Grafo* grafo, int opcion);
void armarGrafo(Grafo* grafo);
int confirmarRand(int* arreglo, int random, int porte);
void rellenarMatrizMaxGrado(Grafo* grafo, int* arreglo, int largo, int peso);
void rellenarMatrizMinGrado(Grafo* grafo, int* arreglo, int largo, int peso);
void escribirArchivo(Grafo* grafo);
Grafo* leerArchivo(char* archivo);
void analizarGrafo(Grafo* grafo);
//Estructuras
typedef struct grafo
{
	int cantVertice;
	int cantArista;
	int ciclo;
	int regular;
	int gradoMaximo;
	int gradoMinimo;
	int peso;
	int conexo;
	int** matrizAdy;
}Grafo;
//
//Main
int main(int argc, char** argv){
	if(argc == 9){
		Grafo* grafo = crearGrafo(argv);
		armarGrafo(grafo);
		printearGrafo(grafo, 1);	
	}
	else if(argc == 3){
		Grafo* grafo2 = leerArchivo(argv[2]);
		if(grafo2 == NULL){
			printf("Archivo vacio, grafo inexistente. \n");
			printf("Favor de ejecutar el programa de nuevo. \n");
		}
		else{
			analizarGrafo(grafo2);
			printearGrafo(grafo2, 2);
		}
	}
}
//

// FUNCIONALIDAD 1: Generación de Grafos

//Funcion para crear el grafo a partir de las caracteristicas entregadas
Grafo* crearGrafo(char** caracteristicas){
	Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
	grafo->cantVertice = atoi(caracteristicas[2]);
	grafo->cantArista = atoi(caracteristicas[3]);
	grafo->ciclo = atoi(caracteristicas[4]);
	grafo->regular = atoi(caracteristicas[5]);
	grafo->gradoMaximo = atoi(caracteristicas[6]);
	grafo->gradoMinimo = atoi(caracteristicas[7]);
	grafo->peso = atoi(caracteristicas[8]);
	grafo->matrizAdy = (int**)malloc(sizeof(int*) * grafo->cantVertice);
	int i;
	for(i = 0; i < grafo->cantVertice; i++){
		grafo->matrizAdy[i] = (int*)malloc(sizeof(int) * grafo->cantVertice);
	}
	int fila;
	int columna;
	for(fila = 0; fila < grafo->cantVertice; fila++){
		for(columna = 0; columna < grafo->cantVertice; columna++){
			grafo->matrizAdy[fila][columna] = 0;
		}

	}
	return grafo;
}
//
//Funcion que permite printear lo almacenado en la estructura grafo y corrobora que esta bien
void printearGrafo(Grafo* grafo, int opcion){
	if(opcion == 1){
		printf("-Caracteristicas: \n");
		printf("%d ", grafo->cantVertice);
		printf("%d ", grafo->cantArista);
		printf("%d ", grafo->ciclo);
		printf("%d ", grafo->regular);
		printf("%d ", grafo->gradoMaximo);
		printf("%d ", grafo->gradoMinimo);
		printf("%d \n", grafo->peso);
		printf("-Matriz: \n");
		int fila;
		int columna;
		for(fila = 0; fila < grafo->cantVertice; fila++){
			for(columna = 0; columna < grafo->cantVertice; columna++){
				printf("%d ", grafo->matrizAdy[fila][columna]);
			}
			printf("\n");
		}
	}
	else if(opcion == 2){
		printf("-Caracteristicas: \n");
		printf("%d ", grafo->cantVertice);
		printf("%d ", grafo->cantArista);
		printf("%d ", grafo->ciclo);
		printf("%d ", grafo->regular);
		printf("%d ", grafo->gradoMaximo);
		printf("%d ", grafo->gradoMinimo);
		printf("%d ", grafo->peso);
		printf("%d \n", grafo->conexo);
		printf("-Matriz: \n");
		int fila;
		int columna;
		for(fila = 0; fila < grafo->cantVertice; fila++){
			for(columna = 0; columna < grafo->cantVertice; columna++){
				printf("%d ", grafo->matrizAdy[fila][columna]);
			}
			printf("\n");
		}
	}
}
//
//Funcion para armar el grafo
void armarGrafo(Grafo* grafo){
	srand(time(NULL));
	int nodo = grafo->cantVertice;
	int aristasRestantes = grafo->cantArista;
	int pesito = grafo->peso/grafo->cantArista;
	int pesoRestante = grafo->peso;

	int num;
	
	int* verticesListos = (int*)malloc(sizeof(int) * grafo->cantVertice);
	int i;
	for(i = 0; i < grafo->cantVertice; i++){
		verticesListos[i] = 0;
	}
	
	int max = grafo->gradoMaximo;
	int maxMasUno = max + 1;
	int* grafoMaximo = (int*)malloc(sizeof(int)*maxMasUno);

	int posicion; 
	for(posicion = 0 ; posicion < maxMasUno; posicion++){
		grafoMaximo[posicion] = 0;	
	}
	posicion = 0;
	while(posicion < maxMasUno){
		num = 1 + rand()%((nodo + 1) - 1);
		if(confirmarRand(grafoMaximo, num, maxMasUno) == 0){
			grafoMaximo[posicion] = num;
			posicion++;	
		}
	}
	
	verticesListos[0] = grafoMaximo[0];
	pesoRestante = pesoRestante - (max*pesito);
	rellenarMatrizMaxGrado(grafo, grafoMaximo, maxMasUno, pesito);
	aristasRestantes = aristasRestantes - max;
	if(aristasRestantes == 0){
		escribirArchivo(grafo);
	}

	posicion = 0;
	int min = grafo->gradoMinimo;

	int minMasUno = min + 1;
	if(min > 1 && aristasRestantes > 0){

		int* grafoMinimo = (int*)malloc(sizeof(int)*minMasUno);

		while(aristasRestantes > 0){
			for(posicion = 0 ; posicion < minMasUno; posicion++){
				grafoMinimo[posicion] = 0;	
			}
			posicion = 0;
			while(posicion < minMasUno){
				num = 1 + rand()%((nodo + 1) - 1);
				if(confirmarRand(verticesListos, num, grafo->cantVertice) == 0){
					if(confirmarRand(grafoMinimo, num, minMasUno) == 0){
						grafoMinimo[posicion] = num;
						posicion++;
					}
				}
			}

			int contador = 0;
			int verificador = 0;
			while(verificador < grafo->cantVertice){
				if(verticesListos[verificador] != 0){
					contador = contador + 1;	
				}
				verificador = verificador + 1;
			}

			verticesListos[contador] = grafoMinimo[0];
			if(min*pesito < pesoRestante){
				pesoRestante = pesoRestante - (min*pesito);
				rellenarMatrizMinGrado(grafo, grafoMinimo, minMasUno, pesito);
			}
			else{
				pesito = pesoRestante/min;
				pesoRestante = pesoRestante - (min*pesito);
				rellenarMatrizMinGrado(grafo, grafoMaximo, minMasUno, pesito);
			}
			aristasRestantes = aristasRestantes - min;

			int numero1;
			int numero2;
			if(aristasRestantes == 1){
				int veri = 0;
				while(veri == 0){
					numero1 = 1 + rand()%((nodo + 1) - 1);
					numero2 = 1 + rand()%((nodo + 1) - 1);
					if(numero1 != numero2){
						if(confirmarRand(verticesListos, numero1, grafo->cantVertice) == 0 && confirmarRand(verticesListos, numero2, grafo->cantVertice) == 0){
							grafo->matrizAdy[numero1 - 1][numero2 - 1] = pesoRestante;
							grafo->matrizAdy[numero2 - 1][numero1 - 1] = pesoRestante;
							pesoRestante = 0;
							aristasRestantes = 0;
							veri = 1;
						}
					}
				}
				escribirArchivo(grafo);
			}
		}
		
		if(aristasRestantes == 0){
			escribirArchivo(grafo);
		}
	}
}
//
//Funcion que permite verificar si el numero se encuentra en el arreglo
int confirmarRand(int* arreglo, int random, int porte){
	int posicion;
	for(posicion = 0; posicion < porte; posicion++){
		if(random == arreglo[posicion]){
			return 1;
		}
	}
	return 0;
}
//
//Funcion para llenar la Matriz de Adyacencia
void rellenarMatrizMaxGrado(Grafo* grafo, int* arreglo, int largo, int peso){
	int posicion;
	int nuevoLargo = largo - 1;
	for(posicion = 0; posicion < nuevoLargo; posicion++){
		int nuevaPosicion = posicion + 1;
		int fila = arreglo[0] - 1;
		int columna = arreglo[nuevaPosicion] - 1;
		grafo->matrizAdy[fila][columna] = peso;
		grafo->matrizAdy[columna][fila] = peso;
	}
}
//
//Funcion para llenar la Matriz de Adyacencia
void rellenarMatrizMinGrado(Grafo* grafo, int* arreglo, int largo, int peso){
	int posicion;
	int nuevoLargo = largo - 1;
	for(posicion = 0; posicion < nuevoLargo; posicion++){
		int nuevaPosicion = posicion + 1;
		int fila = arreglo[0] - 1;
		int columna = arreglo[nuevaPosicion] - 1;
		grafo->matrizAdy[fila][columna] = peso;
		grafo->matrizAdy[columna][fila] = peso;
	}
}
//
//Funcion que permite crear el archivo y rellenarlo con lo que se pide
void escribirArchivo(Grafo* grafo){
	int largo = grafo->cantVertice;
	FILE* archivoSalida = fopen("grafo.out", "w");
	int fila;
	int columna;
	for(fila = 0; fila < largo; fila++){
		fprintf(archivoSalida, "%d ",fila + 1);
		for(columna = 0; columna < largo; columna++){
			if(grafo->matrizAdy[fila][columna] != 0){
				fprintf(archivoSalida, "%d,%d ",columna+ 1, grafo->matrizAdy[fila][columna]);
			}
		}
		fprintf(archivoSalida, "\n");
	}
}
//

// FUNCIONALIDAD 2: Analisis de Grafos

//Funcion que lee el archivo para luego poder crear el grafo a la inversa
Grafo* leerArchivo(char* archivo){
	FILE* archivoEntrada;
	int comprobArch = 0;
	int comprobNom = 0;
	do{
		if(comprobArch == 1){
			printf("Nombre de archivo inexistente.\n");
			printf("Por favor ingrese un nombre válido: ");
			scanf("%s", archivo);
		}
		else{
			comprobArch = 1;
		}
		do{
			if(comprobNom == 1){
				printf("Nombre ingresado no valido.\n");
				printf("Por favor ingrese un nombre válido: ");
				scanf("%s", archivo);
			}
			else{
				comprobNom = 1;
			}
		}while(archivo <= 0);
		archivoEntrada = fopen(archivo, "r");
		comprobNom = 0;
	}while(archivoEntrada == NULL);

	int i = 0;
	int largo;
	Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
	grafo->cantVertice = 0;
	grafo->cantArista = 0;
	grafo->ciclo = 0;
	grafo->regular = 0;
	grafo->gradoMaximo = 0;
	grafo->gradoMinimo = 0;
	grafo->peso = 0;
	char* linea = (char*)malloc(sizeof(char) * 100);
	int contLinea = 0;

	while(feof(archivoEntrada) == 0){
    	fgets(linea, 100, archivoEntrada);
    	contLinea++;
	}
	if(contLinea == 1){
		return NULL;
	}
	else if(contLinea == 2){
		printf("Es un grafo de solo 1 vertice. \n");
		grafo->cantVertice = 1;
		grafo->cantArista = 0;
		grafo->ciclo = 0;
		grafo->regular = 1;
		grafo->gradoMaximo = 0;
		grafo->gradoMinimo = 0;
		grafo->peso = 0;
		grafo->conexo = 1;
		return grafo;
	}
	else{
		largo = contLinea - 1;
		grafo->cantVertice = largo;
		grafo->matrizAdy = (int**)malloc(sizeof(int*) * largo);
		int i;
		for(i = 0; i < largo; i++){
			grafo->matrizAdy[i] = (int*)malloc(sizeof(int) * largo);
		}
		int fila;
		int columna;
		for(fila = 0; fila < grafo->cantVertice; fila++){
			for(columna = 0; columna < grafo->cantVertice; columna++){
				grafo->matrizAdy[fila][columna] = 0;
			}
		}
		fclose(archivoEntrada);
		archivoEntrada = fopen(archivo, "r");
		int contador;
		int contador2 = 0;
		int maximo = 0;
		int minimo = 10000000;
		int aristas;
		int peso;
		int pesoTotal = 0;
		char caracter;
		int vertice1;
		int vertice2;
		char* linea = (char*)malloc(sizeof(char) * 100);
		for(i = 0; i < largo; i++){
			contador = 0;
			peso = 0;
			fscanf(archivoEntrada, "%d%c", &vertice1, &caracter);
			while(feof(archivoEntrada) == 0){
				if(caracter == '\n'){
					break;
				}
				else if(caracter == '\r'){
					fgetc(archivoEntrada);
					break;
				}
				fscanf(archivoEntrada, "%d,%d%c", &vertice2, &peso, &caracter);
				grafo->matrizAdy[vertice1-1][vertice2-1] = peso;
				grafo->matrizAdy[vertice2-1][vertice1-1] = peso;
				contador = contador + 1;
				contador2 = contador2 + 1;
				pesoTotal = pesoTotal + peso;
			}

			if(contador > maximo){
				maximo = contador;
				grafo->gradoMaximo = maximo;
			}
			if(contador < minimo){
				minimo = contador;
				grafo->gradoMinimo = minimo;
			}
		}
		grafo->cantArista = contador2/2;
		grafo->peso = pesoTotal/2;
		return grafo;
	}
}
//
//Funcion para analizar el grafo
void analizarGrafo(Grafo* grafo){
	if(grafo->cantVertice == 1){
		FILE* archivoSalida = fopen("parametros.out", "w");
		fprintf(archivoSalida, "%d \n", grafo->cantVertice);
		fprintf(archivoSalida, "%d \n", grafo->cantArista);
		fprintf(archivoSalida, "%d \n", grafo->ciclo);
		fprintf(archivoSalida, "%d \n", grafo->regular);
		fprintf(archivoSalida, "%d \n", grafo->gradoMaximo);
		fprintf(archivoSalida, "%d \n", grafo->gradoMinimo);
		fprintf(archivoSalida, "%d \n", grafo->peso);
		fprintf(archivoSalida, "%d \n", grafo->conexo);
	}
	else{
		int ciclos;
		if(grafo->gradoMaximo != grafo->gradoMinimo){
			grafo->regular = 0;
		}
		else if(grafo->gradoMaximo == grafo->gradoMinimo){
			grafo->regular = 1;
		}
		
		if(grafo->gradoMinimo == 0){
			grafo->conexo = 0;
		}
		else if(grafo->gradoMinimo != 0){
			grafo->conexo = 1;
		}
		FILE* archivoSalida = fopen("parametros.out", "w");
		fprintf(archivoSalida, "%d \n", grafo->cantVertice);
		fprintf(archivoSalida, "%d \n", grafo->cantArista);
		fprintf(archivoSalida, "%d \n", grafo->ciclo);
		fprintf(archivoSalida, "%d \n", grafo->regular);
		fprintf(archivoSalida, "%d \n", grafo->gradoMaximo);
		fprintf(archivoSalida, "%d \n", grafo->gradoMinimo);
		fprintf(archivoSalida, "%d \n", grafo->peso);
		fprintf(archivoSalida, "%d \n", grafo->conexo);
	}
}
//
//