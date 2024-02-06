#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

char game[22][10];
int const length = 21, width = 7, freeze_countdown = 10;
int score, t = 8, move = 0, level = 1;
int time_flag = 1, time_f = 1;
char karate;

void yesorno();
void usescore();

struct point {
	int i, j, x;
};

void changechar() {
	if (level == 1) karate='Z';
	else if (level == 2) karate='X';
	else if (level == 3) karate='V';
	else if (level == 4) karate='R';
	else if (level == 5) karate='Q';
	else if (level == 6) karate='O';
	else if (level == 7) karate='N';
	else if (level == 8) karate='M';
	else if (level == 9) karate='H';
	else if (level == 10) karate='G';
	else if (level == 11) karate='E';
	else if (level == 12) karate='D';
	else if (level == 13) karate='C';
	else if (level == 14) karate='B';
	else if (level == 15) karate='A';
	else if (level == 16) karate='K';
}

void loadGame() {
	FILE *file;
	file = fopen("C:\\Users\\User\\Desktop\\saved_game.bin", "rb");
	if (file == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
	fread(game, sizeof(char), sizeof(game) / sizeof(char), file);
	fread(&score, sizeof(int), 1, file);
	fread(&level, sizeof(int), 1, file);
	fread(&t, sizeof(int), 1, file);
	
	system("cls");
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0) {
				printf("*   ");
			}
			if (j == width - 1) {
				printf("  *");
			}
			printf("%c", game[i][j]);
		}
		printf("\n");
	}
	printf("\nScore: %d\n", score);
	printf("Level: %d\n", level);
	printf("Time: %d", t);
	
	fclose(file);
}

void lev(int score) {
	if (score < 100) level = 1;
	else if (score < 300) level = 2;
	else if (score < 600) level = 3;
	else if (score < 1000) level = 4;
	else if (score < 1500) level = 5;
	else if (score < 2100) level = 6;
	else if (score < 2800) level = 7;
	else if (score < 3600) level = 8;
	else if (score < 4500) level = 9;
	else if (score < 5500) level = 10;
	else if (score < 7500) level = 11;
	else if (score < 9500) level = 12;
	else if (score < 11500) level = 13;
	else if (score < 13500) level = 14;
	else if (score < 15000) level = 15;
	else if (score >= 15000) level = 16;
}

enum direction {LEFT, RIGHT };
enum direction dir;

void input() {
	char c = getch();
	switch (c) {
		case 'd':
		case 'D':
			dir = RIGHT;
			break;
		case 'a':
		case 'A':
			dir = LEFT;
			break;
		case 's':
		case 'S':
			time_flag = 0;
			yesorno();
			break;
	}
	move = 1;
	if (t <= 7 && time_f) t++;
}

void freeze() {
	int i, j;
	time_f = 0;
	printf("\nFreeze Mode Activated! Remaining moves: %d\n", freeze_countdown);
	for (i = 0; i < freeze_countdown - 1; i++) {
		time_f = 0;
		input();
		switch (dir) {
			case LEFT:
				game[19][1] = karate;
				break;
			case RIGHT:
				game[19][3] = karate;
				break;
		}
		for (i = 19, j = 2; i >= 0; i--) {
			game[i + 1][j + 1] = game[i][j + 1];
			game[i + 1][j - 1] = game[i][j - 1];
		}
		system("cls");
		for (i = 0; i < length; i++) {
			for (j = 0; j < width; j++) {
				if (j == 0) printf("*   ");
				if (j == width - 1) printf("  *");
				printf("%c", game[i][j]);
			}
			printf("\n");
		}
		printf("\rRemaining moves: %d", freeze_countdown - i);
		fflush(stdout);
		sleep(1);
	}
	printf("\nFreeze Mode Deactivated!\n");
	time_f = 1;
}

void twice() {
	int i, j;
	printf("\nTwice Mode Activated! Remaining moves: %d\n", freeze_countdown);
	for (i = 0; i < freeze_countdown - 1; i++) {
		input();
		switch (dir) {
			case LEFT:
				game[19][1] = karate;
				break;
			case RIGHT:
				game[19][3] = karate;
				break;
		}
		for (i = 19, j = 2; i >= 0; i--) {
			game[i + 1][j + 1] = game[i][j + 1];
			game[i + 1][j - 1] = game[i][j - 1];
		}
		system("cls");
		for (i = 0; i < length; i++) {
			for (j = 0; j < width; j++) {
				if (j == 0) printf("*   ");
				if (j == width - 1) printf("  *");
				printf("%c", game[i][j]);
			}
			printf("\n");
		}
		score+=2;
		lev(score);
		printf("\nScore: %d\n", score);
		printf("Level: %d\n", level);
		printf("\n\rRemaining moves: %d", freeze_countdown - i);
		fflush(stdout);
		sleep(1);
	}
	printf("\nTwice Mode Deactivated!\n");
}

void speed() {
	int i, j, k;
	printf("\nSpeed Mode Activated!");
	for (k=0 ; k<6 ; k++) {
		for (i = 19, j = 2; i >= 0; i--) {
			game[i + 1][j + 1] = game[i][j + 1];
			game[i + 1][j - 1] = game[i][j - 1];
		}
		game[19][1]=karate;
		system("cls");
		for (i = 0; i < length; i++) {
			for (j = 0; j < width; j++) {
				if (j == 0) printf("*   ");
				if (j == width - 1) printf("  *");
				printf("%c", game[i][j]);
			}
			printf("\n");
		}
		score+=1;
		lev(score);
		printf("\nScore: %d\n", score);
		printf("Level: %d\n", level);
		Sleep(750);
	}
	time_f = 0;
	printf("Speed Mode Deactivated!\n");
	Sleep(500);
	time_f = 1;
}

void draw_F() {
	int g=rand() % 5;
	if (g==1) {
		int s=rand() % 2;
		if (s==0) game[0][1]='F';
		else if (s==1) game[0][3]='F';
	}
}

void draw_2() {
	int g=rand() % 5;
	if (g==1) {
		int s=rand() % 2;
		if (s==0) game[0][1]='2';
		else if (s==1) game[0][3]='2';
	}
}

void draw_T() {
	int g=rand() % 5;
	if (g==1) {
		int s=rand() % 2;
		if (s==0) game[0][1]='T';
		else if (s==1) game[0][3]='T';
	}
}

void draw_S() {
	int g=rand() % 5;
	if (g==1) {
		int s=rand() % 2;
		if (s==0) game[0][1]='S';
		else if (s==1) game[0][3]='S';
	}
}

void saveGame() {
	FILE *file;
	file = fopen("C:\\Users\\User\\Desktop\\saved_game.bin", "wb");
	if (file == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
	fwrite(game, sizeof(char), sizeof(game) / sizeof(char), file);
	fwrite(&score, sizeof(int), 1, file);
	fwrite(&level, sizeof(int), 1, file);
	fwrite(&t, sizeof(int), 1, file);
	fclose(file);
}

void lose(int a) {
	system("cls");
	printf("    /---------\\\n");
	printf(" |---Gameover!---|\n");
	printf("    \\---------/");
	printf("\a\n");
	if (a==1){
		printf ("Your time is over!\n");
	}
	else {
		printf ("You hit the branch!\n");
	}
	printf("Your Score is: %d\n", score);
	printf("Your Level is: %d\n", level);
	printf("Powered By Hosein Vaezi");
	exit(0);
}

void endgame() {
	saveGame();
	system("cls");
	printf("      /---------\\\n");
	printf(" You have reached the endgame!\n");
	printf("      \\---------/\n\n");
	printf("Your Score is: %d\n", score);
	printf("Your Level is: %d\n", level);
	printf("Powered By Hosein Vaezi");
	exit(0);
}

void setup() {
	score = 0;
}

void draw() {
	system("cls");
	lev(score);
	changechar();
	int i, j;
	int a = rand() % 3;
	for (i = 0; i < length; i++) {
		for (j = 0; j < width; j++) {
			a = rand() % 3;
			if (j == 0) game[i][j] = '*';
			if (j == width - 1) game[i][j] = '*';
			if (j == 2) {
				a = rand() % 3;
				if (a == 0 && i != 20) {
					if (game[i - 1][j - 1] != '-' && game[i][j - 1] != '|') {
						game[i][j] = '|';
						game[i][j + 1] = '-';
						game[i][j - 1] = ' ';
					} else {
						game[i][j] = '|';
						game[i][j + 1] = ' ';
						game[i][j - 1] = ' ';
					}
				} else if (a == 1 && i != 20) {
					if (game[i - 1][j + 1] != '-' && game[i][j + 1] != '|') {
						game[i][j] = '|';
						game[i][j - 1] = '-';
						game[i][j + 1] = ' ';
					} else {
						game[i][j] = '|';
						game[i][j + 1] = ' ';
						game[i][j - 1] = ' ';
					}
				} else if (a == 2 && i != 20) {
					game[i][j - 1] = ' ';
					game[i][j] = '|';
					game[i][j + 1] = ' ';
				}
				if (i == 20) {
					game[i][j] = '|';
					game[i][j + 1] = karate;
					game[i][j + 2] = ' ';
				}
			} else if (game[i][j] != '-' && game[i][j] != karate && game[i][j] != '|') {
				game[i][j] = ' ';
			}
		}
	}
	game[19][3] = game[19][1] = ' ';
	for (i = 0; i < length; i++) {
		for (j = 0; j < width; j++) {
			if (j == 0) {
				printf("*   ");
			}
			if (j == width - 1) {
				printf("  *");
			}
			printf("%c", game[i][j]);
		}
		printf("\n");
	}
	printf("\nScore: %d\n", score);
	printf("Level: %d\n", level);
	printf("Time: %d", t);
}

void *countdown(void *arg) {
	while (t > 0) {
		if (time_flag && time_f) {
			printf("\rTime: %d", t);
			fflush(stdout);
			sleep(1);
			t--;
		}
		if (t == 0) {
			lose(1);
		}
	}
	pthread_exit(NULL);
}

void upsc() {
	int i, j;
	for (i = 19, j = 2; i >= 0; i--) {
		game[i + 1][j + 1] = game[i][j + 1];
		game[i + 1][j - 1] = game[i][j - 1];
	}
	score += 1;
	lev(score);
	changechar();
	system("cls");
	for (i = 0; i < length; i++) {
		for (j = 0; j < width; j++) {
			if (j == 0) {
				printf("*   ");
			}
			if (j == width - 1) {
				printf("  *");
			}
			printf("%c", game[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("Score: %d\n", score);
	printf("Level: %d\n", level);
	printf("Time: %d", t);
	int d = rand() % 3;
	switch (d) {
		case 0:
			game[0][3] = '-';
			game[0][1] = ' ';
			break;
		case 1:
			game[0][1] = '-';
			game[0][3] = ' ';
			break;
		case 2:
			game[0][3] = ' ';
			game[0][1] = ' ';
			break;
	}
	input();
	switch (dir) {
		case LEFT:
			game[19][1] = karate;
			break;
		case RIGHT:
			game[19][3] = karate;
			break;
	}
	move = 0;
}

void logic() {
	changechar();
	int i, j;
	switch (dir) {
		case LEFT:
			game[19][1] = karate;
			break;
		case RIGHT:
			game[19][3] = karate;
			break;
	}
	if (game[length - 1][1] == '-' && dir == LEFT) lose(2);
	if (game[length - 1][3] == '-' && dir == RIGHT) lose(2);

	if (game[length - 1][1] == 'F' && dir == LEFT) freeze();
	if (game[length - 1][3] == 'F' && dir == RIGHT) freeze();

	if (game[length - 1][1] == '2' && dir == LEFT) twice();
	if (game[length - 1][3] == '2' && dir == RIGHT) twice();

	if (game[length - 1][1] == 'T' && dir == LEFT) {
		if (t<=6) t+=2;
	}
	if (game[length - 1][3] == 'T' && dir == RIGHT) {
		if (t<=6) t+=2;
	}

	if (game[length - 1][1] == 'S' && dir == LEFT) speed();
	if (game[length - 1][3] == 'S' && dir == RIGHT) speed();

	if ((game[18][1] == '-' && dir == LEFT) || (game[18][1] == '-' && dir == RIGHT)) {
		upsc();
		move = 1;
		if (dir == LEFT)
			lose(2);
	}
	if ((game[18][3] == '-' && dir == RIGHT) || (game[18][3] == '-' && dir == LEFT)) {
		upsc();
		move = 1;
		if (dir == RIGHT)
			lose(2);
	}

	if ((game[18][1] == 'F' && dir == LEFT) || (game[18][1] == 'F' && dir == RIGHT)) {
		upsc();
		move = 1;
		if (dir == LEFT) freeze();
	}
	if ((game[18][3] == 'F' && dir == RIGHT) || (game[18][3] == 'F' && dir == LEFT)) {
		upsc();
		move = 1;
		if (dir == RIGHT) freeze();
	}

	if ((game[18][1] == '2' && dir == LEFT) || (game[18][1] == '2' && dir == RIGHT)) {
		upsc();
		move = 1;
		if (dir == LEFT) twice();
	}
	if ((game[18][3] == '2' && dir == LEFT) || (game[18][3] == '2' && dir == RIGHT)) {
		upsc();
		move = 1;
		if (dir == LEFT) twice();
	}

	if ((game[18][1] == 'T' && dir == LEFT) || (game[18][1] == 'T' && dir == RIGHT)) {
		upsc();
		move = 1;
		if (dir == LEFT) {
			if (t<=6) t+=2;
		}
	}
	if ((game[18][3] == 'T' && dir == LEFT) || (game[18][3] == 'T' && dir == RIGHT)) {
		upsc();
		move = 1;
		if (dir == LEFT) {
			if (t<=6) t+=2;
		}
	}

	if ((game[18][1] == 'S' && dir == LEFT) || (game[18][1] == 'S' && dir == RIGHT)) {
		upsc();
		move = 1;
		if (dir == LEFT) speed();
	}
	if ((game[18][3] == 'S' && dir == LEFT) || (game[18][3] == 'S' && dir == RIGHT)) {
		upsc();
		move = 1;
		if (dir == LEFT) speed();
	}

	for (i = 19, j = 2; i >= 0; i--) {
		game[i + 1][j + 1] = game[i][j + 1];
		game[i + 1][j - 1] = game[i][j - 1];
	}

	if (game[19][1] == karate && game[19][2] == 'F') {
		freeze();
		game[19][2] = ' ';
	} else if (game[19][3] == karate && game[19][4] == 'F') {
		freeze();
		game[19][4] = ' ';
	}

	int d = rand() % 12;
	switch (d) {
		case 0:
		case 1:
		case 2:
			game[0][3] = '-';
			game[0][1] = ' ';
			break;
		case 3:
		case 4:
		case 5:
			game[0][1] = '-';
			game[0][3] = ' ';
			break;
		case 6:
		case 7:
			game[0][3] = ' ';
			game[0][1] = ' ';
			break;
		case 8:
			draw_F();
			break;
		case 9:
			draw_2();
			break;
		case 10:
			draw_T();
			break;
		case 11:
			draw_S();
			break;
	}

	for (i = 18, j = 2; i >= 0; i--) {
		int f = rand() % 2;
		if (f == 1) {
			if (game[i][j + 1] == '-' && game[i - 1][j - 1] == '-') {
				game[i - 1][j - 1] = ' ';
			} else if (game[i][j - 1] == '-' && game[i - 1][j + 1] == '-') {
				game[i - 1][j + 1] = ' ';
			}
		} else {
			if (game[i][j + 1] == '-' && game[i - 1][j - 1] == '-') {
				game[i - 1][j - 1] = ' ';
				game[i - 1][j + 1] = '-';
			} else if (game[i][j - 1] == '-' && game[i - 1][j + 1] == '-') {
				game[i - 1][j + 1] = ' ';
				game[i - 1][j - 1] = '-';
			}
		}
	}

	changechar();
	system("cls");
	for (i = 0; i < length; i++) {
		for (j = 0; j < width; j++) {
			if (j == 0) {
				printf("*   ");
			}
			if (j == width - 1) {
				printf("  *");
			}
			printf("%c", game[i][j]);
		}
		printf("\n");
	}
	move = 0;
	printf("\n");
	score += 1;
	lev(score);
	printf("Score: %d\n", score);
	printf("Level: %d\n", level);
	printf("Time: %d", t);
}

void yesorno() {
	if (!time_flag) {
		printf("\nDo you want to continue (y/n)? ");
		char response = getch();
		if (response == 'y' || response == 'Y') {
			time_flag = 1;
			input();
			logic();
		} else if (response == 'n' || response == 'N') {
			saveGame();
			endgame();
		}
	}
}

int main() {
	printf ("Do you want to continue the previous game or start a new game? (c=continue/s=start)");
	int sw=0;
	int c;
	c=getch();
	if (c=='c' || c=='C') loadGame();
	else if (c=='s' || c=='S') sw=1;
	else {
		system("cls");
		printf ("You pressed the wrong key!\nPlease try again later.");
		return 0;
	}
	srand(time(NULL));
	if (sw==1) {
		setup();
		draw();
	}

	pthread_t tid;
	pthread_create(&tid, NULL, countdown, NULL);

	while (1) {
		input();
		logic();
		if (t == 0) break;
	}
	pthread_join(tid, NULL);
	return 0;
}