#include "../../include/algorithms/rr.h"

void rr(Process processes[])
{
	sortProcesses(processes, 0);

	int temp[NUM_PROCESSES];
	for (int k = 0; k < NUM_PROCESSES; k++)
	{
		temp[k] = processes[k].remaining_time;
	}

	float esp = WIN_HEIGHT * 0.01;

	float h = (WIN_HEIGHT * 0.48) / NUM_PROCESSES;
	float p_h = ((WIN_HEIGHT / 2) - ((NUM_PROCESSES + 1) * esp)) / NUM_PROCESSES;

	float x = WIN_WIDTH * 0.25;

	float y = WIN_HEIGHT * 0.74;
	float p_y = WIN_HEIGHT * 0.25;

	int processesFinished = 0;

	float w = (QUANTUM * WIN_WIDTH * 0.5) / (10 * (NUM_PROCESSES + 1));

	while ( processesFinished < NUM_PROCESSES )
	{
		for (int i = 0; i < NUM_PROCESSES; i++)
		{
			glColor3f(processes[i].colour, 0.2, 0.2);

			if ( temp[i] > QUANTUM )
			{
				tempo(0, x, y, w, h);
				sub(&temp[i], QUANTUM);

				x += w;
				y -= h;

				continue;
			}

			if (temp[i] == 0)
			{
				/*x += w;
				y -= h;*/

				continue;

			} else {
				tempo(0, x, y, (temp[i] * WIN_WIDTH * 0.5) / (10 * (NUM_PROCESSES + 1)), h);
				temp[i] = 0;

				p_y += esp;
				printp(processes[i], WIN_WIDTH * 0.77, p_y, p_h);
				p_y += p_h;

				processesFinished++;
			}

			x += w;
			y -= h;
		}
		y = WIN_HEIGHT * 0.74;
	}
}

char* rr_desc()
{
	char *desc = "Round Robin : It's a method of ordering processes that\nconsists of treating all of them with the same quantum of time.";
	return desc;
}
