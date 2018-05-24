#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctime> 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

const int MIN_VEL = 100;
const int MAX_VEL = 50000000;

char* clave;
int velAutofantastico;

int menu();
int ingreso();
void salida(unsigned char);
int autofantastico();
void delay(unsigned long int);

int main(int argc, char *argv[]) {
	
	velAutofantastico = 30000000;
	
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
			//system("color 02");		
			printf("*");			
		}else{
			//system("color 08");	
			printf("_");
		}					
	}
}

int autofantastico(){
		
	system("CLS");
	//system("color 07");	
	printf("Auto Fantastico presiona enter para salir\n");	
	printf("Flecha arriba aumenta velocidad, flecha abajo disminuye velocidad\n");
	
	do{			
				
		for(int i = 1; i < 128; i = i<<1){
			printf("\r");	
			salida(i);
			delay(velAutofantastico);
		}
		
		for(int i = 128; i > 1; i = i>>1){
			printf("\r");	
			salida(i);
			delay(velAutofantastico);
		}
		
		if(kbhit() && getch() == 13)
				return 0;
				
		if(kbhit() && getch() == 72 && velAutofantastico < MAX_VEL)
				velAutofantastico += 100;
				
		if(kbhit() && getch() == 80 && velAutofantastico > MIN_VEL)
				velAutofantastico -= 100;
			
	}while(1);
	
	system("CLS");
}

void delay(unsigned long int a){
	while(a) a--;
}
