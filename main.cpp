#define SIDE 512
#define THICC 1.25

#include "include/A0/pixel.h"
#include <iostream>
#include<cmath>
#include <vector>

struct vector3 {
	float x, y, z;
	vector3 operator - (const vector3 &v){
		vector3 ret;
		ret.x = x - v.x;
		ret.y = y - v.y;
		ret.z = z - v.z;
		return ret;
	}
	
	vector3 operator + (const vector3 &v){
		vector3 ret;
		ret.x = x + v.x;
		ret.y = y + v.y;
		ret.z = z + v.z;
		return ret;
	}
};

struct triangle {
	vector3 vertices[3];
};

struct mesh {
	vector3 origin;
	std::vector < triangle > tris;

	void calcOrigin(){
		origin.x = 0;
		origin.y = 0;
		origin.z = 0;
		int nop = 0;//No of points in mesh
		for(auto const &tri : tris){
			for(auto const &vert : tri.vertices){
				nop++;
				origin.x += vert.x;
				origin.y += vert.y;
				origin.z += vert.z;
			}
		}
		origin.x /= (float)nop;
		origin.y /= (float)nop;
		origin.z /= (float)nop;
	}

	//Zero axis is X, 1 Y, and 2 is Z.
	void rotateMesh(int axis, float dTheta){

		/*
		 * ============ Equations derived from rotation transform ======
		 *
		 * ============ Y axis rotation ===========
		 *  posX = posX*cosdY + posZ*sindY
		 *  posY = posY
		 *  posZ = posX*cosdY + posZ*sindY
		 *  =======================================
		 *
		 * ============ X axis rotation ===========
		 *  posX = posX
		 *  posY = posY*cosdX - posZ*sindX
		 *  posZ = posY*sindX + posZ*cosdX
		 *  =======================================
		 *
		 * ============ Z axis rotation ===========
		 *  posX = posX*cosdZ - posY*sindZ
		 *  posY = posX*sindZ + posY*cosdZ
		 *  posZ = posZ
		 *  =======================================
		 * ============================================================
		 */

		float cosTheta = std::cos(dTheta);
		float sinTheta = std::sin(dTheta);
		calcOrigin();

		switch(axis){
			case 0:	//case: X axis
				for(auto &tri : tris){
					for(auto &vert : tri.vertices){
						vert = vert - origin;
						vector3 v = vert;
						//vert.x unchanged
						v.y = vert.y*cosTheta - vert.z*sinTheta;
						v.z = vert.y*sinTheta + vert.z*cosTheta;
						vert = v + origin;
					}
				}
				break;
			case 1: //case: Y axis
				for(auto &tri : tris){
					for(auto &vert : tri.vertices){
						std::cout<<"Old co-odrinates: X: "<<vert.x<<" Z: "<<vert.z;
						//vert = vert - origin;
						vector3 v = vert;
						v.x = vert.z*sinTheta + vert.x*cosTheta;
						//v.y unchanged
						v.z = vert.z*cosTheta - vert.x*sinTheta;
						vert = v;
						//vert = v + origin;
						std::cout<<" New: X: "<<vert.x<<" Z: "<<vert.z<<std::endl;
					}
				}
				break;
			case 2: //case: Z axis
				for(auto &tri : tris){
					for(auto &vert : tri.vertices){
						vert = vert - origin;
						vector3 v = vert;
						v.x = vert.x*cosTheta - vert.y*sinTheta;
						v.y = vert.x*sinTheta + vert.y*cosTheta;
						//vert.z unchanged
						vert = v + origin;
					}
				}
				break;
		}
	}
	//Zero axis is X, 1 Y, 2 Z, 3 is all
	void scale(int axis, float scale){
		calcOrigin();
		scale += 1;
		switch (axis){
			case 0:
				for(auto &tri : tris){
					for(auto &vert : tri.vertices){
						vert.x -= origin.x;
						vert.x *= scale;
						vert.x += origin.x;
					}
				}
				break;
			case 1:
				for(auto &tri : tris){
					for(auto &vert : tri.vertices){
						vert.y -= origin.y;
						vert.y *= scale;
						vert.y += origin.y;
					}
				}
				break;
			case 2:
				for(auto &tri : tris){
					for(auto &vert : tri.vertices){
						vert.z -= origin.z;
						vert.z *= scale;
						vert.z += origin.z;
					}
				}
				break;
			case 3:
				for(auto &tri : tris){
					for(auto &vert : tri.vertices){
						vert = vert - origin;
						vert.x *= scale;
						vert.y *= scale;
						vert.z *= scale;
						vert = vert + origin;
					}
				}
				break;
		}
	}	
};

class application:public pixelMap {

	mesh body;
	float FOVby2;

	bool eventsExec() override {
		bool returnVal = false;
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
					vert.x += 1;
				}
			}
			returnVal = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			for(auto &tri : body.tris){
				for(auto &vert : tri.vertices){
					vert.x -= 1;
				}
			}
			returnVal = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			for(auto &tri : body.tris){
				for(auto &vert : tri.vertices){
					vert.y -= 1;
				}
			}
			returnVal = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			for(auto &tri : body.tris){
				for(auto &vert : tri.vertices){
					vert.y += 1;
				}
			}
			returnVal = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
					body.rotateMesh(0,-0.01);
				} else {
					body.rotateMesh(0,0.01);
				}
				returnVal = true;
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
					body.rotateMesh(1,-0.785);
				} else {
					body.rotateMesh(1,0.785);
				}
				returnVal = true;
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
					body.rotateMesh(2,-0.01);
				} else {
					body.rotateMesh(2,0.01);
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
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
					body.scale(1,-0.01);
				} else {
					body.scale(1,0.01);
				}
				returnVal = true;
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
					body.scale(2,-0.01);
				} else {
					body.scale(2,0.01);
				}
				returnVal = true;
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
					body.scale(3,-0.01);
				} else {
					body.scale(3,0.01);
				}
				returnVal = true;
			}
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

	void drawTriangle(triangle tri, std::vector < uint8_t > &array){
		drawLine(tri.vertices[0], tri.vertices[1], array);
		drawLine(tri.vertices[1], tri.vertices[2], array);
		drawLine(tri.vertices[2], tri.vertices[0], array);
	}

	//overriding of mapper
	void mapper(std::vector < uint8_t > &array) override {
		//Clear screen
		for (auto & x:array) {
			x = 100;
		}
		//Draw object
		for (auto tri :body.tris) {
			triangle projectedTri;
			for(int i=0;i<3;i++){
				//represents projected coordinates
				projectedTri.vertices[i].x = (tri.vertices[i].x)/(2*std::tan(FOVby2)*tri.vertices[i].z);
				projectedTri.vertices[i].y = (tri.vertices[i].y)/(2*std::tan(FOVby2)*tri.vertices[i].z);
			}
			projectedTri.vertices[0].x += SIDE/2;
			projectedTri.vertices[1].x += SIDE/2;
			projectedTri.vertices[2].x += SIDE/2;
			projectedTri.vertices[0].y += SIDE/2;
			projectedTri.vertices[1].y += SIDE/2;
			projectedTri.vertices[2].y += SIDE/2;
			drawTriangle(projectedTri, array);
		}
	}

	public:
	application() {
		body.tris = {
			//SOUTH
			{ 1.0f, 1.0f, 1.0f,    1.0f, 4.0f, 1.0f,    4.0f, 4.0f, 1.0f },//Triangle halves for each 
			{ 1.0f, 1.0f, 1.0f,    4.0f, 4.0f, 1.0f,    4.0f, 1.0f, 1.0f },//face

			// EAST                                                      
			{ 4.0f, 1.0f, 1.0f,    4.0f, 4.0f, 1.0f,    4.0f, 4.0f, 2.0f },
			{ 4.0f, 1.0f, 1.0f,    4.0f, 4.0f, 2.0f,    4.0f, 1.0f, 2.0f },

			// NORTH                                                     
			{ 4.0f, 1.0f, 2.0f,    4.0f, 4.0f, 2.0f,    1.0f, 4.0f, 2.0f },
			{ 4.0f, 1.0f, 2.0f,    1.0f, 4.0f, 2.0f,    1.0f, 1.0f, 2.0f },

			// WEST                                                      
			{ 1.0f, 1.0f, 2.0f,    1.0f, 4.0f, 2.0f,    1.0f, 4.0f, 1.0f },
			{ 1.0f, 1.0f, 2.0f,    1.0f, 4.0f, 1.0f,    1.0f, 1.0f, 1.0f },

			// TOP                                                       
			{ 1.0f, 4.0f, 1.0f,    1.0f, 4.0f, 2.0f,    4.0f, 4.0f, 2.0f },
			{ 1.0f, 4.0f, 1.0f,    4.0f, 4.0f, 2.0f,    4.0f, 4.0f, 1.0f },
			//BOTTOM
			{ 4.0f, 1.0f, 2.0f,    1.0f, 1.0f, 2.0f,    1.0f, 1.0f, 1.0f },
			{ 4.0f, 1.0f, 2.0f,    1.0f, 1.0f, 1.0f,    4.0f, 1.0f, 1.0f },
		};
		body.calcOrigin();
		FOVby2 = 0.05;//0.7853; 45 degree angle, so fov is 90 degrees
	}
};

int main()
{
	application app;
	app.setSleep(500);
	app.setTitle("3D Renderer");
	app.mainLoop();
}
