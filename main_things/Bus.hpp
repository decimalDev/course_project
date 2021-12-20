#include "Public_transport.hpp"
class Bus: public Public_transport{
	public:
	int a;
	Bus(){}
	Bus(Street street1, std::vector<Street> &all_streets): Public_transport(street1,all_streets){
		
	}
	void move(float time,sf::Clock &clock) override{
	
		if(is_machine_broken){
			if((clock.getElapsedTime()-broken_in).asSeconds()>4) is_way_completed = 1;
		}
		
		if(!is_there_machine_in_forward&&!is_machine_broken) velocity = max_velocity;
		
		x+=time*dx*velocity;//troubles in time
		y+=time*dy*velocity;
		rectangle.setPosition(sf::Vector2f(x,y));
		rectangle.setRotation(atan(dy/dx)*180/3.14);//rad to grad
		
		float ang = atan(dy/dx);
		model.setRotation(ang*180/3.14);//rad to grad
		
		
		if(dx==0){
			if(dy>0) ang = 3.14;
			else ang = -3.14;
		}else if(dx<0) ang = ang+3.14;

		
		int dist = 20;
		model.setPosition(sf::Vector2f(x+cos(ang)*dist - sin(ang)*dist ,y+sin(ang)*dist+cos(ang)*dist));
		
		traversed_path = sqrt((next_cross.point.x-cur_cross.point.x)*(next_cross.point.x-cur_cross.point.x) + (next_cross.point.y-cur_cross.point.y)*(next_cross.point.y-cur_cross.point.y)) - sqrt((x-cur_cross.point.x)*(x-cur_cross.point.y) + (y-cur_cross.point.y)*(y-cur_cross.point.y));
		
		if(traversed_path<0){
			is_way_completed = 1;
			dx = 0;
			dy = 0;
		}
		
	}
};