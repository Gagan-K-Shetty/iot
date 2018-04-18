#include <stdio.h>                                                                                                             
#include "NUC1xx.h"
#include "Driver\DrvSYS.h"
#include "Seven_Segment.h"
#include "DrvADC.h"
#include "LCD_Driver.h"

     
int32_t main (void)
{   
    uint16_t value;  
    char TEXT[16];               
    
    UNLOCKREG();
    //SYSCLK->PWRCON.XTL12M_EN = 1;     //Enable 12Mhz and set HCLK->12Mhz
    //SYSCLK->CLKSEL0.HCLK_S = 0;
    DrvSYS_Open(48000000);
    LOCKREG();
    Initial_panel();  // initialize LCD pannel
      clr_all_panel();  // clear LCD panel 
      print_lcd(0,"variable reistor");

    DrvADC_Open(ADC_SINGLE_END,ADC_SINGLE_OP , 0x40,INTERNAL_HCLK , 1);     //make 0x40 -> 0x80 for channel 7
    while(1)
    {
	    DrvADC_StartConvert();   // start A/D conversion
	    while(DrvADC_IsConversionDone()==FALSE);
	    value = ADC->ADDR[6].RSLT & 0xFFF;    //make value 6->7 for channel 7
	    
	    sprintf(TEXT,"Value: %d",value); // convert ADC0 value into text
	    print_lcd(1, TEXT); // output TEXT to LCD

    }
}

