/**
*  RaumZeitLabor Moodlight 
*
*  RC5 Remote Receiver 
*  Based on code by Peter Dannegger (danni@specs.de)
**/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "rc5.h"
#include "control.h"


uint8_t rc5_bit;				// bit value
uint8_t rc5_time;				// count bit time
uint16_t rc5_tmp;				// shift bits in

void rc5_init(void) {
  RC5_DDR &= ~(1 << RC5_PIN);		//set pin as input
  TCCR0B = 1<<CS02;			//divide by 256
  TIMSK0 = 1<<TOIE0;			//enable timer interrupt
  rc5_data.newCmd = 0;
}

void rc5_handler(void) {		// see http://www.sprut.de/electronic/ir/rc5.htm
  if (rc5_data.newCmd) {		// new RC5-Command recieved
    rc5_data.newCmd = 0;		// reset flag

    if (rc5_data.addr == 0) { 	// Addr: TV0
      if (rc5_data.cmd > 0x40 && rc5_data.cmd < 0x4A) {
		control_cmd = CTRL_CMD_SET_COLOR;
		control_param = (rc5_data.cmd - 0x40);
      } else { control_cmd = CTRL_CMD_SET_COLOR;
      switch (rc5_data.cmd) {	//
	case 0x40:
		control_cmd = CTRL_CMD_RUN_FADING;
		break;
	case 0x2B:
//		control_cmd = CTRL_CMD_SET_COLOR;
		control_param = CTRL_COLOR_RED;
		break;
	case 0x2C:
//		control_cmd = CTRL_CMD_SET_COLOR;
		control_param = CTRL_COLOR_GREEN;
		break;
	case 0x2D:
//		control_cmd = CTRL_CMD_SET_COLOR;
		control_param = CTRL_COLOR_YELLOW;
		break;
	case 0x2E:
//		control_cmd = CTRL_CMD_SET_COLOR;
		control_param = CTRL_COLOR_BLUE;
		break;
	case 0x2F:
//		control_cmd = CTRL_CMD_SET_COLOR;
		control_param = CTRL_COLOR_WHITE;
		break;
        case 0x10:	// Vol+
		control_cmd = CTRL_CMD_SPEED_UP;
		break;
        case 0x11:	// Vol-
		control_cmd = CTRL_CMD_SPEED_DOWN;
		break;
	default:
		control_cmd = CTRL_CMD_NONE;  
    }}
//control_setColor(CTRL_COLOR_BLUE);
    }
  }       
}

ISR (SIG_OVERFLOW0)
{
  uint16_t tmp = rc5_tmp;			// for faster access

  TCNT0 = -2;					// 2 * 256 = 512 cycle

  if( ++rc5_time > RC5_PULSE_MAX ){			// count pulse time
    if( !(tmp & 0x4000) && tmp & 0x2000 ) {	// only if 14 bits received
      rc5_data.addr = (tmp >> 6 & 0x1F);
      rc5_data.cmd = ((tmp & 0x3F) | (tmp >> 6 & 0x40));
//      rc5_data.cmd = (tmp & 0x3F);
      rc5_data.newCmd = 1;
//      control_setColor(CTRL_COLOR_GREEN);
      tmp = 0;
    }
  }

  if( (rc5_bit ^ RC5_PORT) & 1<<RC5_PIN ){		// change detect
    rc5_bit = ~rc5_bit;				// 0x00 -> 0xFF -> 0x00

    if( rc5_time < RC5_PULSE_MIN )			// to short
      tmp = 0;

    if( !tmp || rc5_time > RC5_PULSE_1_2 ){		// start or long pulse time
      if( !(tmp & 0x4000) )			// not to many bits
        tmp <<= 1;				// shift
      if( !(rc5_bit & 1<<RC5_PIN) )		// inverted bit
        tmp |= 1;				// insert new bit
      rc5_time = 0;				// count next pulse time
    }
  }

  rc5_tmp = tmp;
}
