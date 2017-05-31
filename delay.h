#ifndef __delay_h__
#define __delay_h__

    #define STCTRL        (*((volatile uint32_t *) 0xE000E010))         // systick control register
    #define STRELOAD      (*((volatile uint32_t *) 0xE000E014))         // systick reload register (24 bit)
    #define STCURRENT     (*((volatile uint32_t *) 0xE000E018))         // systic current (24 bit)
    #define COUNT_FLAG 0x10000          // mask for count flag for STCTRL
    #define STENABLE 0x1                // enable systick bit for STCTRL
    #define STINTEN 0x2                 // interrupt enable for STCTRL
    #define CLK_SRC 0x4                 // clock source for STCTRL
    #define MSEC1_80MHZ 79999;          // systicks for 1ms at 80MHz
    #define MSEC1_40MHZ 39999;          // systicks for 1ms at 40MHz
    #define MSEC1_4MHZ 3999;          // systicks for 1ms at 4MHz

void delay(unsigned int time);          // prototype fucnt for delay

#endif // __delay_h__
