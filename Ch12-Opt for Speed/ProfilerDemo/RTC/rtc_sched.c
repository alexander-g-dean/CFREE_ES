#include "ior5f100le.h"
#include "r_cg_userdefine.h"

#include "rtc_sched.h"
#include "intrinsics.h"

typedef struct {
  int period;
  int delay;
  int ready;
  int enabled;
  void (* task)(void);
} task_t;

typedef unsigned char byte;


/* =================== Global variables ======================= */
task_t GBL_task_list[MAX_TASKS];
int    GBL_run_scheduler=0;
unsigned num_ticks=0;
unsigned ticks_into_sec=0;


/* ==================== Function prototypes ==================== */
void tick_timer_intr(void);

/*****************************************************************************
Name:            void Init_RTC_Scheduler(void)
Parameters:                     
Returns:        
Description:     Intializes board support firmware for scheduler. 

*****************************************************************************/
void Init_RTC_Scheduler(void)
{
  num_ticks = 0;
  Init_Task_Timers();
#if RTC_MONITOR_STANDBY
	RTC_STANDBY_OUTPUT_MODE = DIR_OUT; // Set port bit to output
	RTC_STANDBY_OUTPUT = 1; // Not currently sleeping
#endif	
	
#if RTC_MONITOR_ACTIVITY
	RTC_ACTIVE_OUTPUT_MODE = DIR_OUT; // set port bit to output 
	RTC_ACTIVE_OUTPUT = 1; // No task is currently active
#endif
}

/*****************************************************************************
Name:           tick_timer_intr
Parameters:     none
Returns:        none
Description:    ISR for periodic timer tick.  Decrements the timer value for all
valid and enabled tasks. If timer value reaches 0, set run flag and reset timer 
value to initial value to allow periodic execution.
*****************************************************************************/
void tick_timer_intr(void)
{
  static char i;
#if RTC_MONITOR_ACTIVITY
						RTC_ACTIVE_OUTPUT = 0; // Indicate active
#endif // RTC_MONITOR_ACTIVITY	

  num_ticks++;
  for (i=0 ; i<MAX_TASKS ; i++) {		 /* If this is a scheduled task */
    if (GBL_task_list[i].task != NULL) {
     if (GBL_task_list[i].enabled == 1) {
       if (GBL_task_list[i].delay) { 
         if (--GBL_task_list[i].delay == 0){
           GBL_task_list[i].ready = 1;
           GBL_task_list[i].delay = GBL_task_list[i].period; 
          } 
        } 
      }
    }
  }

#if RTC_MONITOR_ACTIVITY
						RTC_ACTIVE_OUTPUT = 1; // Indicate inactive
#endif // RTC_MONITOR_ACTIVITY	
}

/*****************************************************************************
Name:   	Add_Task    
Parameters:     void (*task)(void), 
                int period (milliseconds), 
                int priority

Returns:        1 executed ok, 0 unable to load task.  priority already assigned. 
Description:    Adds task to Round Robin Scheduler. 

*****************************************************************************/
int	Add_Task(void (*task)(void), int period, int priority)
{
  /* Check for valid priority */
  if (priority >= MAX_TASKS || priority < 0)
    return 0;
  /* Check to see if we are overwriting an already scheduled task */
  if (GBL_task_list[priority].task != NULL)
    return 0;
  /* Schedule the task */
  	GBL_task_list[priority].task = task;
  	GBL_task_list[priority].ready  = 0;
	GBL_task_list[priority].delay = period;
	GBL_task_list[priority].enabled = 1;
  	GBL_task_list[priority].period = period;
    return 1;
}
/*****************************************************************************
Name:        Remove_Task   
Parameters:  void (* task)(void)  "task name"                   
Returns:     none   
Description: Removes task from Round Robin Scheduler.    
*****************************************************************************/
void Remove_Task(void (* task)(void))
{
  int i;

  for (i=0 ; i<MAX_TASKS ; i++) {
    if (GBL_task_list[i].task == task) {
      GBL_task_list[i].task = NULL;
      GBL_task_list[i].delay = 0;
      GBL_task_list[i].period = 0;
      GBL_task_list[i].enabled = 0;
      GBL_task_list[i].ready = 0;
      return;
    } }
}
/*****************************************************************************
Name:      Init_Task_Timers     
Parameters: none                    
Returns:    none    
Description: Initializes task information structure to null and zeroes.     
*****************************************************************************/
void Init_Task_Timers(void)
{
  int i;
  /* Initialize all tasks */
  for (i=0 ; i<MAX_TASKS ; i++) {
    GBL_task_list[i].period = 0;
    GBL_task_list[i].ready = 0;
    GBL_task_list[i].delay = 0;
    GBL_task_list[i].enabled = 0;
    GBL_task_list[i].task = NULL;
  }
}
/*****************************************************************************
Name:         Run_RTC_Scheduler  
Parameters:   none                  
Returns:      none  
Description:  Starts Round Robin Scheduler.  Should be call in Main program after
completing initialization.  Only enabled tasks will be scheduled and run. 
*****************************************************************************/
void Run_RTC_Scheduler(void)
{
  int i;
  GBL_run_scheduler = 1;
  /* Loop forever */
  while (1) {
    /* Check each task */
    for (i=0 ; i<MAX_TASKS ; i++) {
      
      /* If this is a scheduled task */
      if (GBL_task_list[i].task != NULL) { /* valid task */
				if (GBL_task_list[i].enabled == 1) { /* enabled */
				  if (GBL_task_list[i].ready == 1) {  /* ready to run */
#if RTC_MONITOR_ACTIVITY
//						RTC_ACTIVE_OUTPUT = 0; // Indicate task is active
#endif // RTC_MONITOR_ACTIVITY	

				    /* Run the task */
				    GBL_task_list[i].task();

#if RTC_MONITOR_ACTIVITY
//						RTC_ACTIVE_OUTPUT = 1; // Indicate task is inactive
#endif // RTC_MONITOR_ACTIVITY	

				    /* Reset the task ready flag */
				    GBL_task_list[i].ready = 0;
				    break;
	  			}
        } 
      } 
    }
		// reached end of loop, so start at top again
#if RTC_HALT_WHEN_IDLE
		RTC_STANDBY_OUTPUT = 0; // Sleeping
		__halt();
		RTC_STANDBY_OUTPUT = 1; // Not sleeping
#endif // RTC_HALT_WHEN_IDLE

#if RTC_STOP_WHEN_IDLE
		RTC_STANDBY_OUTPUT = 0; // Sleeping
		__stop();
		RTC_STANDBY_OUTPUT = 1; // Not sleeping
#endif // RTC_STOP_WHEN_IDLE
	
  }
}

/*****************************************************************************
Name:         Run_Task  
Parameters:   task_number                  
Returns:      none  
Description:  Set the run flag for the specified task. This will tell the 
 scheduler it is ready to run without further delay.
*****************************************************************************/
void Run_TaskN(int task_number)
{
  GBL_task_list[task_number].ready = 1;
  GBL_task_list[task_number].enabled = 1;
}

/*****************************************************************************
Name:         Reschedule_TaskN  
Parameters:   task number, new_timer_val                  
Returns:      none  
Description:  Modifies the period at which a task will run.
*****************************************************************************/
void Reschedule_TaskN(int n, int new_timer_val)
{
	GBL_task_list[n].period = new_timer_val;
  GBL_task_list[n].delay = new_timer_val;
}

/*****************************************************************************
Name:         Enable_TaskN
Parameters:   task_number                  
Returns:      none  
Description:  Set the "enabled" flag for the task, allowing it to be scheduled.
*****************************************************************************/
void Enable_TaskN(int n)
{
  GBL_task_list[n].enabled = 1;
}

/*****************************************************************************
Name:         Disable_TaskN
Parameters:   task_number                  
Returns:      none  
Description:  Clear the "enabled" flag for the task, keeping it from being 
scheduled.
*****************************************************************************/
void Disable_TaskN(int n)
{
  GBL_task_list[n].enabled = 0;
}

/*****************************************************************************
Name:         Reschedule_Task  
Parameters:   task pointer, new_timer_val                  
Returns:      none  
Description:  Modifies the period at which a task will run.
*****************************************************************************/
void Reschedule_Task(void (*task)(void), int new_timer_val)
{
  int i;
  for (i=0; i<MAX_TASKS; i++) {
    if (GBL_task_list[i].task == task) {
      GBL_task_list[i].period = new_timer_val;
      GBL_task_list[i].delay = new_timer_val;
      return;
    }
  }
}

/*****************************************************************************
Name:         Enable_Task
Parameters:   task_number                  
Returns:      none  
Description:  Set the "enabled" flag for the task, allowing it to be scheduled.
*****************************************************************************/
void Enable_Task(void (*task)(void))
{
  int i;
  for (i=0; i<MAX_TASKS; i++)
    if (GBL_task_list[i].task == task) {
      GBL_task_list[i].enabled = 1;
      return;
    }
}

/*****************************************************************************
Name:         Disable_Task
Parameters:   task_number                  
Returns:      none  
Description:  Clear the "enabled" flag for the task, keeping it from being 
scheduled.
*****************************************************************************/
void Disable_Task(void (*task)(void))
{
  int i;
  for (i=0; i<MAX_TASKS; i++)
    if (GBL_task_list[i].task == task) {
      GBL_task_list[i].enabled = 0;
      return;
    }
}