#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, int *argv[]){

	int numero;
	int par;
	int divisible;

	if (argc != 2){
		perror("\nError en argumentos");
		exit(-1);
	}

	pid_t pid;
	pid = fork();

	if (pid < 0){
		perror("\nError en el fork");
		exit(-1);
	}
	else if (pid == 0){
		printf("\nSoy el proceso hijo");
		numero = atoi(argv[1]);
		par = numero%2;
		if (par == 1){
			printf("\nEl número es impar");
		}else{
			printf("\nEl número es par");
		}
	}else{
		printf("\nSoy el proceso padre");
		numero = atoi(argv[1]);
		divisible = numero%4;
		if (divisible == 0){
			printf("\nEl número es divisible por 4");
		}else{
			printf("\nEl número no es divisible por 4");
		}
	}

	printf("\n");
	return(0);
}
