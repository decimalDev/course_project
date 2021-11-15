#include "abstract_model.cpp"
//#include "header.hpp"

int street_width = 60;
int w_width1 = 800,w_height1 = 800;

class Map_Street{
	public:
	Street *street;
	sf::RectangleShape rectangle;
	Map_Street(Street &str){
		street = &str;
		rectangle = sf::RectangleShape(sf::Vector2f(street->length,street_width));
		rectangle.setOrigin(0,street_width/2);
		rectangle.setPosition(street->cross[0].point);
		rectangle.setRotation(atan(street->street_dy/street->street_dx)*180/3.14);
		rectangle.setFillColor(sf::Color(200,200,200));
	}
};

class Map_Machine{
	public:
	sf::RectangleShape rectangle;
	Machine *machine;
	Map_Machine(Machine &m){
		machine = &m;
		float length = 20.f;
		float width = 10.f;
		rectangle = sf::RectangleShape(sf::Vector2f(length,width));
		rectangle.setOrigin(length/2,width/2);
		rectangle.setPosition(machine->x,machine->y);
		rectangle.setRotation(atan(machine->dy/machine->dx)*180/3.14);
		rectangle.setFillColor(sf::Color::Red);
	}
};


class Map{
	public:
	int num;
	AbstractModel *abstract_model;
	
	Map(int w_width, int w_height,AbstractModel &abstractModel){
		abstract_model = &abstractModel;
	}
	void draw(sf::RenderWindow &window){
		for(Street &s: abstract_model->all_streets){
			Map_Street str(s);
			window.draw(str.rectangle);
		}
		for(Machine &s: abstract_model->machines){
			Map_Machine mach(s);
			window.draw(mach.rectangle);
		}
	}
	
	void loop(){
		sf::RenderWindow window(sf::VideoMode(w_width1,w_height1),"picture");
		//window.setFramerateLimit(15);
		while(window.isOpen()){
			sf::Event event;
			while(window.pollEvent(event)){
				switch(event.type){
					case sf::Event::Closed: window.close(); break;
				}
				abstract_model->physics();
				//window.clear(sf::Color::Green);
				draw(window);
				
			}
			window.display();
		}
	}
	
};