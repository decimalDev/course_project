#include "abstract_model.cpp"

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
	}
	
	void loop(){
		sf::RenderWindow window(sf::VideoMode(w_width1,w_height1),"picture");
		while(window.isOpen()){
			sf::Event event;
			while(window.pollEvent(event)){
				switch(event.type){
					case sf::Event::Closed: window.close(); break;
				}
				window.clear(sf::Color::Green);
				draw(window);
				
			}
			window.display();
		}
	}
	
};