#include "application3D.h"

void application::mainLoop() {                
	sf::Event event;
	bool isFirst = true;
	window.setTitle(title);
	while (window.isOpen()) {
		if (isFirst || eventsExec(window)) {
			isFirst = false;
			updateGeo();
			window.clear();
			window.draw(triangles);
			window.display();
			sf::sleep(sf::milliseconds(sleepTime));
		}
	}
}

void application::updateGeo() {
	int f_index=0;
	int v_index;
	for(auto const &tri : body.tris){
		v_index = 0;
		for(auto const &vert : tri.vertices){
			triangles[f_index * 3 + v_index].position = sf::Vector2f(vert.x,vert.y);
			v_index++;
		}
		f_index++;
	}
}

application::application(): window(sf::VideoMode(640,640), "New Window"){
	FOVby2 = 1;
}

void application::loadObj(std::string file){
	std::ifstream f(file);
	if(f){
		std::stringstream s;
		char type;
		float x,y,z;
		std::string title;
		std::vector <vector3> vvec;
		std::string str;
		no_faces = 0;
		while(!f.eof()){
			std::getline(f,str);
			s.clear();
			s.str(str);
			s>>type;
			if(type == 'v'){
				s>>x>>y>>z;
				vvec.push_back(vector3(x,y,z));
			} else if(type == 'f'){
				s>>x>>y>>z;
				body.tris.push_back(triangle(vvec[(int)x-1], vvec[(int)y-1], vvec[(int)z-1]));
				no_faces++;
			} else if(type == 'o'){
				s>>title;
				title = "Render: " + title;
				setTitle(title);
			}
		}
		triangles = sf::VertexArray(sf::Triangles,no_faces*3);
	} else {
		std::cout<<"File not found!"<<std::endl;
		toExit = true;
	}
}

bool application::eventsExec(sf::RenderWindow &w) {
	bool returnVal = false;
	if(toExit){
		w.close();
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
		FOVby2 += 0.001;
		returnVal = true;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
		FOVby2 -= 0.001;
		returnVal = true;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		for(auto &tri : body.tris){
			for(auto &vert : tri.vertices){
				vert.x += 10;
			}
		}
		returnVal = true;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		for(auto &tri : body.tris){
			for(auto &vert : tri.vertices){
				vert.x -= 10;
			}
		}
		returnVal = true;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		for(auto &tri : body.tris){
			for(auto &vert : tri.vertices){
				vert.y -= 10;
			}
		}
		returnVal = true;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		for(auto &tri : body.tris){
			for(auto &vert : tri.vertices){
				vert.y += 10;
			}
		}
		returnVal = true;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
				body.rotateMesh(0,-0.1);
			} else {
				body.rotateMesh(0,0.1);
			}
			returnVal = true;
		} if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
				body.rotateMesh(1,-0.1);
			} else {
				body.rotateMesh(1,0.1);
			}
			returnVal = true;
		} if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
				body.rotateMesh(2,-0.1);
			} else {
				body.rotateMesh(2,0.1);
			}
			returnVal = true;
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
				body.scale(0,-0.01);
			} else {
				body.scale(0,0.01);
			}
			returnVal = true;
		} if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
				body.scale(1,-0.01);
			} else {
				body.scale(1,0.01);
			}
			returnVal = true;
		} if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
				body.scale(2,-0.01);
			} else {
				body.scale(2,0.01);
			}
			returnVal = true;
		} if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
				body.scale(3,-0.01);
			} else {
				body.scale(3,0.01);
			}
			returnVal = true;
		}
	} 
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::O) && sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		togglePerspective();
		returnVal = true;
	}
	sf::Event e;
	while(w.pollEvent(e)){
		if(e.type == sf::Event::MouseWheelMoved) {
			for(auto &tri : body.tris){
				for(auto &vert : tri.vertices){
					vert.z += 0.1*e.mouseWheel.delta;
				}
			}

			returnVal = true;
		}
		else if (e.type == sf::Event::Closed){
			w.close();
		}
	}
	return returnVal;
}
