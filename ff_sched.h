#ifndef _FF_SCHED_H
#define _FF_SCHED_H

//Processes struct
//priority: used to decide which process to schedule when periods coincide.
//period: process will execute after this many ticks have passed.
//last_ran: which scheduler tick the process last ran.
//work: function to run when this process is scheduled.
struct process
{
  int priority;
  long int period; //how often (in ticks) the process should run
  long int last_ran; //tick at which this process last ran
  void (*work)(); //function pointer to the process work function
};

//Scheduler struct
//process_list: list of processes to schedule.
//num_processes: how many processes have been scheduled.
//max_processes: the maximum number of processes to allow in the scheduler.
//tick_period_divisor: divides the timer function to produce the tick rate.
//active_process: the process that is actively running/last scheduled process.
struct scheduler
{
    struct process* process_list;
    int num_processes;
    int max_processes;
    unsigned long num_ticks;
    int tick_period_divisor;
    int active_process;
};

//Creates an empty list of processes.
//process_list: reference to existing process list.
//size: the size of the process list.
void create_process_list(struct process* process_list, int size);

//Starts the scheduler.
//sched: the scheduler struct to use for this schedule.
//timer_func: user defined timer function. Used in calculating tick rate.
void schedule(struct scheduler *sched, unsigned long (*timer_func)());

//Adds a process to the scheduler.
//sched: the scheduler to add a process to.
//proc: the process to add to the scheduler.
int add_process(struct scheduler* sched, struct process proc);

#endif
