#define F_CPU 12e6
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h> 

#define MOODLAMP_DELAY 100


uint16_t pwmtable[32]  PROGMEM = {0, 1, 2, 2, 2, 3, 3, 4, 5, 6, 7, 8, 10, 11,
                                    13, 16, 19, 23, 27, 32, 38, 45, 54, 64, 76,
                                    91, 108, 128, 152, 181, 215, 255};




volatile uint16_t pwm_counter,pwm_r,pwm_g,pwm_b;

ISR (TIMER0_OVF_vect)
{
	

	if (pwm_counter == 0) {	
	PORTC = 0x00;
		pwm_counter = 255;
	}

	if (pwm_counter <= pgm_read_word(pwmtable+pwm_r)) {
		PORTC |= (1 << PC3);
	}
	if (pwm_counter <= pgm_read_word(pwmtable+pwm_g)) {
		PORTC |= (1 << PC2);
	}
	if (pwm_counter <= pgm_read_word(pwmtable+pwm_b)) {
		PORTC |= (1 << PC1);
	}

	pwm_counter--;
}



int main(void)
{
   
    DDRC = PC1|PC2|PC3;

    pwm_r = 0;pwm_g = 0;pwm_b = 0;pwm_counter = 0;    
	//Interrupt for the Clock enable  
    	TIMSK0 |= (1 << TOIE0);
	//Setzen des Prescaler auf 1 
	TCCR0B |= (1<<CS00 | 0<<CS01 | 0<<CS02);
//	OCR0A = 1;
	sei();


    for (;;) {                           /* loop forever */
	while (pwm_r < 32) {	
	  pwm_r++;
	  _delay_ms(MOODLAMP_DELAY);
	}
	while (pwm_g > 0) {	
	  pwm_g--;
	_delay_ms(MOODLAMP_DELAY);
	}
        while (pwm_b < 32) {	
	  pwm_b++;
	_delay_ms(MOODLAMP_DELAY);
	}
	while (pwm_r > 0) {	
	  pwm_r--;
	  _delay_ms(MOODLAMP_DELAY);
	}
        while (pwm_g < 32) {	
	  pwm_g++;
	_delay_ms(MOODLAMP_DELAY);
	}
	while (pwm_b > 0) {	
	  pwm_b--;
	_delay_ms(MOODLAMP_DELAY);
	}
    }
}


