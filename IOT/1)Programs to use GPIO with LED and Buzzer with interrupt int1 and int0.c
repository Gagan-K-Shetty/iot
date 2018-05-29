#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvGPIO.h"
#include "Driver\DrvUART.h"
#include "Driver\DrvSYS.h"

// External Interrupt Handler (INT button to trigger GPB15)
void EINT1Callback(void) 
{
  DrvGPIO_ClrBit(E_GPB,11); // GPB11 = 0 to turn on Buzzer
	DrvSYS_Delay(100000);	    // Delay 
	DrvGPIO_SetBit(E_GPB,11); // GPB11 = 1 to turn off Buzzer	
	DrvSYS_Delay(100000);	    // Delay 	
}

void EINT0Callback(void) 
{
  DrvGPIO_ClrBit(E_GPA,12); // GPB11 = 0 to turn on Buzzer
	DrvSYS_Delay(100000);	    // Delay 
	DrvGPIO_SetBit(E_GPA,12); // GPB11 = 1 to turn off Buzzer	
	DrvSYS_Delay(100000);	    // Delay 	
}

int main (void)
{
	/*
	UNLOCKREG();
	DrvSYS_SetOscCtrl(E_SYS_XTL12M, 1); // external 12MHz Crystal
	//DrvSYS_Delay(5000);                 // delay for stable clock
	DrvSYS_SelectHCLKSource(0);         // clock source = 12MHz Crystal
	LOCKREG();
	*/
	UNLOCKREG();
	/*DrvSYS_SetOscCtrl(E_SYS_XTL12M, 1); // external 12MHz Crystal
	//DrvSYS_Delay(5000);                 // delay for stable clock
	DrvSYS_SelectHCLKSource(0);         // clock source = 12MHz Crystal
	*/
	DrvSYS_Open(48000000);
LOCKREG();

	DrvGPIO_Open(E_GPB, 11, E_IO_OUTPUT); // initial GPIO pin GPB11 for controlling Buzzer
  DrvGPIO_Open(E_GPA, 12, E_IO_OUTPUT);
//0 External Interrupt 
  DrvGPIO_Open(E_GPB, 5, E_IO_INPUT);                             // configure external interrupt pin GPB15
  DrvGPIO_EnableEINT1(E_IO_BOTH_EDGE, E_MODE_EDGE, EINT1Callback); // configure external interrupt
  DrvGPIO_Open(E_GPB, 14, E_IO_INPUT); 
	DrvGPIO_EnableEINT0(E_IO_BOTH_EDGE, E_MODE_EDGE, EINT0Callback);
  while(1)
	{
	//	  DrvGPIO_Open(E_GPB, 15, E_IO_INPUT);                             // configure external interrupt pin GPB15
  //DrvGPIO_EnableEINT0(E_IO_BOTH_EDGE, E_MODE_EDGE, EINT1Callback); // configure external interrupt
  }
}

// interrupt button -> buzzer
