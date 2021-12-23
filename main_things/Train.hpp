#include "Public_transport.hpp"
class Train: public Public_transport{
	public:
	//dist
	Train(){}
	Train(Street street1, std::vector<Street> &all_streets): Public_transport(street1,all_streets){
		
	}
	void move(float time,sf::Clock &clock) override{
		
		if(dx!=0||dy!=0){
			cur_dx = dx;
			cur_dy = dy;
		}
		std::cout<<"Train:"<<"move"<<std::endl;//debug
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
		
		std::cout<<"Train:"<<"move:first angle = "<<angle<<std::endl;//debug
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
		}else{
			model.setPosition(sf::Vector2f(x,y));
			model.setRotation(ang*180/3.14);//rad to grad
		}
		std::cout<<"Train:"<<"move: angle = "<<angle<<std::endl;//debug
		
		traversed_path = sqrt((next_cross.getPoint().x-cur_cross.getPoint().x)*(next_cross.getPoint().x-cur_cross.getPoint().x) + (next_cross.getPoint().y-cur_cross.getPoint().y)*(next_cross.getPoint().y-cur_cross.getPoint().y)) - sqrt((x-cur_cross.getPoint().x)*(x-cur_cross.getPoint().x) + (y-cur_cross.getPoint().y)*(y-cur_cross.getPoint().y));
		
		if(traversed_path<0){
			is_way_completed = 1;
			dx = 0;
			dy = 0;
			return;
		}
		std::cout<<"Train:"<<"move: traversed_path% = "<<traversed_path/sqrt((next_cross.getPoint().x-cur_cross.getPoint().x)*(next_cross.getPoint().x-cur_cross.getPoint().x) + (next_cross.getPoint().y-cur_cross.getPoint().y)*(next_cross.getPoint().y-cur_cross.getPoint().y))<<std::endl;//debug
		
		if(is_stopped==0&&traversed_path/sqrt((next_cross.getPoint().x-cur_cross.getPoint().x)*(next_cross.getPoint().x-cur_cross.getPoint().x) + (next_cross.getPoint().y-cur_cross.getPoint().y)*(next_cross.getPoint().y-cur_cross.getPoint().y))>=0.49&&traversed_path/sqrt((next_cross.getPoint().x-cur_cross.getPoint().x)*(next_cross.getPoint().x-cur_cross.getPoint().x) + (next_cross.getPoint().y-cur_cross.getPoint().y)*(next_cross.getPoint().y-cur_cross.getPoint().y))<=0.51){
			station_time = clock.getElapsedTime();
			is_stopped = 1;
			dx = 0;
			dy = 0;
			std::cout<<"Train:"<<"move: checking"<<std::endl;//debug
		}else if(is_stopped&&(clock.getElapsedTime()-station_time).asSeconds()>3){
			dx = cur_dx;
			dy = cur_dy;
		}
		
		std::cout<<"Train:"<<"move_end"<<std::endl;//debug
	}
};