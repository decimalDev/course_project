#include<vector>
#include<string>
#include<SFML/Graphics.hpp>
#include<cmath>
#include<iostream>
#include<fstream>
#include "Street.hpp"

class Machine{
	public:
	float x;
	float y;
	float width;
	float length;
	float dx;
	float dy;
	float velocity;
	int street_count;
	int is_way_completed;
	std::vector<int> way;
	Street street;
	sf::RectangleShape rectangle;
	sf::Color color;
	
	void generate_way(std::vector<Street> &all_streets){
		way.push_back(street.number);
		Street str = street;
		int num;
		
		while(!str.next_streets.empty()){
			if(str.next_streets.size()==0){
				return;
			}
			int n = rand()%(str.next_streets.size());
			num = str.next_streets[n];
			
			str = all_streets[num];
			
			if(str.next_streets.size()==0){
				way.push_back(str.number);
				return;
			}
			if(way[0]==num){
				way.push_back(num);
				break;
			}
			for(int i = 0;i<way.size();i++)
			if(all_streets[way[i]].right_dx==-str.right_dx&&all_streets[way[i]].right_dy==-str.right_dy){
				return;
			}
			way.push_back(num);
			
			}

	}
	Machine(Street street1, std::vector<Street> all_streets){
	street_count = 0;
	is_way_completed = 0;
		length = 50.f;
		width = 10.f;
		rectangle = sf::RectangleShape(sf::Vector2f(length,width));
		rectangle.setOrigin(length/2,width/2);
		rectangle.setFillColor(sf::Color::Red);
		this->street = street1;
		x = street.cross[0].point.x;
		y = street.cross[0].point.y;
		dx = street.right_dx;
		dy = street.right_dy;
		velocity = 100;
		rectangle.setPosition(sf::Vector2f(x,y));
		
		generate_way(all_streets);
		color = sf::Color(rand()%255,rand()%255,rand()%255);
		rectangle.setFillColor(color);

	}
	void move(float time){
		x+=time*dx*velocity;
		y+=time*dy*velocity;
		rectangle.setPosition(sf::Vector2f(x,y));
		rectangle.setRotation(atan(dy/dx)*180/3.14);//rad to grad
	}
	bool is_in_cross(){
	return (((x - street.cross[1].point.x)*(x - street.cross[1].point.x) + (y - street.cross[1].point.y)*(y - street.cross[1].point.y))<100);
	}
	
	void next_Street(std::vector<Street> &all_streets){
	if(all_streets[way[street_count]].is_last_street){
		is_way_completed = 1;
		dx = 0;
		dy = 0;
		return;
	}
	if(way.size()==0){
	is_way_completed = 1;
	return;
	}
	//way.erase(way.begin());
	street_count++;
	if(way.size()==street_count){
		is_way_completed = 1;
		dx = 0;
		dy = 0;
		return;
	}
	if(street_count==way.size()-1&&way[0] == way.back()) street_count = 0;
	
	if(way.size()==0){
		dx = 0;
		dy = 0;
		return;
	}
	
	
	
	street = all_streets[way[street_count]];
	dx = street.right_dx;
	dy = street.right_dy;
	}
};