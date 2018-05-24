#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

char* clave;

int menu();
int ingreso();
void salida(unsigned char);
void autofantastico();
void delay(unsigned long int);

int main(int argc, char *argv[]) {
	
	clave = new char[6];
	
	strcpy(clave, "123456");
	
	printf("Ingrese la clave: \n");
	
	if(ingreso()){
		menu();
	}else{
		printf("3 intentos mal, chau");
	}
			
	
	
	return 0;
}

int ingreso(){	
	
	int error = 0;
	char* entrada;
	char caracter;	
	int c = 0;	
	int comp;
	
	
	do{
		
		entrada = new char[6];
		c = 0;
	
	do{		
		if(caracter = getch()){
			printf("*");
			if(caracter != 13){
				*(entrada + c) = caracter;
				c++;
			}			
		}		
	}while(caracter != 13);	
	
	comp = strcmp(clave, entrada);
	
	if(error > 2)
		return 0;
	
	if(!comp){
		return 1;
	}else{
		system("CLS");
		printf("Intente nuevamente:\n");
		error++;
	}
		
	}while(comp > 0 || comp < 0);
		
	return 0;
}



int menu (){
	
	system("CLS");
	
	int seleccion;
	int dato;	
	
	do{
	
	printf("--------------MENU---------------\n");
	printf("1) Auto fantastico\n");
	printf("2) La carrera\n");
	printf("3) funcion 1\n");
	printf("4) funcion 2\n");
	printf("0) Salir\n");
	printf("Seleccione una opcion: ");	
	
	scanf("%i", &seleccion);

	switch(seleccion){
		
		case 0:
			return 0;
		break;
		
		case 1:
			printf("Seleccionaste auto fantastico \n");
			autofantastico();
		break;
		
		case 2:
			printf("Seleccionaste la carrera\n");
		break;
		
		case 3:
			printf("Seleccionaste funcion 1\n");
			scanf("%i", &dato);			
			salida(dato);
		break;
		
		case 4:
			printf("Seleccionaste funcion 2\n");
		break;
		
		default:	
			printf("No seleccionaste ninguna opcion\n");
		break;
		
	}	

	}while(1);
}

void salida(unsigned char c){
	

	int i = 0;
	
	for(i = 7; i >= 0; i--){
		if((c >> i) & 1){
			system("color");		
			printf("*");			
		}else
			printf("_");		
	}
}

void autofantastico(){
	
	int valor = 0;
	
	do{
	
			
		for(int i = 1; i < 128; i = i<<1){
			system("CLS");
			salida(i);
			delay(10000000);
		}
			
		for(int i = 128; i > 1; i = i>>1){
			system("CLS");
			salida(i);
			delay(10000000);
		}
			
	}while(!kbhit());
}

void delay(unsigned long int a){
	while(a) a--;
}
