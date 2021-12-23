#pragma once
#include "Machine.hpp"
class Public_transport: public Machine{
	public:
	sf::Time station_time;
	int is_stopped = 0;
	float angle;
	
	CrossRoads first_next_cross;
	CrossRoads first_cur_cross;//start of current street
	
	float cur_dx;
	float cur_dy;
	int dist = 20;
	Public_transport(){}
	Public_transport(Street street1, std::vector<Street> &all_streets) {
		
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
		model.setSize(sf::Vector2f(model.getLocalBounds().width*3/2,model.getLocalBounds().height));
		model.setOrigin(model.getLocalBounds().width/2,model.getLocalBounds().height/2);
		model.setFillColor(sf::Color::Red);
		
		this->street = street1; //defining current street
		
		std::cout<<"Machine:"<<"number of street: "<<street.number<<std::endl;//debug
		
		dx = street.street_dx;
		dy = street.street_dy;
		
		cur_dx = dx;
		cur_dy = dy;
		
		max_streets = 2+rand()%10;//
		
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
		
		first_next_cross = next_cross;
		first_cur_cross = cur_cross;
		
		std::cout<<"Machine:"<<"Construct_end"<<std::endl;//debug
	}
	
	
	
	void next_Street(std::vector<Street> &all_streets) override{
	is_stopped = 0;
	if(is_way_completed){
		is_way_completed = 0;
		this->street = all_streets[way[0]]; 
		dx = street.street_dx;
		dy = street.street_dy;
		x = street.cross[0].getPoint().x;
		y = street.cross[0].getPoint().y;
		next_cross = street.cross[1];
		cur_cross = street.cross[0];
		street_count = 0;
		is_there_machine_in_forward = 0;
		is_machine_broken = 0;
		return;
	}
	
		
	std::cout<<"Machine:"<<"next_Street"<<std::endl;//debug
	
	std::cout<<"Machine:"<<"next_Street condition 1"<<std::endl;//debug

	if(street_count>=way.size()||all_streets[way[street_count]].is_last_street){
		is_way_completed = 1;
		dx = 0;
		dy = 0;
		std::cout<<"Machine:"<<"next_Street_end condition 1"<<std::endl;//debug
		return;
	}
	street_count++;

	
	std::cout<<"Machine:"<<"next_Street condition 3"<<std::endl;//debug
	if(street_count>=way.size()||way.size()==0){
		is_way_completed = 1;
		dx = 0;
		dy = 0;
		return;
	}
	//std::cout<<"str count: "<<street_count<<" "<<way.size()<<std::endl;//debug
	std::cout<<"Machine:"<<"next_Street condition 4"<<std::endl;//debug

	std::cout<<"Machine:"<<"next_Street expression 1"<<std::endl;//debug
	std::cout<<"Machine:"<<"next_Street expression 1: str count"<<street_count<<" size: "<<way.size()<<std::endl;//debug
	street = all_streets[way[street_count]];
	
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