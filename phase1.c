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
}

void draw() {
	system("cls");
	int i, j, flag=0;

	for (i=0,j=0 ; j<width ; j++) {
		game[i][j]='*';
		printf ("%c ", game[i][j]);
	}

	printf("\n");

	int a=rand() % 3;
	for (i=0 ; i<length ; i++) {
		for (j=0 ; j<width ; j++) {
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


				if (a==0 && i!=19) {
					if (game[i-1][j-1]!='-') {
						game[i][j]='|';
						game[i][j+1]='-';
						game[i][j-1]=' ';
					} else {
						game[i][j]='|';
						game[i][j+1]=' ';
						game[i][j-1]=' ';
					}


				} else if (a==1 && i!=19) {
					if (game[i-1][j+1]!='-') {
						game[i][j]='|';
						game[i][j-1]='-';
						game[i][j+1]=' ';
					} else {
						game[i][j]='|';
						game[i][j+1]=' ';
						game[i][j-1]=' ';
					}


				} else if (a==2 && i!=19) {
					game[i][j]='|';
				}


				if (a==0 && i!=19) {
					printf("%c", game[i][j-1]);
					printf("%c", game[i][j]);
					printf("%c", game[i][j+1]);
				}


				if (a==1 && i!=19) {
					printf("%c", game[i][j-1]);
					printf("%c", game[i][j]);
					printf("%c", game[i][j+1]);
				}

				if (a==2 && i!=19) {
					printf (" ");
					printf("%c ", game[i][j]);
				}


				if (i==19) {
					game[i][j]='|';
					game[i][j+1]='M';
					printf (" ");
					printf("%c", game[i][j]);
					printf("%c", game[i][j+1]);
				}
			} else {
				game[i][j]=' ';
				printf("%c ", game[i][j]);
			}

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
	int c=getch();
	switch (c) {
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



void logic() {
	int i, j;
	switch (dir) {
		case LEFT:
			game[19][1]='M';
			game[19][3]=' ';
			break;
		case RIGHT:
			game[19][3]='M';
			game[19][1]=' ';
			break;
	}

	for (i=17, j=2 ; i>0 ; i--) {
		game[i+1][j]=game[i][j];
		game[i+1][j+1]=game[i][j+1];
		game[i+1][j-1]=game[i][j-1];
	}
	int d=rand() % 3;
	switch (d) {
		case 0:
			game[1][3]='-';
			game[1][1]=' ';
			break;
		case 1:
			game[1][1]='-';
			game[1][3]=' ';
			break;
		case 2:
			game[1][3]=' ';
			game[1][1]=' ';
			break;
	}

	system("cls");


	for (i=0 ; i<length ; i++) {
		for (j=0 ; j<width ; j++) {
			printf ("%c", game[i][j]);
		}
		printf ("\n");
	}


}




int main() {
	srand( time(NULL));

	setup();
	draw();

	while (!gameOver) {
		input();
		logic();
	}

}