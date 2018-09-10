#include <stdint.h>
#include "r_cg_timer.h"
#include "Region.h"
#include "profile.h"
#include "lcd.h"

unsigned long profile_ticks=0;
unsigned char profiling_enabled = 0;


// extern volatile unsigned RegionCount[];
// extern const unsigned NumProfileRegions;

void Init_Profiling(void) {
	unsigned i;
	
	// Clear region counts
  for (i=0; i<NumProfileRegions; i++) {
	  RegionCount[i]=0;
  }
	
	R_TAU0_Channel0_Start();
}

void Disable_Profiling(void) {
  profiling_enabled = 0;
}

void Enable_Profiling(void) {
  profiling_enabled = 1;
}

void Clear_Lower_Screen(void) {
	unsigned line = 2;
	
	while (line <9) {
		LCDPrintf(line, 0, "                 ");
		line++;
	}
}

void Print_Results(void) {
	unsigned n, line=1;
	
	LCDPrintf(1,line, "%ld total ticks", profile_ticks);
	Clear_Lower_Screen();			
	
	line++; // don't overwrite total number of ticks
	for (n=0; n<NumProfileRegions; n++) {
//		LCDPrintf((n%8)+1, 0, "%d %d", n, RegionCount[n]);
		if (RegionCount[n] > 0) {
			LCDPrintf(line, 0, "                 ");
			LCDPrintf(line++, 0, "%d %s", RegionCount[n], RegionTable[n].Name);
		}
		if (line == 9) {
			line = 2;
			Clear_Lower_Screen();			
		}
	}
}