#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

char game[20][10];
int score, gameOver, des;
int const length=20, width=7;

struct point {
	int i, j, x;
};

struct point player, branch;

void setup() {
	gameOver = 0;
	score = 0;
	player.x=game[19][3];
}

void draw() {
	system("cls");
	int i, j;

	for (i=0,j=0 ; j<width ; j++) {
		game[i][j]='*';
		printf ("%c ", game[i][j]);
	}

	printf("\n");

	for (i=0 ; i<length ; i++) {
		for (j=0 ; j<width ; j++) {
			int a=rand() % 3;
			int b=a;
			a=rand() % 3;
			if (j==0) {
				game[i][j]='*';
				printf ("%c", game[i][j]);
			}
			if (j==width-2) {
				game[i][j]='*';
				printf ("%c", game[i][j]);
			}
			if (j==2 && i!=-1 && i!=length) {
				a=rand() % 3;
				if (a==0) {
					game[i][j]='|';
					game[i][j+1]='-';
					game[i][j-1]=' ';
				} else if (a==1) {
					game[i][j]='|';
					game[i][j-1]='-';
					game[i][j+1]=' ';
				} else if (a==2) {
					game[i][j]='|';
				}
				if (a==0) {
					printf("%c", game[i][j-1]);
					printf("%c", game[i][j]);
					printf("%c", game[i][j+1]);
				}
				if (a==1) {
					printf("%c", game[i][j-1]);
					printf("%c", game[i][j]);
					printf("%c", game[i][j+1]);
				}
				if (a==2) {
					printf (" ");
					printf("%c ", game[i][j]);
				}
				
			} else {
				game[i][j]=' ';
				printf("%c ", game[i][j]);
			}
			b=a;
		}
		printf("\n");
	}

	for (i=length-1,j=0 ; j<width ; j++) {
		game[i][j]='*';
		printf ("%c ", game[i][j]);
	}
}


enum direction {LEFT,RIGHT};
enum direction dir;

void input() {
	if (kbhit()) {
		switch (getche()) {
			case 'd':
			case 'D':
				dir = RIGHT;
				break;
			case 'a':
			case 'A':
				dir = LEFT;
				break;
		}
	}
}



void logic() {

}




int main() {
	srand( time(NULL));

	int sw=0;

	setup();

	if (sw==0) {
		draw();
		sw=1;
	}
	while (!gameOver) {
		input();
		logic();
		input();

	}
}