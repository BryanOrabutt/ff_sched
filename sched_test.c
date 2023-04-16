#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "ff_sched.h"

unsigned long millis()
{
    static clock_t start_time = 0;
    if (start_time == 0)
    {
        start_time = clock();
    }
    return (unsigned long)(clock() - start_time) * 1000 / CLOCKS_PER_SEC;
}

void task_a()
{
    printf("Process A is running\n");
}

void task_b()
{
    printf("Process B is running\n");
}

void task_c()
{
    printf("Process C is running\n");
}

void task_d()
{
    printf("Process D is running\n");
}

void task_e()
{
    printf("Process E is running\n");
}

void task_f()
{
    printf("Process F is running\n");
}

int main()
{
    struct process pa = {0, 20, 0, task_a};
    struct process pb = {1, 40, 0, task_b};
    struct process pc = {2, 100, 0, task_c};
    struct process pd = {3, 20, 0, task_d};
    struct process pe = {4, 40, 0, task_e};
    struct process pf = {5, 100, 0, task_f};

    printf("Created six processes...\n");

    struct process proc_list[6];
    create_process_list(proc_list, 6);

    printf("Created process list...\n");

    struct scheduler sched = {proc_list, 0, 6, 0, 50};

    printf("Created scheduler...\n");

    if(!add_process(&sched, pa))
    {
        printf("Could not add Process A!\n");
        return -1;
    }

    printf("Added process A to scheduler...\n");

    if(!add_process(&sched, pb))
    {
        printf("Could not add Process B!\n");
        return -1;
    }

    printf("Added process B to scheduler...\n");

    if(!add_process(&sched, pc))
    {
        printf("Could not add Process C!\n");
        return -1;
    }

    printf("Added process C to scheduler...\n");

    if(!add_process(&sched, pd))
    {
        printf("Could not add Process D!\n");
        return -1;
    }

    printf("Added process D to scheduler...\n");

    if(!add_process(&sched, pe))
    {
        printf("Could not add Process E!\n");
        return -1;
    }

    printf("Added process E to scheduler...\n");

    if(!add_process(&sched, pf))
    {
        printf("Could not add Process F!\n");
        return -1;
    }

    printf("Added process F to scheduler...\n");

    schedule(&sched, millis);

    return 0;
}
