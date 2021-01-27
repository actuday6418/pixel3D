#ifndef APPLICATION3D_H
#define APPLICATION3D_H

#define SIDE 512
#define THICC 1.25

#include "../A0/pixel.h"
#include "meshTools.h"
#include <iostream>
#include<fstream>
#include<sstream>
#include <vector>

class application:public pixelMap {

        mesh body;
        float FOVby2;
        bool perspective = true;
	bool toExit = false;
	
	//Handles Keyboard, mouse and system events
	bool eventsExec(sf::RenderWindow&) override;

        //draws lines
        void drawLine(vector3, vector3, std::vector<uint8_t> &, uint8_t);

        void drawTriangle(triangle, std::vector < uint8_t > &);

        void fillTriangle(triangle, std::vector < uint8_t > &);

        //overriding of mapper
        void mapper(std::vector < uint8_t > &) override;

        public:

        application() {
                FOVby2 = 1;
        }

	void loadObj(std::string);

        void togglePerspective() {
                perspective = !perspective;
        }

};
#endif
