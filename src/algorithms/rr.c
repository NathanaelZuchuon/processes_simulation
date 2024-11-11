#include "../../include/algorithms/rr.h"

void rr(Process processes[])
{
	sortProcesses(processes, 0);
	Process temp[] = *(&processes);

	float h = (WIN_HEIGHT * 0.48) / NUM_PROCESSES;

	float x = WIN_WIDTH * 0.25;
	float y = WIN_HEIGHT * 0.74;

	int processesFinished = 0;
	float w = (QUANTUM * WIN_WIDTH * 0.5) / (10 * (NUM_PROCESSES + 1));

	while ( processesFinished < NUM_PROCESSES )
	{
		for (int i = 0; i < NUM_PROCESSES; i++)
		{
			glColor3f(processes[i].colour, 0.2, 0.2);

			if ( processes[i].remaining_time > QUANTUM )
			{
				tempo(0, x, y, w, h);
				sub(&processes[i], QUANTUM);
			} else {
				tempo(0, x, y, (processes[i].remaining_time * WIN_WIDTH * 0.5) / (10 * (NUM_PROCESSES + 1)), h);
				(&processes[i])->remaining_time = 0;

				processesFinished++;
			}

			x += w;
			y -= h;
		}
		y = WIN_HEIGHT * 0.74;
	}
	*(&processes) = temp;
}

char* rr_desc()
{
	char *desc = "Round Robin : It's a method of ordering processes that\nconsists of treating all of them with the same quantum of time.";
	return desc;
}
