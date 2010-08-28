#include <GL/glfw.h>

void GLFWCALL ResizeViewport(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glViewport(0, 0, w, h);
	glOrtho(int(-(w/2)), int((w/2)), int((h/2)), int(-(h/2)), -10, 10);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// the frame buffer is usually full of junk after resize. clear it.
	glClear(GL_COLOR_BUFFER_BIT);
}

void SetInitialStates()
{
	glClearColor(0,0,0,1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_LIGHTING);
}

void RegisterResizeCallback()
{
	glfwSetWindowSizeCallback(ResizeViewport);
}
