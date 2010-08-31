#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

#include <GL/glfw.h>

struct IEvent {
	int Key;
	int State;
};

class InputManager
{
public:
	InputManager();
	void Update();
};

// A-Z, for game buttons not text input (use the char callback for that!)
enum KeyAliases {
	KEY_A		= 65,
	KEY_B		= 66,
	KEY_C		= 67,
	KEY_D		= 68,
	KEY_E		= 69,
	KEY_F		= 70,
	KEY_G		= 71,
	KEY_H		= 72,
	KEY_I		= 73,
	KEY_J		= 74,
	KEY_K		= 75,
	KEY_L		= 76,
	KEY_M		= 77,
	KEY_N		= 78,
	KEY_O		= 79,
	KEY_P		= 80,
	KEY_Q		= 81,
	KEY_R		= 82,
	KEY_S		= 83,
	KEY_T		= 84,
	KEY_U		= 85,
	KEY_V		= 86,
	KEY_W		= 87,
	KEY_X		= 88,
	KEY_Y		= 89,
	KEY_Z		= 90,

	// some special chars
	KEY_SLASH	= 47,
	KEY_PERIOD	= 46,
	KEY_COMMA	= 44,
	KEY_ESC		= GLFW_KEY_ESC,
	KEY_ENTER	= GLFW_KEY_ENTER,
	KEY_LEFT		= GLFW_KEY_LEFT,
	KEY_RIGHT	= GLFW_KEY_RIGHT,
	KEY_UP		= GLFW_KEY_UP,
	KEY_DOWN	= GLFW_KEY_DOWN,
	KEY_MINUS	= 39,
	KEY_EQUAL	= 59,
	KEY_TILDE	= 92,
	KEY_LBRACKET	= 93,
	KEY_RBRACKET = 91,
	KEY_BACKSLASH = 96,
	KEY_SEMICOLON = 61,
	KEY_QUOTE	= 45,

	// 0-9
	KEY_ZERO	= 48,
	KEY_ONE		= 49,
	KEY_TWO	= 50,
	KEY_THREE	= 51,
	KEY_FOUR	= 52,
	KEY_FIVE		= 53,
	KEY_SIX		= 54,
	KEY_SEVEN	= 55,
	KEY_EIGHT	= 56,
	KEY_NINE		= 57,

	// f1-12
	KEY_F1		= GLFW_KEY_F1,
	KEY_F2		= GLFW_KEY_F2,
	KEY_F3		= GLFW_KEY_F3,
	KEY_F4		= GLFW_KEY_F4,
	KEY_F5		= GLFW_KEY_F5,
	KEY_F6		= GLFW_KEY_F6,
	KEY_F7		= GLFW_KEY_F7,
	KEY_F8		= GLFW_KEY_F8,
	KEY_F9		= GLFW_KEY_F9,
	KEY_F10		= GLFW_KEY_F10,
	KEY_F11		= GLFW_KEY_F11,
	KEY_F12		= GLFW_KEY_F12,
};

enum KeyStates {
	RS_NONE,
	RS_LET_GO,
	RS_FIRST_PRESS,
	RS_HELD,
	RS_LAST // for looping
};

#endif
