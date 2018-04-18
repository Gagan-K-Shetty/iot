#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvSYS.h"
#include "Driver\DrvGPIO.h"

int main (void)
{
    int32_t a;
    char text[16];
    UNLOCKREG();                // unlock register for programming
    DrvSYS_Open(48000000);// set System Clock to run at 48MHz 
                          // 12MHz crystal input, PLL output 48MHz
    LOCKREG();                    // lock register from programming

          // Initialize LEDs (four on-board LEDs below LCD panel)    
    Initial_panel();
    clr_all_panel();
    while (1) // forever loop to keep flashing four LEDs one at a time
    {
        DrvGPIO_SetPortBits(E_GPA,0);
        a=DrvGPIO_GetPortBits(E_GPA);     
        sprintf(text,"port number %d",a);        // delay
        print_lcd(0,text);
    }
}

