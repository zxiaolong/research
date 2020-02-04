#include <stdio.h>
#include <sys/resource.h>

int main()
{
	struct rlimit stRlim; 
	stRlim.rlim_cur = stRlim.rlim_max = RLIM_INFINITY;
	if (0 != setrlimit(RLIMIT_CORE, &stRlim)) 
	{
		printf("Error: setrlimit failed\n");
		return -1;
	}

	int a = 1/0;
	return 0;
}
