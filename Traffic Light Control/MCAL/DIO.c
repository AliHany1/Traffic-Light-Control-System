#include "bitwise_operation.h"
#include "tm4c123gh6pm.h"
#include "DIO.h"
#include "STD_types.h"


/*******************************************************************************
 *                              Functions Definations                          *
 *******************************************************************************/


void GPIO_SetupPinDirection(uint8 PORT, uint8 PIN_NO, GPIO_PinDirectionType Direction)
{
  if((PORT<=PORTF)&&(PIN_NO<=PIN7))
  {
          switch(PORT)
          {
          case PORTA:
            { 
              SYSCTL_PRGPIO_R |= 0x00000001;
              while((SYSCTL_PRGPIO_R&0x00000001) == 0){};
              GPIO_PORTA_LOCK_R = 0x4C4F434B;
              Set_Bit(GPIO_PORTA_CR_R,PIN_NO);
              if(Direction == PIN_INPUT)
                {
                    Clear_Bit(GPIO_PORTA_DIR_R,PIN_NO);
                    Set_Bit(GPIO_PORTA_PUR_R,PIN_NO);
                }
              else if(Direction == PIN_OUTPUT)
                {
                    Set_Bit(GPIO_PORTA_DIR_R,PIN_NO);
                }
                    Set_Bit(GPIO_PORTA_DEN_R,PIN_NO);
              break;
            }
          case PORTB:
            { 
              SYSCTL_PRGPIO_R |= 0x00000002;
              while((SYSCTL_PRGPIO_R&0x00000002) == 0){};
              GPIO_PORTB_LOCK_R = 0x4C4F434B;
              Set_Bit(GPIO_PORTB_CR_R,PIN_NO);
              if(Direction == PIN_INPUT)
                {
                    Clear_Bit(GPIO_PORTB_DIR_R,PIN_NO);
                    Set_Bit(GPIO_PORTB_PUR_R,PIN_NO);
                }
              else if(Direction == PIN_OUTPUT)
                {
                    Set_Bit(GPIO_PORTB_DIR_R,PIN_NO);
                }
                    Set_Bit(GPIO_PORTB_DEN_R,PIN_NO);
              break;
            }
          case PORTC:
            { 
              SYSCTL_PRGPIO_R |= 0x00000004;
              while((SYSCTL_PRGPIO_R&0x00000004) == 0){};
              GPIO_PORTC_LOCK_R = 0x4C4F434B;
              Set_Bit(GPIO_PORTC_CR_R,PIN_NO);
              if(Direction == PIN_INPUT)
                {
                    Clear_Bit(GPIO_PORTC_DIR_R,PIN_NO);
                    Set_Bit(GPIO_PORTC_PUR_R,PIN_NO);
                }
              else if(Direction == PIN_OUTPUT)
                {
                    Set_Bit(GPIO_PORTC_DIR_R,PIN_NO);
                }
                    Set_Bit(GPIO_PORTC_DEN_R,PIN_NO);
              break;
            }
          case PORTD:
            { 
              SYSCTL_PRGPIO_R |= 0x00000008;
              while((SYSCTL_PRGPIO_R&0x00000008) == 0){};
              GPIO_PORTD_LOCK_R = 0x4C4F434B;
              Set_Bit(GPIO_PORTD_CR_R,PIN_NO);
              if(Direction == PIN_INPUT)
                {
                    Clear_Bit(GPIO_PORTD_DIR_R,PIN_NO);
                    Set_Bit(GPIO_PORTD_PUR_R,PIN_NO);
                }
              else if(Direction == PIN_OUTPUT)
                {
                    Set_Bit(GPIO_PORTD_DIR_R,PIN_NO);
                }
                    Set_Bit(GPIO_PORTD_DEN_R,PIN_NO);
              break;
            }
          case PORTE:
            { 
              SYSCTL_PRGPIO_R |= 0x00000010;
              while((SYSCTL_PRGPIO_R&0x00000010) == 0){};
              GPIO_PORTE_LOCK_R = 0x4C4F434B;
              Set_Bit(GPIO_PORTE_CR_R,PIN_NO);
              if(Direction == PIN_INPUT)
                {
                    Clear_Bit(GPIO_PORTE_DIR_R,PIN_NO);
                    Set_Bit(GPIO_PORTE_PUR_R,PIN_NO);
                }
              else if(Direction == PIN_OUTPUT)
                {
                    Set_Bit(GPIO_PORTE_DIR_R,PIN_NO);
                }
                    Set_Bit(GPIO_PORTE_DEN_R,PIN_NO);
              break;
            }
          case PORTF:
            { 
               SYSCTL_PRGPIO_R |= SYSCTL_PRGPIO_R5;
              while((SYSCTL_PRGPIO_R&SYSCTL_PRGPIO_R5) == 0){};
              GPIO_PORTF_LOCK_R = 0x4C4F434B;
              Set_Bit(GPIO_PORTF_CR_R,PIN_NO);
              if(Direction==PIN_INPUT)
                {
                    Clear_Bit(GPIO_PORTF_DIR_R,PIN_NO);
                    Set_Bit(GPIO_PORTF_PUR_R,PIN_NO);
                }
              else if(Direction == PIN_OUTPUT)
                {
                    Set_Bit(GPIO_PORTF_DIR_R,PIN_NO);
                }
              if(PIN_NO == PIN0 || PIN_NO == PIN4)
              {
                    Set_Bit(GPIO_PORTF_PUR_R,PIN_NO);
              }
              
                    Set_Bit(GPIO_PORTF_DEN_R,PIN_NO);
              break;
            }
          }
  }
}
uint8 GPIO_ReadPin(uint8 Port, uint8 PIN_NO)
{
	uint8 ret_value = 0;
               switch(Port)
		{
		case PORTA : ret_value = Get_Bit(GPIO_PORTA_DATA_R, PIN_NO);break;
		case PORTB : ret_value = Get_Bit(GPIO_PORTB_DATA_R, PIN_NO);break;
		case PORTC : ret_value = Get_Bit(GPIO_PORTC_DATA_R, PIN_NO);break;
		case PORTD : ret_value = Get_Bit(GPIO_PORTD_DATA_R, PIN_NO);break;
		case PORTE : ret_value = Get_Bit(GPIO_PORTE_DATA_R, PIN_NO);break;
		case PORTF : ret_value = Get_Bit(GPIO_PORTF_DATA_R, PIN_NO);break;
                 }
        return ret_value;
}
void GPIO_WritePin(uint8 Port, uint8 PIN_NO, uint8 Value)
{
        if(Value == LOW)
        {
                switch(Port)
                {
                case PORTA: Clear_Bit(GPIO_PORTA_DATA_R, PIN_NO); break;
                case PORTB: Clear_Bit(GPIO_PORTB_DATA_R, PIN_NO); break;
                case PORTC: Clear_Bit(GPIO_PORTC_DATA_R, PIN_NO); break;
                case PORTD: Clear_Bit(GPIO_PORTD_DATA_R, PIN_NO); break;
                case PORTE: Clear_Bit(GPIO_PORTE_DATA_R, PIN_NO); break;
                case PORTF: Clear_Bit(GPIO_PORTF_DATA_R, PIN_NO); break;
                }
        }
        else if(Value == HIGH)
        {
                switch(Port)
                {
                case PORTA: Set_Bit(GPIO_PORTA_DATA_R, PIN_NO); break;
                case PORTB: Set_Bit(GPIO_PORTB_DATA_R, PIN_NO); break;
                case PORTC: Set_Bit(GPIO_PORTC_DATA_R, PIN_NO); break;
                case PORTD: Set_Bit(GPIO_PORTD_DATA_R, PIN_NO); break;
                case PORTE: Set_Bit(GPIO_PORTE_DATA_R, PIN_NO); break;
                case PORTF: Set_Bit(GPIO_PORTF_DATA_R, PIN_NO); break;
                }
        }
        else if(Value == TOGGEL)
        {
                switch(Port)
                {
                case PORTA: Toggle_Bit(GPIO_PORTA_DATA_R, PIN_NO); break;
                case PORTB: Toggle_Bit(GPIO_PORTB_DATA_R, PIN_NO); break;
                case PORTC: Toggle_Bit(GPIO_PORTC_DATA_R, PIN_NO); break;
                case PORTD: Toggle_Bit(GPIO_PORTD_DATA_R, PIN_NO); break;
                case PORTE: Toggle_Bit(GPIO_PORTE_DATA_R, PIN_NO); break;
                case PORTF: Toggle_Bit(GPIO_PORTF_DATA_R, PIN_NO); break;
                }
        }
}

void GPIO_SetupPortDirection(uint8 PORT, GPIO_PortDirectionType Direction)
{
  if((PORT<=PORTF))
  {
          switch(PORT)
          {
          case PORTA:
            { 
              SYSCTL_PRGPIO_R |= 0x00000001;
              while((SYSCTL_PRGPIO_R&0x00000001) == 0){};
              GPIO_PORTA_LOCK_R = 0x4C4F434B;
              GPIO_PORTA_CR_R = 0xFF;
              if(Direction == PORT_INPUT)
                {
                    GPIO_PORTA_DIR_R = 0x00;
                    GPIO_PORTA_PUR_R = 0xFF;
                }
              else if(Direction == PORT_OUTPUT)
                {
                    GPIO_PORTA_DIR_R = 0xFF;
                }
                    GPIO_PORTA_DEN_R = 0xFF;
              break;
            }
          case PORTB:
            { 
              SYSCTL_PRGPIO_R |= 0x00000002;
              while((SYSCTL_PRGPIO_R&0x00000002) == 0){};
              GPIO_PORTB_LOCK_R = 0x4C4F434B;
              GPIO_PORTB_CR_R = 0xFF;
              if(Direction == PORT_INPUT)
                {
                    GPIO_PORTB_DIR_R = 0x00;
                    GPIO_PORTB_PUR_R = 0xFF;
                }
              else if(Direction == PORT_OUTPUT)
                {
                    GPIO_PORTB_DIR_R = 0xFF;
                }
                    GPIO_PORTB_DEN_R = 0xFF;
              break;
            }
          case PORTC:
            { 
              SYSCTL_PRGPIO_R |= 0x00000004;
              while((SYSCTL_PRGPIO_R&0x00000004) == 0){};
              GPIO_PORTC_LOCK_R = 0x4C4F434B;
              GPIO_PORTC_CR_R = 0xFF;
              if(Direction == PORT_INPUT)
                {
                    GPIO_PORTC_DIR_R = 0x00;
                    GPIO_PORTC_PUR_R = 0xFF;
                }
              else if(Direction == PORT_OUTPUT)
                {
                    GPIO_PORTC_DIR_R = 0xFF;
                }
                    GPIO_PORTC_DEN_R = 0xFF;
              break;
            }
          case PORTD:
            { 
              SYSCTL_PRGPIO_R |= 0x00000008;
              while((SYSCTL_PRGPIO_R&0x00000008) == 0){};
              GPIO_PORTD_LOCK_R = 0x4C4F434B;
              GPIO_PORTD_CR_R = 0xFF;
              if(Direction == PORT_INPUT)
                {
                    GPIO_PORTD_DIR_R = 0x00;
                    GPIO_PORTD_PUR_R = 0xFF;
                }
              else if(Direction == PORT_OUTPUT)
                {
                     GPIO_PORTD_DIR_R = 0xFF;
                }
                    GPIO_PORTD_DEN_R = 0xFF;
              break;
            }
          case PORTE:
            { 
              SYSCTL_PRGPIO_R |= 0x00000010;
              while((SYSCTL_PRGPIO_R&0x00000010) == 0){};
              GPIO_PORTE_LOCK_R = 0x4C4F434B;
              GPIO_PORTE_CR_R = 0xFF;
              if(Direction == PORT_INPUT)
                {
                    GPIO_PORTE_DIR_R = 0x00;
                    GPIO_PORTE_PUR_R = 0xFF;
                }
              else if(Direction == PORT_OUTPUT)
                {
                   GPIO_PORTE_DIR_R = 0xFF;
                }
                    GPIO_PORTE_DEN_R = 0xFF;
              break;
            }
          case PORTF:
            { 
               SYSCTL_PRGPIO_R |= SYSCTL_PRGPIO_R5;
              while((SYSCTL_PRGPIO_R&SYSCTL_PRGPIO_R5) == 0){};
              GPIO_PORTF_LOCK_R = 0x4C4F434B;
              GPIO_PORTF_CR_R = 0xFF;
              if(Direction == PORT_INPUT)
                {
                    GPIO_PORTF_DIR_R = 0x00;
                    GPIO_PORTF_PUR_R = 0xFF;
                }
              else if(Direction == PORT_OUTPUT)
                {
                     GPIO_PORTF_DIR_R = 0xFF;
                }
                    GPIO_PORTF_DEN_R = 0xFF;
              break;
            }
          }
  }
}

uint8 GPIO_ReadPort(uint8 Port)
{
      uint8 ret_value;
      switch(Port)
      {
      case PORTA: ret_value = GPIO_PORTA_DATA_R; break;
      case PORTB: ret_value = GPIO_PORTB_DATA_R; break;
      case PORTC: ret_value = GPIO_PORTC_DATA_R; break;
      case PORTD: ret_value = GPIO_PORTD_DATA_R; break;
      case PORTE: ret_value = GPIO_PORTE_DATA_R; break;
      case PORTF: ret_value = GPIO_PORTF_DATA_R; break;
      }
      return ret_value;
}
void GPIO_WritePort(uint8 Port, uint8 Value)
{
      switch(Port)
      {
      case PORTA: GPIO_PORTA_DATA_R = Value; break;
      case PORTB: GPIO_PORTB_DATA_R = Value; break;
      case PORTC: GPIO_PORTC_DATA_R = Value; break;
      case PORTD: GPIO_PORTD_DATA_R = Value; break;
      case PORTE: GPIO_PORTE_DATA_R = Value; break;
      case PORTF: GPIO_PORTF_DATA_R = Value; break;
      }
}