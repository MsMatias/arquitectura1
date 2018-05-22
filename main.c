#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int menu();
int ingreso();
void salida(unsigned char);

int main(int argc, char *argv[]) {
	
	int estado_ingreso = 0;
	
	while(estado_ingreso ){
		estado_ingreso = ingreso();		
	}
	
	menu();
		
	system("PAUSE");
	
	return 0;
}

int ingreso(){
	
	int
	
	return 0;
}

int menu (){
	
	system("CLS");
	
	int seleccion;
	int dato;
	

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

	system("PAUSE");
	menu();
}

void salida(unsigned char c){
	
	int b = 0;
	int i = 0;
	
	for(i = 0; i < 8; i++){
		b = (c >> i) & 1;
		if(b == 1){
			printf(" * ");
		}else{
			printf(" _ ");
		}
	}
}
