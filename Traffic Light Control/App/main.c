#include "DioInit.h"
#include "DIO.h"
#include "STD_types.h"
#include "bitwise_operation.h"
#include "Timers.h"
#include "tm4c123gh6pm.h"
#include "SysTick_Timer.h"

#include "stdint.h"
#include "stdbool.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"


#define Enable_Exceptions()    __asm("CPSIE I")

#define Disable_Exceptions()   __asm("CPSID I") 

#define Wait_For_Interrupt()   __asm("WFI")     

uint8 flag = 0;

void Pedestrian_NS_Actions();
void Pedestrian_EW_Actions();

void SysTick_Handler()
{
  flag++;
}

void PORTF_Handler()
{
   //Clear Interrupts
   GPIO_PORTF_ICR_R |= (1<<0); 
   GPIO_PORTF_ICR_R |= (1<<4);
   
   //if a pedestrian pressed NS pedestrian traffic light button and another one pressed EW pedestrain traffic light button
   if((GPIO_ReadPin(PORTF,PIN0)== LOW) && (GPIO_ReadPin(PORTF,PIN4) == LOW))
   {
     //if NS traffic light green and EW traffic light red 
       if((GPIO_ReadPin(PORTE,PIN3) == HIGH) && (GPIO_ReadPin(PORTA,PIN4) == HIGH))
       {
         //Actions taken when pedestrian presses NS pedestrian light button
         Pedestrian_NS_Actions();
       }
        //if EW traffic light green and NS traffic light red 
       else if((GPIO_ReadPin(PORTE,PIN1) == HIGH) && (GPIO_ReadPin(PORTA,PIN3) == HIGH))
       {
        //actions taken when pedestrian presses EW pedestrian light button
        Pedestrian_EW_Actions();
       }
   }
   
   // if pedestrian presses NS pedestrian traffic light button and NS car-traffic light is GREEN
   else if((GPIO_ReadPin(PORTF,PIN4) == LOW) && (GPIO_ReadPin(PORTE,PIN3) == HIGH))
    {
      //actions taken when pedestrian presses NS pedestrian light button
      Pedestrian_NS_Actions();
    }   
   // if pedestrian presses EW pedestrian traffic light button and EW car-traffic light is GREEN
   else if((GPIO_ReadPin(PORTF,PIN0)== LOW) && (GPIO_ReadPin(PORTA,PIN3) == HIGH))
    {
      //actions taken when pedestrian presses EW pedestrian light button
      Pedestrian_EW_Actions();
    }
     
}

void main()
{
  PortA_Init();
  
  PortE_Init();
  
  PortF_Init();
  
  SysTick_Disable();
  
  SysTickPeriodSet(1000);
  
  SysTick_Enable();
  
  Timer1_Init();
  
  Enable_Exceptions();  
  
  
  while (1)
  {
   //At first, the NS traffic light is green and the EW traffic light is RED
  
    if(flag <= 5)
    {
   //Turn off the NS car-traffic lights
    GPIO_WritePin(PORTE,PIN1,LOW);
    GPIO_WritePin(PORTE,PIN2,LOW);
    GPIO_WritePin(PORTE,PIN3,LOW);
    
    //Turn EW car-traffic light RED
    GPIO_WritePin(PORTA,PIN4,HIGH); // Red
    
    //Turn NS car-traffic light GREEN
    GPIO_WritePin(PORTE,PIN3,HIGH); // GREEN for 5-SEC
    
    //Turn off the GREEN NS pedestrian light
    GPIO_WritePin(PORTE,PIN5,LOW);
    
    //Turn NS pedestrian traffic light RED
    GPIO_WritePin(PORTE,PIN4,HIGH);
    
    //Turn off the RED EW pedestrian light
     GPIO_WritePin(PORTF,PIN1,LOW);
     
    //Turn EW pedestrian traffic light GREEN
    GPIO_WritePin(PORTF,PIN3,HIGH);
    }   
 
   else if (flag <= 7 && flag > 5)
    {
   //Turn off the NS car-traffic lights
    GPIO_WritePin(PORTE,PIN1,LOW);
    GPIO_WritePin(PORTE,PIN2,LOW);
    GPIO_WritePin(PORTE,PIN3,LOW);
    
    //Turn NS car-traffic light YELLOW
    GPIO_WritePin(PORTE,PIN2,HIGH); //Yellow 2-SEC
    }

   else if(flag <= 8 && flag > 7)
    {
   //Turn off the NS car-traffic lights
    GPIO_WritePin(PORTE,PIN1,LOW);
    GPIO_WritePin(PORTE,PIN2,LOW);
    GPIO_WritePin(PORTE,PIN3,LOW);
    
    //Turn NS car-traffic light RED
    GPIO_WritePin(PORTE,PIN1,HIGH); //RED for 1-SEC
    
    //Turn off the RED NS pedestrian light
    GPIO_WritePin(PORTE,PIN4,LOW);
    
    //Turn NS pedestrian traffic light GREEN
     GPIO_WritePin(PORTE,PIN5,HIGH);
     
    }
 
   else if(flag <= 13 && flag > 8)
    {
   //Turn off the EW car-traffic lights
    GPIO_WritePin(PORTA,PIN4,LOW);
    GPIO_WritePin(PORTA,PIN2,LOW);
    GPIO_WritePin(PORTA,PIN3,LOW);
    
    //Turn EW car-traffic light GREEN
    GPIO_WritePin(PORTA,PIN3,HIGH);
    
    //Turn off the GREEN EW pedestrian light
    GPIO_WritePin(PORTF,PIN3,LOW);
    
    //Turn EW pedestrian traffic light RED
    GPIO_WritePin(PORTF,PIN1,HIGH);

    }
 
   else if(flag <=15 && flag >13)
    {
    //Turn off the EW car-traffic lights
    GPIO_WritePin(PORTA,PIN4,LOW);
    GPIO_WritePin(PORTA,PIN2,LOW);
    GPIO_WritePin(PORTA,PIN3,LOW);
    
    //Turn EW car-traffic light YELLOW
    GPIO_WritePin(PORTA,PIN2,HIGH);
    
    }
   
    else if(flag <= 16 && flag > 15)
    {
     //Turn off the EW car-traffic lights
     GPIO_WritePin(PORTA,PIN4,LOW);
     GPIO_WritePin(PORTA,PIN2,LOW);
     GPIO_WritePin(PORTA,PIN3,LOW);
     
     //Turn EW car-traffic light RED
     GPIO_WritePin(PORTA,PIN4,HIGH);
    
     //Turn off the RED EW pedestrian light
      GPIO_WritePin(PORTF,PIN1,LOW);
      
      //Turn EW pedestrian traffic light GREEN
      GPIO_WritePin(PORTF,PIN3,HIGH);
   
    }
    
    else if (flag == 17)
    {flag = 0;}    //Start a new cycle for each
 
  }
}

void Pedestrian_NS_Actions()
{
  //Save the last states of both car-traffic lights (the NS and the EW)
    uint32 lEDState1NS = GPIO_ReadPin(PORTE,PIN1);
    uint32 lEDState2NS = GPIO_ReadPin(PORTE,PIN2);
    uint32 lEDState3NS = GPIO_ReadPin(PORTE,PIN3);
    uint32 lEDState4EW = GPIO_ReadPin(PORTA,PIN4);
    uint32 lEDState5EW = GPIO_ReadPin(PORTA,PIN2);
    uint32 lEDState6EW = GPIO_ReadPin(PORTA,PIN3);
    
    //Turn off the NS car-traffic lights
    GPIO_WritePin(PORTE,PIN1,LOW);
    GPIO_WritePin(PORTE,PIN2,LOW);
    GPIO_WritePin(PORTE,PIN3,LOW);
    
    //Turn NS car-traffic light RED
    GPIO_WritePin(PORTE,PIN1,HIGH);
    
    //Turn off the EW car-traffic lights
    GPIO_WritePin(PORTA,PIN4,LOW);
    GPIO_WritePin(PORTA,PIN2,LOW);
    GPIO_WritePin(PORTA,PIN3,LOW);
    
    //Turn EW car-traffic light RED
    GPIO_WritePin(PORTA,PIN4,HIGH);
    
    //Turn off the RED NS pedestrian light
    GPIO_WritePin(PORTE,PIN4,LOW);
    
    //Turn NS pedestrian traffic light GREEN
     GPIO_WritePin(PORTE,PIN5,HIGH);
     
     //Turn off the GREEN EW pedestrian light
     GPIO_WritePin(PORTF,PIN3,LOW);
     
      //Turn EW pedestrian traffic light RED
      GPIO_WritePin(PORTF,PIN1,HIGH);
      
      // Wait 2 SECs
     Timer1Delay_1000MS();
     Timer1Delay_1000MS();
    
    //Turn off the GREEN NS pedestrian light
    GPIO_WritePin(PORTE,PIN5,LOW);
    
    //Turn NS pedestrian traffic light RED
     GPIO_WritePin(PORTE,PIN4,HIGH);
     
     //Turn off the RED EW pedestrian light
     GPIO_WritePin(PORTF,PIN1,LOW);
     
     //Turn EW pedestrian traffic light GREEN
      GPIO_WritePin(PORTF,PIN3,HIGH);
      
      //Start from previous states
      GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1,lEDState1NS);
      GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2,lEDState2NS);
      GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3,lEDState3NS);
    
      GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,lEDState4EW);
      GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_2,lEDState5EW);
      GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,lEDState6EW);
              
}

void Pedestrian_EW_Actions()
{
   //Save the last states of both car-traffic lights (the NS and the EW)
    uint32 lEDState1NS = GPIO_ReadPin(PORTE,PIN1);
    uint32 lEDState2NS = GPIO_ReadPin(PORTE,PIN2);
    uint32 lEDState3NS = GPIO_ReadPin(PORTE,PIN3);
    uint32 lEDState4EW = GPIO_ReadPin(PORTA,PIN4);
    uint32 lEDState5EW = GPIO_ReadPin(PORTA,PIN2);
    uint32 lEDState6EW = GPIO_ReadPin(PORTA,PIN3);
    
     //Turn off the EW car-traffic lights
    GPIO_WritePin(PORTA,PIN4,LOW);
    GPIO_WritePin(PORTA,PIN2,LOW);
    GPIO_WritePin(PORTA,PIN3,LOW);
    
    //Turn EW car-traffic light RED
    GPIO_WritePin(PORTA,PIN4,HIGH);
    
     //Turn off the NS car-traffic lights
    GPIO_WritePin(PORTE,PIN1,LOW);
    GPIO_WritePin(PORTE,PIN2,LOW);
    GPIO_WritePin(PORTE,PIN3,LOW);
    
    //Turn NS car-traffic light GREEN
    GPIO_WritePin(PORTE,PIN3,HIGH);
    
    //Turn off the RED EW pedestrian light
    GPIO_WritePin(PORTF,PIN1,LOW);
     
     //Turn EW pedestrian traffic light GREEN
     GPIO_WritePin(PORTF,PIN3,HIGH);
      
     //Turn off the GREEN NS pedestrian light
     GPIO_WritePin(PORTE,PIN5,LOW);
      
      //Turn NS pedestrian traffic light RED
     GPIO_WritePin(PORTE,PIN4,HIGH);
     
      // Wait 2 SECs
     Timer1Delay_1000MS();
     Timer1Delay_1000MS();
     
      //Turn off the GREEN EW pedestrian light
     GPIO_WritePin(PORTF,PIN3,LOW);
     
      //Turn EW pedestrian traffic light RED
     GPIO_WritePin(PORTF,PIN1,HIGH);
     
     //Turn off the RED NS pedestrian light
     GPIO_WritePin(PORTE,PIN4,LOW);
     
     //Turn NS pedestrian traffic light GREEN
     GPIO_WritePin(PORTE,PIN5,HIGH);
     
      //Start from previous states
      GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1,lEDState1NS);
      GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2,lEDState2NS);
      GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3,lEDState3NS);
    
      GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,lEDState4EW);
      GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_2,lEDState5EW);
      GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,lEDState6EW);
      
}

