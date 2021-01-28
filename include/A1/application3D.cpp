#include "application3D.h"

void application::loadObj(std::string file){
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


void application::drawLine(vector3 v1, vector3 v2, std::vector<uint8_t> &array, uint8_t color){
	/*float deltaX = v2.x - v1.x;
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
	}*/
	// y = mx + c;
	float dx = v2.x - v1.x;
	float dy = v2.y - v1.y;
	if(dx > 0){
		float m = dy/dx;
		float c = v2.y - m * v2.x;
		float x = v1.x;
		float y = v1.y;
		while(x < v2.x){
			setColor(x,y,color,array);
			x++;
			y = m * x + c;
		}
	} else if (dx < 0){
		float m = dy/dx;
		float c = v2.y - m * v2.x;
		float x = v2.x;
		float y = v2.y;
		while(x < v1.x){
			setColor(x,y,color,array);
			x++;
			y = m * x + c;
		}
	} else if(dy>0){
		float x = v1.x;
		float y = v1.y;
		while(y < v2.y){
			setColor(x,y,color,array);
			y++;
		}	
	} else if(dy<0){
		float x = v2.x;
		float y = v2.y;
		while(y < v1.y){
			setColor(x,y,color,array);
			y++;
		}	
	} else {
		setColor(v1.y,v2.y,color,array);
	}	
}

void application::drawTriangle(triangle tri, std::vector < uint8_t > &array){
	drawLine(tri.vertices[0], tri.vertices[1], array, 1);
	drawLine(tri.vertices[1], tri.vertices[2], array, 1);
	drawLine(tri.vertices[2], tri.vertices[0], array, 1);
}

void application::fillTriangle(triangle t, std::vector < uint8_t > &array){

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

void application::mapper(std::vector < uint8_t > &array) {
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
