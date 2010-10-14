/**
* RaumZeitLabor Moodlight 
**/

#define CTRL_CMD_NONE 0x00
#define CTRL_CMD_PAUSE_TOGGLE 0x10
#define CTRL_CMD_PAUSE_ON 0x11
#define CTRL_CMD_PAUSE_OFF 0x12
#define CTRL_CMD_BRIGHTNESS_UP 0x20
#define CTRL_CMD_BRIGHTNESS_DOWN 0x21
#define CTRL_CMD_SPEED_UP 0x30
#define CTRL_CMD_SPEED_DOWN 0x31

volatile uint8_t control_cmd;

void control_handler(void);