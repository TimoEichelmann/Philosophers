#include "philo.h"


int main(void)
{
	struct timeval time;
	long int start;
	gettimeofday(&time, NULL);
	start = time.tv_sec;
	printf("%ld\n", time.tv_usec);
	usleep(1000000);
	gettimeofday(&time, NULL);
	if (time.tv_sec != start)
		time.tv_usec += time.tv_sec - start / 1000000;
	printf("%ld", time.tv_usec);
}