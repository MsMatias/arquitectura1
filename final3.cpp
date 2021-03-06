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

#define TEXTO_VERDE SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN|FOREGROUND_INTENSITY);
#define TEXTO_NEGRO SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
#define TEXTO_ROJO SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_INTENSITY);
#define FONDO_BLANCO SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
#define DEFAULT SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);


//CONSTANTES
const int MIN_VEL = 2200; //Minima velocidad de refrescamiento de secuencia
const int MED_VEL = 4200; //Maxima velocidad de refrescamiento de secuencia
const int MAX_VEL = 5700; //Maxima velocidad de refrescamiento de secuencia

//Clave
char clave[5];

//Variable de estado de ejecuciones de secuencias
int ejecucion = 1;

//velocidades
int velocidades[] = {MED_VEL, MED_VEL, MED_VEL, MED_VEL, MED_VEL};

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

//Array de datos de canicas
char datosCanicas[] = {
0x3C,
0x3A,
0x39,
0x3A,
0x3C,
0x5C,
0x9C,
0x5C
};

//Declaraciones de firmas de funciones
void menu();
int ingreso();
void salida(unsigned char);
void autofantastico(int);
void elchoque(int);
void billar(int);
void tenis(int);
void canicas(int);
void delay(unsigned long int, int);
void medidor(int);

int main(int argc, char *argv[]) {
	
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
	char entrada[5];
	char caracter;	
	int c = 0;	
	int comp;
		
	do{		
	
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
				entrada[c] = caracter;
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
		
	}while(comp != 0); //Siempre y cuando la comparacion sea mayor a 0 (clave > entrada) o menor a 0 (clave < entrada)
		
	return 0;
}

//Funcion de menu
void menu (){
	
	//Limpiamos consola
	system("CLS");
	
	int seleccion = 1;
	int dato;	
	int estado = 0;	
	unsigned char ch1, ch2;		
	do{			
		FONDO_BLANCO
		printf("--------------MENU---------------\n");
		DEFAULT
				
		printf("- Auto fantastico\n");
		printf("- El choque\n");
		printf("- Billar\n");
		printf("- Tenis\n");
		printf("- Canicas\n");
		printf("- Salir\n");	

		//Desplazamos en puntero
		gotoxy(0, seleccion);	
		//Retornamos carro e imprimimos >>
	
		printf("\r>>");	

		while(!estado){	
	
			if(kbhit()){				
				ch1 = getch();
				if(ch1 == 224 || ch1 == 0){
					printf("\r- ");	
					ch2 = getch();						
					
            		switch (ch2)
            		{          	
                		case 72:               // Arriba
                			if(seleccion > 1)
                   				seleccion--;
                   		break;
                		case 80:               // Abajo
                			if(seleccion < 6)
                    			seleccion++;
                    	break;
                    	default:
                    	break;
            		}
        			gotoxy(0, seleccion); 
					printf("\r>>");	
					 
				}else if(ch1 == 13)
					estado = 1;	
					
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
				//Llamamos a la funcion canicas
				canicas(seleccion-1);
			break;
		
			case 6:
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
			TEXTO_VERDE
			printf("*");		
			DEFAULT
		}else{
			//Imprimimo un _
			TEXTO_NEGRO
			printf("_");
			DEFAULT
		}					
	}
		
}


//Funcion del auto fantastico
void autofantastico(int v){
		
	//Limpiamos la consola
	system("CLS");
	//Imprimimos mensaje
	printf("Auto Fantastico presiona enter para volver al menu\n");	
	//Imprimimos mensaje
	printf("Flecha arriba aumenta velocidad, flecha abajo disminuye velocidad\n");
	
	int estado = 0;
	int i = 128;

	do{	
	
		medidor(v);	
		salida(i);
		delay(velocidades[v], v);
	
		if(!estado)			
			i = i >> 1;
		else
			i = i << 1;
			
		if(i == 128)
			estado = 0;
		
		if(i == 1)
			estado = 1;		

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
	printf("El choque presiona enter para volver al menu\n");	
	//Imprimimos mensaje
	printf("Flecha arriba aumenta velocidad, flecha abajo disminuye velocidad\n");
	
	int i = 0;
			
	do{		
	
		medidor(v);		
		salida(datosElchoque[i]);
		delay(velocidades[v], v);
	
		if(i == sizeof(datosElchoque)-1)
			i = 0;
		else
			i++;

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
	printf("Billar presiona enter para volver al menu\n");	
	//Imprimimos mensaje
	printf("Flecha arriba aumenta velocidad, flecha abajo disminuye velocidad\n");
		
	int i = 0;
			
	do{		
	
		medidor(v);		
		salida(datosBillar[i]);
		delay(velocidades[v], v);
	
		if(i == sizeof(datosBillar)-1)
			i = 0;
		else
			i++;
					
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
	printf("Tenis presiona enter para volver al menu\n");
	//Imprimimos mensaje
	printf("Flecha arriba aumenta velocidad, flecha abajo disminuye velocidad\n");
							
	int i = 0;
			
	do{		
	
		medidor(v);		
		salida(datosTenis[i]);
		delay(velocidades[v], v);
	
		if(i == sizeof(datosTenis)-1)
			i = 0;
		else
			i++;
					
	}while(ejecucion);
	
	//Limpiamos la consola	
	system("CLS");
	
	return;
	
}

//Funcion Canicas
void canicas(int v){
	
	//Limpiamos la consola	
	system("CLS");
	//Imprimimos mensaje
	printf("Canicas presiona enter para volver al menu\n");
	//Imprimimos mensaje
	printf("Flecha arriba aumenta velocidad, flecha abajo disminuye velocidad\n");
							
	int i = 0;
			
	do{		
	
		medidor(v);		
		salida(datosCanicas[i]);
		delay(velocidades[v], v);
	
		if(i == sizeof(datosCanicas)-1)
			i = 0;
		else
			i++;
					
	}while(ejecucion);
	
	//Limpiamos la consola	
	system("CLS");
	
	return;
	
}

//Funcion delay (retardo)
void delay(unsigned long int a, int v){
	
	unsigned char ch1;
    unsigned char ch2;
		
	while(a){
	
		a--;
		
		if (kbhit())
        {
            ch1 = getch();
			if(ch1 == 224 || ch1 == 0){
			
				ch2 = getch();			
			
           		switch (ch2)
            	{  	
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
			}else if(ch1 == 13){				// Enter
				a = 0;
            	ejecucion = 0;
            	return;
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
			TEXTO_VERDE
			printf("=");
			DEFAULT		
		}else{
			TEXTO_ROJO
			printf("#");
			DEFAULT
		}
	}
	gotoxy(0,2);
}

