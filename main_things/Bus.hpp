#include "Public_transport.hpp"
class Bus: public Public_transport{
	public:
	Bus(){}
	Bus(Street street1, std::vector<Street> &all_streets): Public_transport(street1,all_streets){
		
	}
	void move(float time,sf::Clock &clock) override{
		
		if(dx!=0||dy!=0){
			cur_dx = dx;
			cur_dy = dy;
		}
		std::cout<<"Bus:"<<"move"<<std::endl;//debug
		if(is_machine_broken){
			if((clock.getElapsedTime()-broken_in).asSeconds()>4) is_way_completed = 1;
			return;
		}
		
		if(!is_there_machine_in_forward&&!is_machine_broken) velocity = max_velocity;
		
		x+=time*dx*velocity;
		y+=time*dy*velocity;
		rectangle.setPosition(sf::Vector2f(x,y));
		rectangle.setRotation(atan(dy/dx)*180/3.14);//rad to grad
		
		
		
		
		float ang = atan(dy/dx);

		std::cout<<"Bus:"<<"move:first angle = "<<angle<<std::endl;//debug
			if(dx==0&&dy!=0){
			if(dy>0) ang = 3.14;
			else ang = -3.14;
			//angle = ang;
		}else if(dx<0){
			ang = ang+3.14;
			//angle = ang;
		}
		
		if(dx!=0||dy!=0) angle = ang;
		
		if(dx==0&&dy==0){
			model.setRotation(angle*180/3.14);//rad to grad
			rectangle.setRotation(angle*180/3.14);//rad to grad
			//model.setPosition(sf::Vector2f(x+cos(angle)*dist - sin(angle)*dist ,y+sin(angle)*dist+cos(angle)*dist));
		}else{
			model.setPosition(sf::Vector2f(x+cos(ang)*dist - sin(ang)*dist ,y+sin(ang)*dist+cos(ang)*dist));
		model.setRotation(ang*180/3.14);//rad to grad
		}
		std::cout<<"Bus:"<<"move: angle = "<<angle<<std::endl;//debug
		
		traversed_path = sqrt((next_cross.getPoint().x-cur_cross.getPoint().x)*(next_cross.getPoint().x-cur_cross.getPoint().x) + (next_cross.getPoint().y-cur_cross.getPoint().y)*(next_cross.getPoint().y-cur_cross.getPoint().y)) - sqrt((x-cur_cross.getPoint().x)*(x-cur_cross.getPoint().x) + (y-cur_cross.getPoint().y)*(y-cur_cross.getPoint().y));
		
		if(traversed_path<0){
			is_way_completed = 1;
			dx = 0;
			dy = 0;
			return;
		}
		std::cout<<"Bus:"<<"move: traversed_path% = "<<traversed_path/sqrt((next_cross.getPoint().x-cur_cross.getPoint().x)*(next_cross.getPoint().x-cur_cross.getPoint().x) + (next_cross.getPoint().y-cur_cross.getPoint().y)*(next_cross.getPoint().y-cur_cross.getPoint().y))<<std::endl;//debug
		
		if(is_stopped==0&&traversed_path/sqrt((next_cross.getPoint().x-cur_cross.getPoint().x)*(next_cross.getPoint().x-cur_cross.getPoint().x) + (next_cross.getPoint().y-cur_cross.getPoint().y)*(next_cross.getPoint().y-cur_cross.getPoint().y))>=0.49&&traversed_path/sqrt((next_cross.getPoint().x-cur_cross.getPoint().x)*(next_cross.getPoint().x-cur_cross.getPoint().x) + (next_cross.getPoint().y-cur_cross.getPoint().y)*(next_cross.getPoint().y-cur_cross.getPoint().y))<=0.51){
			station_time = clock.getElapsedTime();
			is_stopped = 1;
			dx = 0;
			dy = 0;
			std::cout<<"Bus:"<<"move: checking"<<std::endl;//debug
			model.setPosition(sf::Vector2f(x+cos(angle)*dist*2 - sin(angle)*dist*2 ,y+sin(angle)*dist*2+cos(angle)*dist*2));
		}else if(is_stopped&&(clock.getElapsedTime()-station_time).asSeconds()>3){
			dx = cur_dx;
			dy = cur_dy;
		}
		
		std::cout<<"Bus:"<<"move_end"<<std::endl;//debug
	}
};