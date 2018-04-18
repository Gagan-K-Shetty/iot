// Sampl_GPIO_StepMotor 
// 5V Step Motor 28BYJ-48, driver IC = ULN2003A
//
// Driver board connections:
// ULN2003A    NUC140
// INA      to GPA3
// INB      to GPA2
// INC      to GPA1
// IND      to GPA0
//
#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvGPIO.h"
#include "Driver\DrvSYS.h"

// Definitions for Step Motor turning degree
/*#define d360 512
#define d180 512/2
#define d90  512/4
#define d45  512/8
*/
#define d2 51

unsigned char CW[8] ={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08}; //Clockwise Sequence
unsigned char CCW[8]={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09}; //Counter-Clockwise Sequence

void CW_MOTOR(uint16_t deg)
{
 int i=0,j=0;

for(j=0;j<(deg);j++)
{
    for(i=0;i<8;i++)
    {
    GPIOA->DOUT=CW[i];
    DrvSYS_Delay(20000);//delay 2000us = 2ms
    }
 }
}

void CCW_MOTOR(uint16_t deg)
{
 int i=0,j=0;

for(j=0;j<(deg);j++)
{
    for(i=0;i<8;i++)
    {
    GPIOA->DOUT=CCW[i];
    DrvSYS_Delay(20000);//delay 2000us = 2ms
    }
 }
}

int main (void)
{      
    CW_MOTOR(d2/2); // Clockwise         for 180 degree
    CCW_MOTOR(d2/4);// Counter-Clockwise for 90 degree
}

