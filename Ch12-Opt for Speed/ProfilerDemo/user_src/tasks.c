#include <ior5f100le.h>
#include <stdint.h>
#include "rtc_sched.h"
#include "lcd.h"

void Task1(void) {
	static char led_state=0;
	
	P5_bit.no5 = led_state;
	led_state ^= 1;
}

void Task2(void) {
	static char led_state=0;
	
	P6_bit.no2 = led_state;
	led_state ^= 1;
}

// Task3 runs at 1 Hz, updates elapsed time on LCD
void Task3(void) {
	static char led_state=0;
	static unsigned char m=0, s=0;
	
	P6_bit.no3 = led_state;
	led_state ^= 1;
	
	s++;
	if (s>59) {
		m++;
		s = 0;
	}
	
	LCDPrintf(0,0, "%02u:%02u", m, s);
}
