#include "../../include/algorithms/fcfs.h"

void fcfs(Process processes[])
{
	sortProcesses(processes, 0);
	scheduling(processes);
}

char *fcfs_desc()
{
	char *desc = "Fisrt Come First Served : It's a method of ordering processes that\nconsists of treating the first come.";
	return desc;
}

// ===
void tempo(int value, float x, float y, int w, float h)
{
	while (value < w)
	{
		glutSwapBuffers();

		glBegin(GL_QUADS);
		glVertex2f(x, y);			   // lower left corner
		glVertex2f(x + value, y);	   // lower right corner
		glVertex2f(x + value, y - h); // upper right corner
		glVertex2f(x, y - h);		   // upper left corner
		glEnd();

		glutSwapBuffers();

		value += 1;
	}
}

void sortProcesses(Process processes[], int attr)
{
	for (int i = 0; i < NUM_PROCESSES - 1; i++)
	{
		for (int j = 0; j < NUM_PROCESSES - i - 1; j++)
		{
			switch (attr)
			{
				case 0:
					if (processes[j].id >= processes[j + 1].id)
					{
						permute(&processes[j], &processes[j + 1]);
					}
					break;
				case 1:
					if (processes[j].priority <= processes[j + 1].priority)
					{
						permute(&processes[j], &processes[j + 1]);
					}
					break;

				case 2:
					if (processes[j].burst_time >= processes[j + 1].burst_time)
					{
						permute(&processes[j], &processes[j + 1]);
					}
					break;

				default:
					printf("Unknowed Error !!");
					break;
			}
		}
	}
}

void permute(Process *p1, Process *p2)
{
	Process temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

void scheduling(Process processes[])
{
	float h = (WIN_HEIGHT * 0.48) / NUM_PROCESSES;

	float x = WIN_WIDTH * 0.25;
	float y = WIN_HEIGHT * 0.74;

	float w = 0.0;
	for (int i = 0; i < NUM_PROCESSES; i++)
	{
		w = (processes[i].burst_time * WIN_WIDTH * 0.5) / (10 * (NUM_PROCESSES + 1));

		glColor3f(processes[i].colour, 0.2, 0.2);
		tempo(0, x, y, w, h);

		x += w;
		y -= h;
	}
}
// ===
