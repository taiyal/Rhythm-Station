#ifndef _MOUSE_HANDLER_H_
#define _MOUSE_HANDLER_H_

void RegisterMouseCallbacks();

struct MouseInfo
{  
	int x,y;
	bool left, right, middle;
};

extern MouseInfo Mouse;

#endif
