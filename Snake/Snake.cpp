#include<iostream>  // Esta libreria permite la entrada y salida de datos en la consola.
#include<windows.h>  //Esta libreria proporciona funciones para manipular caracteristicas de la ventana de la consola, como la posicion del cursor y el color del texto.
#include<conio.h>    //Esta libreria proporciona funciones para leer las teclas presionadas por el usuario.
#include<stdlib.h>   //Esta libreria proporciona funciones estandar, como system, que se utiliza para ejecutar comandos del sistema operativo
#include<time.h>     //Esta libreria proporciona funciones para trabajar con el tiempo, como la generacion de numeros aleatorios basados en la hora actual.

// Definicion de constantes para las teclas de direccion y ESC
#define ARRIBA 72
#define ABAJO 80
#define DERECHA 77
#define IZQUIERDA 75
#define ESC 27
// Variables globales
int snake[200][2]; // Matriz para almacenar las coordenadas del cuerpo de la serpiente
int s = 1; // Indice para el cuerpo de la serpiente
int dist = 5; // Longitud inicial de la serpiente
int x = 10; // Coordenada x de la cabeza de la serpiente
int y = 12; // Coordenada y de la cabeza de la serpiente
int xc = 30; // Coordenada x de la comida
int yc = 15; // Coordenada y de la comida
int dir = 3; // Direccion de movimiento de la serpiente (1: arriba, 2: abajo, 3: derecha, 4: izquierda)
char funciones; // Variable para almacenar la tecla presionada por el usuario
int velocidad = 100; // Velocidad de movimiento de la serpiente
int puntuacion = 0; // Puntuacion del jugador
int j = 1; // Variable para controlar la velocidad


/*Esta funcion se utiliza para posicionar el cursor en una coordenada especifica de la consola. 
 Toma como parametros las coordenadas X y Y a las que se desea mover el cursor.*/
void gotoxy(int x, int y){
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}


/* Esta funcion dibuja el tablero del juego en la consola, 
utilizando caracteres especiales para crear los bordes y las lineas del tablero. */
void tablero(){
	for (int i = 2; i < 78; i++){
		gotoxy(i,3); printf("%c", 205); // Dibujar linea horizontal superior
		gotoxy(i,23); printf("%c", 205); // Dibujar linea horizontal inferior
	}
	for (int i = 4; i < 23; i++){
		gotoxy(2,i); printf("%c",186); // Dibujar linea vertical izquierda
		gotoxy(77,i); printf("%c",186); // Dibujar linea vertical derecha
	}
	gotoxy(2,3); printf("%c", 201); // Dibujar esquina superior izquierda
	gotoxy(77,3); printf("%c", 187); // Dibujar esquina superior derecha
	gotoxy(77,23); printf("%c", 188); // Dibujar esquina inferior derecha
	gotoxy(2,23); printf("%c", 200); // Dibujar esquina inferior izquierda
}


/* Esta funcion guarda las coordenadas de cada segmento de la serpiente en la matriz snake. 
Cada vez que se llama a esta funcion, se guarda la coordenada actual de la cabeza de la serpiente en la matriz y se incrementa el contador s.
 Si s alcanza el valor de dist (distancia entre segmentos), se reinicia a 1. */
void guardar(){
	snake[s][0] = x; // Guardar la coordenada x de la cabeza de la serpiente
	snake[s][1] = y; // Guardar la coordenada y de la cabeza de la serpiente
	s++;
	if(s == dist){
		s = 1;
	}
}


/*  Esta funcion dibuja la serpiente en la pantalla.
 Utiliza un bucle para recorrer la matriz snake y dibujar cada segmento en las coordenadas correspondientes. */
void draw(){
	for(int i = 1; i < dist; i++){
		gotoxy(snake[i][0], snake[i][1]); printf("%c",215); // Dibujar el cuerpo de la serpiente
	}
}



/*  Esta funcion borra la serpiente de la pantalla.
 Utiliza un bucle para recorrer la matriz snake y borrar cada segmento de la consola.*/
void clear(){
	for (int i = 1; i < dist; i++){
		gotoxy(snake[i][0],snake[i][1]); printf(" "); // Borrar el cuerpo de la serpiente
	} 
}


/*  Esta funcion gestiona los movimientos de la serpiente segun la tecla presionada por el usuario.
Utiliza la funcion kbhit de la libreria conio.h para verificar si se ha presionado una tecla.
Si es asi, lee la tecla con getch y actualiza la variable funciones con el codigo de la tecla presionada. 
Luego, utiliza un condicional switch para determinar la direccion de movimiento de la serpiente segun la tecla presionada.*/
void movimientos(){
	if(kbhit())
	{
		funciones=getch();
		switch(funciones){
			case ARRIBA:
				if(dir!=2){
					dir = 1; // Cambiar la direccion hacia arriba
				}
				break;
			case ABAJO:
				if(dir!=1){
					dir = 2; // Cambiar la direccion hacia abajo
				}
				break;
			case DERECHA:
				if(dir!=4){
					dir = 3; // Cambiar la direccion hacia la derecha
				}
				break;
			case IZQUIERDA:
				if(dir!=3){
					dir = 4; // Cambiar la direccion hacia la izquierda
				}
				break;
		}
	}
}



/*  Esta funcion ajusta la velocidad del juego. 
Cada vez que se alcanza una puntuacion multiplo de 20, se reduce la velocidad velocidad en 10 unidades y se incrementa la variable j. 
Esto hace que el juego se vuelva mas rapido a medida que el jugador obtiene mas puntos.*/
void vel(){ 
	if(puntuacion == j*20){ 
		velocidad -= 10; // Aumentar la velocidad cada 20 puntos
		j++;
	}
}


/* Esta funcion

 gestiona la generacion de la comida para la serpiente. Si la cabeza de la serpiente alcanza las mismas coordenadas que la comida, 
 se genera una nueva posicion aleatoria para la comida, se incrementa la longitud de la serpiente dist,
  se incrementa la puntuacion puntuacion en 10 puntos y se dibuja la comida en la nueva posicion.*/
void comida() { 
	if(x == xc && y == yc){ 
		xc = (rand() % 73) + 4; // Generar una nueva coordenada x para la comida
		yc = (rand() % 19) + 4; // Generar una nueva coordenada y para la comida
		dist++; // Incrementar la longitud de la serpiente
		puntuacion +=10; // Aumentar la puntuacion del jugador
		gotoxy(xc,yc); printf("%c", 1); // Dibujar la comida en la nueva posicion
	}
	vel();
}

/*Esta funcion verifica si ha ocurrido una colision. 
Comprueba si la cabeza de la serpiente ha alcanzado los limites del tablero (bordes) o si ha chocado*/

bool collision() { 
	if(x == 2 || x == 77 || y == 3 || y == 23)	  return false; // Verificar si la serpiente ha chocado con los bordes
	for(int i = dist - 1; i > 0; i-- ){
		if (snake[i][0] == x && snake[i][1] == y) return false; // Verificar si la serpiente ha chocado consigo misma
	} 
	return true;	
}


//La funcion puntos se encarga de mostrar la puntuacion del jugador en la parte superior izquierda de la pantalla del juego./
void puntos() { 
	gotoxy(3,1); printf("Puntos: %d", puntuacion); // Mostrar la puntuacion del jugador
}

int main(){
	srand(time(NULL));
	tablero();
	gotoxy(xc,yc); printf("%c", 1); // Dibujar la comida en la posicion inicial
	while(funciones != ESC && collision()){
		clear();
		guardar();
		draw();
		comida();
		puntos();
		movimientos();
		movimientos();
		if(dir == 1)	y--; // Mover hacia arriba
		if(dir == 2)	y++; // Mover hacia abajo
		if(dir == 3)	x++; // Mover hacia la derecha
		if(dir == 4)	x--; // Mover hacia la izquierda
		Sleep(velocidad); // Esperar un tiempo antes de actualizar el movimiento
	}
	system ("pause>null");
	return 0;	
}
