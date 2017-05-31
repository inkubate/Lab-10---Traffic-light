// ***** 0. Documentation Section *****
// TableTrafficLight.c for Lab 10
// Runs on LM4F120/TM4C123
// Index implementation of a Moore finite state machine to operate a traffic light.  
// Daniel Valvano, Jonathan Valvano
// January 15, 2016

// east/west red light connected to PB5
// east/west yellow light connected to PB4
// east/west green light connected to PB3
// north/south facing red light connected to PB2
// north/south facing yellow light connected to PB1
// north/south facing green light connected to PB0
// pedestrian detector connected to PE2 (1=pedestrian present)
// north/south car detector connected to PE1 (1=car present)
// east/west car detector connected to PE0 (1=car present)
// "walk" light connected to PF3 (built-in green LED)
// "don't walk" light connected to PF1 (built-in red LED) 

// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
#include "tm4c123gh6pm.h"
#include "portEF_init.h"
#include "stdint.h"
#include "delay.h"

// ***** 2. Global Declarations Section *****

struct state {           // this is the structure
  uint16_t carlgts;      // 16 bits for the output of main lights
	uint8_t pedlgts;      // 8 bits for the output of ped lights
  uint16_t wait;         // wait time in the state
  uint8_t next[8];      // array for the eight possible next states
} ;                                                     
typedef const struct state sType;                // use the structure to create a new type called ‘sType’

#define GoWs 0           // give a number to the state go west. These are called in next struct and match the sensor inputs
#define WtWs 1           // give a number to the state wait west
#define GoSt 2           // give a number to the state go south
#define WtSt 3          // give a number to the state wait south
#define BthRd 4           // give a number to the state wait both
#define PedFl 5           // give a number to the state stop both
#define PedFla 6           // give a number to the state stop flash red
#define PedFlb 7          // give a number to the state stop flash


#define SthRED 0x04
#define SthYEL 0x02
#define SthGRN 0x01
#define WstRED 0x20
#define WstYEL 0x10
#define WstGRN 0x08

#define LIGHTS (*((volatile uint32_t *)0x400050FC)) // output bits on port B. These are atomic so only 6 bits affected
#define PEDLGTS (*((volatile uint32_t *)0x400250FC)) // output bits on port F. These are atomic so only 6 bits affected
#define IPREAD (GPIO_PORTE_DATA_R & 0x07)     // inputs on port E. Bit masked for bit 0 to 2.

// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

// ***** 3. Subroutines Section *****

int main(void){ 
  unsigned char cState = GoWs;          // initialise the current State to GoWs
  uint8_t input;                   // space to hold input state reading
	
	  sType FSM[8] = {        // create 8 instances of the new sType called ‘FSM' and pre define values
    {(WstGRN | SthRED), 0x02, 2000, {GoWs,	GoWs,	WtWs,	WtWs,	WtWs,	WtWs,	WtWs,	WtWs} }, 					//GoWS          
    {(WstYEL | SthRED), 0x02, 1000, {GoSt,	GoSt,	GoSt,	GoSt,	BthRd,	BthRd,	BthRd,	GoSt} },   //WtWs
		{(WstRED | SthGRN), 0x02, 2000, {GoSt,	WtSt,	GoSt,	WtSt,	WtSt,	WtSt,	WtSt,	WtSt} },  			  //GoSt
		{(WstRED | SthYEL), 0x02, 1000, {GoWs,	GoWs,	GoWs,	GoWs,	BthRd,	BthRd,	BthRd,	BthRd} },   //WtSt
		{(WstRED | SthRED), 0x08, 2000, {PedFl,	PedFl,	PedFl,	PedFl,	PedFl,	PedFl,	PedFl,	PedFl} },  //BthRd
		{(WstRED | SthRED), 0x02, 1000, {PedFla,	PedFla,	PedFla,	PedFla,	PedFla,	PedFla,	PedFla,	PedFla} }, //PedFl
		{(WstRED | SthRED), 0x00, 1000, {PedFlb,	PedFlb,	PedFlb,	PedFlb,	PedFlb,	PedFlb,	PedFlb,	PedFlb} }, //PedFla
		{(WstRED | SthRED), 0x02, 1000, {GoWs,	GoWs,	GoSt,	GoWs,	GoWs,	GoWs,	GoSt,	GoWs} } 								//PedFlb

  }  ;    

	portEF_init();                   // initialise ports NEEDS WRITING
	
	TExaS_Init(SW_PIN_PE210, LED_PIN_PB543210,ScopeOff); // activate grader and set system clock to 80 MHz
  EnableInterrupts();
	
  while(1){
         
		LIGHTS = FSM[cState].carlgts;      // state is from 0 to 8. Set output to val in current state
		PEDLGTS = FSM[cState].pedlgts;      // state is from 0 to 8. Set output to val in current state
    delay(FSM[cState].wait);                     // wait the delay period define in current state
    input = IPREAD;                                  // check PE0 to PE2 
    cState = FSM[cState].next[input];        // cState changed to the next defined in the struct.

  }
}

