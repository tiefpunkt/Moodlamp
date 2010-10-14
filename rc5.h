/**
*  RC5 Remote Receiver 
*  Based on code by Peter Dannegger (danni@specs.de)
**/


#define	RC5_DDR		DDRB
#define	RC5_PORT	PINB
#define	RC5_PIN		PB0			// IR input low active


#define RC5_TIME 	1.778e-3		// 1.778msec
#define RC5_PULSE_MIN	(uint8_t)(F_CPU / 512 * RC5_TIME * 0.4 + 0.5)
#define RC5_PULSE_1_2	(uint8_t)(F_CPU / 512 * RC5_TIME * 0.8 + 0.5)
#define RC5_PULSE_MAX	(uint8_t)(F_CPU / 512 * RC5_TIME * 1.2 + 0.5)

volatile uint16_t	rc5_data;				// store result
void rc5_init(void);
