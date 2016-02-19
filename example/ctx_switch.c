#include "fiber_manager.h"
#include "fiber.h"

void* fiber_function(void* param)
{
    int i;
    int id = *((int *) param);
    for (i=0;i<10;i++) {
        printf("From thread %d: i = %d\n", id, i);
        fiber_yield();
    }
    return NULL;
}

int main()
{
    printf("Starting experiment...\n");
    int a = 1, b = 2;
    fiber_manager_init(1);

    fiber_t* client_fiber1 = fiber_create(10240, &fiber_function, (void*)&a);
    
    fiber_t *client_fiber2 = fiber_create(10240, &fiber_function, (void*)&b);
    
    fiber_join(client_fiber1, NULL);
    fiber_join(client_fiber2, NULL);
    return 0;
}
