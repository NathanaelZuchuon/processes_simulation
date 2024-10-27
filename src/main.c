// Author: Nathanael Zuchuon 3GI 2024-2025
// =======================================

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glu.h>
#include <unistd.h>
#include <stdbool.h>
#include <windows.h>

#include "../include/GL/glut.h"
#include "../include/algorithms/fcfs.h"
#include "../include/algorithms/ps.h"
#include "../include/algorithms/rr.h"
#include "../include/algorithms/sjf.h"

#define WIN_WIDTH 1200 // window's width
#define WIN_HEIGHT 600 // window's height

#define FONT GLUT_BITMAP_HELVETICA_18 // font family used

#define NUM_PROCESSES 5 // number of processes
#define NUM_ALGORITHMS 4 // number of algorithms implemented
#define ALGO(a, b, c, d) {"FCFS", "PS", "RR", "SJF"} // algorithms
// ===============================================================

void start();
void popup();
void myInit();
void closeW(int W);
void drawStartButton();
float zuchuon(double x);
void draw(int i_colour);
int random(int min, int max);
void temporisation(int value);
void drawRectangle(char *side);
void drawDescZone(char *desc, int i_colour);
bool onButton(int indexButton, int x, int y);
// colour of button when clicked : fcfs->0 • ps->1 • rr->2 • sjf->3
void drawAlgorithmButtons(int n, int i_colour);
// ----------------------------------------------------------------
void create(int x, int y, int w, int h, char *type);
void clickMouse(int button, int state, int x, int y);
void drawButton(const char *text, int x, int y, int i_colour);

typedef struct
{
	int id; // [|1;5|]
	int priority; // [|0;10|]
	int arrival_time; // [|0;10|]
	int burst_time; // [|1;10|]
	float colour; // zuch(priority)
	int remaining_time; // (-)burst_time
} Process;

typedef struct
{
	int x;
	int y;
	int w;
	int h;
} Button;

Button buttons[5]; // start->0 • fcfs->1 • ps->2 • rr->3 • sjf->4
int indexButton = 0;

char *algoUsed = "";
Process processes[NUM_PROCESSES];

int mainFrame;
int popupFrame;

bool v = true; // Do not generate processes while `Start` is pressed many times

float *s_y; // start_y
float *processWidth;
float *processHeight;
// ============================================================================

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutInitWindowPosition(100, 100);

	mainFrame = glutCreateWindow("Processes Simulation");

	glutDisplayFunc(start);
	glutMouseFunc(clickMouse);
	glutMainLoop();

	return 0;
}
// ============================================================================

void pop()
{
	myInit();
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(75, 300);

	char *text = "Select the Algorithm firstly !";
	for (const char *t = text; *t != '\0'; t++)
	{
		glutBitmapCharacter(FONT, *t);
	}
	glutSwapBuffers();

	Sleep(1000);
	closeW(popupFrame);
}

void start()
{
	draw(-1);
}

void popup()
{
	popupFrame = glutCreateWindow("ERROR");

	glutPositionWindow(600, 300);
	glutReshapeWindow(250, 100);

	glutDisplayFunc(pop);
}

void myInit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIN_WIDTH, WIN_HEIGHT, 0, -1, 1); // (0,0) -> (ww,wh)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.3, 0.3, 0.3, 0.2); // bg-color
	glClear(GL_COLOR_BUFFER_BIT);
}

void closeW(int W)
{
	glutDestroyWindow(W);
}

void drawStartButton()
{
	drawButton("START !", WIN_WIDTH * 0.5, WIN_HEIGHT * 0.875, -1);
}

float zuchuon(double x)
{
	return x / RAND_MAX;
}

void draw(int i_colour)
{
	myInit();

	drawRectangle("left");
	drawRectangle("right");
	drawStartButton();
	drawAlgorithmButtons(NUM_ALGORITHMS, i_colour);
	drawDescZone(NULL, i_colour);

	glutSwapBuffers(); // because of GLUT_DOUBLE : glFlush <=> GLUT_SINGLE
}

int random(int min, int max)
{
	return min + rand() % (max - min + 1);
}

void temporisation(int value)
{
	while (*processWidth < value)
	{
		Sleep(5);

		glutSwapBuffers();
		create(WIN_WIDTH * 0.02, *s_y, *processWidth, *processHeight, "button");
		glutSwapBuffers();

		*processWidth += 1;
	}
}

void drawRectangle(char *side)
{
	float t = (side == "left") ? 0 : WIN_WIDTH * 0.75; // translation

	glColor3f(1.0, 1.0, 1.0);
	glPointSize(5);
	create(WIN_WIDTH * 0.01 + t, WIN_HEIGHT * 0.25, WIN_WIDTH * 0.23, WIN_HEIGHT * 0.5, "frame");
}

void drawDescZone(char *desc, int i_colour)
{
	if (desc == NULL)
	{
		glColor3f(1.0, 1.0, 1.0);
		create(WIN_WIDTH * 0.24, WIN_HEIGHT * 0.125, WIN_WIDTH * 0.52, WIN_HEIGHT * 0.125, "frame");
	}
	else
	{
		start();
		drawAlgorithmButtons(NUM_ALGORITHMS, i_colour);

		glColor3f(0.3, 0.3, 0.3);
		create(WIN_WIDTH * 0.24, WIN_HEIGHT * 0.125, WIN_WIDTH * 0.52, WIN_HEIGHT * 0.125, "button");

		glColor3f(1.0, 1.0, 1.0);
		create(WIN_WIDTH * 0.24, WIN_HEIGHT * 0.125, WIN_WIDTH * 0.52, WIN_HEIGHT * 0.125, "frame");

		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(WIN_WIDTH * 0.24416, WIN_HEIGHT * 0.1583);
		for (const char *d = desc; *d != '\0'; d++)
		{
			if (*d == '\n')
			{
				glRasterPos2f(WIN_WIDTH * 0.24416, WIN_HEIGHT * 0.1916);
				continue;
			}
			glutBitmapCharacter(FONT, *d);
		}

		glutSwapBuffers();
	}
}

bool onButton(int indexButton, int x, int y)
{
	if ( x >= buttons[indexButton].x && x <= (buttons[indexButton].x + buttons[indexButton].w) && \
			y >= buttons[indexButton].y && y <= (buttons[indexButton].y + buttons[indexButton].h) )
	{
		return true;
	}
	return false;
}

void drawAlgorithmButtons(int n, int i_colour)
{
	int w = WIN_WIDTH / 15;
	int eps = WIN_WIDTH / 80; // soucis d'alignement personnel
	int n_esp = WIN_WIDTH / 120;
	char *algo[NUM_ALGORITHMS] = ALGO(a, b, c, d);

	int start_x = WIN_WIDTH * 0.24 + eps, start_y = WIN_HEIGHT * 0.0625;
	for (int i = 0; i < n; i++)
	{
		start_x += n_esp;
		if (i == i_colour)
		{
			drawButton(algo[i], start_x, start_y, 1);
		}
		else
		{
			drawButton(algo[i], start_x, start_y, -1);
		}
		start_x += w;
	}
}

void create(int x, int y, int w, int h, char *type)
{
	if ( type == "button" )
	{
		glBegin(GL_QUADS);
	}
	if ( type == "frame" )
	{
		glBegin(GL_LINE_LOOP);
	}
	glVertex2f(x, y); // upper left corner
	glVertex2f(x+w, y); // upper right corner
	glVertex2f(x+w, y+h); // lower right corner
	glVertex2f(x, y+h); // lower left corner
	glEnd();
}

void clickMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (onButton(0, x, y))
		{
			if (algoUsed == "")
			{
				popup();
			}
			else
			{
				if (v)
				{
					srand(time(NULL));
					for (int i = 0; i < NUM_PROCESSES; i++)
					{
						processes[i].id = i + 1;
						processes[i].priority = random(RAND_MAX*0.25, RAND_MAX);
						processes[i].arrival_time = random(1, 10);
						processes[i].burst_time = random(1, 10);
						processes[i].remaining_time = processes[i].burst_time;
						processes[i].colour = zuchuon((double)processes[i].priority);
					}

					// BEGIN ===
					float esp = WIN_HEIGHT * 0.01;
						
					processWidth = malloc(sizeof(float));
					*processWidth = 0.0;

					processHeight = malloc(sizeof(float));
					*processHeight = ( (WIN_HEIGHT / 2) - ((NUM_PROCESSES + 1) * esp) ) / NUM_PROCESSES;

					s_y = malloc(sizeof(float));
					*s_y = WIN_HEIGHT * 0.25;

					for (int i = 0; i < NUM_PROCESSES; i++)
					{
						*s_y += esp;
						glColor3f(processes[i].colour, 0.2, 0.2);
						temporisation((int)(processes[i].burst_time * WIN_WIDTH * 0.021));
						*s_y += *processHeight;

						*processWidth = 0.0;
					}
					free(s_y);
					free(processHeight);
					// END =====
					v = false;
				}
			}
		}

		if (onButton(1, x, y))
		{
			drawDescZone(fcfs_desc(), 0);
			algoUsed = "fcfs";
		}

		if (onButton(2, x, y))
		{
			drawDescZone(ps_desc(), 1);
			algoUsed = "ps";
		}

		if (onButton(3, x, y))
		{
			drawDescZone(rr_desc(), 2);
			algoUsed = "rr";
		}

		if (onButton(4, x, y))
		{
			drawDescZone(sjf_desc(), 3);
			algoUsed = "sjf";
		}
	}
}

void drawButton(const char *text, int x, int y, int i_colour)
{
	glPointSize(5);

	int textWidth = 0;
	for (const char *t = text; *t != '\0'; t++)
	{
		textWidth += glutBitmapWidth(FONT, *t);
	}

	int buttonWidth = textWidth + (WIN_WIDTH /120);
	int buttonHeight = WIN_HEIGHT / 20;

	if (i_colour == -1)
	{
		glColor3f(1.0, 1.0, 1.0);
	}
	else
	{
		glColor3f(0.0, 1.0, 0.0);
	}
	create(x - textWidth / 2, y, buttonWidth, buttonHeight, "button");

	// ----------------------------------------
	buttons[indexButton].x = x - textWidth / 2;
	buttons[indexButton].y = y;
	buttons[indexButton].w = buttonWidth;
	buttons[indexButton].h = buttonHeight;
	indexButton++;
	// ----------------------------------------

	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(x - textWidth / 2 + (buttonWidth - textWidth) / 2, y + (buttonHeight + WIN_HEIGHT * 0.023) / 2);
	for (const char *t = text; *t != '\0'; t++)
	{
		glutBitmapCharacter(FONT, *t);
	}
}