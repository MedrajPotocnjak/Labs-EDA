#include <stdio.h>
#include <stdlib.h>

int* panquequear(int* arr, int len);
int* appendar_int(int* arr, int len, int valor);
void reverse(int arr[], int n);
int get_max(int* arr, int len);
int get_index(int* arr, int len, int valor);


int main(){

	int n;
	printf("Ingrese cantidad de panqqs: ");
	scanf("%d", &n);
	int arr[n];
	int i;
	for (i = 0; i < n; ++i){
		printf("Ingrese diametro del panqq: ");
	    scanf("%d", &arr[i]);
	}

	int* secuencia = panquequear(arr, n);
	printf("Panquequeado\n");
	printf("La secuencia es: ");
	for(i = 0; secuencia[i] != 0; i++){
		printf("%d ", secuencia[i]);
	}
	printf("0\n");

	return 0;
}

int* panquequear(int* arr, int len){
	printf("Panquequeando\n");
	int* secuencia = (int*)malloc(sizeof(int));
	int len_secuencia = 0;

	int indice_ordenado = 0;
	int ind_mayor_no_ordenado = 0;
	int len_subArr = len;

	while(indice_ordenado != len){
		//Al principio subArr es el arreglo completo, al ordenarse un nro subArr tendra el resto
		int* subArr = &arr[indice_ordenado];

		int i;
		printf("subArr desde arr[%d]\n", indice_ordenado);
		for(i = 0; i < len_subArr; i++){
			printf("subArr[%d]: %d\n", i, subArr[i]);
		}

		//Revisar si el 1er elemento de subArr esta ordenado
		int max_sub = get_max(subArr, len_subArr);
		printf("calculo get_max = %d\n", max_sub);
		int index_max_sub = get_index(subArr, len_subArr, max_sub);
		printf("calculo index_max_sub = %d\n", index_max_sub);

		if(index_max_sub != 0){ //Si no esta ordenado

			printf("%d no esta ordenado\n", max_sub);
			ind_mayor_no_ordenado = index_max_sub;
			printf("ind_mayor_no_ordenado = %d\n", ind_mayor_no_ordenado);

			//Hay que ordenarlo xd hay que llevarlo al final, y luego al principio
			//Si no esta en el final, se voltea en su indice
			printf("len_subArr = %d\n", len_subArr);
			if(ind_mayor_no_ordenado != (len_subArr - 1)){

				int* subArrVoltear = &subArr[ind_mayor_no_ordenado];
				int i;
				printf("subArrVoltear desde subArr[%d]\n", ind_mayor_no_ordenado);
				int len_subArrVoltear = len_subArr - ind_mayor_no_ordenado;

				for(i = 0; i < len_subArrVoltear; i++){
					printf("subArrVoltear[%d]: %d\n", i, subArrVoltear[i]);
				}

				reverse(subArrVoltear, len_subArrVoltear);
				printf("subArr despues de reverseo de subArrVoltear:\n");
				for(i = 0; i < len_subArr; i++){
					printf("\tsubArr[%d]: %d\n", i, subArr[i]);
				}

				secuencia = appendar_int(secuencia, len_secuencia, indice_ordenado + ind_mayor_no_ordenado + 1);
				printf("Se appendeo %d en secuencia\n", indice_ordenado + ind_mayor_no_ordenado + 1);
				len_secuencia++;
			}

			//Si ya esta en el final, se voltea desde el inicio de subArr
			reverse(subArr, len_subArr);
			printf("Se reverseo subArr\n");
			printf("arr despues de reverseo de subArr:\n");
			for(i = 0; i < len; i++){
				printf("\tarr[%d]: %d\n", i, arr[i]);
			}

			secuencia = appendar_int(secuencia, len_secuencia, indice_ordenado + 1);
			printf("Se appendeo %d en secuencia\n", indice_ordenado + 1);
			len_secuencia++;

		}

		indice_ordenado++;
		len_subArr--;

	}
	printf("termino while\n");

	secuencia = appendar_int(secuencia, len_secuencia, 0);

	return secuencia;
}

int* appendar_int(int* arr, int len, int valor){
	if(len == 0){
		arr[0] = valor;
		return arr;
	}
	int* appendado;
	appendado = (int*) realloc(arr, (len + 1) * sizeof(arr[0]));
	appendado[len] = valor;
	return appendado;
}

void reverse(int arr[], int n){
	int aux[n];

	for (int i = 0; i < n; i++) {
		aux[n - 1 - i] = arr[i];
	}

	for (int i = 0; i < n; i++) {
		arr[i] = aux[i];
	}
}

int get_max(int* arr, int len){

	if(len == 0){
		printf("No hay elementos en arr\n");
		return -1;
	}

	int max = arr[0];
	int i;
	for(i = 0; i < len; i++){
		if(arr[i] > max){
			max = arr[i];
		}
	}

	return max;
}

int get_index(int* arr, int len, int valor){

	int i;
	int index = -1;
	for(i = 0; i < len; i++){
		if(arr[i] == valor){
			index = i;
			break;
		}
	}

	return index;
}
