#include <sys/time.h>

#include "fiber_manager.h"
#include "fiber.h"

#define IT_COUNT 1000000

struct timeval in;
void* fiber_function(void* param)
{
    gettimeofday(&in, NULL);
    return NULL;
}

int main()
{
    int i;
    struct timeval start, end;
    long init_time = 0 , destroy_time = 0;

    printf("Starting experiment...\n");
    fiber_manager_init(1);

	for (i=0;i<IT_COUNT;i++) {
    	gettimeofday(&start, NULL);
    	fiber_t* client_fiber1 = fiber_create(10240, &fiber_function, NULL);
    	fiber_join(client_fiber1, NULL);
    	gettimeofday(&end, NULL);
		init_time += (in.tv_sec - start.tv_sec) * 1000000 + 
			(in.tv_usec - start.tv_usec);
		destroy_time += (end.tv_sec - in.tv_sec) * 1000000 + 
			(end.tv_usec - in.tv_usec);
	}
    
	printf("Creation time = %lf, dectruction time = %lf", 
			(double)init_time/IT_COUNT, (double)destroy_time/IT_COUNT);
    
	return 0;
}
