#include "ff_sched.h"

//dummy task for process_list creation.
int dummy_task()
{
    return 0;
}

//Creates an empty list of processes.
//process_list: reference to existing process list.
//size: the size of the process list.
void create_process_list(struct process* process_list, int size)
{
    //initialize each process as a dummy process
    for(int i = 0; i < size; i++)
    {
        process_list[i].period = 0;
        process_list[i].last_ran = 0;
        process_list[i].work = (void*)dummy_task;
        process_list[i].priority = 0;
    }
}

//Adds a process to the scheduler.
//sched: the scheduler to add a process to.
//proc: the process to add to the scheduler.
int add_process(struct scheduler* sched, struct process proc)
{
    //if there is room in the scheduler, add the process.
    if(sched->num_processes < sched->max_processes)
    {
        sched->process_list[sched->num_processes] = proc;
        sched->num_processes += 1;
        return 1;
    }

    return 0;
}

//Starts the scheduler.
//sched: the scheduler struct to use for this schedule.
//timer_func: user defined timer function. Used in calculating tick rate.
void schedule(struct scheduler *sched, unsigned long (*timer_func)())
{
    //record the time the scheduler started. Will be used to track passage of ticks.
    unsigned long start_time = timer_func();

    while (1)
    {
        //determine if enough time has passed to update tick counter.
        unsigned long now = timer_func();
        unsigned long delta = now - start_time;
        char tick_update = delta/sched->tick_period_divisor;

        //if enough time has passed, update tick counter.
        if(tick_update)
        {
            sched->num_ticks += 1;
            start_time = timer_func();
        }

        int next_proc = -1;
        struct process np = {-1, 0, 0, (void*)dummy_task};

        //iterate over scheduled processes
        for(int i = 0; i < sched->num_processes; i++)
        {
            struct process ip = sched->process_list[i];

            unsigned long tick_delta = sched->num_ticks - ip.last_ran;

            //if a process is past period
            if(tick_delta >= ip.period)
            {
                //and the process is higher priority than the next process
                if(np.priority < ip.priority)
                {
                    //make this process the next process.
                    next_proc = i;
                    np = ip;
                }
            }
        }

        //a process is ready to run
        if(next_proc > -1)
        {
            //update process's last run time, set it as active, and execute.
            sched->process_list[next_proc].last_ran = sched->num_ticks;
            sched->active_process = next_proc;
            sched->process_list[next_proc].work();
        }

    }
}
