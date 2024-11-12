#include "../../include/algorithms/ps.h"

void ps(Process processes[])
{
	sortProcesses(processes, 1);
	scheduling(processes);
}

char* ps_desc()
{
	char *desc = "Priority Scheduling : It's a method of ordering processes that\nconsists of treating the one with the highest priotity.";
	return desc;
}
