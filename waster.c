#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define DP_NUM 15
#define DP_SIZE 100000

int main(int argc, char** argv)
{
	void* dp[DP_SIZE];
	int dp_to_alloc;
	FILE *fp=NULL;
       
	if (argc > 1)
		dp_to_alloc = atoi(argv[1]);
	else
		dp_to_alloc = DP_NUM;

	ushort alloc_count=0;
	fp = fopen("/proc/self/oom_adj", "w");
	if (fp)
	{
		fprintf(fp,"%d", -17);
		fclose(fp);
	}

	while(1)
	{
		if (alloc_count < dp_to_alloc)
		{
			void* p = (void*) malloc(1024*1024);
			if (!p)
			{
				printf("alloc failed at %d\n", alloc_count);
				sleep(1);
			}
			else
			{
				memset(p, 0, 1024*1024);
				alloc_count++;
			}
		}
		else
		{
			sleep(2);
			printf("defined max reached\n");
		}
	}

	return 0;
}
