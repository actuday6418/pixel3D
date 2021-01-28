#ifndef APPLICATION3D_H
#define APPLICATION3D_H

#define SIDE 512
#define THICC 1.25

#include "meshTools.h"
#include <iostream>
#include<fstream>
#include<sstream>
#include <vector>
#include<SFML/Graphics.hpp>

class application {

        mesh body;
        float FOVby2;
	int sleepTime = 10;
        bool perspective = true;
	bool toExit = false;
	int no_faces;

	std::string title;
	sf::RenderWindow window;
	sf::VertexArray triangles;
	
	//Handles Keyboard, mouse and system events
	bool eventsExec(sf::RenderWindow&);

        //draws lines
        //void drawLine(vector3, vector3, std::vector<uint8_t> &, uint8_t);

        //void drawTriangle(triangle, std::vector < uint8_t > &);

	void updateGeo();

public:

	void mainLoop();
        
	application();

	void loadObj(std::string);

        void togglePerspective() {
                perspective = !perspective;
        }

	void setSleep(int t){
		sleepTime = t;
	}

	void setTitle(std::string t){
		title = t;
	}
};
#endif
