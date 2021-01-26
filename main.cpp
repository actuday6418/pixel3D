#define SIDE 512
#define THICC 1.25

#include "include/A0/pixel.h"
#include <iostream>
#include<X11/Xlib.h>
#include<fstream>
#include<sstream>
#include<cmath>
#include <vector>

struct vector3 {
	float x, y, z;

	vector3(float x=0, float y=0, float z=0): x(x), y(y), z(z){}

	vector3 operator - (const vector3 &v){
		vector3 ret(x-v.x, y-v.y, z-v.z);
		return ret;
	}

	vector3 operator + (const vector3 &v){
		vector3 ret(x+v.x, y+v.y, z+v.z);
		return ret;
	}
};

struct triangle {
	vector3 vertices[3];

	triangle(vector3 a=vector3(), vector3 b=vector3(), vector3 c=vector3()): vertices{a,b,c}{}

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
		 *  posZ = posz*cosdY - posX*sindY
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
						vert = vert - origin;
						vector3 v = vert;
						v.x = vert.z*sinTheta + vert.x*cosTheta;
						//v.y unchanged
						v.z = vert.z*cosTheta - vert.x*sinTheta;
						vert = v;
						vert = v + origin;
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
	bool perspective = true;
	bool q=false;

	bool eventsExec(sf::RenderWindow &w) override {
		/*
		sf::WindowHandle handle = w.getSystemHandle();
		XEvent event;
		bool loop=true;
		Display *cdisDisplay = XOpenDisplay(NULL);
		while (loop==true)
	    {
  			XNextEvent(handle,&event);
  			switch (event.type)
    		{
    			case ClientMessage:
      			std::cout<<"window closed"<<std::endl;
				loop=false;
      			break;
    		}
  		}
		*/
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
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
			q = true;
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
	};

	//draws lines
	void drawLine(vector3 v1, vector3 v2, std::vector<uint8_t> &array, uint8_t color){
		float deltaX = v2.x - v1.x;
		float deltaY = v2.y - v1.y;
		float slopeErr = 0;
		if(deltaX == 0){
			int X = v1.x;
			int Y = v1.y;
			if(deltaY > 0){
				while(Y <= v2.y){
					setColor(X,Y,color,array);
					Y++;
				}
				return;
			} else if(deltaY < 0){
				while(Y >= v2.y){
					setColor(X,Y,color,array);
					Y--;
				}
				return;
			} else {//end points are the same
				setColor(X,Y,color,array);
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
					setColor(X,Y,color,array);
					if(deltaY > 0){
						if(v1.x - X == 0){
							X++;
						} else {
							while((Y - v1.y)/(std::abs(v1.x - X)) < deltaSlope){
								setColor(X,Y,color,array);
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
								setColor(X,Y,color,array);
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
					setColor(X,Y,color,array);
					if(deltaY > 0){
						if(v1.x - X == 0){
							X--;
						} else {
							while((Y - v1.y)/(std::abs(v1.x - X)) < deltaSlope){
								setColor(X,Y,color,array);
								Y++;
							}
							X--;
						}
					} else if(deltaY < 0){
						if(v1.x - X == 0){
							X--;
						} else {
							while((v1.y - Y)/(std::abs(v1.x - X)) < deltaSlope){
								setColor(X,Y,color,array);
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
		drawLine(tri.vertices[0], tri.vertices[1], array, 1);
		drawLine(tri.vertices[1], tri.vertices[2], array, 1);
		drawLine(tri.vertices[2], tri.vertices[0], array, 1);
	}

	void fillTriangle(triangle t, std::vector < uint8_t > &array){

		//get length of all sides
		float d1 = std::sqrt(std::pow((t.vertices[1].y-t.vertices[0].y),2)+std::pow((t.vertices[1].x-t.vertices[0].x),2));
		float d2 = std::sqrt(std::pow((t.vertices[2].y-t.vertices[1].y),2)+std::pow((t.vertices[2].x-t.vertices[1].x),2));
		float d3 = std::sqrt(std::pow((t.vertices[0].y-t.vertices[2].y),2)+std::pow((t.vertices[0].x-t.vertices[2].x),2)); 

		vector3 A = t.vertices[0] - t.vertices[1];
		vector3 B = t.vertices[2] - t.vertices[1];

		//Find unit normal vector, extract Z component,additive inverse, multiply by color factor
		float shadeColor = (A.x * B.y - A.y * B.x)/
			std::sqrt(std::pow(A.y * B.z - A.z * B.y,2) + std::pow(A.z * B.x - A.x * B.z,2) + std::pow(A.x * B.y - A.y * B.x,2));
		shadeColor = 255*(1 - shadeColor);

		if(( (d1<d2) || (d1=d2) ) && ( (d1<d2) || (d1=d2) )){ //the first side is the shortest
			float tx = t.vertices[0].x;
			float ty = t.vertices[0].y;
			float vx = (t.vertices[1].x-t.vertices[0].x)/d1;
			float vy = (t.vertices[1].y-t.vertices[0].y)/d1;
			int counter = 0;
			while(counter<d1){
				vector3 temp(tx,ty,0);
				drawLine(t.vertices[2],temp, array, shadeColor);
				//drawing a line from point(t.vertices[2].x,t.vertices[2].y) to point(tx,ty).
				tx = tx + vx;
				ty = ty + vy;
				counter++;
			}
		} else if((d2<d3) || (d2=d3)) { //the second side is the shortest
			float tx = t.vertices[1].x;
			float ty = t.vertices[1].y;
			float vx = (t.vertices[2].x-t.vertices[1].x)/d2;
			float vy = (t.vertices[2].y-t.vertices[1].y)/d2;
			int counter = 0;
			while(counter<d2){
				vector3 temp(tx,ty);
				drawLine(t.vertices[0],temp, array, shadeColor);
				tx = tx + vx;
				ty = ty + vy;
				counter++;
			}
		}
		else { // the third side is shortest
			float tx = t.vertices[2].x;
			float ty = t.vertices[2].y;
			float vx = (t.vertices[0].x-t.vertices[2].x)/d3;
			float vy = (t.vertices[0].y-t.vertices[2].y)/d3;
			int counter = 0;
			while(counter<d3){
				vector3 temp(tx,ty);
				drawLine(t.vertices[1],temp, array, shadeColor);
				tx = tx + vx;
				ty = ty + vy;
				counter++;
			}
		}
	}

	//overriding of mapper
	void mapper(std::vector < uint8_t > &array) override {
		//Clear screen
		for (auto & x:array) {
			x = 100;
		}
		//Draw farther triangles first
		std::sort(body.tris.begin(), body.tris.end(),[](triangle t1, triangle t2){
				if((t1.vertices[0].z + t1.vertices[1].z + t1.vertices[2].z) <
						(t2.vertices[0].z + t2.vertices[1].z + t2.vertices[2].z)){
				return true;
				} else {
				return false;
				}
				});
		//Draw object
		for (auto tri :body.tris) {
			triangle projectedTri;
			if(perspective){
				for(int i=0;i<3;i++){
					//represents projected coordinates
					projectedTri.vertices[i].x = (FOVby2 * tri.vertices[i].x)/tri.vertices[i].z;
					projectedTri.vertices[i].y = (FOVby2 * tri.vertices[i].y)/tri.vertices[i].z;
					projectedTri.vertices[i].z = tri.vertices[i].z;
				}
			} else {
				for(int i=0;i<3;i++){
					//represents projected coordinates
					projectedTri.vertices[i].x = tri.vertices[i].x;
					projectedTri.vertices[i].y = tri.vertices[i].y;
					projectedTri.vertices[i].z = tri.vertices[i].z;
				}
			}

			projectedTri.vertices[0].x += SIDE/2;
			projectedTri.vertices[1].x += SIDE/2;
			projectedTri.vertices[2].x += SIDE/2;
			projectedTri.vertices[0].y += SIDE/2;
			projectedTri.vertices[1].y += SIDE/2;
			projectedTri.vertices[2].y += SIDE/2;
			fillTriangle(projectedTri, array);
			//drawTriangle(projectedTri, array);
		}
	}

	public:
	application() {
	/*	body.tris = {
			//SOUTH
			{	vector3( 1.0f, 1.0f, 1.0f),    vector3(1.0f, 4.0f, 1.0f),   vector3( 4.0f, 4.0f, 1.0f )},//Triangle halves for each 
			{vector3( 1.0f, 1.0f, 1.0f),    vector3(4.0f, 4.0f, 1.0f),    vector3(4.0f, 1.0f, 1.0f )},//face

			// EAST                                                      
			{vector3( 4.0f, 1.0f, 1.0f),    vector3(4.0f, 4.0f, 1.0f),    vector3(4.0f, 4.0f, 2.0f )},
			{vector3( 4.0f, 1.0f, 1.0f),    vector3(4.0f, 4.0f, 2.0f),    vector3(4.0f, 1.0f, 2.0f )},

			// NORTH                                                     
			{vector3( 4.0f, 1.0f, 2.0f),    vector3(4.0f, 4.0f, 2.0f),    vector3(1.0f, 4.0f, 2.0f )},
			{vector3( 4.0f, 1.0f, 2.0f),    vector3(1.0f, 4.0f, 2.0f),    vector3(1.0f, 1.0f, 2.0f )},

			// WEST                                                      
			{vector3( 1.0f, 1.0f, 2.0f),    vector3(1.0f, 4.0f, 2.0f),    vector3(1.0f, 4.0f, 1.0f )},
			{vector3( 1.0f, 1.0f, 2.0f),    vector3(1.0f, 4.0f, 1.0f),    vector3(1.0f, 1.0f, 1.0f )},

			// TOP                                                       
			{vector3( 1.0f, 4.0f, 1.0f),    vector3(1.0f, 4.0f, 2.0f),    vector3(4.0f, 4.0f, 2.0f )},
			{vector3( 1.0f, 4.0f, 1.0f),    vector3(4.0f, 4.0f, 2.0f),    vector3(4.0f, 4.0f, 1.0f )},
			//BOTTOM
			{vector3( 4.0f, 1.0f, 2.0f),    vector3(1.0f, 1.0f, 2.0f),    vector3(1.0f, 1.0f, 1.0f )},
			{vector3(4.0f, 1.0f, 2.0f),    vector3(1.0f, 1.0f, 1.0f),    vector3(4.0f, 1.0f, 1.0f )},
		};*/

		FOVby2 = 1;
	}
	
	void loadObj(std::string file){
		std::ifstream f(file);
		if(f){
			std::stringstream s;
			char type;
			float x,y,z;
			std::string title;
			std::vector <vector3> vvec;
			std::string str;
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
				} else if(type == 'o'){
					s>>title;
					title = "Render: " + title;
					setTitle(title);
				}
			}
		} else {
			std::cout<<"File not found!"<<std::endl;
		}
	}		


	void togglePerspective() {
		perspective = !perspective;
	}

};

int main()
{
	application app;
	app.setSleep(0);
	app.togglePerspective();
	app.setTitle("3D Renderer");
	app.loadObj("/home/actuday/untitled.obj");
	app.mainLoop();
}
