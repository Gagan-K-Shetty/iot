#include <stdio.h>                                                                                                             
#include "NUC1xx.h"
#include "LCD_Driver.h"
#define BAUDRATE 9600

void InitADC(void)
{
    /* Step 1. GPIO initial */ 
    GPIOA->OFFD|=0x00400000;     //Disable digital input path
    SYS->GPAMFP.ADC7_SS21_AD6=1;         //Set ADC function 
                
    /* Step 2. Enable and Select ADC clock source, and then enable ADC module */          
    SYSCLK->CLKSEL1.ADC_S = 2;    //Select 22Mhz for ADC
    SYSCLK->CLKDIV.ADC_N = 1;    //ADC clock source = 22Mhz/2 =11Mhz;
    SYSCLK->APBCLK.ADC_EN = 1;    //Enable clock source
    ADC->ADCR.ADEN = 1;            //Enable ADC module

    /* Step 3. Select Operation mode */
    ADC->ADCR.DIFFEN = 0;         //single end input
    ADC->ADCR.ADMD   = 0;         //single mode
        
    /* Step 4. Select ADC channel */
    ADC->ADCHER.CHEN = 0x40;
    
    /* Step 5. Enable ADC interrupt */
    ADC->ADSR.ADF =1;             //clear the A/D interrupt flags for safe 
    ADC->ADCR.ADIE = 1;
//    NVIC_EnableIRQ(ADC_IRQn);
    
    /* Step 6. Enable WDT module */
    ADC->ADCR.ADST=1;
}
//--------------------------------------------
void InitPWM(void)
{
     /* Step 1. GPIO initial */ 
    SYS->GPAMFP.PWM0_AD13=1;
                
    /* Step 2. Enable and Select PWM clock source*/        
    SYSCLK->APBCLK.PWM01_EN = 1;//Enable PWM clock
    SYSCLK->CLKSEL1.PWM01_S = 3;//Select 22.1184Mhz for PWM clock source

    PWMA->PPR.CP01=1;            //Prescaler 0~255, Setting 0 to stop output clock
    PWMA->CSR.CSR0=0;            // PWM clock = clock source/(Prescaler + 1)/divider
                         
    /* Step 3. Select PWM Operation mode */
    //PWM0
    PWMA->PCR.CH0MOD=1;            //0:One-shot mode, 1:Auto-load mode
                                //CNR and CMR will be auto-cleared after setting CH0MOD form 0 to 1.
    PWMA->CNR0=0xFFFF;
    PWMA->CMR0=0xFFFF;

    PWMA->PCR.CH0INV=0;            //Inverter->0:off, 1:on
    PWMA->PCR.CH0EN=1;            //PWM function->0:Disable, 1:Enable
     PWMA->POE.PWM0=1;            //Output to pin->0:Diasble, 1:Enable
}

void Delay(int count)
{
    while(count--)
    {
//        __NOP;
     }
}

/*----------------------------------------------------------------------------
  MAIN function
  ----------------------------------------------------------------------------*/
int32_t main (void)
{
    //Enable 12Mhz and set HCLK->12Mhz
    char adc_value[15]="ADC Value:";    
    UNLOCKREG();
    //SYSCLK->PWRCON.XTL12M_EN = 1;
    //SYSCLK->CLKSEL0.HCLK_S = 0;
    DrvSYS_Open(48000000);
    LOCKREG();

    InitPWM();
    InitADC();

    Initial_panel();  //call initial pannel function
    clr_all_panel();
                                 
    /* Synch field transmission & Request Identifier Field transmission*/
                     
    while(1)
    {
        while(ADC->ADSR.ADF==0);
        ADC->ADSR.ADF=1;
        PWMA->CMR0=ADC->ADDR[6].RSLT<<4;
        //Show_Word(0,11,' ');
        //Show_Word(0,12,' ');
        //Show_Word(0,13,' ');
        sprintf(adc_value+10,"%d",ADC->ADDR[7].RSLT);
        print_lcd(0, adc_value);
        Delay(20000);
        ADC->ADCR.ADST=1;
    }
}

