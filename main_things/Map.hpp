#include "abstract_model.cpp"
//#include "header.hpp"

int street_width = 60;
int w_width1 = 800,w_height1 = 800;

class Map{
	public:
	int num;
	AbstractModel *abstract_model;
	std::vector<sf::RectangleShape> street_shapes;
	
	Map(int w_width, int w_height,AbstractModel &abstractModel){
		abstract_model = &abstractModel;
		//defining streets shapes
		for(int i = 0;i<abstract_model->all_streets.size();i++){
			Street* street = &(abstract_model->all_streets[i]);
			sf::RectangleShape rectangle = sf::RectangleShape(sf::Vector2f(street->length,street_width));
			rectangle.setOrigin(0,street_width/2);
			rectangle.setPosition(street->cross[0].point);
			if(street->street_dx>0)
				rectangle.setRotation(atan(street->street_dy/street->street_dx)*180/3.14);
			else if(street->street_dx==0)
				if(street->street_dy>0) rectangle.setRotation(90);
				else rectangle.setRotation(-90);
			else rectangle.setRotation(atan(street->street_dy/street->street_dx)*180/3.14+180);
			rectangle.setFillColor(sf::Color(200,200,200));
			street_shapes.push_back(rectangle);
		}
		
	}
	
	void draw_streets(sf::RenderWindow &window){
		for(int i = 0;i<street_shapes.size();i++)
			window.draw(street_shapes[i]);
	}
	void draw_machines(sf::RenderWindow &window){
		for(int i = 0;i<abstract_model->machines.size();i++){
			window.draw(abstract_model->machines[i].rectangle);
		}
	}
	
	void draw(sf::RenderWindow &window){
		draw_streets(window);
		draw_machines(window);
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
				
				
			}
			window.clear(sf::Color::Green);
			draw(window);
			window.display();
			abstract_model->physics();
		}
	}
	
};