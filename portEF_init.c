#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "delay.h"


void portEF_init() {
  
  volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000032;      // 1) B E F clock
	delay = SYSCTL_RCGC2_R;            // delay to allow clock to stabilize     
	
	
GPIO_PORTB_AFSEL_R &= ~0x3F; // alt funct disabled on all IP
GPIO_PORTB_PUR_R &= ~0x3F; // pull up disabled        
GPIO_PORTB_DEN_R |= 0x3F; // digital enable all pins
GPIO_PORTB_DIR_R |= 0x3F; // set PF0 to PF5 as an output
GPIO_PORTB_AMSEL_R &= ~0x3F; //analog mode disabled
GPIO_PORTB_PCTL_R = 0x00000000; // all 0 for GPIO 	
	
GPIO_PORTE_AFSEL_R &= ~0x07; // alt funct disabled on all IP
GPIO_PORTE_PUR_R &= ~0x07; // pull up disabled        
GPIO_PORTE_DEN_R |= 0x07; // digital enable all pins
GPIO_PORTE_DIR_R &= ~0x07; // set PF0 to PF1 as an input
GPIO_PORTE_AMSEL_R &= ~0x07; //analog mode disabled
GPIO_PORTE_PCTL_R = 0x00000000; // all 0 for GPIO 

GPIO_PORTF_AFSEL_R &= ~0x0A; // alt funct disabled on all IP
GPIO_PORTF_PUR_R &= ~0x0A; // pull up disabled        
GPIO_PORTF_DEN_R |= 0x0A; // digital enable all pins
GPIO_PORTF_DIR_R |= 0x0A; // set PF0 to PF5 as an output
GPIO_PORTF_AMSEL_R &= ~0x0A; //analog mode disabled
GPIO_PORTF_PCTL_R = 0x00000000; // all 0 for GPIO 

}
