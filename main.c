#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void salida(unsigned char);

int main(int argc, char *argv[]) {
	
	int dato;
	
	do{
	
	
	printf("--------------MENU---------------\n");
	printf("1) Auto fantastico\n");
	printf("2) La carrera\n");
	printf("3) funcion 1\n");
	printf("4) funcion 2\n");
	printf("0) Salir\n");
	printf("Seleccione una opcion: ");
	
	
	scanf("%i", &dato);

	switch(dato){
		
		case 0:
		break;
		
		case 1:
			printf("Seleccionaste auto fantastico \n");
		break;
		
		case 2:
			printf("Seleccionaste la carrera\n");
		break;
		
		case 3:
			printf("Seleccionaste funcion 1\n");
		break;
		
		case 4:
			printf("Seleccionaste funcion 2\n");
		break;
		
		default:			
			system("CLS");
			printf("No seleccionaste ninguna opcion\n");
		break;
		
	}	
	
	}while(dato < 0 || dato > 5);
	
	salida(255);
	
	
	system("PAUSE");
	return 0;
}

void salida(unsigned char c){
	printf("%i \n", c >> 1);
	printf("%i \n", c >> 2);
	printf("%i \n", c >> 3);
	printf("%i \n", c >> 4);
}
