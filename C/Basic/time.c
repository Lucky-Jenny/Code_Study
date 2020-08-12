#include <stdio.h>
#include <time.h>

int main()
{
	time_t lxtime;				// time_t is long In <time.h>
	struct tm *timeinfo;		// tm defined in <time.h>

	time(&lxtime);				// time() MUST!! -> TimeStamps from 1970
	printf("Timestamp is %ld\n", lxtime);

	timeinfo = localtime(&lxtime);		// localtime() -> convert to tm in local Time Zone.
	printf("The current time is: %s\n", asctime(timeinfo));
			// asctime() --> Wed Aug 12 10:01:21 2020
	return 0;
}


