#include<iostream>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h> 

#define ARRIBA 72
#define ABAJO 80
#define DERECHA 77
#define IZQUIERDA 75
#define ESC 27

int snake[200][2];
int s = 1;
int dist = 5;
int x = 10;
int y = 12;
int xc = 30;
int yc = 15;
int dir = 3;
char funciones;
int velocidad = 100; 
int puntuacion = 0;
int j = 1; 

void gotoxy(int x, int y){
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}

void tablero(){
	for (int i = 2; i < 78; i++){
		gotoxy(i,3); printf("%c", 205);
		gotoxy(i,23); printf("%c", 205);
	}
	for (int i = 4; i < 23; i++){
		gotoxy(2,i); printf("%c",186);
		gotoxy(77,i); printf("%c",186);
	}
	gotoxy(2,3); printf("%c", 201);
	gotoxy(77,3); printf("%c", 187);
	gotoxy(77,23); printf("%c", 188);
	gotoxy(2,23); printf("%c", 200);
}
	
void guardar(){
	snake[s][0] = x;
	snake[s][1] = y;
	s++;
	if(s == dist){
		s = 1;
	}
}
void draw(){
	for(int i = 1; i < dist; i++){
		gotoxy(snake[i][0], snake[i][1]); printf("%c",215);
	}
}

void clear(){
	for (int i = 1; i < dist; i++){
 		gotoxy(snake[i][0],snake[i][1]); printf(" ");
	} 
}

void movimientos(){
	if(kbhit())
	{
		funciones=getch();
		switch(funciones){
			case ARRIBA:
				if(dir!=2){
					dir = 1;
				}
				break;
			case ABAJO:
			if(dir!=1){
				dir = 2;
			}
			break;
			case DERECHA:
			if(dir!=4){
				dir = 3;
			}
			break;
			case IZQUIERDA:
			if(dir!=3){
				dir = 4;
			}
			break;
		}
	}
}

void vel(){ 
	if(puntuacion == j*20){ 
		velocidad -= 10; 
		j++;
	}
}

void comida() { 
	if(x == xc && y == yc){ 
		xc = (rand() % 73) + 4; 
		yc = (rand() % 19) + 4;
		dist++;
		puntuacion +=10;
		gotoxy(xc,yc); printf("%c", 1); 
	}
	vel();
}
	
bool collision() { 
	if(x == 2 || x == 78 || y == 3 || y == 23)	  return false;
	for(int i = dist - 1; i > 0; i-- ){
		if (snake[i][0] == x && snake[i][1] == y) return false;
	} 
	return true;	
}

void puntos() { 
	gotoxy(3,1); printf("Puntos: %d", puntuacion);
}

int main(){
	srand(time(NULL));
	tablero();
	gotoxy(xc,yc); printf("%c", 1);
	while(funciones != ESC && collision()){
		clear();
		guardar();
		draw();
		comida();
		puntos();
		movimientos();
		movimientos();
		if(dir == 1)	y--;
		if(dir == 2)	y++;
		if(dir == 3)	x++;
		if(dir == 4)	x--;
		Sleep(velocidad);
	}
	system ("pause>null");
	return 0;	
}
