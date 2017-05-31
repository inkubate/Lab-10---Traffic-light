
#include "stdint.h"
#include "delay.h"


void delay(unsigned int time) { //delay takes an unsigned int as number of milliseconds
  unsigned int count;
  STCTRL |= CLK_SRC;                    //systick clock source set to system clock
  STCTRL &= (~STINTEN);                 // disable interrupt generation 
  
  STRELOAD = MSEC1_80MHZ;               // set reload to 1 millisecond at 80MHz
  
  for(count = time; count > 0; count--) { // loop for duration of systick reload register
    STCURRENT = 0x1;            // write anything to clear current register
    STCTRL |= STENABLE;         // start the systick count by enabling it
    while((STCTRL & COUNT_FLAG) == 0) {}        // wait until the conuter has couted down and flag bit is 1
  }
  
  
}
