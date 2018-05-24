#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctime> 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

//CONSTANTES
const int MIN_VEL = 5;
const int MAX_VEL = 800;

//Variable de clock
unsigned long t1;

//Clave
char* clave;

//velocidades
int velocidades[] = {100, 100, 100};

//Array de datos para la secuencia de luces de el choque
char datosElchoque[] = { 0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42};

//Array de datos del billar 
char datosBillar[] = {0x10
,0x10
,0x11
,0x11
,0x13
,0x13
,0x17
,0x17
,0x13
,0x13
,0x11
,0x11
,0x10
,0x10
,0x11
,0x11
,0x13
,0x13
,0x17
,0x17
,0x13
,0x13
,0x11
,0x11
,0x10
,0x10
,0x11
,0x13
,0x17
,0x1F
,0x2F
,0x4F
,0x8F
,0x0F
,0x07
,0x07
,0x03
,0x03
,0x01
,0x01
,0x00
};

//Declaraciones de firmas de funciones
int menu();
int ingreso();
void salida(unsigned char);
int autofantastico(int);
int billar(int);
int elchoque(int);
void delay(unsigned long int);

int main(int argc, char *argv[]) {
	
	//Asignamos espacio de memoria al puntero clave
	clave = new char[5];
	
	//Guardamos en clave un dato
	strcpy(clave, "38411");
	
	//Imprimimos mensaje
	printf("Ingrese la clave: \n");
	
	//Verificacion de ingreso de clave (3 intentos)
	if(ingreso()){
		menu();
	}else{
		printf("3 intentos mal, se cierra el programa");
	}	
	
	return 0;
}

//Funcion de control de acceso
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

//Funcion de menu
int menu (){
	
	system("CLS");
	
	int seleccion;
	int dato;	
	
	do{
	
	printf("--------------MENU---------------\n");
	printf("1) Auto fantastico\n");
	printf("2) El choque\n");
	printf("3) Billar\n");
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
			autofantastico(seleccion-1);
		break;
		
		case 2:
			t1=clock();
			elchoque(seleccion-1);
		break;
		
		case 3:
			t1=clock();
			billar(seleccion-1);
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

//Funcion de salida de las luces
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


//Funcion del auto fantastico
int autofantastico(int v){
		
	system("CLS");
	printf("Auto Fantastico presiona enter para salir\n");	
	printf("Flecha arriba aumenta velocidad, flecha abajo disminuye velocidad\n");
	
	int i = 1;
	int estado = 0;
	
	int estadoSalida;
	
	do{			
	
		estadoSalida = (!kbhit() || getch() != 13);	
	
		if(i < 128 && !estado && (clock()-t1) >= velocidades[v] && estadoSalida){
			printf("\r");	
			salida(i);
			i = i<<1;
			t1=clock();
		}else if(i == 128){
			estado = 1;
		}
		
		if(i > 1 && estado && (clock()-t1) >= velocidades[v] && estadoSalida){
			printf("\r");	
			salida(i);
			i = i>>1;
			t1=clock();
		}else if(i == 1){
			estado = 0;
		}
				
		if(kbhit() && getch() == 80 && velocidades[v] < MAX_VEL)
				velocidades[v] += 5;
				
		if(kbhit() && getch() == 72 && velocidades[v] > MIN_VEL)
				velocidades[v] -= 5;
			
	}while(estadoSalida);
	
	system("CLS");
	return 0;
		
}

//Funcion de el choque
int elchoque(int v){
		
	system("CLS");
	printf("El choque presiona enter para salir\n");	
	printf("Flecha arriba aumenta velocidad, flecha abajo disminuye velocidad\n");
	
	int i = 0;
	int estadoSalida;
	
	do{	
	
		estadoSalida = (!kbhit() || getch() != 13);		
		
		if((clock()-t1) >= velocidades[v] && estadoSalida){
			printf("\r");	
			salida(datosElchoque[i]);
			if(i < sizeof(datosElchoque)-1)
				i++;
			else
				i = 0;			
			t1=clock();
		}
						
		if(kbhit() && getch() == 80 && velocidades[v] < MAX_VEL)
				velocidades[v] += 5;
				
		if(kbhit() && getch() == 72 && velocidades[v] > MIN_VEL)
				velocidades[v] -= 5;
			
	}while(estadoSalida);
	
	system("CLS");
	return 0;
		
}

//Funcion billar
int billar(int v){
	
	system("CLS");
	printf("Billar presiona enter para salir\n");	
	printf("Flecha arriba aumenta velocidad, flecha abajo disminuye velocidad\n");
	
	int i = 0;
	
	do{			
		
		if((clock()-t1) >= velocidades[v]){
			printf("\r");	
			salida(datosBillar[i]);
			if(i < sizeof(datosBillar)-1)
				i++;
			else
				i = 0;			
			t1=clock();
		}
						
		if(kbhit() && getch() == 80 && velocidades[v] < MAX_VEL)
				velocidades[v] += 10;
				
		if(kbhit() && getch() == 72 && velocidades[v] > MIN_VEL)
				velocidades[v] -= 10;
			
	}while(!kbhit() || getch() != 13);
	
	system("CLS");
	return 0;
	
}

//Funcion delay (retardo)
void delay(unsigned long int a){
	while(a) a--;
}
