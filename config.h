/**
* RaumZeitLabor Moodlight 
* http://raumzeitlabor.de/wiki/Moodlamp
*
* config.h - Moodlamp configuration
**/

#ifndef _CONFIG_H
#define _CONFIG_H

// USART Debug Interface
//#define USART_DEBUG  1

#ifdef USART_DEBUG
#define BAUD 115200                    //definiert die Bautrate für den USART.
#define USART0_RX_BUFFER_SIZE 32      //definiert die größe des Empfangsbuffers. Die Buffergröße kann 2, 4, 8, 16, 32, 64, 128 oder 256 Byte groß sein.
#define USART0_TX_BUFFER_SIZE 32      //definiert die größe des Sendebuffers. Die Buffergröße kann 2, 4, 8, 16, 32, 64, 128 oder 256 Byte groß sein.
#endif


#define F_MCP F_CPU
#endif // ifndef CONFIG_H
