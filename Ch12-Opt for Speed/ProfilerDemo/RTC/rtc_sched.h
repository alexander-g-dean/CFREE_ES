#ifndef RTC_SCHED_H
#define RTC_SCHED_H

#ifndef NULL
#define NULL (0)
#endif

#define MAX_TASKS 			10 // Set maximum number of tasks to be used in system 
                           // Will affect performance. 

#define RTC_TICK_FREQ  (1024) // Tick frequency in Hz, assuming using interval 
													//	timer with 32.768 kHz clock and compare value of 31
	
#define RTC_FREQ_TO_TICKS(f)  (RTC_TICK_FREQ/f) // Macro used to set task period

// power saving options
#define RTC_STOP_WHEN_IDLE (0)
#define RTC_HALT_WHEN_IDLE (0)

// debugging options
#define RTC_MONITOR_ACTIVITY (1)
#define RTC_ACTIVE_OUTPUT 			GLED6
#define RTC_ACTIVE_OUTPUT_MODE 	GLED6_M

#define RTC_MONITOR_STANDBY (1)
#define RTC_STANDBY_OUTPUT 			GLED5
#define RTC_STANDBY_OUTPUT_MODE 	GLED5_M


/**** Run to completion scheduler API ************************************************/
extern void tick_timer_intr(void);
extern void Init_RTC_Scheduler(void);
extern void Init_Task_Timers(void);
extern int  Add_Task(void (*task)(void), int period, int priority);
extern void Remove_Task(void (*task)(void));
extern void Run_RTC_Scheduler(void);
extern void Run_TaskN(int task_number);
extern void Reschedule_TaskN(int task_number, int new_period);
extern void Enable_TaskN(int task_number);
extern void Disable_TaskN(int task_number);

extern void Reschedule_Task(void (*task)(void), int new_period);
extern void Enable_Task(void (*task)(void));
extern void Disable_Task(void (*task)(void));

#endif // #ifndef RTC_SCHED_H
