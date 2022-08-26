#include "stdint.h"
#include "stdbool.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
#include "driverlib/timer.h"

#include "Timers.h"
#include "tm4c123gh6pm.h"
#include "STD_types.h"

//Initialize Timer0
/*void Timer0_Init()
{
  //Enable the Timer0 peripheral
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

  //Wait for the Timer1 module to be stable   
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)){}
  
  //Disable the timer
  TimerDisable(TIMER0_BASE, TIMER_A); 
  
  //Configure the timer as down counting periodic timer
  TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC); 
  
  //Configure the clk source for the timer 
  TimerClockSourceSet(TIMER0_BASE,TIMER_CLOCK_SYSTEM);

  //Stop the timer when debugging
  TimerControlStall(TIMER0_BASE, TIMER_A, TRUE); 

  //Allow Interrupts
  TIMER0_IMR_R |= 0x01;
  NVIC_EN0_R= 1<<19;

  //Enable the timer
  TimerEnable(TIMER0_BASE, TIMER_A);
}


void Timer0Delay_1000MS()
{
    //Disable the timer
    TimerDisable(TIMER0_BASE, TIMER_A);

    //Load the value which is equivalent to 1 sec
    TimerLoadSet(TIMER0_BASE, TIMER_A, 16000000-1);

    //Clear interrupt that arised when the timer timed out
    TIMER0_ICR_R = 0x01;
    
    //enable the timer
    TimerEnable(TIMER0_BASE, TIMER_A);

    //wait for the timer to time out
    while((TIMER0_RIS_R & 0x01) == 0);
}
*/

void Timer1_Init()
{
  //Enable the Timer1 peripheral
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);   

  //Wait for the Timer1 module to be stable
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER1)){}
  
  //Disable the timer
  TimerDisable(TIMER1_BASE, TIMER_BOTH); 

  //Configure the timer as down counting periodic timer
  TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC); 

  //Stop the timer when debugging
  TimerControlStall(TIMER1_BASE, TIMER_BOTH, TRUE);    

  //Enable the timer
  TimerEnable(TIMER1_BASE, TIMER_BOTH);
}

void Timer1Delay_1000MS()
{
    //Disbale the timer
    TimerDisable(TIMER1_BASE, TIMER_BOTH);
    
    //Load the value which is equivalent to 1 sec
    TimerLoadSet(TIMER1_BASE, TIMER_BOTH, 16000000-1);
    
    //Clear interrupt that arised when the timer timed out
    TIMER1_ICR_R = 0x01;
    
    //Enable the timer
    TimerEnable(TIMER1_BASE, TIMER_BOTH);

   //Wait for the timer to time out
    while((TIMER1_RIS_R & 0x01) == 0);
}