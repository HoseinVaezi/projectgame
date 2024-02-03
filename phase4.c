#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>


char game[22][10];
int score, des;
int const length=21, width=7;

struct point {
	int i, j, x;
};

struct point player, branch;

void setup() {
	score = 0;
}

void lose() {
	system("cls");

	printf ("    /---------\\\n");
	printf (" |---Gameover!---|\n");
	printf ("    \\---------/");
	printf ("\a\n");

	printf ("Your Score is: %d", score);

	exit(0);
}

void draw() {
	system("cls");
	int i, j;


	int a=rand() % 3;
	for (i=0 ; i<length ; i++) {
		for (j=0 ; j<width ; j++) {
			a=rand() % 3;
			if (j==0) {
				game[i][j]='*';
			}
			if (j==width) {
				game[i][j]='*';
			}
			if (j==2) {
				a=rand() % 3;


				if (a==0 && i!=20) {
					if (game[i-1][j-1]!='-') {
						game[i][j]='|';
						game[i][j+1]='-';
						game[i][j-1]=' ';
					} else {
						game[i][j]='|';
						game[i][j+1]=' ';
						game[i][j-1]=' ';
					}


				} else if (a==1 && i!=20) {
					if (game[i-1][j+1]!='-') {
						game[i][j]='|';
						game[i][j-1]='-';
						game[i][j+1]=' ';
					} else {
						game[i][j]='|';
						game[i][j+1]=' ';
						game[i][j-1]=' ';
					}


				} else if (a==2 && i!=20) {
					game[i][j-1]=' ';
					game[i][j]='|';
					game[i][j+1]=' ';
				}

				if (i==20) {
					game[i][j]='|';
					game[i][j+1]='M';
					game[i][j+2]=' ';
				}
			} else if (game[i][j]!='-' && game[i][j]!='M') {
				game[i][j]=' ';
			}


		}
	}
	
	game[19][3]=game[19][1]=' ';

	for (i=0 ; i<length ; i++) {
		for (j=0 ; j<width ; j++) {
			if (j==0) {
				printf ("*");
				printf("   ");
			}
			if (j==width-1) {
				printf("  ");
				printf ("*");
			}
			printf ("%c", game[i][j]);
		}
		printf ("\n");
	}


	printf ("\nScore: %d", score);
}

enum direction {LEFT,RIGHT};
enum direction dir;

void input() {
	char c=getch();
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

void upsc() {
	int i, j;

	for (i=19, j=2 ; i>=0 ; i--) {
		game[i+1][j+1]=game[i][j+1];
		game[i+1][j-1]=game[i][j-1];
	}

	system("cls");

	for (i=0 ; i<length ; i++) {
		for (j=0 ; j<width ; j++) {
			if (j==0) {
				printf ("*");
				printf("   ");
			}
			if (j==width-1) {
				printf("  ");
				printf ("*");
			}
			printf ("%c", game[i][j]);
		}
		printf ("\n");
	}

	printf("\n");
	score+=1;
	printf ("Score: %d", score);

	int d=rand() % 3;
	switch (d) {
		case 0:
			game[0][3]='-';
			game[0][1]=' ';
			break;
		case 1:
			game[0][1]='-';
			game[0][3]=' ';
			break;
		case 2:
			game[0][3]=' ';
			game[0][1]=' ';
			break;
	}
	input();
	switch (dir) {
		case LEFT:
			game[19][1]='M';
			break;
		case RIGHT:
			game[19][3]='M';
			break;
	}


}

void logic() {
	int i, j;
	switch (dir) {
		case LEFT:
			game[19][1]='M';
			break;
		case RIGHT:
			game[19][3]='M';
			break;
	}

	if (game[length-1][1]=='-' && dir==LEFT) lose();
	if (game[length-1][3]=='-' && dir==RIGHT) lose();


	if (game[18][1]=='-' && dir==LEFT) {
		upsc();
		if (dir==LEFT) lose();
	}
	if (game[18][3]=='-' && dir==RIGHT) {
		upsc();
		if (dir==RIGHT) lose();
	}

	for (i=19, j=2 ; i>=0 ; i--) {
		game[i+1][j+1]=game[i][j+1];
		game[i+1][j-1]=game[i][j-1];
	}

	int d=rand() % 3;
	switch (d) {
		case 0:
			game[0][3]='-';
			game[0][1]=' ';
			break;
		case 1:
			game[0][1]='-';
			game[0][3]=' ';
			break;
		case 2:
			game[0][3]=' ';
			game[0][1]=' ';
			break;
	}


	for (i=18, j=2 ; i>=0 ; i--) {
		int f=rand() % 2;
		if (f==1) {
			if (game[i][j+1]=='-' && game[i-1][j-1]=='-') game[i-1][j-1]=' ';
			else if (game[i][j-1]=='-' && game[i-1][j+1]=='-') game[i-1][j+1]=' ';
		} else {
			if (game[i][j+1]=='-' && game[i-1][j-1]=='-') {
				game[i-1][j-1]=' ';
				game[i-1][j+1]='-';
			} else if (game[i][j-1]=='-' && game[i-1][j+1]=='-') {
				game[i-1][j+1]=' ';
				game[i-1][j-1]='-';
			}
		}
	}

	system("cls");

	for (i=0 ; i<length ; i++) {
		for (j=0 ; j<width ; j++) {
			if (j==0) {
				printf ("*");
				printf("   ");
			}
			if (j==width-1) {
				printf("  ");
				printf ("*");
			}
			printf ("%c", game[i][j]);
		}
		printf ("\n");
	}

	printf("\n");
	score+=1;
	printf ("Score: %d", score);
}




int main() {
	srand( time(NULL));

	setup();
	draw();

	while (1) {
		input();
		logic();

	}

}