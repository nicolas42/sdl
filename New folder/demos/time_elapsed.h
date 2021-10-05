#include <time.h>

double time_elapsed(void){
	return clock()/(double)CLOCKS_PER_SEC;
}
