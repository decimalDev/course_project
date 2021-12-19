#include "Street.hpp"
class TrafficLight{
	public:
	CrossRoads* cross;
	Street* street;
	int swithch_on = 0;
	float working_time = 10;
	sf::Time time;
	sf::CircleShape shape;
	//TrafficLight(){}
	TrafficLight(CrossRoads &cross,Street &street,sf::Clock clock){
		this->cross = &cross;
		this->street = &street;
		shape = sf::CircleShape(5);
		shape.setOrigin(2.5,2.5);
		shape.setPosition(cross.point.x,cross.point.y);
		shape.setFillColor(sf::Color::Red);
		time = clock.getElapsedTime();
	}
	void switching(int i,sf::Clock &clock){
		swithch_on = i;
		time = clock.getElapsedTime();
	}
	void work(sf::Clock clock){
		sf::Time time2 = clock.getElapsedTime();
		if(swithch_on){
			if((time2-time).asSeconds()>=working_time){
				switching(0,clock);
			}
		}else{
			if((time2-time).asSeconds()>=working_time){
				switching(1,clock);
			}
		}
	}
	
};