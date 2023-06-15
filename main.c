#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define JUMP 'w'
#define END  'q'

const int width = 35;			//Ширина карты
const int height = 20;			//Высота карты
int x = 8;						//Позиция игрока по оси X
int y = 8;						//Позиция игрока по оси Y
int minX = 20;					//Позиция колонны
int maxX = 30;					//Тоже позиция колонны
int score = 0;					//Счет
int top = 6;					//Высота верхней колонны
int bottom = 14;				//Высота нижней колонны
bool gameOver = false;		

void Draw()
{
    system("cls");
	//Верхняя стенка
	for (int i = 0; i < width; i++) {
		if (i == 0) printf("[");
		else if (i == width - 1) printf("]");
		else printf("#");
	}

	printf("\n");
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0) printf("["); //Отрисовка левой боковой стенки
			else if (j == x && i == y) printf("0"); //Отрисовка игрока
			else if (j == width - 1) printf("]"); //Отрисовка правой боковой стенки
			else if ((j >= minX && j <= maxX) && (i >= 0 && i < top || i >= bottom && i < height)) printf("#"); //Отрисовка колонны
			else printf(" ");
		}
		printf("\n");
	}

	//Нижняя стенка
	for (int i = 0; i < width; i++) {
		if (i == 0) printf("[");
		else if (i == width - 1) printf("]");
		else printf("#");
	}
	printf("\nScore: %d", score);

}

void Logic()
{
    //Движение колонн
	minX--;
	maxX--;

	//Перемещение колонн
	if (maxX <= 0) {
		maxX = width + 10;
		if (score % 2 == 0) {
			top += 4;
			bottom += 4;
		}
		else {
			top -= 4;
			bottom -= 4;
		}
		score++;
	}
	if (minX <= -10) minX = width;

	//Гравитация и проверка на столкновение с змелей
	y++;
	if (y >= height || y <= 0) gameOver = true;

	//Проверка на столкновение с колонной
	if ((x >= minX && x <= maxX) && (y >= 0 && y < top || y >= bottom && y < height))
		gameOver = true;
}

void Input()
{
    //Обработка нажатий
	if (_kbhit()) {
		switch (_getch()) {
			case JUMP:
					y -= 5;
				break;
			case END:
				gameOver = true;
				break;
		}
	}
}

int main(void)
{
	while (!gameOver) 
    {
        Draw();
        Logic();
        Input();
	}
	printf("\n\n\t  GameOver\n");
	return 0;
}