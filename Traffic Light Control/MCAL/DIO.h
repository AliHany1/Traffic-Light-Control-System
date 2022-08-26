#ifndef DIO_H_
#define DIO_H_

#include "STD_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PORTA 1
#define PORTB 2
#define PORTC 3
#define PORTD 4
#define PORTE 5
#define PORTF 6

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

typedef enum
{
	PORT_INPUT,PORT_OUTPUT = 0xFF
}GPIO_PortDirectionType;



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


void GPIO_SetupPinDirection(uint8 PORT, uint8 PIN_NO, GPIO_PinDirectionType Direction);
uint8 GPIO_ReadPin(uint8 PORT, uint8 PIN_NO);
void GPIO_WritePin(uint8 PORT, uint8 PIN_NO, uint8 Value);
void GPIO_SetupPortDirection(uint8 PORT, GPIO_PortDirectionType Direction);
uint8 GPIO_ReadPort(uint8 PORT);
void GPIO_WritePort(uint8 PORT, uint8 Value);


#endif /* DIO_H_ */