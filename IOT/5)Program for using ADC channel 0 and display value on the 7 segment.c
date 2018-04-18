#include <stdio.h>                                                                                                             
#include "NUC1xx.h"
#include "Driver\DrvSYS.h"
#include "Seven_Segment.h"
#include "DrvADC.h"
#include "LCD_Driver.h"
void seg_display(int16_t value)
{
  int8_t digit;
    digit = value / 1000;
    close_seven_segment();
    show_seven_segment(3,digit);
    DrvSYS_Delay(5000);
            
    value = value - digit * 1000;
    digit = value / 100;
    close_seven_segment();
    show_seven_segment(2,digit);
    DrvSYS_Delay(5000);

    value = value - digit * 100;
    digit = value / 10;
    close_seven_segment();
    show_seven_segment(1,digit);
    DrvSYS_Delay(5000);

    value = value - digit * 10;
    digit = value;
    close_seven_segment();
    show_seven_segment(0,digit);
    DrvSYS_Delay(5000);
}
     
int32_t main (void)
{  
    uint16_t value;  
    char TEXT[16];               
    
    UNLOCKREG();
    //SYSCLK->PWRCON.XTL12M_EN = 1;     //Enable 12Mhz and set HCLK->12Mhz
   // SYSCLK->CLKSEL0.HCLK_S = 0;
    DrvSYS_Open(48000000);
    LOCKREG();
    Initial_panel();  // initialize LCD pannel
    clr_all_panel();  // clear LCD panel 
    print_lcd(0,"variable reistor");

       
    DrvADC_Open(ADC_SINGLE_END,ADC_SINGLE_OP , 0x01,INTERNAL_HCLK , 1);     // changed from DrvADC_Open(ADC_SINGLE_END,ADC_SINGLE_OP , 0x80,INTERNAL_HCLK , 1);  
    while(1)
    {
    DrvADC_StartConvert();   // start A/D conversion
    while(DrvADC_IsConversionDone()==FALSE);
    value = ADC->ADDR[0].RSLT & 0xFFF;    // changed from value = ADC->ADDR[7].RSLT & 0xFFF;    
    
    sprintf(TEXT,"Value: %d",value); // convert ADC0 value into text
    print_lcd(1, TEXT); // output TEXT to LCD
    seg_display(value);
    }
}

