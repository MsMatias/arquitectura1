#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctime> 
#include <windows.h> 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

//Funcion gotoxy definida por que no existe en windows.h
 void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 } 
 
//Define de deteccion de tecla flecha abajo (el corrimiento del 1 es por que me interesa el bit mas significativo)
#define ABAJO GetAsyncKeyState(VK_DOWN) & ( 1 << 15 )
//Define de deteccion de tecla flecha arriba (el corrimiento del 1 es por que me interesa el bit mas significativo)
#define ARRIBA GetAsyncKeyState(VK_UP) & ( 1 << 15 )
//Define de deteccion de tecla flecha abajo (el corrimiento del 1 es por que me interesa el bit mas significativo)
#define ENTER GetAsyncKeyState(VK_RETURN) & ( 1 << 15 )
//Define de delay
#define DELAY_TIME 150000000

//CONSTANTES
const int MIN_VEL = 20; //Minima velocidad de refrescamiento de secuencia
const int MAX_VEL = 800; //Maxima velocidad de refrescamiento de secuencia

//Variable de clock
unsigned long t1, t0;

//Clave
char* clave;

//velocidades
int velocidades[] = {100, 100, 100, 100};

//Array de datos para la secuencia de luces de el choque
char datosElchoque[] = { 0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42};

//Array de datos del billar 
char datosBillar[] = {
0x08,
0x09,
0x09,
0x0B,
0x0B,
0x09,
0x09,
0x0B,
0x0B,
0x09,
0x0B,
0x0F,
0x17,
0x23,
0x41,
0x80,
0x00
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
		printf("\n3 intentos mal, se cierra el programa");
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
		
		//Asignacion de memoria a entrada
		entrada = new char[5];
		//Inicializamos al contador c = 0
		c = 0;
	
	do{		
		//guardamos la tecla presionada y verificamos si caracter > 0
		if(caracter = getch()){	
			//Verificamos que la tecla no sea ni ENTER ni BACKSPACE y que el contador sea menor a 5	
			if(caracter != 13 && caracter != 8 && c < 5){
				//Imprimimos un * por cada tecla presionada
				printf("*");
				//Guardamos en caracter en el char point
				*(entrada + c) = caracter;
				//Incrementamos al contador c
				c++;
			}	
			//Verificamos si la tecla presionada es BACKSPACE y que contador sea mayor a 0
			if(caracter == 8 && c > 0){
				//Retrocedemos
				printf("%c", 8);
				//Sobreescribimos con un espacio
				printf(" ");
				//Volvemos a retroceder
				printf("%c", 8);
				//Decrementamos al contador c
				c--;
			}		
		}		
	}while(!(ENTER && (clock()-t0) >= 200)); //Siempre y cuando no se presione enter (con un debounce para detectar una pulsacion)	
	
	//Guardamos en t0 el tiempo actual del tiempo que lleva en ejecucion el programa
	t0 = clock();
	
	//Comparamos la clave con la clave ingresada
	comp = strcmp(clave, entrada);
	
	//Verificamos que las claves sean iguales
	if(!comp){
		return 1;
	}else{
		//Limpiamos la pantalla
		system("CLS");
		//Imprimimos mensaje
		printf("Intente nuevamente:\n");
		//Incrementamos el contador error
		error++;
	}
	
	//Verificamos que el usuario coloco mas de 2 veces mal la clave
	if(error > 2)
		return 0;
		
	}while(comp > 0 || comp < 0); //Siempre y cuando la comparacion sea mayor a 0 (clave > entrada) o menor a 0 (clave < entrada)
		
	return 0;
}

//Funcion de menu
int menu (){
	
	//Limpiamos consola
	system("CLS");
	
	int seleccion = 1;
	int dato;	
	int estado = 0;	
	
	do{			
	
	printf("--------------MENU---------------\n");
	printf("- Auto fantastico\n");
	printf("- El choque\n");
	printf("- Billar\n");
	printf("- Tenis\n");
	printf("- Salir\n");	
	
	//Desplazamos en puntero
	gotoxy(0, seleccion);	
	//Retornamos carro e imprimimos >>
	printf("\r>>");	
			
	do{	
	
	//Verificamos que presiono la tecla abajo, que el debounce se cumplio y que seleccion sea menor a 5	
	if(ABAJO && (clock()-t0) >= 200 && seleccion < 5){
		//Retornamos carro e imprimimos -
		printf("\r- ");	
		//Incrementamos seleccion
		seleccion++;
		//Desplazamos en puntero
		gotoxy(0, seleccion);
		//Retornamos carro e imprimimos >>
		printf("\r>>");		
		//Guardamos en t0 el tiempo actual del tiempo que lleva en ejecucion el programa
		t0 = clock();
	}				
				
	//Verificamos que presiono la tecla ARRIBA, que el debounce se cumplio y que seleccion sea mayor a 5				
	if(ARRIBA && (clock()-t0) >= 200 && seleccion > 1){
		//Retornamos carro e imprimimos -
		printf("\r- ");	
		//Decrementamos seleccion
		seleccion--;
		//Desplazamos en puntero
		gotoxy(0, seleccion);
		//Retornamos carro e imprimimos >>
		printf("\r>>");		
		//Guardamos en t0 el tiempo actual del tiempo que lleva en ejecucion el programa
		t0 = clock();
	}
	
	}while(!(ENTER && (clock()-t0) >= 200)); //Siempre y cuando no se presione enter (con un debounce para detectar una pulsacion)
	
	//Delay para el retarde de la llamada a las opciones
	delay(DELAY_TIME);
	
	//Guardamos en t1 el tiempo actual del tiempo que lleva en ejecucion el programa
	t1=clock();	
	
	//Switch de seleccion de opcion
	switch(seleccion){
		
		case 1:			
			//Llamamos a la funcion auto fantastico
			autofantastico(seleccion-1);
		break;
		
		case 2:
			//Llamamos a la funcion el choque
			elchoque(seleccion-1);
		break;
		
		case 3:
			//Llamamos a la funcion billar
			billar(seleccion-1);
		break;
		
		case 4:
			//Llamamos a la funcion tenis
			tenis(seleccion-1);
		break;
		
		case 5:
			//Salimos
			return 0;			
		break;
		
		default:	
			printf("No seleccionaste ninguna opcion\n");
		break;
		
	}
	
	}while(1);
	
	return 0;
}

//Funcion de salida de las luces
void salida(unsigned char c){
		
	//For decremental
	for(int i = 7; i >= 0; i--){
		//Verificamos el resultado del corrimiento de c & 1
		if((c >> i) & 1){
			//Imprimimos un *
			printf("*");		
		}else{
			//Imprimimo un _
			printf("_");
		}					
	}
	
	//Retornamos carro
	printf("\r");
	
}


//Funcion del auto fantastico
int autofantastico(int v){
		
	//Limpiamos la consola
	system("CLS");
	//Imprimimos mensaje
	printf("Auto Fantastico presiona enter para salir\n");	
	//Imprimimos mensaje
	printf("Flecha arriba aumenta velocidad, flecha abajo disminuye velocidad\n");
	
	//Inicializamos i = 1
	int i = 1;
	//Inicializamos estado = 0
	int estado = 0;
		
	do{			
		//Verificamos que i sea menor a 128 que la secuencia este en estado = 0
		//y que el tiempo entre secuencia sea mayor o igual a la velocida de la secuencia
		if(i < 128 && !estado && (clock()-t1) >= velocidades[v]){
			//Llamamos a la funcion salida
			salida(i);
			// Corremos un lugar a la izquierda a i
			i = i<<1;
			//Guardamos en t1 el tiempo actual del tiempo que lleva en ejecucion el programa
			t1=clock();
		}else if(i == 128){
			//Cuando i = 128 cambiamos el estado para ejecutar la secuencia de vuelta de la luz
			estado = 1;
		}
		
		//Verificamos que i sea mayor a 1 que la secuencia este en estado = 1
		//y que el tiempo entre secuencia sea mayor o igual a la velocida de la secuencia
		if(i > 1 && estado && (clock()-t1) >= velocidades[v]){
			//Llamamos a la funcion salida	
			salida(i);
			// Corremos un lugar a la derecha a i
			i = i>>1;
			//Guardamos en t1 el tiempo actual del tiempo que lleva en ejecucion el programa
			t1=clock();
		}else if(i == 1){
			//Cuando i = 128 cambiamos el estado para ejecutar la secuencia de ida de la luz
			estado = 0;
		}
						
		//Verificamos que presiono la tecla ABAJO, que el debounce se cumplio
		//y que la velocidad de la secuencia sea menor a MAX_VEL				
		if(ABAJO && (clock()-t0) >= 200 && velocidades[v] < MAX_VEL){
			//Incrementamos de a 10 a la velocidad
			velocidades[v] += 10;
			//Guardamos en t0 el tiempo actual del tiempo que lleva en ejecucion el programa
			t0 = clock();
		}
				
		//Verificamos que presiono la tecla ARRIBA, que el debounce se cumplio
		//y que la velocidad de la secuencia sea mayor a MIN_VEL		
		if(ARRIBA && (clock()-t0) >= 200 && velocidades[v] > MIN_VEL){
			//Decrementamos de a 10 a la velocidad
			velocidades[v] -= 10;
			//Guardamos en t0 el tiempo actual del tiempo que lleva en ejecucion el programa
			t0 = clock();
		}
			
	}while(!(ENTER && (clock()-t0) >= 200)); //Siempre y cuando no se presione enter (con un debounce para detectar una pulsacion)
	
	//Delay para el retarde de la llamada a las opciones
	delay(DELAY_TIME);
	//Limpiamos la consola
	system("CLS");
	
	return 0;
		
}

//Funcion de el choque
int elchoque(int v){
		
	//Limpiamos la consola	
	system("CLS");
	//Imprimimos mensaje
	printf("El choque presiona enter para salir\n");	
	//Imprimimos mensaje
	printf("Flecha arriba aumenta velocidad, flecha abajo disminuye velocidad\n");
	
	//Inicializamos i = 1
	int i = 0;
	
	do{	
	
		//Verificamos que el tiempo entre secuencia sea mayor o igual a la velocida de la secuencia
		if((clock()-t1) >= velocidades[v]){
			//Llamamos a la funcion salida
			salida(datosElchoque[i]);
			//Verificamos que i sea menor que el tamaño del array unidimensional datosElchoque
			if(i < sizeof(datosElchoque)-1)
				//Incrementamos el contador i
				i++;
			else
				//Asignamos 0 al contador i
				i = 0;	
			//Guardamos en t1 el tiempo actual del tiempo que lleva en ejecucion el programa			
			t1=clock();
		}
			
		//Verificamos que presiono la tecla ABAJO, que el debounce se cumplio
		//y que la velocidad de la secuencia sea menor a MAX_VEL				
		if(ABAJO && (clock()-t0) >= 200 && velocidades[v] < MAX_VEL){
			//Incrementamos de a 10 a la velocidad
			velocidades[v] += 10;
			//Guardamos en t0 el tiempo actual del tiempo que lleva en ejecucion el programa
			t0 = clock();
		}
				
		//Verificamos que presiono la tecla ARRIBA, que el debounce se cumplio
		//y que la velocidad de la secuencia sea mayor a MIN_VEL		
		if(ARRIBA && (clock()-t0) >= 200 && velocidades[v] > MIN_VEL){
			//Decrementamos de a 10 a la velocidad
			velocidades[v] -= 10;
			//Guardamos en t0 el tiempo actual del tiempo que lleva en ejecucion el programa
			t0 = clock();
		}
			
	}while(!(ENTER && (clock()-t0) >= 200)); //Siempre y cuando no se presione enter (con un debounce para detectar una pulsacion)
	
	//Delay para el retarde de la llamada a las opciones
	delay(DELAY_TIME);
	//Limpiamos la consola	
	system("CLS");
	
	return 0;
		
}

//Funcion billar
int billar(int v){
	
	//Limpiamos la consola	
	system("CLS");
	//Imprimimos mensaje
	printf("Billar presiona enter para salir\n");	
	//Imprimimos mensaje
	printf("Flecha arriba aumenta velocidad, flecha abajo disminuye velocidad\n");
	
	//Inicializamos i = 1
	int i = 0;
	
	do{			
		
		//Verificamos que el tiempo entre secuencia sea mayor o igual a la velocida de la secuencia
		if((clock()-t1) >= velocidades[v]){	
			//Llamamos a la funcion salida
			salida(datosBillar[i]);
			//Verificamos que i sea menor que el tamaño del array unidimensional datosBillar
			if(i < sizeof(datosBillar)-1)
				//Incrementamos el contador i
				i++;
			else
				//Asignamos 0 al contador i
				i = 0;	
			//Guardamos en t1 el tiempo actual del tiempo que lleva en ejecucion el programa		
			t1=clock();
		}
			
		//Verificamos que presiono la tecla ABAJO, que el debounce se cumplio
		//y que la velocidad de la secuencia sea menor a MAX_VEL				
		if(ABAJO && (clock()-t0) >= 200 && velocidades[v] < MAX_VEL){
			//Incrementamos de a 10 a la velocidad
			velocidades[v] += 10;
			//Guardamos en t0 el tiempo actual del tiempo que lleva en ejecucion el programa
			t0 = clock();
		}
				
		//Verificamos que presiono la tecla ARRIBA, que el debounce se cumplio
		//y que la velocidad de la secuencia sea mayor a MIN_VEL		
		if(ARRIBA && (clock()-t0) >= 200 && velocidades[v] > MIN_VEL){
			//Decrementamos de a 10 a la velocidad
			velocidades[v] -= 10;
			//Guardamos en t0 el tiempo actual del tiempo que lleva en ejecucion el programa
			t0 = clock();
		}
			
	}while(!(ENTER && (clock()-t0) >= 200)); //Siempre y cuando no se presione enter (con un debounce para detectar una pulsacion)
	
	//Delay para el retarde de la llamada a las opciones
	delay(DELAY_TIME);
	//Limpiamos la consola	
	system("CLS");
	
	return 0;
	
}

//Funcion Tenis
int tenis(int v){
	
	//Limpiamos la consola	
	system("CLS");
	//Imprimimos mensaje
	printf("Tenis presiona enter para salir\n");
	//Imprimimos mensaje
	printf("Flecha arriba aumenta velocidad, flecha abajo disminuye velocidad\n");
	
	//Inicializamos i = 1	
	int i = 0;
	
	do{			

		//Verificamos que el tiempo entre secuencia sea mayor o igual a la velocida de la secuencia
		if((clock()-t1) >= velocidades[v]){				
			//Llamamos a la funcion salida
			salida(datosTenis[i]);
			//Verificamos que i sea menor que el tamaño del array unidimensional datosTenis
			if(i < sizeof(datosTenis)-1)
				//Incrementamos el contador i
				i++;
			else
				//Asignamos 0 al contador i
				i = 0;	
			//Guardamos en t1 el tiempo actual del tiempo que lleva en ejecucion el programa		
			t1=clock();
		}
			
		//Verificamos que presiono la tecla ABAJO, que el debounce se cumplio
		//y que la velocidad de la secuencia sea menor a MAX_VEL				
		if(ABAJO && (clock()-t0) >= 200 && velocidades[v] < MAX_VEL){
			//Incrementamos de a 10 a la velocidad
			velocidades[v] += 10;
			//Guardamos en t0 el tiempo actual del tiempo que lleva en ejecucion el programa
			t0 = clock();
		}
				
		//Verificamos que presiono la tecla ARRIBA, que el debounce se cumplio
		//y que la velocidad de la secuencia sea mayor a MIN_VEL		
		if(ARRIBA && (clock()-t0) >= 200 && velocidades[v] > MIN_VEL){
			//Decrementamos de a 10 a la velocidad
			velocidades[v] -= 10;
			//Guardamos en t0 el tiempo actual del tiempo que lleva en ejecucion el programa
			t0 = clock();
		}
			
	}while(!(ENTER && (clock()-t0) >= 200)); //Siempre y cuando no se presione enter (con un debounce para detectar una pulsacion)
	
	//Delay para el retarde de la llamada a las opciones
	delay(DELAY_TIME);
	//Limpiamos la consola	
	system("CLS");
	
	return 0;
	
}

//Funcion delay (retardo)
void delay(unsigned long int a){
	while(a) a--;
}
