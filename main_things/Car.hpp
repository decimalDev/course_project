#include "Machine.hpp"
class Car: public Machine{
	public:
	Car(){}
	virtual void move(float time,sf::Clock &clock) override{
	
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
		
		traversed_path = sqrt((next_cross.getPoint().x-cur_cross.getPoint().x)*(next_cross.getPoint().x-cur_cross.getPoint().x) + (next_cross.getPoint().y-cur_cross.getPoint().y)*(next_cross.getPoint().y-cur_cross.getPoint().y)) - sqrt((x-cur_cross.getPoint().x)*(x-cur_cross.getPoint().y) + (y-cur_cross.getPoint().y)*(y-cur_cross.getPoint().y));
		
		if(traversed_path<0){
			is_way_completed = 1;
			dx = 0;
			dy = 0;
		}
		
	}
	
	Car(Street street1, std::vector<Street> &all_streets){
	std::cout<<"Machine:"<<"Construct"<<std::endl;//debug
	is_public_transport = 0;
		srand(time(0));
		this->all_streets = &all_streets;
		
		std::cout<<"Machine:"<<"number of streets: "<<this->all_streets->size()<<std::endl;//debug
		
		street_count = 0;
		number = -1;
		is_way_completed = 0;
		length = 25.f;
		width = 10.f;
		rectangle = sf::RectangleShape(sf::Vector2f(length,width));
		rectangle.setOrigin(length/2,width/2);
		rectangle.setFillColor(sf::Color::Red);
		
		model = sf::RectangleShape(sf::Vector2f(length,width));
		model.setOrigin(length/2,width/2);
		model.setFillColor(sf::Color::Red);
		
		this->street = street1; //defining current street
		
		std::cout<<"Machine:"<<"number of street: "<<street.number<<std::endl;//debug
		
		dx = street.street_dx;
		dy = street.street_dy;
		
		max_streets = 1+rand()%10;//
		
		x = street.cross[0].getPoint().x;
		y = street.cross[0].getPoint().y;
		next_cross = street.cross[1];
		cur_cross = street.cross[0];
		
		generate_way();
		
		srand(time(0));
		
		velocity = 50+(rand()+way.size()*way[0])%150;//for more randomizing
		max_velocity = velocity;
		rectangle.setPosition(sf::Vector2f(x,y));
		model.setPosition(sf::Vector2f(x,y));
		
		color = sf::Color((rand()+way.size()*way[0])%255,(rand()+way.size()*way[0])%255,(rand()+way.size()*way[0])%255);
		rectangle.setFillColor(color);
		model.setFillColor(color);
		
		std::cout<<"Machine:"<<"Construct_end"<<std::endl;//debug
	}
	
	void next_Street(std::vector<Street> &all_streets) override{
	std::cout<<"Machine:"<<"next_Street"<<std::endl;//debug
	
	std::cout<<"Machine:"<<"next_Street condition 1"<<std::endl;//debug
	//std::cout<<"Machine:"<<"next_Street condition 1: str count: "<<street_count<<" size: "<<way.size()<<" str: "<<all_streets[way[street_count]].is_last_street<<std::endl;//debug
	if(street_count>=way.size()||all_streets[way[street_count]].is_last_street){
		is_way_completed = 1;
		dx = 0;
		dy = 0;
		std::cout<<"Machine:"<<"next_Street_end condition 1"<<std::endl;//debug
		return;
	}
	street_count++;
	
	//if(street_count==way.size()-1&&way[0] == way.back()) street_count = 0;
	
	std::cout<<"Machine:"<<"next_Street condition 3"<<std::endl;//debug
	if(street_count>=way.size()||way.size()==0){
		is_way_completed = 1;
		dx = 0;
		dy = 0;
		return;
	}
	//std::cout<<"str count: "<<street_count<<" "<<way.size()<<std::endl;//debug
	std::cout<<"Machine:"<<"next_Street condition 4"<<std::endl;//debug
	/*
	std::cout<<"Machine:"<<"next_Street condition 4: "<<next_cross.getNumber()<<" "<<street.cross[0].getNumber()<<std::endl;//debug
	if(next_cross.getNumber()==street.cross[0].getNumber()){
		
	}
	*/
	std::cout<<"Machine:"<<"next_Street expression 1"<<std::endl;//debug
	std::cout<<"Machine:"<<"next_Street expression 1: str count"<<street_count<<" size: "<<way.size()<<std::endl;//debug
	street = all_streets[way[street_count]];
	
	//std::cout<<"next street: "<<street.number<<std::endl;//debug
	
	//std::cout<<next_cross.getNumber()<<" "<<street.cross[0].getNumber()<<std::endl;//debug
	std::cout<<"Machine:"<<"next_Street condition 5"<<std::endl;//debug
	if(next_cross.getNumber()==street.cross[0].getNumber()){
		dx = street.street_dx;
		dy = street.street_dy;
		next_cross = street.cross[1];
		cur_cross = street.cross[0];
		x = cur_cross.getPoint().x;
		y = cur_cross.getPoint().y;
		
	}else{
		dx = -street.street_dx;
		dy = -street.street_dy;
		next_cross = street.cross[0];
		cur_cross = street.cross[1];
		x = cur_cross.getPoint().x;
		y = cur_cross.getPoint().y;
	}
	std::cout<<"Machine:"<<"next_Street_end"<<std::endl;//debug
	}
	
};