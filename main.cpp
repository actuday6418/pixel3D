#include "include/A0/pixel.h"
#include <iostream>
#include<math.h>
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

	void eventsExec() override {
		int s;
	};
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
				projectedTri.vertex[i].x = (tri.vertex[i].x)/(2*std::tan(FOVby2)*tri.vertex[i].y);
				projectedTri.vertex[i].y = (tri.vertex[i].y)/(2*std::tan(FOVby2)*tri.vertex[i].x);
				setColor(projectedTri.vertex[i].x, projectedTri.vertex[i].y, 255, array);
			}
		}
	}

	public:
	application() {
		body.tris = {
			{1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 20.0f, 20.0f, 1.0f},	//Triangle halves
			{1.0f, 1.0f, 1.0f, 20.0f, 20.0f, 1.0f, 20.0f, 1.0f, 1.0f},	//for each face 

			{20.0f, 1.0f, 1.0f, 20.0f, 20.0f, 1.0f, 20.0f, 20.0f, 2.0f},	//of a cube
			{20.0f, 1.0f, 1.0f, 20.0f, 20.0f, 2.0f, 20.0f, 1.0f, 2.0f},

			{20.0f, 1.0f, 2.0f, 20.0f, 20.0f, 2.0f, 1.0f, 20.0f, 2.0f},
			{20.0f, 1.0f, 2.0f, 1.0f, 20.0f, 2.0f, 1.0f, 1.0f, 2.0f},

			{1.0f, 1.0f, 2.0f, 1.0f, 20.0f, 2.0f, 1.0f, 20.0f, 1.0f},
			{1.0f, 1.0f, 2.0f, 1.0f, 20.0f, 1.0f, 1.0f, 1.0f, 1.0f},

			{1.0f, 20.0f, 1.0f, 1.0f, 20.0f, 2.0f, 20.0f, 20.0f, 2.0f},
			{1.0f, 20.0f, 1.0f, 20.0f, 20.0f, 2.0f, 20.0f, 20.0f, 1.0f},

			{20.0f, 1.0f, 2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f},
			{20.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 20.0f, 1.0f, 1.0f},
		};
		FOVby2 = 0.7853; //45 degree angle, so fov is 90 degrees
	}
};

int main()
{
	application app;
	app.setTitle("3D Renderer");
	app.mainLoop();
}
