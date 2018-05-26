#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctime> 
#include <windows.h> 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

 void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 } 
 
#define ABAJO GetAsyncKeyState(VK_DOWN) & ( 1 << 15 )
#define ARRIBA GetAsyncKeyState(VK_UP) & ( 1 << 15 )
#define ENTER GetAsyncKeyState(VK_RETURN) & ( 1 << 15 )
#define DELAY_TIME 200000000

//CONSTANTES
const int MIN_VEL = 10;
const int MAX_VEL = 400;

//Variable de clock
unsigned long t1, t0;

//Clave
char* clave;

//velocidades
int velocidades[] = {100, 100, 100, 100};

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

//Array de datos de tenis
char datosTenis[] = {
0x85,
0x86,
0x89,
0x89,
0x91,
0x91,
0xA1,
0x61,
0x91,
0x91,
0x89,
0x89
};

//Declaraciones de firmas de funciones
int menu();
int ingreso();
void salida(unsigned char);
int autofantastico(int);
int elchoque(int);
int billar(int);
int tenis(int);
void delay(unsigned long int);

int main(int argc, char *argv[]) {
	
	//Asignamos espacio de memoria al puntero clave
	clave = new char[5];
	
	//Guardamos en clave un dato
	strcpy(clave, "38411");
	
	//Inicializamos contador de deteccion de teclas
	t0=clock();
	
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
			if(caracter != 13 && caracter != 8 && c < 5){
				printf("*");
				*(entrada + c) = caracter;
				c++;
			}	
			if(caracter == 8 && c > 0){
				printf("%c", 8);
				printf(" ");
				printf("%c", 8);
				c--;
			}		
		}		
	}while(!(ENTER && (clock()-t0) >= 200));	
	
	t0 = clock();
	
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
	
	int seleccion = 1;
	int dato;	
	int estado = 0;	
		
	gotoxy(0, 0);	
	printf("--------------MENU---------------\n");
	printf(">>Auto fantastico\n");
	printf("- El choque\n");
	printf("- Billar\n");
	printf("- Tenis\n");
	printf("- Salir\n");
	//printf("Seleccione una opcion: ");	
	gotoxy(0, seleccion);
		
	do{		
	if(ABAJO && (clock()-t0) >= 200 && seleccion < 5){
		printf("\r- ");	
		seleccion++;
		gotoxy(0, seleccion);
		printf("\r>>");		
		t0 = clock();
	}				
				
				
	if(ARRIBA && (clock()-t0) >= 200 && seleccion > 1){
		printf("\r- ");	
		seleccion--;
		gotoxy(0, seleccion);
		printf("\r>>");	
		t0 = clock();
	}
	
	}while(!(ENTER && (clock()-t0) >= 200));
	
	delay(DELAY_TIME);
	
	switch(seleccion){
		
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
			t1=clock();
			tenis(seleccion-1);
		break;
		
		case 5:
			return 0;			
		break;
		
		default:	
			printf("No seleccionaste ninguna opcion\n");
		break;
		
	}
	
	menu();
	
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
		
	do{			
		
		if(i < 128 && !estado && (clock()-t1) >= velocidades[v]){
			printf("\r");	
			salida(i);
			i = i<<1;
			t1=clock();
		}else if(i == 128){
			estado = 1;
		}
		
		if(i > 1 && estado && (clock()-t1) >= velocidades[v]){
			printf("\r");	
			salida(i);
			i = i>>1;
			t1=clock();
		}else if(i == 1){
			estado = 0;
		}
				
		if(ABAJO && (clock()-t0) >= 200 && velocidades[v] < MAX_VEL){
			velocidades[v] += 10;
			t0 = clock();
		}
				
				
		if(ARRIBA && (clock()-t0) >= 200 && velocidades[v] > MIN_VEL){
			velocidades[v] -= 10;
			t0 = clock();
		}
			
	}while(!(ENTER && (clock()-t0) >= 200));
	delay(DELAY_TIME);
	system("CLS");
	return 0;
		
}

//Funcion de el choque
int elchoque(int v){
		
	system("CLS");
	printf("El choque presiona enter para salir\n");	
	printf("Flecha arriba aumenta velocidad, flecha abajo disminuye velocidad\n");
	
	int i = 0;
	
	do{	
	
		
		if((clock()-t1) >= velocidades[v]){
			printf("\r");	
			salida(datosElchoque[i]);
			if(i < sizeof(datosElchoque)-1)
				i++;
			else
				i = 0;			
			t1=clock();
		}
						
		if(ABAJO && (clock()-t0) >= 200 && velocidades[v] < MAX_VEL){
			velocidades[v] += 10;
			t0 = clock();
		}
				
				
		if(ARRIBA && (clock()-t0) >= 200 && velocidades[v] > MIN_VEL){
			velocidades[v] -= 10;
			t0 = clock();
		}
			
	}while(!(ENTER && (clock()-t0) >= 200));
	delay(DELAY_TIME);
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
						
		if(ABAJO && (clock()-t0) >= 200 && velocidades[v] < MAX_VEL){
			velocidades[v] += 10;
			t0 = clock();
		}
				
				
		if(ARRIBA && (clock()-t0) >= 200 && velocidades[v] > MIN_VEL){
			velocidades[v] -= 10;
			t0 = clock();
		}
			
	}while(!(ENTER && (clock()-t0) >= 200));
	delay(DELAY_TIME);
	system("CLS");
	return 0;
	
}

//Funcion Tenis
int tenis(int v){
	
	system("CLS");
	printf("Tenis presiona enter para salir\n");	
	printf("Flecha arriba aumenta velocidad, flecha abajo disminuye velocidad\n");
	
	int i = 0;
	
	do{			
		
		if((clock()-t1) >= velocidades[v]){
			printf("\r");	
			salida(datosTenis[i]);
			if(i < sizeof(datosTenis)-1)
				i++;
			else
				i = 0;			
			t1=clock();
		}
						
		if(ABAJO && (clock()-t0) >= 200 && velocidades[v] < MAX_VEL){
			velocidades[v] += 10;
			t0 = clock();
		}
				
				
		if(ARRIBA && (clock()-t0) >= 200 && velocidades[v] > MIN_VEL){
			velocidades[v] -= 10;
			t0 = clock();
		}
			
	}while(!(ENTER && (clock()-t0) >= 200));
	delay(DELAY_TIME);
	system("CLS");
	return 0;
	
}

//Funcion delay (retardo)
void delay(unsigned long int a){
	while(a) a--;
}
