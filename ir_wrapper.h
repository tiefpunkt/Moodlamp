
/* 		RC Commands		*/

//	Functions on Remote Control
#define RC_BRIGHTER		5		
#define RC_DARKER		4
#define RC_OFF			6		
#define RC_ON			7		
#define RC_FLASH		15		
#define RC_STROBE		23	
#define RC_FADE			27
#define RC_SMOOTH		19

//	Colors on Remote Control
#define RC_RED			9		
#define RC_GREEN		8
#define RC_BLUE			10
#define RC_WHITE		11

#define RC_RED1			13
#define RC_RED2			21
#define RC_RED3			25
#define RC_RED4			17

#define RC_GREEN1		12
#define RC_GREEN2		20
#define RC_GREEN3		24
#define RC_GREEN4		16

#define RC_BLUE1		14
#define RC_BLUE2		22
#define RC_BLUE3		26
#define RC_BLUE4		18


void ir_init();
void ir_handler();
