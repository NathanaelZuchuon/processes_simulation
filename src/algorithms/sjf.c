#include "../../include/algorithms/sjf.h"

void sjf(Process processes[])
{
	sortProcesses(processes, 2);
	scheduling(processes);
}

char* sjf_desc()
{
	char *desc = "Short Job First : It's a method of ordering processes that\nconsists of treating the one with the smallest burst time.";
	return desc;
}
