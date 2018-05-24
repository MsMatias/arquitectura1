#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctime> 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

const int MIN_VEL = 10;
const int MAX_VEL = 500;

unsigned t1;

char* clave;
int velAutofantastico;

int menu();
int ingreso();
void salida(unsigned char);
int autofantastico();
void delay(unsigned long int);

int main(int argc, char *argv[]) {
	
	velAutofantastico = 100;
	
	clave = new char[5];
	
	strcpy(clave, "38411");
	
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
		
		entrada = new char[5];
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
			t1=clock();		
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
			printf("*");			
		}else{
			printf("_");
		}					
	}
}

int autofantastico(){
		
	system("CLS");
	printf("Auto Fantastico presiona enter para salir\n");	
	printf("Flecha arriba aumenta velocidad, flecha abajo disminuye velocidad\n");
	
	int i = 1;
	int estado = 0;
	
	do{			
	
		if(i < 128 && !estado && (clock()-t1) >= velAutofantastico){
			printf("\r");	
			salida(i);
			i = i<<1;
			t1=clock();
		}else if(i == 128){
			estado = 1;
		}
		
		if(i > 1 && estado && (clock()-t1) >= velAutofantastico){
			printf("\r");	
			salida(i);
			i = i>>1;
			t1=clock();
		}else if(i == 1){
			estado = 0;
		}
		
		if(kbhit() && getch() == 13){
			system("CLS");
			return 0;
		}				
				
		if(kbhit() && getch() == 72 && velAutofantastico < MAX_VEL)
				velAutofantastico += 10;
				
		if(kbhit() && getch() == 80 && velAutofantastico > MIN_VEL)
				velAutofantastico -= 10;
			
	}while(1);
		
}

void delay(unsigned long int a){
	while(a) a--;
}
