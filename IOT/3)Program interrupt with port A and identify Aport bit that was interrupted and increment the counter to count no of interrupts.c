#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvUART.h"
#include "Driver\DrvGPIO.h"
#include "Driver\DrvSYS.h"
#include "LCD_Driver.h"

volatile uint32_t irqA_counter = 0;


void GPIOAB_INT_CallBack(uint32_t GPA_IntStatus, uint32_t GPB_IntStatus)
{
     /*int32_t a;
     char text[16];
     DrvGPIO_SetPortBits(E_GPA,0);
     a=DrvGPIO_GetPortBits(E_GPA);
     if ((GPA_IntStatus>>15) & 0x01) irqA_counter++;
     sprintf(text,"port number %d",a);
     print_lcd(3,"GPA interrupt !! ");
     print_lcd(2,text);*/
     irqA_counter++;
}



int32_t main()
{
    int32_t a;
    char TEXT[16];
     char text[16];
    UNLOCKREG();
    /*SYSCLK->PWRCON.XTL12M_EN=1;           //commented
    DrvSYS_Delay(5000);                    // Waiting for 12M Xtal stalble
    SYSCLK->CLKSEL0.HCLK_S=0;*/
    DrvSYS_Open(48000000);
    LOCKREG();

  // setup GPA15 & GPD15 to get interrupt input
    
    DrvGPIO_Open(E_GPA,15,E_IO_INPUT);
    DrvGPIO_EnableInt(E_GPA, 15, E_IO_RISING, E_MODE_EDGE);
    DrvGPIO_SetDebounceTime(5, 1);
    DrvGPIO_EnableDebounce(E_GPA, 15);
    
    DrvGPIO_SetIntCallback(GPIOAB_INT_CallBack,NULL);

    Initial_panel();
    clr_all_panel();
                    
    print_lcd(0,"Smpl_GPIO_Intr");
    
    while(1)
    {
          
         
          DrvGPIO_SetPortBits(E_GPA,0);
          a=DrvGPIO_GetPortBits(E_GPA);
         
          sprintf(text,"%d",a);
          print_lcd(3,"GPA interrupt !! ");
          print_lcd(2,text);
          sprintf(TEXT,"IRQ_A: %d",irqA_counter);
          print_lcd(1, TEXT);
        
    }
}
//connect gpa15 to ground and then to vcc. Repeat every time
