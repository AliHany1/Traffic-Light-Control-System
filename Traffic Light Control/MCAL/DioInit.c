#include "DioInit.h"
#include "DIO.h"
#include "STD_types.h"
#include "bitwise_operation.h"
#include "tm4c123gh6pm.h"

#include "stdint.h"
#include "stdbool.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/


#define GPIO_PORTF_PRIORITY_MASK      0xFF1FFFFF
#define GPIO_PORTF_PRIORITY_BITS_POS  21
#define GPIO_PORTF_INTERRUPT_PRIORITY 2


/*******************************************************************************
 *                              Functions Definations                          *
 *******************************************************************************/

void PortF_Init()
{
  // Configure PIN0 & PIN4 as Input Pins (Switches)
  GPIO_SetupPinDirection(PORTF, PIN0, PIN_INPUT);
  GPIO_PORTF_IS_R    &= ~(1<<0);      /* PF0 detect edges */
  GPIO_PORTF_IBE_R   &= ~(1<<0);      /* PF0 will detect a certain edge */
  GPIO_PORTF_IEV_R   &= ~(1<<0);      /* PF0 will detect a falling edge */
  GPIO_PORTF_ICR_R   |= (1<<0);       /* Clear Trigger flag for PF0 (Interupt Flag) */
  GPIO_PORTF_IM_R    |= (1<<0);       /* Enable Interrupt on PF0 pin */
  
  GPIO_SetupPinDirection(PORTF, PIN4, PIN_INPUT);
  GPIO_PORTF_IS_R    &= ~(1<<4);      /* PF4 detect edges */
  GPIO_PORTF_IBE_R   &= ~(1<<4);      /* PF4 will detect a certain edge */
  GPIO_PORTF_IEV_R   &= ~(1<<4);      /* PF4 will detect a falling edge */
  GPIO_PORTF_ICR_R   |= (1<<4);       /* Clear Trigger flag for PF4 (Interupt Flag) */
  GPIO_PORTF_IM_R    |= (1<<4);       /* Enable Interrupt on PF4 pin */
  
  // Configure PIN1,PIN2 & PIN3 as Output Pins (LEDs)
  GPIO_SetupPinDirection(PORTF, PIN1, PIN_OUTPUT);
  GPIO_SetupPinDirection(PORTF, PIN2, PIN_OUTPUT);
  GPIO_SetupPinDirection(PORTF, PIN3, PIN_OUTPUT);
  
  //Interrupt Enable
  NVIC_PRI7_R = (NVIC_PRI7_R & GPIO_PORTF_PRIORITY_MASK) | (GPIO_PORTF_INTERRUPT_PRIORITY << GPIO_PORTF_PRIORITY_BITS_POS); 
  NVIC_EN0_R         |= 0x40000000;   /* Enable NVIC Interrupt for GPIO PORTF by set bit number 30 in EN0 Register */
  
}

void PortE_Init()
{
  // Configure PIN1,PIN2, PIN3, PIN4 & PIN5 as Output Pins (LEDs)
  GPIO_SetupPinDirection(PORTE, PIN1, PIN_OUTPUT);
  GPIO_SetupPinDirection(PORTE, PIN2, PIN_OUTPUT);
  GPIO_SetupPinDirection(PORTE, PIN3, PIN_OUTPUT);
  GPIO_SetupPinDirection(PORTE, PIN4, PIN_OUTPUT);
  GPIO_SetupPinDirection(PORTE, PIN5, PIN_OUTPUT);

}
void PortA_Init()
{
  // Configure PIN1 & PIN2 Output Pins (LEDs)
  GPIO_SetupPinDirection(PORTA, PIN4, PIN_OUTPUT);
  GPIO_SetupPinDirection(PORTA, PIN2, PIN_OUTPUT);
  GPIO_SetupPinDirection(PORTA, PIN3, PIN_OUTPUT);
}
