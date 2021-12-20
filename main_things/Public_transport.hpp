#pragma once
#include "Machine.hpp"
class Public_transport: public Machine{
	public:
	int p;
	//virtual void move(float time,sf::Clock &clock) = 0;
	Public_transport(){}
	Public_transport(Street street1, std::vector<Street> &all_streets) {
		model.setSize(sf::Vector2f(model.getLocalBounds().width*3/2,model.getLocalBounds().height));
		is_public_transport = 1;
		std::cout<<"Machine:"<<"Construct"<<std::endl;//debug
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
		
		x = street.cross[0].point.x;
		y = street.cross[0].point.y;
		next_cross = street.cross[1];
		cur_cross = street.cross[0];
		
		generate_way();
		//std::cout<<"Machine:"<<"catch me if you can"<<std::endl;//debug
		
		srand(time(0));
		
		velocity = 50+(rand()+way.size()*way[0])%150;//for more randomizing
		max_velocity = velocity;
		rectangle.setPosition(sf::Vector2f(x,y));
		model.setPosition(sf::Vector2f(x,y));
		
		//generate()
		color = sf::Color((rand()+way.size()*way[0])%255,(rand()+way.size()*way[0])%255,(rand()+way.size()*way[0])%255);
		rectangle.setFillColor(color);
		model.setFillColor(color);
		
		//debug
		//showInf();
		/*
		std::cout<<"car x "<<x<<" car y "<<y<<std::endl;
		std::cout<<"rectangle x"<<rectangle.getPosition().x<<" rectangle y "<<rectangle.getPosition().y<<std::endl;
		std::cout<<"street x"<<street.cross[0].point.x<<" street y "<<street.cross[0].point.y<<std::endl;
		std::cout<<std::endl;
		*/
		std::cout<<"Machine:"<<"Construct_end"<<std::endl;//debug
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