#define SIDE 1024
#define THICC 2

#include "include/A0/pixel.h"
#include <iostream>
#include<cmath>
#include <vector>

struct vector3 {
	float x, y, z;
};

struct triangle {
	vector3 vertex[3];
};

struct mesh {
	std::vector < triangle > tris;
};

class application:public pixelMap {

	mesh body;
	float FOVby2;

	bool eventsExec() override {
		bool returnVal = false;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			for(auto &tri : body.tris){
				for(auto &vert : tri.vertex){
					vert.x += 1;
				}
			}
			returnVal = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			FOVby2 += 0.01;
			returnVal = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			FOVby2 -= 0.01;std::cout<<"DE"<<std::endl;
			returnVal = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			for(auto &tri : body.tris){
				for(auto &vert : tri.vertex){
					vert.x -= 1;
				}
			}
			returnVal = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			for(auto &tri : body.tris){
				for(auto &vert : tri.vertex){
					vert.y -= 1;
				}
			}
			returnVal = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			for(auto &tri : body.tris){
				for(auto &vert : tri.vertex){
					vert.y += 1;
				}
			}
			returnVal = true;
		}
		return returnVal;
	};
	//draws lines
	void drawLine(vector3 v1, vector3 v2, std::vector<uint8_t> &array){
		float deltaX = v2.x - v1.x;
		float deltaY = v2.y - v1.y;
		float slopeErr = 0;
		if(deltaX == 0){
			int X = v1.x;
			int Y = v1.y;
			if(deltaY > 0){
				while(Y <= v2.y){
					setColor(X,Y,255,array);
					Y++;
				}
				return;
			} else if(deltaY < 0){
				while(Y >= v2.y){
					setColor(X,Y,255,array);
					Y--;
				}
				return;
			} else {//end points are the same
				setColor(X,Y,255,array);
				return;
			}
		}
		float deltaSlope = std::abs(deltaY/deltaX);

		int Y = v1.y;
		int X = v1.x;
		while(true){
			if(v1.x < v2.x){
				if(X > v2.x){
					return;
				} else {
					setColor(X,Y,255,array);
					if(deltaY > 0){
						if(v1.x - X == 0){
							X++;
						} else {
							while((Y - v1.y)/(std::abs(v1.x - X)) < deltaSlope){
								setColor(X,Y,255,array);
								Y++;
							}
							X++;
						}
					} else if(deltaY < 0){
						if(v1.x - X == 0){
							X++;
							break;
						} else {
							while((v1.y - Y)/(std::abs(v1.x - X)) < deltaSlope){
								setColor(X,Y,255,array);
								Y--;
							}
							X++;
						}
					} else {
						X++;
					}
				}				
			} else if(v1.x > v2.x){
				if(X < v2.x){
					return;
				} else {
					setColor(X,Y,255,array);
					if(deltaY > 0){
						if(v1.x - X == 0){
							X--;
						} else {
							while((Y - v1.y)/(std::abs(v1.x - X)) < deltaSlope){
								setColor(X,Y,255,array);
								Y++;
							}
							X--;
						}
					} else if(deltaY < 0){
						if(v1.x - X == 0){
							X--;
						} else {
							while((v1.y - Y)/(std::abs(v1.x - X)) < deltaSlope){
								setColor(X,Y,255,array);
								Y--;
							}
							X--;
						}
					} else {
						X--;
					}
				}				
			}
		}
	}
	//overriding of mapper
	void mapper(std::vector < uint8_t > &array) override {
		//Clear screen
		for (auto & x:array) {
			x = 100;
		}
		std::cout<<"-----------------------------\n";
		//Draw object
		for (auto tri :body.tris) {
			triangle projectedTri;
			for(int i=0;i<3;i++){
				//represents projected coordinates
				projectedTri.vertex[i].x = (tri.vertex[i].x)/(2*std::tan(FOVby2)*tri.vertex[i].z);
				projectedTri.vertex[i].y = (tri.vertex[i].y)/(2*std::tan(FOVby2)*tri.vertex[i].z);
				std::cout<<"X: "<<projectedTri.vertex[i].x<<" Y: "<<projectedTri.vertex[i].y<<std::endl;
			}
			drawLine(projectedTri.vertex[0], projectedTri.vertex[1], array);
			drawLine(projectedTri.vertex[1], projectedTri.vertex[2], array);
			drawLine(projectedTri.vertex[2], projectedTri.vertex[0], array);
		}
	}

	public:
	application() {
		body.tris = {
		//SOUTH
		{ 1.0f, 1.0f, 1.0f,    1.0f, 10.0f, 1.0f,    10.0f, 10.0f, 1.0f },//Triangle halves for each 
		{ 1.0f, 1.0f, 1.0f,    10.0f, 10.0f, 1.0f,    10.0f, 1.0f, 1.0f },//face

		// EAST                                                      
		{ 10.0f, 1.0f, 1.0f,    10.0f, 10.0f, 1.0f,    10.0f, 10.0f, 10.0f },
		{ 10.0f, 1.0f, 1.0f,    10.0f, 10.0f, 10.0f,    10.0f, 1.0f, 10.0f },

		// NORTH                                                     
		{ 10.0f, 1.0f, 10.0f,    10.0f, 10.0f, 10.0f,    1.0f, 10.0f, 10.0f },
		{ 10.0f, 1.0f, 10.0f,    1.0f, 10.0f, 10.0f,    1.0f, 1.0f, 10.0f },

		// WEST                                                      
		{ 1.0f, 1.0f, 10.0f,    1.0f, 10.0f, 10.0f,    1.0f, 10.0f, 1.0f },
		{ 1.0f, 1.0f, 10.0f,    1.0f, 10.0f, 1.0f,    1.0f, 1.0f, 1.0f },

		// TOP                                                       
		{ 1.0f, 10.0f, 1.0f,    1.0f, 10.0f, 10.0f,    10.0f, 10.0f, 10.0f },
		{ 1.0f, 10.0f, 1.0f,    10.0f, 10.0f, 10.0f,    10.0f, 10.0f, 1.0f },
		//BOTTOM
		{ 10.0f, 1.0f, 10.0f,    1.0f, 1.0f, 10.0f,    1.0f, 1.0f, 1.0f },
		{ 10.0f, 1.0f, 10.0f,    1.0f, 1.0f, 1.0f,    10.0f, 1.0f, 1.0f },
		};
		FOVby2 = 0.2;//0.7853; //45 degree angle, so fov is 90 degrees
	}
};

int main()
{
	application app;
	app.setSleep(0);
	app.setTitle("3D Renderer");
	app.mainLoop();
}
