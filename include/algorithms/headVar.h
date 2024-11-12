#define WIN_WIDTH 1200 // window's width
#define WIN_HEIGHT 600 // window's height

#define NUM_PROCESSES 5 // number of processes

#ifndef hV
#define hV

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "../GL/glut.h"

typedef struct
{
	int id;				// [|1;n|]  • 0
	int priority;		// [|0;10|] • 1
	int burst_time;		// [|1;10|] • 2
	int remaining_time; // (-)burst_time
	float colour;		// zuchuon(priority)
} Process;

void tempo(int value, float x, float y, int w, float h);
void create(int x, int y, int w, int h, char *type);
void sortProcesses(Process processes[], int attr);
void printp(Process p, int x, int y, float h);
void permute(Process *p1, Process *p2);
void scheduling(Process processes[]);
void sub(int *t, int q);

#endif
