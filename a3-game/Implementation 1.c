/* PING-PONG GAME */


#include <curses.h> /* getch () */
#include <stdio.h> /* putchar () */
#include <stdlib.h> /* system () */


#define UP 72 /* up arrow key code */
#define ESC 27 /* escape key code */
#define DOWN 80 /* down arrow key code */


void reverse_direction(); /* reverses the direction of the ball */
void refresh(); /* prints game process */
int calculate(int c); /* calculates next positions of objects (player1, player2, ball, etc.) */
void init(); /* initializes the player1, player2, ball structures */


struct
{
	int x, y; /* positions */
} player1, player2; /* left and right players */


struct
{
	int x, y; /* positions */
	struct
	{
		int x, y; /* how fast the ball moves */
	} speed;
	enum
	{
		LEFT_DOWN = 1,
		LEFT_UP,
		RIGHT_DOWN,
		RIGHT_UP
	} direction; /* contains information about what direction the ball should move in */
} ball;


int main(void)
{
	int c; /* stores code of a pressed key */
	init(); /* initializes the structures */
	refresh(); /* clears the screen and prints characters */
	while (c = _getch())
		if (calculate(c)) /* refresh () only if one if certain keys was pressed, if the escape key was pressed it calls exit (0) */
			refresh();
	return 0;
}


void refresh()
{
	int i = 0, j = 0;
	system("cls");
	while (i < 25)
	{
		j = 0;
		while (j < 80)
		{
			if ((j == player1.x && i == player1.y) || (j == player2.x && i == player2.y) || (j == ball.x && i == ball.y))
				putchar(219);
			else
				putchar(' ');
			++j;
		}
		++i;
	}
	return;
}


void init()
{
	player1.x = 0;
	player1.y = 0;
	player2.x = 79;
	player2.y = 0;
	ball.x = 50;
	ball.y = 15;
	ball.speed.x = 1;
	ball.speed.y = 1;
	ball.direction = RIGHT_DOWN;
	return;
}


int calculate(int c)
{
	if ((((ball.x == (player1.x + 1)) && (ball.y == player1.y)) || (ball.x == (player2.x - 1) && (ball.y == player2.y))) || (ball.y == 0 || ball.y == 24))
		reverse_direction();
	if (ball.direction == LEFT_DOWN)
	{
		ball.x -= ball.speed.x;
		ball.y += ball.speed.y;
	}
	else if (ball.direction == LEFT_UP)
	{
		ball.x -= ball.speed.x;
		ball.y -= ball.speed.y;
	}
	else if (ball.direction == RIGHT_UP)
	{
		ball.x += ball.speed.x;
		ball.y -= ball.speed.y;
	}
	else if (ball.direction == RIGHT_DOWN)
	{
		ball.x += ball.speed.x;
		ball.y += ball.speed.y;
	}
	if (c == UP)
		player1.y--;
	else if (c == DOWN)
		player1.y++;
	else if (c == 'q')
		player2.y--;
	else if (c == 'a')
		player2.y++;
	else if (c == ESC)
	{
		system("cls");
		exit(0);
	}
	else
		return 0;
	return 1;
}


void reverse_direction(void)
{
	if (ball.direction == RIGHT_UP)
		ball.direction = RIGHT_DOWN;
	if (ball.direction == RIGHT_DOWN)
		ball.direction = RIGHT_UP;
	if (ball.direction == LEFT_DOWN)
		ball.direction = LEFT_UP;
	if (ball.direction == LEFT_UP)
		ball.direction = LEFT_DOWN;
	return;
}