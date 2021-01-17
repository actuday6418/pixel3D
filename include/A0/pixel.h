#ifndef PIXEL_H
#define PIXEL_H

#include<SFML/Graphics.hpp>
#include<iostream>

//SIDE is to be defined by the user

class pixelMap {
 protected:
	sf::VertexArray varray;
	sf::RenderWindow window;
	bool log;
	int tik_factor;
	//default value is sixty
	int FPS;

 public:
	 pixelMap():varray(sf::Quads, SIDE * SIDE * 4),
	    window(sf::VideoMode(640, 640), "New Window") {
		setPositions();
		tik_factor = 1;
		FPS = 60;
		log = false;
	};

	void setTitle(const std::string & title) {
		window.setTitle(title);
	}

	void setFPS(unsigned int FPS) {
		window.setFramerateLimit(FPS);
		this->FPS = FPS;
	}
	void logger() {
		log = true;
	}
	//virtual function that has to be overriden by the user for updating pixel map each frame.
	virtual void mapper(std::vector < uint8_t > &array) = 0;
	virtual void eventsExec() = 0;

	void setTickFactor(int fac) {
		tik_factor = fac;
	}
	//contains main loop
	void mainLoop() {
		sf::Clock clock;
		int tick = 1;
		int delta = 0, prev_sec = 0, new_sec;

		while (window.isOpen()) {
			if (tick == FPS / tik_factor) {
				eventsExec();
				new_sec =
				    (int)clock.getElapsedTime().asSeconds();
				delta = new_sec - prev_sec;
				if (log)
					std::cout << "Time to " << FPS <<
					    " frames: " << delta << std::endl;
				tick = 1;
			}
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			setColors();
			window.draw(varray);
			window.display();
			tick++;
		}
	}
	//called once during construction to set positions of each pixel
	void setPositions() {
		for (int k = 0; k < SIDE * SIDE * 4; k += 4) {
			int i = (k % (SIDE * 4)) / 4;
			int j = k / (SIDE * 4);

			varray[k].position = sf::Vector2f(i * THICC, j * THICC);
			varray[k + 1].position =
			    sf::Vector2f(i * THICC + THICC, j * THICC);
			varray[k + 2].position =
			    sf::Vector2f(i * THICC + THICC, j * THICC + THICC);
			varray[k + 3].position =
			    sf::Vector2f(i * THICC, j * THICC + THICC);
		}
	}

	//set the Color of a particular pixel at location (x,y)
	void setColor(int x, int y, uint8_t color,
		      std::vector < uint8_t > &array) {
		if (x < SIDE && y < SIDE) {
			array[y * SIDE + x] = color;
		} else {
			std::cout << "Set color call out of bounds - " << x <<
			    " " << y << std::endl;
		}
	}

	//called every frame to set color of each pixel.
	void setColors() {
		std::vector < uint8_t > array(SIDE * SIDE, 0);
		mapper(array);
		for (int k = 0, i = 0; k < SIDE * SIDE * 4; k += 4, i++) {
			varray[k].color =
			    sf::Color(array[i], array[i], array[i],
				      (uint8_t) 255);
			varray[k + 1].color =
			    sf::Color(array[i], array[i], array[i],
				      (uint8_t) 255);
			varray[k + 2].color =
			    sf::Color(array[i], array[i], array[i],
				      (uint8_t) 255);
			varray[k + 3].color =
			    sf::Color(array[i], array[i], array[i],
				      (uint8_t) 255);
		}
	}
};
#endif
