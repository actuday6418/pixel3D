#include "include/A1/application3D.h"

int main()
{
	application app;
	app.setSleep(0);
	app.togglePerspective();
	app.setTitle("3D Renderer");
	app.loadObj("/home/actuday/untitled.obj");
	app.mainLoop();
}
