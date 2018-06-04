#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
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
 
//Define de delay
#define DELAY_TIME 5000

//CONSTANTES
const int MIN_VEL = 1500; //Minima velocidad de refrescamiento de secuencia
const int MED_VEL = 2000; //Maxima velocidad de refrescamiento de secuencia
const int MAX_VEL = 5000; //Maxima velocidad de refrescamiento de secuencia

//Clave
char* clave;

//Variable de estado de ejecuciones de secuencias
int ejecucion = 1;

//velocidades
int velocidades[] = {MED_VEL, MED_VEL, MED_VEL, MED_VEL};

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
0x08,
0x08,
0x09,
0x09,
0x0B,
0x0B,
0x09,
0x08,
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
void menu();
int ingreso();
void salida(unsigned char);
void autofantastico(int);
void elchoque(int);
void billar(int);
void tenis(int);
void delay(unsigned long int, int);
void medidor(int);

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
			
			if(caracter == 13)
				break;
		}	
				
	}while(1);	
	
	//Comparamos la clave con la clave ingresada
	comp = strcmp(clave, entrada);
	
	//Verificamos que las claves sean iguales
	if(!comp){
		return 1;
	}else{
		//Limpiamos la pantalla
		system("CLS");
		//Incrementamos el contador error
		error++;
			//Imprimimos mensaje
		printf("Intente nuevamente [ Intentos restantes: %d] : \n"  ,3-error );
	}
	
	//Verificamos que el usuario coloco mas de 2 veces mal la clave
	if(error > 2)
		return 0;
		
	}while(comp > 0 || comp < 0); //Siempre y cuando la comparacion sea mayor a 0 (clave > entrada) o menor a 0 (clave < entrada)
		
	return 0;
}

//Funcion de menu
void menu (){
	
	//Limpiamos consola
	system("CLS");
	
	int seleccion = 1;
	int dato;	
	int estado = 0;	
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	do{			
		SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY); 
		printf("--------------MENU---------------\n");
		SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY); 
		
		

		printf("- Auto fantastico\n");
		printf("- El choque\n");
		printf("- Billar\n");
		printf("- Tenis\n");
		printf("- Salir\n");	
	
	

		//Desplazamos en puntero
		gotoxy(0, seleccion);	
		//Retornamos carro e imprimimos >>
	
		printf("\r>>");	

		while(!estado){		
	
			if(kbhit()){
	
				printf("\r- ");	
				char ch = getch();
            	switch (ch)
            	{
            		case 13:				// Enter
            			estado = 1;
            		break;            	
                	case 72:               // Arriba
                		if(seleccion > 1)
                   			seleccion--;
                   	break;
                	case 80:               // Abajo
                		if(seleccion < 5)
                    		seleccion++;
                    break;
            	}
        		gotoxy(0, seleccion); 
				printf("\r>>");	   
    		}	
		
		} 
		
		estado = 0;	
		ejecucion = 1;

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
				return;			
			break;
		
			default:
				system("CLS");
				seleccion = 1;	
				printf("No seleccionaste ninguna opcion\n");
			break;
		
		}
	
	}while(1);
	
	return;
}

//Funcion de salida de las luces
void salida(unsigned char c){
	
	gotoxy(0,2);
	
	
	//For decremental
	for(int i = 7; i >= 0; i--){
		//Verificamos el resultado del corrimiento de c & 1
		if((c >> i) & 1){
			//Imprimimos un *
			SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY); 
			printf("*");		
			SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		}else{
			//Imprimimo un _
			printf("_");
		}					
	}
		
}


//Funcion del auto fantastico
void autofantastico(int v){
		
	//Limpiamos la consola
	system("CLS");
	//Imprimimos mensaje
	printf("Auto Fantastico presiona enter para salir\n");	
	//Imprimimos mensaje
	printf("Flecha arriba aumenta velocidad, flecha abajo disminuye velocidad\n");

	do{	
							
		for(int i = 1; i < 128 && ejecucion; i = i<<1){	
			medidor(v);	
			salida(i);
			delay(velocidades[v], v);
		}
		
		for(int i = 128; i > 1 && ejecucion; i = i>>1){				
			medidor(v);		
			salida(i);
			delay(velocidades[v], v);
		}

	}while(ejecucion);
	
	//Limpiamos la consola
	system("CLS");
	
	return;
		
}

//Funcion de el choque
void elchoque(int v){
		
	//Limpiamos la consola	
	system("CLS");
	//Imprimimos mensaje
	printf("El choque presiona enter para salir\n");	
	//Imprimimos mensaje
	printf("Flecha arriba aumenta velocidad, flecha abajo disminuye velocidad\n");
			
	do{		
							
		for(int i = 0; i < sizeof(datosElchoque) && ejecucion; i++){		
			medidor(v);		
			salida(datosElchoque[i]);
			delay(velocidades[v], v);
		}	
		
	}while(ejecucion); 
	
	//Limpiamos la consola	
	system("CLS");
	
	return;
		
}

//Funcion billar
void billar(int v){
	
	//Limpiamos la consola	
	system("CLS");
	//Imprimimos mensaje
	printf("Billar presiona enter para salir\n");	
	//Imprimimos mensaje
	printf("Flecha arriba aumenta velocidad, flecha abajo disminuye velocidad\n");
		
	do{	
								
		for(int i = 0; i < sizeof(datosBillar) && ejecucion; i++){	
			medidor(v);	
			salida(datosBillar[i]);
			delay(velocidades[v], v);
		}	
					
	}while(ejecucion); 
	
	//Limpiamos la consola	
	system("CLS");
	
	return;
	
}

//Funcion Tenis
void tenis(int v){
	
	//Limpiamos la consola	
	system("CLS");
	//Imprimimos mensaje
	printf("Tenis presiona enter para salir\n");
	//Imprimimos mensaje
	printf("Flecha arriba aumenta velocidad, flecha abajo disminuye velocidad\n");

	do{			
							
		for(int i = 0; i < sizeof(datosTenis) && ejecucion; i++){	
			medidor(v);	
			salida(datosTenis[i]);
			delay(velocidades[v], v);
		}
					
	}while(ejecucion);
	
	//Limpiamos la consola	
	system("CLS");
	
	return;
	
}

//Funcion delay (retardo)
void delay(unsigned long int a, int v){
		

	while(a){
	
		a--;
		
		if (kbhit())
        {
            char ch = getch();
            switch (ch)
            {
            	case 13:				// Enter
            		a = 0;
            		ejecucion = 0;
            		return;
            		break;            	
                case 72:               // Arriba
                    if(velocidades[v] > MIN_VEL)            	
						velocidades[v] -= 100;	
					if(a > MIN_VEL)
                    	a-=100;
                    break;
                case 80:               // Abajo
                    if(velocidades[v] < MAX_VEL)                    	
						velocidades[v] += 100;
					if(a < MAX_VEL)
						a+=100;						
                    break;
                default:
                	break;
            }
        }
	} 
	
}

void medidor(int v){
	
	gotoxy(6,4);
	printf("Velocidad de la secuencia");
	gotoxy(0,5);
	
	for(int i = MAX_VEL; i >= MIN_VEL; i-=100){
		if(i < velocidades[v] || i > velocidades[v]){
			
			
			SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN|FOREGROUND_INTENSITY); 
			printf("=");
			SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
			
		}else{
				SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_INTENSITY); 
			printf("#");
			SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
		}
	}
	gotoxy(0,2);

	 

}
