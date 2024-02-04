#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

char game[22][10];
int score, des;
int const length = 21, width = 7;
int t = 8, move = 0, level = 1;
int time_flag = 1; // اضافه کردن یک علامت برای متوقف کردن زمان

struct point {
	int i, j, x;
};

void lev(int score) {
	if (score < 100)
		level = 1;
	else if (score < 300)
		level = 2;
	// ...
}

void freeze() {
}

void saveScore() {
	FILE *file;
	file = fopen("C:\\Users\\User\\Desktop\\highscore1.txt.txt", "a");  // باز کردن فایل برای افزودن داده

	if (file == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}

	fprintf(file, "Score: %d, Level: %d\n", score, level);

	fclose(file);  // بستن فایل
}

void lose() {
	system("cls");

	printf("    /---------\\\n");
	printf(" |---Gameover!---|\n");
	printf("    \\---------/");
	printf("\a\n");

	printf("Your Score is: %d\n", score);
	printf("Your Level is: %d\n", level);

	saveScore();

	printf("Powered By Hosein Vaezi");

	exit(0);
}

void endgame() {
	system("cls");
	printf("      /---------\\\n");
	printf(" You have reached the endgame!\n");
	printf("      \\---------/");
	printf ("\a\n");

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
	int i, j;

	int a = rand() % 3;
	for (i = 0; i < length; i++) {
		for (j = 0; j < width; j++) {
			a = rand() % 3;
			if (j == 0) {
				game[i][j] = '*';
			}
			if (j == width - 1) {
				game[i][j] = '*';
			}
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
					game[i][j + 1] = 'M';
					game[i][j + 2] = ' ';
				}
			} else if (game[i][j] != '-' && game[i][j] != 'M' && game[i][j] != '|') {
				game[i][j] = ' ';
			}
		}
	}

	game[19][3] = game[19][1] = ' ';

	for (i = 0; i < length; i++) {
		for (j = 0; j < width; j++) {
			if (j == 0) {
				printf("*");
				printf("   ");
			}
			if (j == width - 1) {
				printf("  ");
				printf("*");
			}
			printf("%c", game[i][j]);
		}
		printf("\n");
	}

	lev(score);

	printf("\nScore: %d\n", score);
	printf("Level: %d\n", level);
	printf("Time: %d", t);
}

enum direction {
	LEFT,
	RIGHT
};
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
			// اگر کلید "s" یا "S" فشرده شد، زمان متوقف می‌شود
			time_flag = 0;
			break;
	}
	move = 1;

	// اگر زمان کمتر یا مساوی 7 باشد، یک ثانیه به زمان اضافه شود
	if (t <= 7) {
		t++;
	}
}

void *countdown(void *arg) {
	while (t > 0) {
		// اگر زمان متوقف نباشد، زمان کاهش پیدا می‌کند
		if (time_flag) {
			printf("\rTime: %d", t);
			fflush(stdout);
			sleep(1);
			t--;
		}
		// اگر زمان تمام شد، بازی اتمام می‌یابد
		if (t == 0) {
			lose();
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

	system("cls");

	for (i = 0; i < length; i++) {
		for (j = 0; j < width; j++) {
			if (j == 0) {
				printf("*");
				printf("   ");
			}
			if (j == width - 1) {
				printf("  ");
				printf("*");
			}
			printf("%c", game[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	score += 1;
	lev(score);
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
			game[19][1] = 'M';
			break;
		case RIGHT:
			game[19][3] = 'M';
			break;
	}

	move = 0;
}

void logic() {
	int i, j;
	switch (dir) {
		case LEFT:
			game[19][1] = 'M';
			break;
		case RIGHT:
			game[19][3] = 'M';
			break;
	}

	if (game[length - 1][1] == '-' && dir == LEFT)
		lose();
	if (game[length - 1][3] == '-' && dir == RIGHT)
		lose();

	if ((game[18][1] == '-' && dir == LEFT) || (game[18][1] == '-' && dir == RIGHT)) {
		upsc();
		move = 1;
		if (dir == LEFT)
			lose();
	}
	if ((game[18][3] == '-' && dir == RIGHT) || (game[18][3] == '-' && dir == LEFT)) {
		upsc();
		move = 1;
		if (dir == RIGHT)
			lose();
	}

	for (i = 19, j = 2; i >= 0; i--) {
		game[i + 1][j + 1] = game[i][j + 1];
		game[i + 1][j - 1] = game[i][j - 1];
	}

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

	system("cls");

	for (i = 0; i < length; i++) {
		for (j = 0; j < width; j++) {
			if (j == 0) {
				printf("*");
				printf("   ");
			}
			if (j == width - 1) {
				printf("  ");
				printf("*");
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

int main() {
	srand(time(NULL));

	setup();
	pthread_t tid;
	pthread_create(&tid, NULL, countdown, NULL);

	draw();

	while (1) {
		input();
		logic();

		// اگر زمان متوقف باشد و کلید s یا S را زد
		if (!time_flag) {
			printf("\nDo you want to continue (y/n)? ");
			char response = getch();
			if (response == 'y' || response == 'Y') {
				// اگر بازیکن می‌خواهد ادامه دهد، زمان را فعال کرده و از ابتدا شروع می‌کند
				time_flag = 1;
				input();
				logic();
			} else if (response == 'n' || response == 'N') {
				saveScore();
				endgame();
			}
		}
		if (t == 0)
			break;
	}

	pthread_join(tid, NULL);
	return 0;
}
