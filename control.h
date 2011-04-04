/**
* RaumZeitLabor Moodlight 
* http://raumzeitlabor.de/wiki/Moodlamp
*
* control.h - Interface between lamp and control data sources (ir etc.)
**/

#define CTRL_CMD_NONE 				0x00
#define CTRL_CMD_PAUSE_TOGGLE 		0x10
#define CTRL_CMD_PAUSE_ON 			0x11
#define CTRL_CMD_PAUSE_OFF 			0x12
#define CTRL_CMD_BRIGHTNESS_UP 		0x20
#define CTRL_CMD_BRIGHTNESS_DOWN 	0x21
#define CTRL_CMD_SPEED_UP			0x30
#define CTRL_CMD_SPEED_DOWN			0x31
#define CTRL_CMD_SET_COLOR			0x40
#define CTRL_CMD_RUN_FADING			0x41
#define CTRL_CMD_STANDBY			0x50
#define CTRL_CMD_POWERON			0x51

#define CTRL_COLOR_RED			0x01
#define CTRL_COLOR_GREEN		0x02
#define CTRL_COLOR_BLUE			0x03
#define CTRL_COLOR_YELLOW		0x04
#define CTRL_COLOR_VIOLET		0x05
#define CTRL_COLOR_WHITE		0x06
#define CTRL_COLOR_ORANGE		0x07
#define CTRL_COLOR_LIGHTGREEN	0x08
#define CTRL_COLOR_LIGHTBLUE	0x09

// Hue-calculated values for the china remote
#define CTRL_COLOR_HUE_0        0x60	// Red
#define CTRL_COLOR_HUE_24       0x61	// Orange
#define CTRL_COLOR_HUE_48		0x62	// Redish Yellow
#define CTRL_COLOR_HUE_72		0x63	// Greenish Yellow
#define CTRL_COLOR_HUE_96		0x64	// Acid Green
#define CTRL_COLOR_HUE_120		0x65	// Intense Green
#define CTRL_COLOR_HUE_144		0x66	// Blueish green
#define CTRL_COLOR_HUE_168		0x67	// Turquise
#define CTRL_COLOR_HUE_192		0x68	// Intensive Turquise
#define CTRL_COLOR_HUE_222		0x69	// Blue
#define CTRL_COLOR_HUE_246		0x70	// Intensive Blue
#define CTRL_COLOR_HUE_270		0x71	// Lila
#define CTRL_COLOR_HUE_294		0x72	// Pink
#define CTRL_COLOR_HUE_318		0x73	// Rose
#define CTRL_COLOR_HUE_342		0x74	// Pink Red


volatile uint8_t control_cmd;
volatile uint8_t control_param;

const char msgbuf[128];

void control_init(void);
void control_handler(void);
void control_setColor(uint8_t color);
void control_setColorRGB(uint8_t red, uint8_t green, uint8_t blue);
