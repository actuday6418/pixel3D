#include "include/application3D.h"
#include "include/meta.h"


void doMetaScreen(std::string *str){
	auto app = Gtk::Application::create("org.actuday6418.dot");
	Meta h = Meta(str);
	h.set_default_size(500, 500);
	app->run(h);
	if(str->size() > 5){
		str->erase(0,7);
	}
}

void doRender(std::string *str){
	application app3;
	app3.setSleep(0);
	app3.togglePerspective();
	app3.setTitle("3D Renderer");
	app3.loadObj(*str);
	app3.mainLoop();
}

int main()
{
	std::string str;
	doMetaScreen(&str);
	if(str.size() != 0) {
		doRender(&str);
	} else {
		std::cout<<"Exited with no .obj file provided!\n";
	}
}
