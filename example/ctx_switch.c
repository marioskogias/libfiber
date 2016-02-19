#include <sys/time.h>

#include "fiber_manager.h"
#include "fiber.h"

#define IT_COUNT 10000000

void* fiber_function(void* param)
{
    int i;
    //int id = *((int *) param);
    for (i=0;i<IT_COUNT;i++) {
        //printf("From thread %d: i = %d\n", id, i);
        fiber_yield();
    }
    return NULL;
}

int main()
{
    int a = 1, b = 2;
    struct timeval start, end;
    long total_time;

    printf("Starting experiment...\n");
    fiber_manager_init(1);

    fiber_t* client_fiber1 = fiber_create(10240, &fiber_function, (void*)&a);
    
    fiber_t *client_fiber2 = fiber_create(10240, &fiber_function, (void*)&b);

    printf("Before join\n");    
    gettimeofday(&start, NULL);
    fiber_join(client_fiber1, NULL);
    fiber_join(client_fiber2, NULL);
    gettimeofday(&end, NULL);

    total_time = (end.tv_sec - start.tv_sec) * 1000000 + 
        (end.tv_usec - start.tv_usec);
    
    printf("Total time = %lu usec\t#ctx_switch = %d\tduration of ctx_switch = %f usec\n", 
            total_time, IT_COUNT, (double) total_time / IT_COUNT);
    return 0;
}
